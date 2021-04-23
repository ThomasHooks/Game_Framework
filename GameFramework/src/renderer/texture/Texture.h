#ifndef Texture_H_
#define Texture_H_

#include <filesystem>




class Texture 
{
public:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="filepath"></param>
	Texture(const std::filesystem::path& filepath);



	Texture(const Texture& other) = delete;



	Texture(Texture&& other) noexcept;



	~Texture();



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



private:

	unsigned int m_id;

	mutable int m_slot = 0;

	bool m_moved = false;

	std::filesystem::path m_filepath;

	unsigned int m_width, m_height, m_channels;
}; 


#endif /* Texture_H_ */



