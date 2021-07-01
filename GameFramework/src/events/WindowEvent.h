#ifndef IEVENT_H_
#define IEVENT_H_




#include "events/IEvent.hpp"




class WindowEvent : public IEvent<WindowEvent>
{
public:

	enum struct Action { CLOSE, RESIZE, MINIMIZED, MAXIMIZED };



	WindowEvent(unsigned int widthIn, unsigned int heightIn, Action typeIn)
		: m_width(widthIn), m_height(heightIn), m_type(typeIn) 
	{}



	/// <summary>
	/// Gets the current width of the window
	/// </summary>
	/// <returns></returns>
	unsigned int width() const { return m_width; }



	/// <summary>
	/// Gets the current height of the window
	/// </summary>
	/// <returns></returns>
	unsigned int height() const { return m_height; }



	/// <summary>
	/// Gets the window event type
	/// </summary>
	/// <returns></returns>
	Action action() const { return m_type; }



protected:

	unsigned int m_width, m_height;

	Action m_type;
};


#endif /* IEVENT_H_ */



