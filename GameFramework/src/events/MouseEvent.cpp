#include <SDL.h>

#include "MouseEvent.h"




MouseEvent::Button MouseEvent::button() const
{
	switch (m_buttoncode)
	{
	case SDL_BUTTON_LEFT:
		return Button::LEFT;

	case SDL_BUTTON_MIDDLE:
		return Button::MIDDLE;

	case SDL_BUTTON_RIGHT:
		return Button::RIGHT;

	case SDL_BUTTON_X1:
		return Button::X1;

	case SDL_BUTTON_X2:
		return Button::X2;

	default:
		return Button::NONE;
	}
}



int MouseEvent::x() const
{
	return m_x;
}



int MouseEvent::y() const
{
	return m_y;
}



MouseEvent::Action MouseEvent::action() const
{
	return m_type;
}



