#include <iostream>
#include <fstream>
#include <filesystem>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "renderer/shaders/Shader.h"




Shader::Shader()
{
	m_logger = Loggers::getLog();
}



Shader::Shader(Shader&& other) noexcept
	: m_id(other.m_id), m_activeUniforms(other.m_activeUniforms)
{
	buildUniforms();
	other.m_id = 0;
	other.m_uniforms.clear();
	other.m_activeUniforms = 0;
	other.m_moved = true;
}



Shader::~Shader()
{
	if (!m_moved)
	{
		m_uniforms.clear();
		glDeleteProgram(m_id);
		m_id = 0;
	}
}



void Shader::create(const std::filesystem::path& vertexFilepath, const std::filesystem::path& pixelFilepath)
{
	if (!m_id)
	{
		if (vertexFilepath.extension().string() != ".vsh")
		{
			m_logger->error("Invalid vertex shader '{0}'", vertexFilepath.string());
			__debugbreak();
		}
		else if (pixelFilepath.extension().string() != ".psh")
		{
			m_logger->error("Invalid pixel shader '{0}'", pixelFilepath.string());
			__debugbreak();
		}
		else
		{
			unsigned int vertexShaderID = Shader::compile(Type::VERTEX, Shader::load(vertexFilepath.string()));
			unsigned int pixelShaderID = Shader::compile(Type::PIXEL, Shader::load(pixelFilepath.string()));
			m_id = Shader::link(vertexShaderID, pixelShaderID);
			buildUniforms();
		}
	}
	else
		m_logger->warn("Shader has already been created");
}



void Shader::createFromString(const std::string& vertexSrc, const std::string& pixelSrc)
{
	if (!m_id)
	{
		unsigned int vertexShaderID = Shader::compile(Type::VERTEX, vertexSrc);
		unsigned int pixelShaderID = Shader::compile(Type::PIXEL, pixelSrc);
		m_id = Shader::link(vertexShaderID, pixelShaderID);
		buildUniforms();
	}
	else
		m_logger->warn("Shader has already been created");
}



std::string Shader::load(const std::string& filepath) {

	std::string source;
	std::ifstream file(filepath, std::ios::in | std::ios::binary);
	if (file) 
	{
		file.seekg(0, std::ios::end);
		source.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&source[0], source.size());
		file.close();
	}
	else
		Loggers::getLog()->error("Unable to open shader source file '{0}'", filepath);

	return source;
}



unsigned int Shader::compile(Type type, const std::string& src) 
{
	unsigned int shaderID = glCreateShader(Shader::get_glShaderType(type));
	const char* source = src.c_str();
	glShaderSource(shaderID, 1, &source, 0);
	glCompileShader(shaderID);

	int isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) 
	{
		int maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> infoLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(shaderID);

		if (type == Type::PIXEL)
			Loggers::getLog()->critical("Pixel shader compilation failed! {0}", infoLog.data());
		else
			Loggers::getLog()->critical("Vertex shader compilation failed! {0}", infoLog.data());

		__debugbreak();
	}

	return shaderID;
}



unsigned int Shader::link(unsigned int vertexShaderID, unsigned int pixelShaderID) 
{
	unsigned int programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, pixelShaderID);
	glLinkProgram(programID);

	int isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) 
	{
		int maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(programID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(pixelShaderID);

		Loggers::getLog()->critical("Vertex and pixel shader linking failed! {0}", infoLog.data());
		__debugbreak();
	}
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, pixelShaderID);

	return programID;
}



ShaderUniform* Shader::getUniform(const std::string& nameIn)
{
	bind();
	if (m_uniforms.find(nameIn) != m_uniforms.end())
		return m_uniforms[nameIn].get();
	else
	{
		m_logger->warn("Uniform '{0}' is either unused, invalid, or misspelled", nameIn);
		return nullptr;
	}
}



Shader& Shader::setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, bool dataIn)
{
	if (m_uniforms.find(nameIn) != m_uniforms.end())
		dynamic_cast<Bool1Uniform*>(getUniform(nameIn))->set(dataIn);
	else
		m_logger->warn("Uniform '{0}' is either unused, invalid, or misspelled", nameIn);
	return *this;
}



Shader& Shader::setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, int value)
{
	if (m_uniforms.find(nameIn) != m_uniforms.end())
	{
		switch (typeIn)
		{
		case ShaderUniform::Type::Int1:
			dynamic_cast<Int1Uniform&>(*getUniform(nameIn)).set(value);
			break;

		case ShaderUniform::Type::Sampler2D:
			dynamic_cast<Sampler2DUniform&>(*getUniform(nameIn)).set(value);
			break;

		default:
			break;
		}
	}
	else
		m_logger->warn("Uniform '{0}' is either unused, invalid, or misspelled", nameIn);
	return *this;
}



Shader& Shader::setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, float dataIn)
{
	if (m_uniforms.find(nameIn) != m_uniforms.end())
		dynamic_cast<Float1Uniform*>(getUniform(nameIn))->set(dataIn);
	else
		m_logger->warn("Uniform '{0}' is either unused, invalid, or misspelled", nameIn);
	return *this;
}



Shader& Shader::setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, const glm::vec2& dataIn)
{
	if (m_uniforms.find(nameIn) != m_uniforms.end())
		dynamic_cast<Float2Uniform*>(getUniform(nameIn))->set(dataIn);
	else
		m_logger->warn("Uniform '{0}' is either unused, invalid, or misspelled", nameIn);
	return *this;
}



Shader& Shader::setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, const glm::vec3& dataIn)
{
	if (m_uniforms.find(nameIn) != m_uniforms.end())
		dynamic_cast<Float3Uniform*>(getUniform(nameIn))->set(dataIn);
	else
		m_logger->warn("Uniform '{0}' is either unused, invalid, or misspelled", nameIn);
	return *this;
}



Shader& Shader::setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, const glm::vec4& dataIn)
{
	if (m_uniforms.find(nameIn) != m_uniforms.end())
		dynamic_cast<Float4Uniform*>(getUniform(nameIn))->set(dataIn);
	else
		m_logger->warn("Uniform '{0}' is either unused, invalid, or misspelled", nameIn);
	return *this;
}



Shader& Shader::setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, const glm::mat3& dataIn)
{
	if (m_uniforms.find(nameIn) != m_uniforms.end())
		dynamic_cast<Mat3Uniform*>(getUniform(nameIn))->set(dataIn);
	else
		m_logger->warn("Uniform '{0}' is either unused, invalid, or misspelled", nameIn);
	return *this;
}



Shader& Shader::setUniform(const std::string& nameIn, ShaderUniform::Type typeIn, const glm::mat4& dataIn)
{
	if (m_uniforms.find(nameIn) != m_uniforms.end())
		dynamic_cast<Mat4Uniform*>(getUniform(nameIn))->set(dataIn);
	else
		m_logger->warn("Uniform '{0}' is either unused, invalid, or misspelled", nameIn);
	return *this;
}



bool Shader::validate() const
{
	glValidateProgram(m_id);
	int isValid;
	glGetProgramiv(m_id, GL_VALIDATE_STATUS, &isValid);
	return isValid == GL_TRUE;
}



void Shader::bind() const
{
	glUseProgram(m_id);
}



void Shader::unbind() const
{
	glUseProgram(0);
}



void Shader::buildUniforms()
{
	glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &m_activeUniforms);
	const int BUFSIZE = 24;
	int length, size;
	unsigned int type;
	char name[BUFSIZE];
	for (int i = 0; i < m_activeUniforms; i++)
	{
		glGetActiveUniform(m_id, i, BUFSIZE, &length, &size, &type, name);
		if (length > BUFSIZE)
		{
			m_logger->error("Uniform '{0}' name is greater than the maximum name length of {1}", name[0], BUFSIZE);
			__debugbreak();
		}
		else
		{
			int location = glGetUniformLocation(m_id, name);
			if (location == -1) 
			{
				m_logger->error("Error getting the location for Uniform '{0}' it is either unused, invalid, or misspelled", name, glGetError());
				__debugbreak();
			}
			m_uniforms.insert({ name, std::unique_ptr<ShaderUniform>(createUniform(name, type, size, location, m_id)) });
		}
	}
}



unsigned int Shader::get_glShaderType(Type type)
{
	switch (type) 
	{
	case Type::VERTEX:
		return GL_VERTEX_SHADER;

	case Type::GEOMETRY:
		return GL_GEOMETRY_SHADER;

	case Type::PIXEL:
		return GL_FRAGMENT_SHADER;

	default:
		Loggers::getLog()->error("Invalid Shader type");
		__debugbreak();
		return 0;
	}
}



