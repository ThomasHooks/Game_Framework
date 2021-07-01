#ifndef WINDOW_H_
#define WINDOW_H_


#include <memory>
#include <string>

#include <SDL.h>

#include "utilities/Loggers.hpp"
#include "utilities/math/Pos2.hpp"




struct WindowData
{
	WindowData(const std::string& titleIn = "Name of Application", unsigned int widthIn = 640, unsigned int heightIn = 480)
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



	Window(Window &&other) = delete;



	Window(const Window &other) = delete;



	~Window();



	/// <summary>
	/// Updates this window should be called each frame
	/// </summary>
	void update();



	/// <summary>
	/// Destroies this window
	/// </summary>
	void shutdown();



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
	/// Exposes this window's SDL window
	/// </summary>
	/// <returns>A SDL_Window pointer or null if the window has not been initialized</returns>
	SDL_Window* get();



	/// <summary>
	/// <para>nullable</para>
	/// Exposes this window's SDL window
	/// </summary>
	/// <returns>A SDL_Window pointer or null if the window has not been initialized</returns>
	const SDL_Window* get() const;



	/// <summary>
	/// <para>nullable</para>
	/// Exposes this window's OpenGL context
	/// </summary>
	/// <returns></returns>
	SDL_GLContext getGlContext();



	/// <summary>
	/// <para>nullable</para>
	/// Exposes this window's OpenGL context
	/// </summary>
	/// <returns></returns>
	const SDL_GLContext getGlContext() const;



private:

	std::shared_ptr<spdlog::logger> m_logger;

	Pos2N m_size;

	SDL_Window* m_window;

	SDL_GLContext m_glContext;

	WindowData m_winData;

	bool m_destroyed = false;
};


#endif /* WINDOW_H_ */



