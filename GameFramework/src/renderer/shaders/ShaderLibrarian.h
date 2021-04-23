#ifndef ShaderLibrarian_H_
#define ShaderLibrarian_H_

#include <string>
#include <filesystem>
#include <unordered_map>
#include <memory>




class ShaderLibrarian 
{
public:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <param name="vertexFilepath"></param>
	/// <param name="pixelFilepath"></param>
	void add(const std::string& nameIn, const std::filesystem::path& vertexFilepath, const std::filesystem::path& pixelFilepath);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <param name="vertexSrc"></param>
	/// <param name="pixelSrc"></param>
	void addFromString(const std::string& nameIn, const std::string& vertexSrc, const std::string& pixelSrc);



	/// <summary>
	/// 
	/// </summary>
	/// <param nameIn="tag"></param>
	void remove(const std::string& nameIn);



	/// <summary>
	/// 
	/// </summary>
	void removeAll();



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <returns></returns>
	bool has(const std::string& nameIn) const;



	/// <summary>
	/// 
	/// </summary>
	/// <param nameIn="tag"></param>
	/// <returns></returns>
	std::weak_ptr<class Shader> get(const std::string& nameIn);



private:

	std::unordered_map<std::string, std::shared_ptr<class Shader>> m_shaders;
}; 


#endif /* ShaderLibrarian_H_ */



