#ifndef MouseEvent_H_
#define MouseEvent_H_


#include "events/IEvent.hpp"




class MouseEvent : public IEvent<MouseEvent>
{
public:

	enum class Action { PRESS, RELEASE, MOVE, SCROLL };



	enum class Button { NONE, LEFT, MIDDLE, RIGHT, X1, X2 };



	MouseEvent(uint8_t buttonIn, int32_t xIn, int32_t yIn, Action typeIn)
		: m_buttoncode(buttonIn), m_x(xIn), m_y(yIn), m_type(typeIn)
	{};



	/// <summary>
	/// Gets the currently pressed mouse button
	/// </summary>
	/// <returns></returns>
	Button button() const;



	/// <summary>
	/// Gets the X coordinate of the mouse pointer relative to window
	/// <para>When the event type is scroll it will get the amount scrolled horizontally, positive to the right and negative to the left</para>
	/// </summary>
	/// <returns></returns>
	int x() const;



	/// <summary>
	/// Gets the Y coordinate of the mouse pointer relative to window
	/// <para>When the event type is scroll it will get the amount scrolled vertically, positive away from the user and negative towards the user</para>
	/// </summary>
	/// <returns></returns>
	int y() const;



	/// <summary>
	/// Gets the mouse event type
	/// </summary>
	/// <returns></returns>
	Action action() const;



protected:

	uint8_t m_buttoncode;

	int32_t m_x, m_y;

	Action m_type;
};


#endif /* MouseEvent_H_ */



