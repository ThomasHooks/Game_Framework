#ifndef Texture_H_
#define Texture_H_

#include <filesystem>

#include <glm/glm.hpp>




struct SubTexture
{
	/// <summary>
	/// Bottom-left most coordinate 
	/// </summary>
	glm::vec2 min;



	/// <summary>
	/// Top-right most coordinate 
	/// </summary>
	glm::vec2 max;
};



class Texture 
{
public:

	Texture(const std::filesystem::path& filepath, unsigned int GuidIn);



	Texture(const Texture& other) = delete;



	Texture(Texture&& other) noexcept;



	virtual ~Texture();



	/// <summary>
	/// Binds this texture to the given texture slot, or to texture slot 0 if no slot is given
	/// </summary>
	/// <param name="slot">Specifies the texture slot</param>
	void bind(unsigned int slot = 0) const;



	/// <summary>
	/// Unbinds the currently bound texture
	/// </summary>
	void unbind() const;



	/// <summary>
	/// Gets the sub-texture in this texture specified by its index
	/// </summary>
	/// <param name="spriteIndex">Specifies the sub-texture's index</param>
	/// <returns></returns>
	virtual SubTexture getSubTexture(unsigned int spriteIndex) const;



	/// <summary>
	/// Gets the total number of sub-textures in this texture atlas
	/// </summary>
	/// <returns></returns>
	virtual int getNumberOfSubTextures() const;



	/// <summary>
	/// Gets the width of this texture
	/// </summary>
	/// <returns></returns>
	unsigned int width() const { return m_width; }



	/// <summary>
	/// Gets the height of this texture
	/// </summary>
	/// <returns></returns>
	unsigned int height() const { return m_height; }



	/// <summary>
	/// Gets the tag of this texture
	/// </summary>
	/// <returns></returns>
	const std::string& tag() const;



	/// <summary>
	/// Gets the file path of this texture
	/// </summary>
	/// <returns></returns>
	const std::filesystem::path& location() const { return m_filepath; }



	int getSlot() const { return m_slot; }



	unsigned int getID() const { return m_guid; }



protected:

	void destroy();



	unsigned int m_id;

	mutable int m_slot = 0;

	bool m_movedOrDestroyed = false;

	std::filesystem::path m_filepath;

	unsigned int m_width, m_height, m_channels, m_guid;
}; 


#endif /* Texture_H_ */



