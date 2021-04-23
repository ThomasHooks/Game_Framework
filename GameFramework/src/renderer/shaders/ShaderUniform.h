#ifndef ShaderUniform_H_
#define ShaderUniform_H_

#include <string>
#include <memory>

#include <glm/glm.hpp>




class ShaderUniform 
{
public:

	enum class Type 
	{
		Invalid,
		Bool1,
		Int1,
		Float1, 
		Float2, 
		Float3, 
		Float4,
		Mat3, 
		Mat4,
		Sampler2D
	};



	virtual ~ShaderUniform() = default;



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const std::string& getName() const { return m_name; }



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Type getType() const { return m_type; }



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int getSize() const { return m_size; }



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int getLocation() const { return m_location; }



	/// <summary>
	/// 
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	static unsigned int TypeSize(Type type);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	static unsigned int TypeCount(Type type);



protected:

	ShaderUniform(const std::string & nameIn, Type typeIn, int sizeIn, int locationIn, int programIn);



	std::string m_name;

	Type m_type;

	int m_size, m_location;

	unsigned int m_program;
};



ShaderUniform* createUniform(const std::string& nameIn, unsigned int typeIn, int sizeIn, int locationIn, int programIn);



class Bool1Uniform : public ShaderUniform
{
public:

	Bool1Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn);



	void set(bool value);
};



class Int1Uniform : public ShaderUniform
{
public:

	Int1Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn);



	void set(int value);
};



class Float1Uniform : public ShaderUniform
{
public:

	Float1Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn);



	void set(float value);
};



class Float2Uniform : public ShaderUniform
{
public:

	Float2Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn);



	void set(const glm::vec2& vector);
};



class Float3Uniform : public ShaderUniform
{
public:

	Float3Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn);



	void set(const glm::vec3& vector);
};



class Float4Uniform : public ShaderUniform
{
public:

	Float4Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn);



	void set(const glm::vec4& vector);
};



class Mat3Uniform : public ShaderUniform
{
public:

	Mat3Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn);



	void set(const glm::mat3& matrix);
};



class Mat4Uniform : public ShaderUniform
{
public:

	Mat4Uniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn);



	void set(const glm::mat4& matrix);
};



class Sampler2DUniform : public ShaderUniform
{
public:

	Sampler2DUniform(const std::string& nameIn, int sizeIn, int locationIn, int programIn);



	void set(int slot);
};


#endif /* ShaderUniform_H_ */



