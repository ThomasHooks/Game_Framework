#include "AssetLibrarian.h"
#include "renderer/shaders/Shader.h"
#include "renderer/texture/Texture.h"
#include "renderer/texture/TextureAtlas.h"
#include "utilities/Assertions.h"




AssetLibrarian::AssetLibrarian() 
{
	m_logger = Loggers::getLog();
}



void AssetLibrarian::addShader(const std::string& nameIn, const std::filesystem::path& vertexFilepath, const std::filesystem::path& pixelFilepath)
{
	GAME_ASSERT(m_shaders.find(nameIn) == m_shaders.end());

	m_logger->trace("Loading shader: '{0}' vertex shader at '{1}' and pixel shader at '{2}'", nameIn, vertexFilepath.string(), pixelFilepath.string());
	m_shaders[nameIn] = std::make_shared<Shader>();
	m_shaders[nameIn]->create(vertexFilepath, pixelFilepath);
	m_logger->trace("Shader '{0}' has been Loaded", nameIn);
}



void AssetLibrarian::addShaderFromString(const std::string& nameIn, const std::string& vertexSrc, const std::string& pixelSrc)
{
	GAME_ASSERT(m_shaders.find(nameIn) == m_shaders.end());

	m_logger->trace("Loading shader: '{0}' from strings", nameIn);
	m_shaders[nameIn] = std::make_shared<Shader>();
	m_shaders[nameIn]->createFromString(vertexSrc, pixelSrc);
	m_logger->trace("Shader '{0}' has been Loaded", nameIn);
}



bool AssetLibrarian::hasShader(const std::string& nameIn) const
{
	return m_shaders.find(nameIn) != m_shaders.end();
}



std::weak_ptr<Shader> AssetLibrarian::getShader(const std::string& nameIn)
{
	GAME_ASSERT(m_shaders.find(nameIn) != m_shaders.end());

	return m_shaders[nameIn];
}



void AssetLibrarian::addTexture(const std::filesystem::path& filepathIn)
{
	std::string name = filepathIn.stem().string();
	m_logger->trace("Loading texture: '{0}' at '{1}'", name, filepathIn.string());
	if (m_textures.find(name) != m_textures.end())
	{
		m_logger->warn("Unable to load texture: '{0}', file name is not unique", name);
		return;
	}

	m_textures[name] = std::make_shared<Texture>(filepathIn, m_nextTextureID++);
	m_logger->trace("Texture '{0}' has been loaded", name);
}



void AssetLibrarian::addTexture(const std::filesystem::path& filepathIn, const glm::uvec2& spriteSizeIn)
{
	addTexture(filepathIn, spriteSizeIn, { 0, 0 });
}



void AssetLibrarian::addTexture(const std::filesystem::path& filepathIn, const glm::uvec2& spriteSizeIn, const glm::uvec2& spritePaddingIn)
{
	std::string name = filepathIn.stem().string();
	m_logger->trace("Loading texture: '{0}' at '{1}'", name, filepathIn.string());
	if (m_textures.find(name) != m_textures.end())
	{
		m_logger->warn("Unable to load texture atlas: '{0}', file name is not unique", name);
		return;
	}

	m_textures[name] = std::make_shared<TextureAtlas>(filepathIn, spriteSizeIn, spritePaddingIn, m_nextTextureID++);
	m_logger->trace("Texture atlas '{0}' has been loaded", name);
}



bool AssetLibrarian::hasTexture(const std::string& nameIn)
{
	return m_textures.find(nameIn) != m_textures.end();
}



std::weak_ptr<Texture> AssetLibrarian::getTexture(const std::string& nameIn)
{
	GAME_ASSERT(m_textures.find(nameIn) != m_textures.end());

	return m_textures[nameIn];
}



