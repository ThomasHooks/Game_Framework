#ifndef Shader_H_
#define Shader_H_

#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <functional>

#include <glm/glm.hpp>

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


	
	class Uniform
	{
	public:

		enum class Type
		{
			Invalid,
			Bool1,
			Int1,
			Int2,
			Int3,
			Int4,
			Int1Array,
			Float1,
			Float2,
			Float3,
			Float4,
			Mat3,
			Mat4,
			Sampler2D,
			Sampler2D1Array
		};



		/// <summary>
		/// 
		/// </summary>
		/// <param name="typeIn"></param>
		/// <returns></returns>
		static std::string uniformTypeToString(Type typeIn);



		Uniform(const std::string& nameIn, Type typeIn, int sizeIn, int locationIn, unsigned int programIn);



		/// <summary>
		/// Gets this uniform's variable name
		/// </summary>
		/// <returns></returns>
		const std::string& getName() const { return m_name; }



		/// <summary>
		/// Gets this uniform's variable type
		/// </summary>
		/// <returns></returns>
		Type getType() const { return m_type; }



		/// <summary>
		/// Gets the number of variables in this uniform
		/// <para>Normaly returns 1 unless this uniform is an array, in which case it will return the length or the array</para>
		/// </summary>
		/// <returns></returns>
		int getCount() const { return m_size; }



		/// <summary>
		/// Gets this uniform's location in the shader
		/// </summary>
		/// <returns></returns>
		int getLocation() const { return m_location; }



	private:

		std::string m_name;

		Type m_type;

		int m_size, m_location;

		unsigned int m_program;
	};
	


	Shader();



	Shader(const Shader& other) = delete;



	Shader(Shader&& other) noexcept;



	~Shader();



	/// <summary>
	/// Creates this shader from the specified sorce files
	/// </summary>
	/// <param name="vertexFilepath">Specifies the file path of the vertex shader file</param>
	/// <param name="pixelFilepath">Specifies the file path of the pixel shader file</param>
	void create(const std::filesystem::path& vertexFilepath, const std::filesystem::path& pixelFilepath);



	/// <summary>
	/// Creates this shader from the specified sorce strings
	/// </summary>
	/// <param name="vertexSrc">Specifies the vertex shader sorce string</param>
	/// <param name="pixelSrc">Specifies the pixel shader sorce string</param>
	void createFromString(const std::string& vertexSrc, const std::string& pixelSrc);



	/// <summary>
	/// Checks if the specified uniform is part of this shader
	/// </summary>
	/// <param name="nameIn">Specifies the shader unifrom's variable name</param>
	/// <returns>True if present</returns>
	bool hasUniform(const std::string& nameIn) const;



	/// <summary>
	/// <para>nullable</para>
	/// Gets the specified shader uniform
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform</param>
	/// <returns>The shader uniform or null if it's not present</returns>
	Uniform* getUniform(const std::string& nameIn);



	/// <summary>
	/// Gets all of this shader's uniforms
	/// </summary>
	/// <returns></returns>
	std::vector<Uniform>& getUniforms();



	/// <summary>
	/// Gets all of this shader's uniforms
	/// </summary>
	/// <returns></returns>
	const std::vector<Uniform>& getUniforms() const;



	/// <summary>
	/// Sends boolean data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the boolean data that is to be sent</param>
	/// <returns>A referance to this shader</returns>
	Shader& setUniformBool1(const std::string& nameIn, bool dataIn);



	/// <summary>
	/// Sends integer data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the integer data that is to be sent</param>
	/// <returns>A referance to this shader</returns>
	Shader& setUniformInt1(const std::string& nameIn, int dataIn);



	/// <summary>
	/// Sends an array of integer data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the integer data that is to be sent</param>
	/// <param name="countIn">Specifies the number of integer elements in the array</param>
	/// <returns></returns>
	Shader& setUniformInt1(const std::string& nameIn, int* dataIn, unsigned int countIn);



	/// <summary>
	/// Sends vector integer data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the vector integer data that is to be sent</param>
	/// <returns></returns>
	Shader& setUniformInt2(const std::string& nameIn, const glm::ivec2& dataIn);



	/// <summary>
	/// Sends vector integer data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the vector integer data that is to be sent</param>
	/// <returns></returns>
	Shader& setUniformInt3(const std::string& nameIn, const glm::ivec3& dataIn);



	/// <summary>
	/// Sends vector integer data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the vector integer data that is to be sent</param>
	/// <returns></returns>
	Shader& setUniformInt4(const std::string& nameIn, const glm::ivec4& dataIn);



	/// <summary>
	/// Sends 2D texture slot data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the 2D texture slot data that is to be sent</param>
	/// <returns>A referance to this shader</returns>
	Shader& setUniformSampler2D(const std::string& nameIn, int dataIn);



	/// <summary>
	/// Sends an array of Sampler2D data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the Sampler2D data that is to be sent</param>
	/// <param name="countIn">Specifies the number of Sampler2D elements in the array</param>
	/// <returns></returns>
	Shader& setUniformSampler2D(const std::string& nameIn, int* dataIn, unsigned int countIn);



	/// <summary>
	/// Sends floating point data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the floating point data that is to be sent</param>
	/// <returns>A referance to this shader</returns>
	Shader& setUniformFloat1(const std::string& nameIn, float dataIn);



	/// <summary>
	/// Sends vector floating point data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the vector floating point data that is to be sent</param>
	/// <returns>A referance to this shader</returns>
	Shader& setUniformFloat2(const std::string& nameIn, const glm::vec2& dataIn);



	/// <summary>
	/// Sends vector floating point data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the vector floating point data that is to be sent</param>
	/// <returns>A referance to this shader</returns>
	Shader& setUniformFloat3(const std::string& nameIn, const glm::vec3& dataIn);



	/// <summary>
	/// Sends vector floating point data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the vector floating point data that is to be sent</param>
	/// <returns>A referance to this shader</returns>
	Shader& setUniformFloat4(const std::string& nameIn, const glm::vec4& dataIn);



	/// <summary>
	/// Sends matrix floating point data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the matrix floating point data that is to be sent</param>
	/// <returns>A referance to this shader</returns>
	Shader& setUniformMat3(const std::string& nameIn, const glm::mat3& dataIn);



	/// <summary>
	/// Sends matrix floating point data to the specified shader uniform variable if it's present
	/// </summary>
	/// <param name="nameIn">Specifies the shader uniform variable name</param>
	/// <param name="dataIn">Specifies the matrix floating point data that is to be sent</param>
	/// <returns>A referance to this shader</returns>
	Shader& setUniformMat4(const std::string& nameIn, const glm::mat4& dataIn);



	/// <summary>
	/// Gets the number of shader unifroms that are being used by this shader
	/// </summary>
	/// <returns></returns>
	int numberOfUniforms() const { return m_activeUniforms; }



	/// <summary>
	/// Checks if this shader is valid
	/// </summary>
	/// <returns>True if this shader is valid</returns>
	bool validate() const;
	
	
	
	/// <summary>
	/// Gets this shander's OpenGL identifier
	/// </summary>
	/// <returns></returns>
	unsigned int getID() const { return m_id; }



	/// <summary>
	/// Makes this the active shader
	/// </summary>
	void bind() const;



	/// <summary>
	/// Makes the currently active shader inactive
	/// </summary>
	void unbind() const;



private:

	/// <summary>
	/// Loads the given shader file into a string
	/// </summary>
	/// <param name="filepath">Location of the shader file</param>
	/// <returns>Specifies the string containg the shader's source or an empty string on failure</returns>
	static std::string load(const std::string& filepath);



	/// <summary>
	/// Compiles the given shader source
	/// </summary>
	/// <param name="type">Specifies the type of shader to be compiled</param>
	/// <param name="src">Specifies the string containg the shader's source</param>
	/// <returns>The compiled shader's ID, or 0 on error</returns>
	static unsigned int compile(Type type, const std::string& src);



	/// <summary>
	/// Creates a new shader program and links the given vertex and pixel shaders to it
	/// </summary>
	/// <param name="vertexShaderID">Specifies the ID of the vertex shader to be linked</param>
	/// <param name="pixelShaderID">Specifies the ID of the vertex pixel to be linked</param>
	/// <returns>The ID of the new shader program or 0 on error</returns>
	static unsigned int link(unsigned int vertexShaderID, unsigned int pixelShaderID);



	/// <summary>
	/// Gets the shader uniform type from the OpenGL shader uniform type
	/// </summary>
	/// <param name="typeIn">Specifies the OpenGL shader uniform type</param>
	/// <param name="sizeIn">Specifies the size of the uniform variable</param>
	/// <returns></returns>
	static Uniform::Type getUniformTypeFromGL(unsigned int typeIn, int sizeIn);



	/// <summary>
	/// Gathers all active shader unifroms in this shader
	/// </summary>
	void buildUniforms();



	/// <summary>
	/// Gets the GL shader type ID
	/// </summary>
	/// <param name="type">Specifies the type of shader</param>
	/// <returns></returns>
	static unsigned int get_glShaderType(Type type);



	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="nameIn"></param>
	/// <param name="typeIn"></param>
	/// <param name="dataIn"></param>
	/// <param name="countIn"></param>
	/// <param name="function"></param>
	template<typename T>
	void setUniform(const std::string& nameIn, Uniform::Type typeIn, T dataIn, unsigned int countIn, std::function<void(T dataIn, unsigned int countIn, const Uniform& uniform)> function)
	{
		if (m_uniformsLookup.find(nameIn) == m_uniformsLookup.end())
		{
			m_logger->warn("Uniform '{0}' is either unused, invalid, or misspelled", nameIn);
			return;
		}

		unsigned int i = m_uniformsLookup[nameIn];
		if (m_uniforms[i].getType() == typeIn)
		{
			function(dataIn, countIn, m_uniforms[i]);
		}
		else
			m_logger->warn("Tried to submit data of type '{0}' to uniform '{1}', which is of type '{2}'", Uniform::uniformTypeToString(typeIn), nameIn, Uniform::uniformTypeToString(m_uniforms[i].getType()));
	}



	std::shared_ptr<spdlog::logger> m_logger;

	std::vector<Uniform> m_uniforms;

	std::unordered_map<std::string, unsigned int> m_uniformsLookup;

	bool m_moved = false;

	unsigned int m_id = 0;

	int m_activeUniforms = 0;
}; 


#endif /* Shader_H_ */



