#ifndef AssetLibrarian_H_
#define AssetLibrarian_H_

#include <string>
#include <filesystem>
#include <unordered_map>
#include <memory>

#include <glm/glm.hpp>

#include "utilities/Loggers.hpp"




class AssetLibrarian 
{
public:

	AssetLibrarian();



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <param name="vertexFilepath"></param>
	/// <param name="pixelFilepath"></param>
	void addShader(const std::string& nameIn, const std::filesystem::path& vertexFilepath, const std::filesystem::path& pixelFilepath);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <param name="vertexSrc"></param>
	/// <param name="pixelSrc"></param>
	void addShaderFromString(const std::string& nameIn, const std::string& vertexSrc, const std::string& pixelSrc);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <returns></returns>
	bool hasShader(const std::string& nameIn) const;



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <returns></returns>
	std::weak_ptr<class Shader> getShader(const std::string& nameIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="filepathIn"></param>
	void addTexture(const std::filesystem::path& filepathIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="filepathIn"></param>
	/// <param name="spriteSizeIn"></param>
	void addTexture(const std::filesystem::path& filepathIn, const glm::uvec2& spriteSizeIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="filepathIn"></param>
	/// <param name="spriteSizeIn"></param>
	/// <param name="spritePaddingIn"></param>
	void addTexture(const std::filesystem::path& filepathIn, const glm::uvec2& spriteSizeIn, const glm::uvec2& spritePaddingIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <returns></returns>
	bool hasTexture(const std::string& nameIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <returns></returns>
	std::weak_ptr<class Texture> getTexture(const std::string& nameIn);



private:

	std::shared_ptr<spdlog::logger> m_logger;

	std::unordered_map<std::string, std::shared_ptr<class Shader>> m_shaders;

	std::unordered_map<std::string, std::shared_ptr<class Texture>> m_textures;

	unsigned int m_nextTextureID = 1;
}; 


#endif /* AssetLibrarian_H_ */



