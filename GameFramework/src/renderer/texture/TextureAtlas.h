#ifndef TextureAtlas_H_
#define TextureAtlas_H_

#include <vector>

#include <glm/glm.hpp>

#include "renderer/texture/Texture.h"




class TextureAtlas : public Texture
{
public:

	TextureAtlas(const std::filesystem::path& filepath, const glm::uvec2& spriteSizeIn, const glm::uvec2& spritePaddingIn, unsigned int GuidIn);



	TextureAtlas(const std::filesystem::path& filepath, const glm::uvec2& spriteSizeIn, unsigned int GuidIn);



	TextureAtlas(const TextureAtlas& other) = delete;



	TextureAtlas(TextureAtlas&& other) noexcept;



	~TextureAtlas();



	/// <summary>
	/// Gets the sub-texture in this texture specified by its index
	/// </summary>
	/// <param name="spriteIndex">Specifies the sub-texture's index</param>
	/// <returns></returns>
	virtual SubTexture getSubTexture(unsigned int spriteIndex) const override;



	/// <summary>
	/// Gets the total number of sub-textures in this texture atlas
	/// </summary>
	/// <returns></returns>
	int getNumberOfSubTextures() const override;



protected:

	void buildSubTextures();



	glm::uvec2 m_spriteSize;

	glm::uvec2 m_spritePadding;

	std::vector<SubTexture> m_subTextures;
}; 


#endif /* TextureAtlas_H_ */



