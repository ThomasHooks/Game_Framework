#include <iostream>

#include "renderer/buffers/VertexBuffer.h"
#include "renderer/RendererFondation.h"




unsigned int getGL_DataType(VertexBuffer::Attribute typeIn)
{
	switch (typeIn) 
	{
	case VertexBuffer::Attribute::Float1:
		return GL_FLOAT;

	case VertexBuffer::Attribute::Float2:
		return GL_FLOAT;

	case VertexBuffer::Attribute::Float3:
		return GL_FLOAT;

	case VertexBuffer::Attribute::Float4:
		return GL_FLOAT;

	default:
		return GL_FLOAT;
	}
}



unsigned int getVertexAttributeSize(VertexBuffer::Attribute typeIn)
{
	switch (typeIn)
	{
	case VertexBuffer::Attribute::Float1:
		return sizeof(float);

	case VertexBuffer::Attribute::Float2:
		return sizeof(float) * 2;

	case VertexBuffer::Attribute::Float3:
		return sizeof(float) * 3;

	case VertexBuffer::Attribute::Float4:
		return sizeof(float) * 4;

	default:
		Loggers::getLog()->error("Invalid vertex buffer attribute data type!");
		__debugbreak();
		return 0;
	}
}



VertexBuffer::Element::Element(VertexBuffer::Attribute typeIn, const std::string& nameIn, bool isNormalized)
	: type(typeIn), name(nameIn), size(getVertexAttributeSize(typeIn)), offset(0), normalized(isNormalized)
{
}



unsigned int VertexBuffer::Element::count() const
{
	switch (type)
	{
	case VertexBuffer::Attribute::Float1:
		return 1;

	case VertexBuffer::Attribute::Float2:
		return 2;

	case VertexBuffer::Attribute::Float3:
		return 3;

	case VertexBuffer::Attribute::Float4:
		return 4;

	default:
		return 0;
	}
}



VertexBuffer::Layout& VertexBuffer::Layout::add(VertexBuffer::Attribute typeIn, const std::string& nameIn, bool isNormalized)
{
	m_elements.push_back({ typeIn, nameIn, isNormalized });
	return *this;
}



VertexBuffer::Layout& VertexBuffer::Layout::add(VertexBuffer::Attribute typeIn, const std::string& nameIn)
{
	m_elements.push_back({ typeIn, nameIn, false });
	return *this;
}



const std::vector<VertexBuffer::Element>& VertexBuffer::Layout::get() const
{
	return m_elements;
}



void VertexBuffer::Layout::update()
{
	m_stride = 0;
	unsigned int offset = 0;
	for (auto& element : m_elements)
	{
		element.offset = offset;
		offset += element.size;
		m_stride += element.size;
	}
}



VertexBuffer::VertexBuffer()
	: m_id(0), m_vbo(0), m_usage(Usage::Static) 
{
	m_logger = Loggers::getLog();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glCreateVertexArrays(1, &m_id);
	glBindVertexArray(m_id);
}



VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	: m_id(other.m_id), m_vbo(other.m_vbo), m_usage(other.m_usage) 
{
	other.m_id = 0;
	other.m_vbo = 0;
	other.m_movedOrDestroyed = true;
}



VertexBuffer::~VertexBuffer() 
{
	destroy();
}



void VertexBuffer::create(float* vertices, unsigned int size, Usage usage) 
{
	if (m_vbo) 
	{
		m_logger->warn("This vertex buffer has already been created.");
		return;
	}

	glBindVertexArray(m_id);
	glCreateBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	m_usage = usage;

	switch (usage) 
	{
	case Usage::Stream:
		if (vertices != nullptr) 
		{
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STREAM_DRAW);
		}
		else 
		{
			m_logger->warn("Failed to create vertex buffer.");
			m_logger->warn("Vertex buffer '{0}' usage has been set to 'Stream', buffer data cannot be null.", m_vbo);
			glDeleteBuffers(1, &m_vbo);
		}
		break;

	case Usage::Static:
		if (vertices != nullptr) 
		{
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		}
		else 
		{
			m_logger->warn("Failed to create vertex buffer.");
			m_logger->warn("Vertex buffer '{0}' usage has been set to 'Static', buffer data cannot be null.", m_vbo);
			glDeleteBuffers(1, &m_vbo);
		}
		break;

	case Usage::Dynamic:
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
		break;

	default:
		m_logger->warn("Failed to create vertex buffer.");
		m_logger->critical("Vertex buffer '{0}' usage type is in an unknow state!", m_vbo);
		__debugbreak();
		break;
	}
}



void VertexBuffer::destroy()
{
	if (!m_movedOrDestroyed)
	{
		m_logger->trace("Vertex array '{0}' has been deleted", m_id);
		glDeleteVertexArrays(1, &m_id);
		m_logger->trace("Vertex buffer '{0}' has been deleted", m_vbo);
		glDeleteBuffers(1, &m_vbo);
		m_movedOrDestroyed = true;
	}
}



void VertexBuffer::setLayout(VertexBuffer::Layout& layout) 
{
	if (!m_vbo) 
	{
		m_logger->warn("A vertex buffer must be created before its layout can be set.");
		return;
	}

	glBindVertexArray(m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	layout.update();
	unsigned int index = 0;
	for (const auto& element : layout.m_elements) 
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			element.count(),
			getGL_DataType(element.type),
			element.normalized ? GL_TRUE : GL_FALSE,
			layout.m_stride,
			(const void*)element.offset);

		index++;
	}
	m_layouts.push_back(layout);
}



const std::vector<VertexBuffer::Layout>& VertexBuffer::getLayout() const
{
	return m_layouts;
}



void VertexBuffer::submitData(float* vertices, unsigned int size, unsigned int offset)
{

	switch (m_usage) 
	{
	case Usage::Static:
	case Usage::Stream:
		m_logger->warn("Vertex buffer {0} is not 'Dynamic', vertex data cannot be changed.", m_vbo);
		break;

	case Usage::Dynamic:
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
		break;

	default:
		m_logger->critical("Vertex buffer {0}'s usage type is in an unknow state!", m_vbo);
		__debugbreak();
		break;
	}
}



void VertexBuffer::submitData(float* vertices, unsigned int size)
{
	submitData(vertices, size, 0);
}



void VertexBuffer::bind() const 
{
	glBindVertexArray(m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}



void VertexBuffer::unbind() const 
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



