#ifndef EVENTS_KEYBOARDEVENT_H_
#define EVENTS_KEYBOARDEVENT_H_

#include "events/IEvent.hpp"




class KeyboardEvent : public IEvent<KeyboardEvent>
{
public:

	enum struct Action { PRESS, RELEASE, REPEAT };



	KeyboardEvent(int keycodeIn, int scancodeIn, Action typeIn)
		: m_keycode(keycodeIn), m_scancode(scancodeIn), m_type(typeIn) 
	{};



	/// <summary>
	/// Gets the SDL "virtual" key code
	/// </summary>
	/// <returns></returns>
	int getKeyCode() const { return m_keycode; }



	/// <summary>
	/// Gets the key scan code ie. the physical key on the keyboard
	/// </summary>
	/// <returns></returns>
	int getScanCode() const { return m_scancode; }



	Action action() const { return m_type; }



protected:

	int m_keycode, m_scancode;

	Action m_type;
};


#endif /* EVENTS_KEYBOARDEVENT_H_ */



