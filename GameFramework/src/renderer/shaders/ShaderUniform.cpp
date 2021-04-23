#include "ShaderUniform.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

#include "renderer/shaders/ShaderUniform.h"
#include "utilities/Loggers.hpp"




ShaderUniform::ShaderUniform(const std::string& nameIn, Type typeIn, int sizeIn, int locationIn, int programIn)
	: m_name(nameIn), m_type(typeIn), m_size(sizeIn), m_location(locationIn), m_program(programIn)
{
}



unsigned int ShaderUniform::TypeSize(Type typeIn)
{
	switch (typeIn)
	{
	case Type::Bool1:
		return 4;

	case Type::Int1:
		return 4;

	case Type::Float1:
		return 4;

	case Type::Float2:
		return 4 * 2;

	case Type::Float3:
		return 4 * 3;

	case Type::Float4:
		return 4 * 4;

	case Type::Mat3:
		return 4 * 3 * 3;

	case Type::Mat4:
		return 4 * 4 * 4;

	case Type::Sampler2D:
		return 4;

	default:
		Loggers::getLog()->error("Invalid shader uniform type!");
		return 0;
	}
}



unsigned int ShaderUniform::TypeCount(Type typeIn)
{
	switch (typeIn)
	{
	case Type::Bool1:
		return 1;

	case Type::Int1:
		return 1;

	case Type::Float1:
		return 1;

	case Type::Float2:
		return 2;

	case Type::Float3:
		return 3;

	case Type::Float4:
		return 4;

	case Type::Mat3:
		return 3 * 3;

	case Type::Mat4:
		return 4 * 4;

	case Type::Sampler2D:
		return 1;

	default:
		Loggers::getLog()->error("Invalid shader uniform type!");
		__debugbreak();
		return 0;
	}
}



ShaderUniform::Type getUniformType(unsigned int typeIn)
{
	switch (typeIn)
	{
	case GL_BOOL:
		return ShaderUniform::Type::Bool1;

	case GL_INT:
		return ShaderUniform::Type::Int1;

	case GL_FLOAT:
		return ShaderUniform::Type::Float1;

	case GL_FLOAT_VEC2:
		return ShaderUniform::Type::Float2;

	case GL_FLOAT_VEC3:
		return ShaderUniform::Type::Float3;

	case GL_FLOAT_VEC4:
		return ShaderUniform::Type::Float4;

	case GL_FLOAT_MAT3:
		return ShaderUniform::Type::Mat3;

	case GL_FLOAT_MAT4:
		return ShaderUniform::Type::Mat4;

	case GL_SAMPLER_2D:
		return ShaderUniform::Type::Sampler2D;

	default:
		Loggers::getLog()->error("Invalid shader uniform type!");
		__debugbreak();
		return ShaderUniform::Type::Invalid;
	}
}



ShaderUniform* createUniform(const std::string& nameIn, unsigned int typeIn, int sizeIn, int locationIn, int programIn)
{
	ShaderUniform::Type type = getUniformType(typeIn);
	switch (type)
	{
	case ShaderUniform::Type::Bool1:
		return new Bool1Uniform(nameIn, sizeIn, locationIn, programIn);

	case ShaderUniform::Type::Int1:
		return new Int1Uniform(nameIn, sizeIn, locationIn, programIn);

	case ShaderUniform::Type::Float1:
		return new Float1Uniform(nameIn, sizeIn, locationIn, programIn);

	case ShaderUniform::Type::Float2:
		return new Float2Uniform(nameIn, sizeIn, locationIn, programIn);

	case ShaderUniform::Type::Float3:
		return new Float3Uniform(nameIn, sizeIn, locationIn, programIn);

	case ShaderUniform::Type::Float4:
		return new Float4Uniform(nameIn, sizeIn, locationIn, programIn);

	case ShaderUniform::Type::Mat3:
		return new Mat3Uniform(nameIn, sizeIn, locationIn, programIn);

	case ShaderUniform::Type::Mat4:
		return new Mat4Uniform(nameIn, sizeIn, locationIn, programIn);

	case ShaderUniform::Type::Sampler2D:
		return new Sampler2DUniform(nameIn, sizeIn, locationIn, programIn);

	default:
	case ShaderUniform::Type::Invalid:
		Loggers::getLog()->error("Invalid shader uniform type!");
		__debugbreak();
		return nullptr;
	}
}



Bool1Uniform::Bool1Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn)
	: ShaderUniform(nameIn, Type::Bool1, sizeIn, locationIn, programIn)
{
}



void Bool1Uniform::set(bool value)
{
	glUniform1i(m_location, value ? 1 : 0);
}



Int1Uniform::Int1Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn)
	: ShaderUniform(nameIn, Type::Int1, sizeIn, locationIn, programIn)
{
}



void Int1Uniform::set(int value)
{
	int params;
	glGetUniformiv(m_program, m_location, &params);
	if (params != value)
		glUniform1i(m_location, value);
}



Float1Uniform::Float1Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn)
	: ShaderUniform(nameIn, Type::Float1, sizeIn, locationIn, programIn)
{
}



void Float1Uniform::set(float value)
{
	float params;
	glGetUniformfv(m_program, m_location, &params);
	if (params != value)
		glUniform1f(m_location, value);
}



Float2Uniform::Float2Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn)
	: ShaderUniform(nameIn, Type::Float2, sizeIn, locationIn, programIn)
{
}


void Float2Uniform::set(const glm::vec2& vector)
{
	glUniform2fv(m_location, 1, glm::value_ptr(vector));
}



Float3Uniform::Float3Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn)
	: ShaderUniform(nameIn, Type::Float3, sizeIn, locationIn, programIn)
{
}



void Float3Uniform::set(const glm::vec3& vector)
{
	glUniform4fv(m_location, 1, glm::value_ptr(vector));
}



Float4Uniform::Float4Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn)
	: ShaderUniform(nameIn, Type::Float4, sizeIn, locationIn, programIn)
{
}



void Float4Uniform::set(const glm::vec4& vector)
{
	glUniform4fv(m_location, 1, glm::value_ptr(vector));
}



Mat3Uniform::Mat3Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn)
	: ShaderUniform(nameIn, Type::Mat3, sizeIn, locationIn, programIn)
{
}



void Mat3Uniform::set(const glm::mat3& matrix)
{
	glUniformMatrix3fv(m_location, 1, GL_FALSE, glm::value_ptr(matrix));
}



Mat4Uniform::Mat4Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn)
	: ShaderUniform(nameIn, Type::Mat4, sizeIn, locationIn, programIn)
{
}



void Mat4Uniform::set(const glm::mat4& matrix)
{
	glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(matrix));
}



Sampler2DUniform::Sampler2DUniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn)
	: ShaderUniform(nameIn, Type::Sampler2D, sizeIn, locationIn, programIn)
{
}



void Sampler2DUniform::set(int slot)
{
	int params;
	glGetUniformiv(m_program, m_location, &params);
	if (params != slot)
		glUniform1i(m_location, slot);
}



