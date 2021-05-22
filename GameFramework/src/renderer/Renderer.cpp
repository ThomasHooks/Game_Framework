#include <spdlog/spdlog.h>

#include "renderer/Renderer.h"
#include "renderer/RendererFondation.h"
#include "renderer/shaders/Shader.h"
#include "renderer/screen/Camera.h"
#include "utilities/Assertions.h"




Renderer::Renderer()
	: m_defaultShaderName("FlatSprite")
{
	m_logger = Loggers::getLog();
}



void Renderer::init(unsigned int maxQuadsPerBatch)
{
	if (m_hasBeenInit)
		return;

	m_logger->info("Initializing renderer");
	m_hasBeenInit = true;
	m_maxQuadsPerBatch = maxQuadsPerBatch;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_librarian.addShader(m_defaultShaderName, "data/shaders/flatSprite.vsh", "data/shaders/flatSprite.psh");

	VertexBuffer::Layout layout;
	layout.add(VertexBuffer::Attribute::Float3, "a_pos")
		  .add(VertexBuffer::Attribute::Float4, "a_color")
		  .add(VertexBuffer::Attribute::Float2, "a_texCord")
		  .add(VertexBuffer::Attribute::Float1, "a_texSlot");

	unsigned int vertexBufferSize = m_maxQuadsPerBatch * NUMBER_OF_VERTICES_PER_QUAD * layout.count() * static_cast<unsigned int>(sizeof(float));
	m_vbo.create(nullptr, vertexBufferSize, VertexBuffer::Usage::Dynamic);
	m_vbo.setLayout(layout);

	unsigned int indexBufferCount = m_maxQuadsPerBatch * NUMBER_OF_INDICES_PER_QUAD;
	m_ibo.create(nullptr, indexBufferCount, IndexBuffer::Usage::Dynamic);

	m_maxTexturesSlotsPerBatch = DEFAULT_NUMBER_OF_TEXTURE_SLOTS;
	m_activeTextures.reserve(m_maxTexturesSlotsPerBatch);

	m_logger->info("Renderer has been initialized");
}



void Renderer::shutdown()
{
	m_logger->info("Shutting down Renderer");

	m_ibo.destroy();
	m_vbo.destroy();

	m_logger->info("Rendering stopped");
}



void Renderer::begin(const std::shared_ptr<Camera>& cameraIn)
{
	m_camera = cameraIn;
}



void Renderer::clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void Renderer::clear()
{
	clear(0.1f, 0.1f, 0.1f, 1.0f);
}



void Renderer::drawQuad(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn)
{
	m_quadDrawQueue.emplace(posIn, sizeIn, colorIn);
}



void Renderer::drawQuad(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn, const std::string& textureNameIn)
{
	drawQuad(posIn, sizeIn, colorIn, textureNameIn, 0);
}



void Renderer::drawQuad(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn, const std::string& textureNameIn, unsigned int spriteIndexIn)
{
	auto texture = m_librarian.getTexture(textureNameIn).lock();

	if (m_activeTexturesLookup.find(textureNameIn) == m_activeTexturesLookup.end())
	{
		m_activeTexturesLookup[textureNameIn] = m_nextTextureSlot++;
		m_activeTextures.push_back(m_librarian.getTexture(textureNameIn));
	}

	m_quadDrawQueue.emplace(posIn, sizeIn, colorIn, m_activeTexturesLookup[textureNameIn], spriteIndexIn);
}



void Renderer::end()
{
	m_vbo.bind();
	m_ibo.bind();

	int lastTextureSlot = -1;
	while (!m_quadDrawQueue.empty())
	{
		QuadDrawCommand command = m_quadDrawQueue.top();

		if (command.hasTexture)
		{
			if (lastTextureSlot != command.textureID)
			{
				lastTextureSlot = command.textureID;
				m_textureSlotsInCurrentBatch++;

				// It is -1 because texture slot 0 is reserved for non-texture solid color quads
				if (m_textureSlotsInCurrentBatch >= (m_maxTexturesSlotsPerBatch - 1))
				{
					flush();
					m_textureSlotsInCurrentBatch = 1;
					m_textureSlotOffset = lastTextureSlot;
				}
			}

			auto texture = m_activeTextures[command.textureID].lock();
			SubTexture subTexture = texture->getSubTexture(command.subTextureIndex);
			bakeQuad(command.pos, command.size, command.color, subTexture, command.textureID - m_textureSlotOffset + 1.0f);
		}
		else
		{
			SubTexture subTexture = { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
			bakeQuad(command.pos, command.size, command.color, subTexture, 0.0f);
		}

		m_quadDrawQueue.pop();

		if (m_quadsInCurrentBatch >= m_maxQuadsPerBatch)
			flush();
	}

	flush();

	m_ibo.unbind();
	m_vbo.unbind();

	m_camera.reset();

	m_nextTextureSlot = 0;
	m_textureSlotsInCurrentBatch = 0;
	m_textureSlotOffset = 0;
	m_activeTextures.clear();
	m_activeTexturesLookup.clear();
}



void Renderer::bakeQuad(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn, const SubTexture& subTextureIn, float textureSlotIn)
{
	if (m_quadsInCurrentBatch > m_maxQuadsPerBatch)
	{
		m_logger->error("Tried to bake more quads than the maximum batch size");
		return;
	}

	glm::vec2 max(posIn.x + static_cast<float>(sizeIn.x), posIn.y + static_cast<float>(sizeIn.y));
	glm::vec2 min(posIn.x, posIn.y);

	float vertices[] = {
		min.x, min.y, posIn.z, colorIn.r, colorIn.g, colorIn.b, colorIn.a, subTextureIn.min.x, subTextureIn.max.y, textureSlotIn,
		max.x, min.y, posIn.z, colorIn.r, colorIn.g, colorIn.b, colorIn.a, subTextureIn.max.x, subTextureIn.max.y, textureSlotIn,
		max.x, max.y, posIn.z, colorIn.r, colorIn.g, colorIn.b, colorIn.a, subTextureIn.max.x, subTextureIn.min.y, textureSlotIn,
		min.x, max.y, posIn.z, colorIn.r, colorIn.g, colorIn.b, colorIn.a, subTextureIn.min.x, subTextureIn.min.y, textureSlotIn
	};
	m_vbo.submitData(vertices, sizeof(vertices), m_quadsInCurrentBatch * sizeof(vertices));

	unsigned int indices[] = {
		0 + m_nextVertexOffset, 
		1 + m_nextVertexOffset, 
		2 + m_nextVertexOffset, 
		2 + m_nextVertexOffset, 
		3 + m_nextVertexOffset, 
		0 + m_nextVertexOffset
	};
	m_ibo.submitData(indices, NUMBER_OF_INDICES_PER_QUAD, m_nextIndexOffset * sizeof(unsigned int));

	m_nextVertexOffset += NUMBER_OF_VERTICES_PER_QUAD;
	m_nextIndexOffset += NUMBER_OF_INDICES_PER_QUAD;
	m_quadsInCurrentBatch++;
}



void Renderer::flush()
{
	if (m_quadsInCurrentBatch == 0)
		return;

	auto shaderPtr = m_librarian.getShader(m_defaultShaderName);
	auto shader = shaderPtr.lock();
	shader->bind();

	shader->setUniformMat4("u_camera", m_camera->getViewProjection());

	GAME_ASSERT(m_textureSlotsInCurrentBatch < DEFAULT_NUMBER_OF_TEXTURE_SLOTS);
	int slot[DEFAULT_NUMBER_OF_TEXTURE_SLOTS] = { 0 };
	for (int i = 0; i < m_textureSlotsInCurrentBatch; i++)
	{
		// Since i represents the index of active textures one is added to it for the slot index
		// This is because slot 0 is reserved for non-texture solid color quads
		size_t texture = static_cast<size_t>(i) + m_textureSlotOffset;
		m_activeTextures[texture].lock()->bind(i + 1);
		slot[i + 1] = i + 1;
	}
	shader->setUniformSampler2D("u_texSlots[0]", slot, DEFAULT_NUMBER_OF_TEXTURE_SLOTS);

	if (shader->validate())
		glDrawElements(GL_TRIANGLES, m_ibo.count(), GL_UNSIGNED_INT, nullptr);
	else
		m_logger->critical("Shader '{0}' failed validation", m_defaultShaderName);

	for (int i = 0; i < m_textureSlotsInCurrentBatch; i++)
		m_activeTextures[i].lock()->unbind();

	shader->unbind();

	m_nextVertexOffset = 0;
	m_nextIndexOffset = 0;
	m_quadsInCurrentBatch = 0;
}



AssetLibrarian& Renderer::assetLibrarian()
{
	return m_librarian;
}



Renderer::QuadDrawCommand::QuadDrawCommand(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn)
	: pos(posIn), size(sizeIn), color(colorIn), textureID(-1), subTextureIndex(0), hasTexture(false)
{
}



Renderer::QuadDrawCommand::QuadDrawCommand(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn, int TextureIdIn)
	: pos(posIn), size(sizeIn), color(colorIn), textureID(TextureIdIn), subTextureIndex(0), hasTexture(true)
{
}



Renderer::QuadDrawCommand::QuadDrawCommand(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn, int TextureIdIn, unsigned int subTextureIndexIn)
	: pos(posIn), size(sizeIn), color(colorIn), textureID(TextureIdIn), subTextureIndex(subTextureIndexIn), hasTexture(true)
{
}



