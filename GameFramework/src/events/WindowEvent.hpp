#ifndef EVENTS_WINDOWEVENT_HPP_
#define EVENTS_WINDOWEVENT_HPP_




#include "events/IEvent.hpp"




class WindowEvent : public IEvent<WindowEvent>
{
public:

	enum struct Action { CLOSE, RESIZE, MINIMIZED, MAXIMIZED };



	WindowEvent(unsigned int widthIn, unsigned int heightIn, Action typeIn)
		: m_width(widthIn), m_height(heightIn), m_type(typeIn) {}



	unsigned int width() const { return m_width; }



	unsigned int height() const { return m_height; }



	Action action() const { return m_type; }



protected:

	unsigned int m_width, m_height;
	Action m_type;
};


#endif /* EVENTS_WINDOWEVENT_HPP_ */



