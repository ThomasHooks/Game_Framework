#ifndef WINDOW_H_
#define WINDOW_H_


#include <memory>
#include <string>

#include <SDL.h>

#include "utilities/Loggers.hpp"
#include "utilities/math/Pos2.hpp"




struct WindowData
{
	WindowData(const std::string& titleIn = "Name of Game", unsigned int widthIn = 640, unsigned int heightIn = 480)
		: title(titleIn), width(widthIn), height(heightIn) 
	{};

	std::string title;
	unsigned int width, height;
	bool hidden = false;
	SDL_Window* window = nullptr;
};



int filterEventCallback(void *userdata, SDL_Event * event);



class Window
{
public:

	Window(const std::string &title, const Pos2N &sizeIn, unsigned int flags);



	~Window();



	Window(Window &&other) = delete;



	Window(const Window &other) = delete;



	/// <summary>
	/// Gets the Window's width or '0' if the window has not been initialized
	/// </summary>
	/// <returns></returns>
	int width() const;



	/// <summary>
	/// Gets the Window's height or '0' if the window has not been initialized
	/// </summary>
	/// <returns></returns>
	int height() const;



	/// <summary>
	/// Checks if this Window is open
	/// </summary>
	/// <returns></returns>
	bool isOpen() const;



	/// <summary>
	/// <para>nullable</para>
	/// Exposes the SDL_Window inside of this wrapper
	/// </summary>
	/// <returns>A SDL_Window pointer or null if the window has not been initialized</returns>
	SDL_Window* get();



private:

	Pos2N m_size;

	SDL_Window* m_window;

	WindowData m_winData;

	std::shared_ptr<spdlog::logger> m_logger;
};


#endif



