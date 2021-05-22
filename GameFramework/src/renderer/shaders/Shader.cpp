#include <iostream>
#include <fstream>
#include <filesystem>

#include <glm/gtc/type_ptr.hpp>

#include "renderer/shaders/Shader.h"
#include "renderer/RendererFondation.h"




Shader::Shader()
{
	m_logger = Loggers::getLog();
}



Shader::Shader(Shader&& other) noexcept
	: m_id(other.m_id), m_activeUniforms(other.m_activeUniforms)
{
	buildUniforms();
	other.m_id = 0;
	other.m_uniformsLookup.clear();
	other.m_activeUniforms = 0;
	other.m_moved = true;
}



Shader::~Shader()
{
	if (!m_moved)
	{
		m_uniformsLookup.clear();
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
		m_logger->warn("Shader OpenGL ID: '{0}' has already been created", m_id);
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
		m_logger->warn("Shader OpenGL ID: '{0}' has already been created", m_id);
}



std::string Shader::load(const std::string& filepath) 
{
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

		switch (type)
		{
		case Shader::Type::VERTEX:
			Loggers::getLog()->critical("Vertex shader compilation failed! {0}", infoLog.data());
			break;

		case Shader::Type::PIXEL:
			Loggers::getLog()->critical("Pixel shader compilation failed! {0}", infoLog.data());
			break;

		case Shader::Type::GEOMETRY:
			Loggers::getLog()->critical("Geometry shader compilation failed! {0}", infoLog.data());
			break;

		default:
			Loggers::getLog()->critical("Unknown shader type compilation failed! {0}", infoLog.data());
			break;
		}

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



bool Shader::hasUniform(const std::string& nameIn) const
{
	return m_uniformsLookup.find(nameIn) != m_uniformsLookup.end();
}



Shader::Uniform* Shader::getUniform(const std::string& nameIn)
{
	this->bind();
	if (m_uniformsLookup.find(nameIn) == m_uniformsLookup.end())
	{
		m_logger->warn("Uniform '{0}' is either unused, invalid, or misspelled", nameIn);
		return nullptr;
	}
	
	unsigned int i = m_uniformsLookup[nameIn];
	return &m_uniforms[i];
}



std::vector<Shader::Uniform>& Shader::getUniforms()
{
	return m_uniforms;
}



const std::vector<Shader::Uniform>& Shader::getUniforms() const
{
	return m_uniforms;
}



Shader& Shader::setUniformBool1(const std::string& nameIn, bool dataIn)
{
	setUniform<bool>(nameIn, Uniform::Type::Bool1, dataIn, 1, [this](bool dataIn, unsigned int countIn, const Uniform& uniform)
		{
			int params;
			glGetUniformiv(m_id, uniform.getLocation(), &params);

			if ((params ? 1 : 0) != dataIn)
				glUniform1i(uniform.getLocation(), dataIn ? 1 : 0);
		});

	return *this;
}



Shader& Shader::setUniformInt1(const std::string& nameIn, int dataIn)
{
	setUniform<int>(nameIn, Uniform::Type::Int1, dataIn, 1, [this](int dataIn, unsigned int countIn, const Uniform& uniform)
		{
			int params;
			glGetUniformiv(m_id, uniform.getLocation(), &params);
			if (params != dataIn)
				glUniform1i(uniform.getLocation(), dataIn);
		});

	return *this;
}



Shader& Shader::setUniformInt1(const std::string& nameIn, int* dataIn, unsigned int countIn)
{
	setUniform<int*>(nameIn, Uniform::Type::Int1Array, dataIn, countIn, [this](int* dataIn, unsigned int countIn, const Uniform& uniform)
		{
			glUniform1iv(uniform.getLocation(), countIn, dataIn);
		});

	return *this;
}



Shader& Shader::setUniformInt2(const std::string& nameIn, const glm::ivec2& dataIn)
{
	setUniform<glm::ivec2>(nameIn, Uniform::Type::Int2, dataIn, 1, [this](glm::ivec2 dataIn, unsigned int countIn, const Uniform& uniform)
		{
			glUniform2iv(uniform.getLocation(), 1, glm::value_ptr(dataIn));
		});

	return *this;
}



Shader& Shader::setUniformInt3(const std::string& nameIn, const glm::ivec3& dataIn)
{
	setUniform<glm::ivec3>(nameIn, Uniform::Type::Int3, dataIn, 1, [this](glm::ivec3 dataIn, unsigned int countIn, const Uniform& uniform)
		{
			glUniform3iv(uniform.getLocation(), 1, glm::value_ptr(dataIn));
		});

	return *this;
}



Shader& Shader::setUniformInt4(const std::string& nameIn, const glm::ivec4& dataIn)
{
	setUniform<glm::ivec4>(nameIn, Uniform::Type::Int4, dataIn, 1, [this](glm::ivec4 dataIn, unsigned int countIn, const Uniform& uniform)
		{
			glUniform4iv(uniform.getLocation(), 1, glm::value_ptr(dataIn));
		});

	return *this;
}



Shader& Shader::setUniformSampler2D(const std::string& nameIn, int dataIn)
{
	setUniform<int>(nameIn, Uniform::Type::Sampler2D, dataIn, 1, [this](const int dataIn, unsigned int countIn, const Uniform& uniform)
		{
			int params;
			glGetUniformiv(m_id, uniform.getLocation(), &params);
			if (params != dataIn)
				glUniform1i(uniform.getLocation(), dataIn);
		});

	return *this;
}



Shader& Shader::setUniformSampler2D(const std::string& nameIn, int* dataIn, unsigned int countIn)
{
	setUniform<int*>(nameIn, Uniform::Type::Sampler2D1Array, dataIn, countIn, [this](int* dataIn, unsigned int countIn, const Uniform& uniform)
		{
			glUniform1iv(uniform.getLocation(), countIn, dataIn);
		});

	return *this;
}




Shader& Shader::setUniformFloat1(const std::string& nameIn, float dataIn)
{
	setUniform<float>(nameIn, Uniform::Type::Float1, dataIn, 1, [this](float dataIn, unsigned int countIn, const Uniform& uniform)
		{
			float params;
			glGetUniformfv(m_id, uniform.getLocation(), &params);
			if (params != dataIn)
				glUniform1f(uniform.getLocation(), dataIn);
		});

	return *this;
}



Shader& Shader::setUniformFloat2(const std::string& nameIn, const glm::vec2& dataIn)
{
	setUniform<glm::vec2>(nameIn, Uniform::Type::Float2, dataIn, 1, [this](glm::vec2 dataIn, unsigned int countIn, const Uniform& uniform)
		{
			glUniform2fv(m_id, 1, glm::value_ptr(dataIn));
		});

	return *this;
}



Shader& Shader::setUniformFloat3(const std::string& nameIn, const glm::vec3& dataIn)
{
	setUniform<glm::vec3>(nameIn, Uniform::Type::Float3, dataIn, 1, [this](glm::vec3 dataIn, unsigned int countIn, const Uniform& uniform)
		{
			glUniform3fv(m_id, 1, glm::value_ptr(dataIn));
		});

	return *this;
}



Shader& Shader::setUniformFloat4(const std::string& nameIn, const glm::vec4& dataIn)
{
	setUniform<glm::vec4>(nameIn, Uniform::Type::Float4, dataIn, 1, [this](glm::vec4 dataIn, unsigned int countIn, const Uniform& uniform)
		{
			glUniform4fv(m_id, 1, glm::value_ptr(dataIn));
		});

	return *this;
}



Shader& Shader::setUniformMat3(const std::string& nameIn, const glm::mat3& dataIn)
{
	setUniform<glm::mat3>(nameIn, Uniform::Type::Mat3, dataIn, 1, [this](glm::mat3 dataIn, unsigned int countIn, const Uniform& uniform)
		{
			glUniformMatrix3fv(uniform.getLocation(), 1, GL_FALSE, glm::value_ptr(dataIn));
		});

	return *this;
}



Shader& Shader::setUniformMat4(const std::string& nameIn, const glm::mat4& dataIn)
{
	setUniform<glm::mat4>(nameIn, Uniform::Type::Mat4, dataIn, 1, [this](glm::mat4 dataIn, unsigned int countIn, const Uniform& uniform)
		{
			glUniformMatrix4fv(uniform.getLocation(), 1, GL_FALSE, glm::value_ptr(dataIn));
		});

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
			m_uniforms.emplace_back(name, getUniformTypeFromGL(type, size), size, location, m_id);
			m_uniformsLookup.insert({ name, i });
		}
	}
}



Shader::Uniform::Uniform(const std::string& nameIn, Type typeIn, int sizeIn, int locationIn, unsigned int programIn)
	: m_name(nameIn), m_type(typeIn), m_size(sizeIn), m_location(locationIn), m_program(programIn)
{
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



std::string Shader::Uniform::uniformTypeToString(Type typeIn)
{
	switch (typeIn)
	{
	case Type::Bool1:
		return std::string("Bool1");

	case Type::Int1:
		return std::string("Int1");

	case Type::Int2:
		return std::string("Int2");

	case Type::Int3:
		return std::string("Int3");
		
	case Type::Int4:
		return std::string("Int4");

	case Type::Int1Array:
		return std::string("Int1Array");

	case Type::Float1:
		return std::string("Float1");

	case Type::Float2:
		return std::string("Float2");

	case Type::Float3:
		return std::string("Float3");

	case Type::Float4:
		return std::string("Float4");

	case Type::Mat3:
		return std::string("Mat3");

	case Type::Mat4:
		return std::string("Mat4");

	case Type::Sampler2D:
		return std::string("Sampler2D");

	case Type::Sampler2D1Array:
		return std::string("Sampler2D1Array");

	case Type::Invalid:
	default:
		return std::string("Invalid");
	}
}



Shader::Uniform::Type Shader::getUniformTypeFromGL(unsigned int typeIn, int sizeIn)
{
	switch (typeIn)
	{
	case GL_BOOL:
		return Shader::Uniform::Type::Bool1;

	case GL_INT:
		if (sizeIn == 1)
			return Shader::Uniform::Type::Int1;
		else
			return Shader::Uniform::Type::Int1Array;

	case GL_INT_VEC2:
		return Shader::Uniform::Type::Int2;

	case GL_INT_VEC3:
		return Shader::Uniform::Type::Int3;

	case GL_INT_VEC4:
		return Shader::Uniform::Type::Int4;

	case GL_FLOAT:
		return Shader::Uniform::Type::Float1;

	case GL_FLOAT_VEC2:
		return Shader::Uniform::Type::Float2;

	case GL_FLOAT_VEC3:
		return Shader::Uniform::Type::Float3;

	case GL_FLOAT_VEC4:
		return Shader::Uniform::Type::Float4;

	case GL_FLOAT_MAT3:
		return Shader::Uniform::Type::Mat3;

	case GL_FLOAT_MAT4:
		return Shader::Uniform::Type::Mat4;

	case GL_SAMPLER_2D:
		if (sizeIn == 1)
			return Shader::Uniform::Type::Sampler2D;
		else
			return Shader::Uniform::Type::Sampler2D1Array;

	default:
		Loggers::getLog()->error("Invalid shader uniform type!");
		__debugbreak();
		return Shader::Uniform::Type::Invalid;
	}
}



