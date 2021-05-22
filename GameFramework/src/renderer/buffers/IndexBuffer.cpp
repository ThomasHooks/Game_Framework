#include <iostream>

#include "IndexBuffer.h"
#include "renderer/RendererFondation.h"




IndexBuffer::IndexBuffer() 
	: m_id(0), m_indexCount(0), m_usage(Usage::Static)
{
	m_logger = Loggers::getLog();
}



IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
	: m_id(other.m_id), m_indexCount(other.m_indexCount), m_usage(other.m_usage)
{
	other.m_id = 0;
	other.m_movedOrDestroyed = true;
}



IndexBuffer::~IndexBuffer() 
{
	destroy();
}



void IndexBuffer::create(unsigned int* indices, unsigned int count, Usage usage)
{
	if (m_id) 
	{
		m_logger->warn("This index buffer has already been created.");
		return;
	}

	glCreateBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	m_indexCount = count;
	m_usage = usage;

	switch (usage)
	{
	case Usage::Stream:
		if (indices != nullptr)
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STREAM_DRAW);
		}
		else
		{
			m_logger->warn("Failed to create index buffer.");
			m_logger->warn("Index buffer {0}'s usage has been set to 'Stream', index data cannot be null.", m_id);
			glDeleteBuffers(1, &m_id);
			m_indexCount = 0;
		}
		break;

	case Usage::Static:
		if (indices != nullptr)
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		}
		else
		{
			m_logger->warn("Failed to create index buffer.");
			m_logger->warn("Index buffer {0}'s usage has been set to 'Static', index data cannot be null.", m_id);
			glDeleteBuffers(1, &m_id);
			m_indexCount = 0;
		}
		break;

	case Usage::Dynamic:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
		break;

	default:
		m_logger->warn("Failed to create index buffer.");
		m_logger->critical("Index buffer {0}'s usage type is in an unknow state!", m_id);
		__debugbreak();
		break;
	}
}



void IndexBuffer::destroy()
{
	if (!m_movedOrDestroyed) 
	{
		m_logger->trace("Index buffer '{0}' has been deleted", m_id);
		glDeleteBuffers(1, &m_id);
		m_id = 0;
		m_movedOrDestroyed = true;
	}
}



void IndexBuffer::submitData(unsigned int* indices, unsigned int count, unsigned int offset)
{
	switch (m_usage)
	{
	case Usage::Static:
	case Usage::Stream:
		m_logger->warn("Index buffer {0} is not 'Dynamic', index data cannot be changed.", m_id);
		break;

	case Usage::Dynamic:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, count * sizeof(unsigned int), indices);
		m_indexCount = count + offset;
		break;

	default:
		m_logger->critical("Index buffer {0}'s usage type is in an unknow state!", m_id);
		__debugbreak();
		break;
	}
}



void IndexBuffer::submitData(unsigned int* indices, unsigned int count)
{
	submitData(indices, count, 0);
}



void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}



void IndexBuffer::unbind() const 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



unsigned int IndexBuffer::count() const 
{
	return m_indexCount;
}



IndexBuffer::Usage IndexBuffer::getUsage() const
{
	return m_usage;
}



