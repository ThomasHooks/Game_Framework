#ifndef Shader_H_
#define Shader_H_

#include <string>
#include <filesystem>
#include <unordered_map>

#include "renderer/shaders/ShaderUniform.h"
#include "utilities/Loggers.hpp"




class Shader 
{
public:

	enum class Type 
	{ 
		VERTEX, 
		GEOMETRY, 
		PIXEL 
	};



	Shader();



	Shader(const Shader& other) = delete;



	Shader(Shader&& other) noexcept;



	~Shader();



	/// <summary>
	/// 
	/// </summary>
	/// <param name="vertexFilepath"></param>
	/// <param name="pixelFilepath"></param>
	void create(const std::filesystem::path& vertexFilepath, const std::filesystem::path& pixelFilepath);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="vertexSrc"></param>
	/// <param name="pixelSrc"></param>
	void createFromString(const std::string& vertexSrc, const std::string& pixelSrc);




	/// <summary>
	/// Gets the given shader uniform
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform</param>
	/// <returns>The given shader uniform or null if it's not present</returns>
	ShaderUniform* getUniform(const std::string& nameIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <param name="typeIn"></param>
	/// <param name="dataIn"></param>
	/// <returns></returns>
	Shader& setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, bool dataIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <param name="typeIn"></param>
	/// <param name="dataIn"></param>
	/// <returns></returns>
	Shader& setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, int dataIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <param name="typeIn"></param>
	/// <param name="dataIn"></param>
	/// <returns></returns>
	Shader& setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, float dataIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <param name="typeIn"></param>
	/// <param name="dataIn"></param>
	/// <returns></returns>
	Shader& setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, const glm::vec2& dataIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <param name="typeIn"></param>
	/// <param name="dataIn"></param>
	/// <returns></returns>
	Shader& setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, const glm::vec3& dataIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <param name="typeIn"></param>
	/// <param name="dataIn"></param>
	/// <returns></returns>
	Shader& setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, const glm::vec4& dataIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <param name="typeIn"></param>
	/// <param name="dataIn"></param>
	/// <returns></returns>
	Shader& setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, const glm::mat3& dataIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="nameIn"></param>
	/// <param name="typeIn"></param>
	/// <param name="dataIn"></param>
	/// <returns></returns>
	Shader& setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, const glm::mat4& dataIn);



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int numberOfUniforms() const { return m_activeUniforms; }



	/// <summary>
	/// Checks if this shader is valid
	/// </summary>
	/// <returns>True if this shader is valid</returns>
	bool validate() const;
	
	
	
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	unsigned int getID() const { return m_id; }



	/// <summary>
	/// 
	/// </summary>
	void bind() const;



	/// <summary>
	/// 
	/// </summary>
	void unbind() const;



private:

	/// <summary>
	/// Loads the given shader file into a string
	/// </summary>
	/// <param name="filepath">Location of the shader file</param>
	/// <returns>A string containg the shader's source or an empty string on failure</returns>
	static std::string load(const std::string& filepath);



	/// <summary>
	/// Compiles the given shader source
	/// </summary>
	/// <param name="type">Specifies the type of shader to be compiled</param>
	/// <param name="src">A string containg the shader's source</param>
	/// <returns>The compiled shader's ID, or 0 on error</returns>
	static unsigned int compile(Type type, const std::string& src);



	/// <summary>
	/// Creates a new shader program and links the given vertex and pixel shaders to it
	/// </summary>
	/// <param name="vertexShaderID">The ID of the vertex shader to be linked</param>
	/// <param name="pixelShaderID">The ID of the vertex pixel to be linked</param>
	/// <returns>The ID of the new shader program or 0 on error</returns>
	static unsigned int link(unsigned int vertexShaderID, unsigned int pixelShaderID);



	/// <summary>
	/// 
	/// </summary>
	void buildUniforms();



	/// <summary>
	/// Gets the GL shader type ID
	/// </summary>
	/// <param name="type">Specifies the type of shader</param>
	/// <returns></returns>
	static unsigned int get_glShaderType(Type type);



	std::shared_ptr<spdlog::logger> m_logger;

	bool m_moved = false;

	unsigned int m_id = 0;

	int m_activeUniforms = 0;

	std::unordered_map<std::string, std::unique_ptr<ShaderUniform>> m_uniforms;
}; 


#endif /* Shader_H_ */



