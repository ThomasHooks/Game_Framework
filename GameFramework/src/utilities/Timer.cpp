#include <SDL.h>
#include <ctime>

#include "Timer.h"




Timer::Timer()
	: m_tickStart(0), m_stopped(true)
{}



void Timer::start() 
{
	m_stopped = false;
	m_tickStart = SDL_GetTicks();
}



void Timer::stop() 
{
	m_stopped = true;
	m_tickStart = 0;
}



float Timer::getSec() const 
{
	return getMil()/1000.0f;
}



unsigned int Timer::getMil() const 
{
	return m_stopped ? 0 : SDL_GetTicks() - m_tickStart;
}







