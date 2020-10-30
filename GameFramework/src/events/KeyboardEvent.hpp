#ifndef EVENTS_KEYBOARDEVENT_HPP_
#define EVENTS_KEYBOARDEVENT_HPP_




#include "events/IEvent.hpp"




class KeyboardEvent : public IEvent<KeyboardEvent>
{
public:

	enum struct Action { PRESS, RELEASE, REPEAT };



	KeyboardEvent(int keycodeIn, int scancodeIn, Action typeIn)
		: m_keycode(keycodeIn), m_scancode(scancodeIn), m_type(typeIn) {};



	// @return Gets the SDL "virtual" key code
	int getKeyCode() const { return m_keycode; }



	// @returns Gets the key scan code ie. the physical key on the keyboard
	int getScanCode() const { return m_scancode; }



	Action action() const { return m_type; }



protected:

	int m_keycode, m_scancode;
	Action m_type;
};


#endif /* EVENTS_KEYBOARDEVENT_HPP_ */



