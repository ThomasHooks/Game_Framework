#include "TextureAtlas.h"
#include "utilities/Assertions.h"




TextureAtlas::TextureAtlas(const std::filesystem::path& filepath, const glm::uvec2& spriteSizeIn, const glm::uvec2& spritePaddingIn, unsigned int GuidIn)
	: Texture(filepath, GuidIn), m_spriteSize(spriteSizeIn), m_spritePadding(spritePaddingIn)
{
	buildSubTextures();
}



TextureAtlas::TextureAtlas(const std::filesystem::path& filepath, const glm::uvec2& spriteSizeIn, unsigned int GuidIn)
	: Texture(filepath, GuidIn), m_spriteSize(spriteSizeIn), m_spritePadding(0, 0)
{
	buildSubTextures();
}



TextureAtlas::TextureAtlas(TextureAtlas&& other) noexcept
	: Texture(std::move(other)), m_spriteSize(other.m_spriteSize), m_spritePadding(other.m_spritePadding)
{
	other.m_spriteSize = { 0.0f, 0.0f };
	other.m_spritePadding = { 0.0f, 0.0f };
	other.m_subTextures.clear();
}



TextureAtlas::~TextureAtlas()
{
	if (!m_movedOrDestroyed)
	{
		destroy();
		m_spriteSize = { 0.0f, 0.0f };
		m_spritePadding = { 0.0f, 0.0f };
		m_subTextures.clear();
	}
}



SubTexture TextureAtlas::getSubTexture(unsigned int spriteIndex) const
{
	GAME_ASSERT(spriteIndex < m_subTextures.size());
	return m_subTextures[spriteIndex];
}



int TextureAtlas::getNumberOfSubTextures() const
{
	return static_cast<int>(m_subTextures.size());
}



void TextureAtlas::buildSubTextures()
{
	GAME_ASSERT(m_spriteSize.x != 0 && m_spriteSize.y != 0);
	unsigned int numberOfRows = m_width / (m_spriteSize.x + m_spritePadding.x);
	unsigned int numberOfColumns = m_height / (m_spriteSize.y + m_spritePadding.y);
	for (unsigned int y = 0; y < numberOfColumns; y++)
	{
		for (unsigned int x = 0; x < numberOfRows; x++)
		{
			float minx = ((m_spriteSize.x + m_spritePadding.x) * x) / static_cast<float>(m_width);
			float miny = ((m_spriteSize.y + m_spritePadding.y) * y) / static_cast<float>(m_height);
			float maxx = ((m_spriteSize.x + m_spritePadding.x) * x + m_spriteSize.x) / static_cast<float>(m_width);
			float maxy = ((m_spriteSize.y + m_spritePadding.y) * y + m_spriteSize.y) / static_cast<float>(m_height);
			SubTexture tex = { { minx, miny }, { maxx, maxy } };
			m_subTextures.push_back(tex);
		}
	}
}



