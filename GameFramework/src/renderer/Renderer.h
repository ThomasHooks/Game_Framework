#ifndef RENDERER_H_
#define RENDERER_H_


#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
#include <functional>

#include <glm/glm.hpp>

#include "renderer/AssetLibrarian.h"
#include "renderer/texture/Texture.h"
#include "renderer/buffers/VertexBuffer.h"
#include "renderer/buffers/IndexBuffer.h"
#include "utilities/Loggers.hpp"




/*
TODO: add TTF support and text rendering
*/
class Renderer 
{
	struct QuadDrawCommand
	{
		QuadDrawCommand(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn);



		QuadDrawCommand(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn, int TextureIdIn);



		QuadDrawCommand(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn, int TextureIdIn, unsigned int subTextureIndexIn);



		bool operator>(const QuadDrawCommand& other) const
		{
			return textureID > other.textureID;
		}



		bool operator<(const QuadDrawCommand& other) const
		{
			return textureID < other.textureID;
		}



		glm::vec3 pos;

		glm::vec2 size;

		glm::vec4 color;

		int textureID;

		unsigned int subTextureIndex;

		bool hasTexture;
	};



public:

	Renderer();



	Renderer(const Renderer &other) = delete;



	Renderer(Renderer &&other) = delete;



	/// <summary>
	/// Initializes the Renderer and must be called before using any other methods
	/// </summary>
	/// <param name="windowIn"></param>
	void init(unsigned int maxQuadsPerBatch);



	/// <summary>
	/// 
	/// </summary>
	void shutdown();



	/// <summary>
	/// 
	/// </summary>
	/// <param name="cameraIn"></param>
	void begin(const std::shared_ptr<class Camera>& cameraIn);



	/// <summary>
	/// 
	/// </summary>
	void end();



	/// <summary>
	/// Forces the renderer to draw the current batch
	/// </summary>
	void flush();



	/// <summary>
	/// Clears the screen and fills it in with the given color
	/// </summary>
	/// <param name="red">Specifies the amount of red</param>
	/// <param name="green">Specifies the amount of green</param>
	/// <param name="blue">Specifies the amount of blue</param>
	/// <param name="alpha">Specifies the amount of alpha</param>
	void clear(float red, float green, float blue, float alpha);



	/// <summary>
	/// Clears the screen and fills it with black
	/// </summary>
	void clear();



	/// <summary>
	/// 
	/// </summary>
	/// <param name="posIn"></param>
	/// <param name="sizeIn"></param>
	/// <param name="colorIn"></param>
	void drawQuad(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="posIn"></param>
	/// <param name="sizeIn"></param>
	/// <param name="colorIn"></param>
	/// <param name="textureNameIn"></param>
	void drawQuad(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn, const std::string& textureNameIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="posIn"></param>
	/// <param name="sizeIn"></param>
	/// <param name="colorIn"></param>
	/// <param name="textureNameIn"></param>
	/// <param name="spriteIndexIn"></param>
	void drawQuad(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn, const std::string& textureNameIn, unsigned int spriteIndexIn);



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	AssetLibrarian& assetLibrarian();



private:

	/// <summary>
	/// Adds a new quad to the current renderer batch
	/// <para>increments the number of quads in the current batch</para>
	/// </summary>
	/// <param name="posIn"></param>
	/// <param name="sizeIn"></param>
	/// <param name="colorIn"></param>
	/// <param name="subTextureIn"></param>
	void bakeQuad(const glm::vec3& posIn, const glm::vec2& sizeIn, const glm::vec4& colorIn, const SubTexture& subTextureIn, float textureSlotIn);



	std::shared_ptr<spdlog::logger> m_logger;

	bool m_hasBeenInit = false;



	VertexBuffer m_vbo;

	IndexBuffer m_ibo;

	static constexpr int NUMBER_OF_VERTICES_PER_QUAD = 4;

	static constexpr int NUMBER_OF_INDICES_PER_QUAD = 6;

	int m_maxQuadsPerBatch = 1000;

	int m_quadsInCurrentBatch = 0;

	unsigned int m_nextVertexOffset = 0;

	int m_nextIndexOffset = 0;



	std::unordered_map<std::string, int> m_activeTexturesLookup;

	std::vector<std::weak_ptr<Texture>> m_activeTextures;

	static constexpr int DEFAULT_NUMBER_OF_TEXTURE_SLOTS = 16;

	int m_nextTextureSlot = 0;

	int m_maxTexturesSlotsPerBatch = 16;

	int m_textureSlotsInCurrentBatch = 0;

	int m_textureSlotOffset = 0;



	std::priority_queue<QuadDrawCommand, std::vector<QuadDrawCommand>, std::greater<QuadDrawCommand>> m_quadDrawQueue;



	AssetLibrarian m_librarian;



	std::string m_defaultShaderName;

	std::shared_ptr<class Camera> m_camera;
};


#endif /* RENDERER_H_ */



