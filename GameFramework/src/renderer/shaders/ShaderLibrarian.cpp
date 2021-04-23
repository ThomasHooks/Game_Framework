#include "ShaderLibrarian.h"
#include "renderer/shaders/Shader.h"
#include "utilities/Assertions.h"




void ShaderLibrarian::add(const std::string& nameIn, const std::filesystem::path& vertexFilepath, const std::filesystem::path& pixelFilepath)
{
	GAME_ASSERT(m_shaders.find(nameIn) == m_shaders.end());
	m_shaders[nameIn] = std::make_shared<Shader>();
	m_shaders[nameIn]->create(vertexFilepath, pixelFilepath);
}



void ShaderLibrarian::addFromString(const std::string& nameIn, const std::string& vertexSrc, const std::string& pixelSrc)
{
	GAME_ASSERT(m_shaders.find(nameIn) == m_shaders.end());
	m_shaders[nameIn] = std::make_shared<Shader>();
	m_shaders[nameIn]->createFromString(vertexSrc, pixelSrc);
}



void ShaderLibrarian::remove(const std::string& nameIn)
{
	m_shaders.erase(nameIn);
}



void ShaderLibrarian::removeAll()
{
	m_shaders.clear();
}



bool ShaderLibrarian::has(const std::string& nameIn) const
{
	return m_shaders.find(nameIn) != m_shaders.end();
}



std::weak_ptr<Shader> ShaderLibrarian::get(const std::string& nameIn)
{
	GAME_ASSERT(m_shaders.find(nameIn) != m_shaders.end());
	return m_shaders[nameIn];
}



