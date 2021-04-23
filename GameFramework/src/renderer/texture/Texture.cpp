#include <string>

#include <glad/glad.h>
#include <stb_image/stb_image.h>

#include "Texture.h"
#include "utilities/Loggers.hpp"
#include "utilities/Assertions.h"




Texture::Texture(const std::filesystem::path& filepath)
	: m_id(0), m_width(0), m_height(0), m_channels(0) 
{
	stbi_set_flip_vertically_on_load(1);

	int width, height, channels;
	stbi_uc* imageData = stbi_load(filepath.string().c_str(), &width, &height, &channels, 0);
	GAME_ASSERT(imageData != nullptr);

	m_width = width;
	m_height = height;
	m_channels = channels;
	m_filepath = filepath;

	GLenum internalformat = 0;
	GLenum format = 0;
	switch (channels)
	{
	case 3:
		internalformat = GL_RGB8;
		format = GL_RGB;
		break;

	case 4:
		internalformat = GL_RGBA8;
		format = GL_RGBA;
		break;

	default:
		Loggers::getLog()->critical("Texture '{0}' is in a non-supported image format", filepath.string());
		break;
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
	glTextureStorage2D(m_id, 1, internalformat, m_width, m_height);

	glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, imageData);
	stbi_image_free(imageData);
}



Texture::Texture(Texture&& other) noexcept
	: m_id(other.m_id), m_filepath(other.m_filepath), m_width(other.m_width), m_height(other.m_height), m_channels(other.m_channels)
{
	other.m_id = 0;
	other.m_filepath.clear();
	other.m_width = 0;
	other.m_height = 0;
	other.m_channels = 0;
	other.m_moved = true;
}



Texture::~Texture()
{
	if (!m_moved)
		glDeleteTextures(1, &m_id);
}



void Texture::bind(unsigned int slot) const
{
	if (slot > 31)
	{
		Loggers::getLog()->warn("Tried to bind texture '{0}' in slot '{1}' but there are only 32 slots", this->tag(), slot + 1);
		slot = 31;
	}
	m_slot = slot;
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_id);
}



void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}



const std::string& Texture::tag() const
{
	return m_filepath.stem().string();
}



