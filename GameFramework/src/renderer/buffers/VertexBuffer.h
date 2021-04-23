#ifndef VertexBuffer_H_
#define VertexBuffer_H_

#include <vector>
#include <memory>

#include "utilities/Loggers.hpp"




class VertexBuffer 
{
public:

	enum  class Usage : uint8_t 
	{
		Stream,
		Static,
		Dynamic
	};



	enum class Attribute : uint8_t
	{
		Float1,
		Float2,
		Float3,
		Float4
	};



	struct Element
	{
		Element(VertexBuffer::Attribute typeIn, const std::string& nameIn, bool isNormalized);



		/// <summary>
		/// Gets the number of components in this vertex buffer element
		/// </summary>
		/// <returns></returns>
		unsigned int count() const;



		VertexBuffer::Attribute type;

		std::string name;

		unsigned int size;

		unsigned int offset;

		bool normalized;
	};



	class Layout
	{
		friend VertexBuffer;

	public:

		/// <summary>
		/// Adds a new element to this vertex attribute layout
		/// </summary>
		/// <param name="typeIn">Specifies the vertext attribute data type</param>
		/// <param name="nameIn">Specifies the vertext attribute's name</param>
		/// <param name="isNormalized">Specifies if this vertext attribute has been normalized</param>
		/// <returns>A referance to this vertext buffer layout</returns>
		Layout& add(VertexBuffer::Attribute typeIn, const std::string& nameIn, bool isNormalized);



		/// <summary>
		/// Adds a new element to this vertex attribute layout
		/// </summary>
		/// <param name="typeIn">Specifies the vertext attribute data type</param>
		/// <param name="nameIn">Specifies the vertext attribute's name</param>
		/// <returns>A referance to this vertext buffer layout</returns>
		Layout& add(VertexBuffer::Attribute typeIn, const std::string& nameIn);



		/// <summary>
		/// Exposes this vertext buffer layout
		/// </summary>
		/// <returns></returns>
		const std::vector<VertexBuffer::Element>& get() const;



	private:

		/// <summary>
		/// Updates all element's offset and stride in vertext buffer layout
		/// </summary>
		void update();



		std::vector<VertexBuffer::Element> m_elements;

		unsigned int m_stride = 0;
	};



	VertexBuffer();



	VertexBuffer(const VertexBuffer& other) = delete;



	VertexBuffer(VertexBuffer&& other) noexcept;



	~VertexBuffer();



	/// <summary>
	/// Creates a new vertex buffer of the given usage type and data
	/// <para>
	/// If the vertex buffer is dynamic a null pointer can be passed in for vertices
	/// </para>
	/// </summary>
	/// <param name="vertices">Specifies the data to be stored in the vertex buffer</param>
	/// <param name="size">Specifies the size of the vertex buffer</param>
	/// <param name="usage">Specifies the vertex buffers storage type</param>
	void create(float* vertices, unsigned int size, Usage usage);



	/// <summary>
	/// Destroys this vertex buffer and frees all of its data
	/// </summary>
	void destroy();



	/// <summary>
	/// Sets this vertex buffer's layout
	/// </summary>
	/// <param name="layout">Specifies the vertex buffer's layout</param>
	void setLayout(Layout& layout);



	/// <summary>
	/// Gets this vertex buffer's layout
	/// </summary>
	/// <returns></returns>
	const std::vector<Layout>& getLayout() const;



	/// <summary>
	/// Adds new vertex data to this vertex buffer at the given location
	/// <para>
	/// This vertex buffer must be dynamic to use this method
	/// </para>
	/// </summary>
	/// <param name="vertices">Specifies the new vertex data</param>
	/// <param name="size">Specifies the size of the new vertex data</param>
	/// <param name="offset">Specifies the start location of the new vertex data</param>
	void submitData(float* vertices, unsigned int size, unsigned int offset);



	/// <summary>
	/// Adds new vertex data to the beginning of this vertex buffer
	/// <para>
	/// This vertex buffer must be dynamic to use this method
	/// </para>
	/// </summary>
	/// <param name="vertices">Specifies the new vertex data</param>
	/// <param name="size">Specifies the size of the new vertex data</param>
	void submitData(float* vertices, unsigned int size);



	/// <summary>
	/// Makes this the active vertex buffer
	/// </summary>
	void bind() const;



	/// <summary>
	/// Makes the currently active vertex buffer inactive
	/// </summary>
	void unbind() const;



private:

	std::shared_ptr<spdlog::logger> m_logger;

	unsigned int m_id;

	bool m_movedOrDestroyed = false;

	unsigned int m_vbo;

	std::vector<Layout> m_layouts;

	Usage m_usage;
}; 


#endif /* VertexBuffer_H_ */



