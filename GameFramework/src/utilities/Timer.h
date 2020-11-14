#ifndef SRC_GAME_TIMER_H_
#define SRC_GAME_TIMER_H_


#include <stdint.h>


class Timer 
{
public:

	Timer();



	/// <summary>
	/// Starts this Timer that measures the number of ticks in milliseconds
	/// </summary>
	void start();



	/// <summary>
	/// Stops and resets this Timer
	/// </summary>
	void stop();



	/// <summary>
	/// Gets the number of seconds since this Timer was started
	/// </summary>
	/// <returns></returns>
	float getSec() const;



	/// <summary>
	/// Gets the number of ticks measured in milliseconds since this Timer was started
	/// </summary>
	/// <returns></returns>
	unsigned int getMil() const;



	/// <summary>
	/// Checks if this Timer is currently running
	/// </summary>
	/// <returns></returns>
	bool isRunning() const { return m_stopped; }



	operator float() const { return getSec(); }



private:

	unsigned int m_tickStart;

	bool m_stopped;
};


#endif



