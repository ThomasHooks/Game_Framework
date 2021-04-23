#ifndef IndexBuffer_H_
#define IndexBuffer_H_

#include <memory>

#include "utilities/Loggers.hpp"




class IndexBuffer 
{
public:

	enum  class Usage : uint8_t
	{
		Stream,
		Static,
		Dynamic
	};



	IndexBuffer();



	IndexBuffer(const IndexBuffer& other) = delete;



	IndexBuffer(IndexBuffer&& other) noexcept;



	~IndexBuffer();



	/// <summary>
	/// Creates a new index buffer of the given data
	/// </summary>
	/// <param name="indices">Specifies the index data to be stored</param>
	/// <param name="count">Specifies the number of indices</param>
	/// <param name="usage">Specifies the storage type</param>
	void create(unsigned int* indices, unsigned int count, Usage usage);



	/// <summary>
	/// Destroys this index buffer and frees all of its data
	/// </summary>
	void destroy();



	/// <summary>
	/// Adds new index data to this index buffer at the given location
	/// <para>
	/// This index buffer must be dynamic to use this method
	/// </para>
	/// </summary>
	/// <param name="indices">Specifies the index data to be stored</param>
	/// <param name="count">Specifies the number of new indices</param>
	/// <param name="offset">Specifies the start location of the new index data</param>
	void submitData(unsigned int* indices, unsigned int count, unsigned int offset);



	/// <summary>
	/// Adds new index data to the beginning of this index buffer
	/// <para>
	/// This index buffer must be dynamic to use this method
	/// </para>
	/// </summary>
	/// <param name="indices">Specifies the index data to be stored</param>
	/// <param name="count">Specifies the number of new indices</param>
	void submitData(unsigned int* indices, unsigned int count);



	/// <summary>
	/// Makes this the active index buffer
	/// </summary>
	void bind() const;



	/// <summary>
	/// Makes the currently active index buffer inactive
	/// </summary>
	void unbind() const;



	/// <summary>
	/// Gets the number of indices in this index buffer
	/// </summary>
	/// <returns>Number of indices</returns>
	unsigned int count() const;



private:

	std::shared_ptr<spdlog::logger> m_logger;

	unsigned int m_id = 0;

	unsigned int m_indexCount = 0;

	Usage m_usage;

	bool m_movedOrDestroyed = false;
}; 


#endif /* IndexBuffer_H_ */



