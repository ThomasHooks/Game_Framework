#include <string>

#include <stb_image/stb_image.h>

#include "Texture.h"
#include "renderer/RendererFondation.h"
#include "utilities/Loggers.hpp"
#include "utilities/Assertions.h"




Texture::Texture(const std::filesystem::path& filepath, unsigned int GuidIn)
	: m_id(0), m_width(0), m_height(0), m_channels(0), m_guid(GuidIn)
{
	stbi_set_flip_vertically_on_load(TRUE);

	int width, height, channels;
	stbi_uc* imageData = stbi_load(filepath.string().c_str(), &width, &height, &channels, 0);
	GAME_ASSERT(imageData != nullptr);

	m_width = width;
	m_height = height;
	m_channels = channels;
	m_filepath = filepath;

	GLenum internalformat = 0, format = 0;
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
		__debugbreak();
		break;
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
	glTextureStorage2D(m_id, 1, internalformat, m_width, m_height);

	glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, imageData);
	stbi_image_free(imageData);
}



Texture::Texture(Texture&& other) noexcept
	: m_id(other.m_id), m_filepath(other.m_filepath), m_width(other.m_width), m_height(other.m_height), m_channels(other.m_channels), m_guid(other.m_guid)
{
	other.m_id = 0;
	other.m_filepath.clear();
	other.m_width = 0;
	other.m_height = 0;
	other.m_channels = 0;
	other.m_movedOrDestroyed = true;
}



Texture::~Texture()
{
	destroy();
}



void Texture::bind(unsigned int slot) const
{
	m_slot = slot;
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_id);
}



void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}



SubTexture Texture::getSubTexture(unsigned int spriteIndex) const
{
	SubTexture sprite = { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
	return sprite;
}



int Texture::getNumberOfSubTextures() const
{
	return 1;
}



const std::string& Texture::tag() const
{
	return m_filepath.stem().string();
}



void Texture::destroy()
{
	if (!m_movedOrDestroyed)
	{
		glDeleteTextures(1, &m_id);
		m_id = 0;
		m_filepath.clear();
		m_width = 0;
		m_height = 0;
		m_channels = 0;
		m_movedOrDestroyed = true;
	}
}



