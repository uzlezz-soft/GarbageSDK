#include "Timer.h"

garbage::Timer::Timer()
{
	m_lastTime = glfwGetTime();
}

float garbage::Timer::Restart()
{
	float time = glfwGetTime();
	m_elapsedTime = time - m_lastTime;
	m_lastTime = time;

	return m_elapsedTime;
}

float garbage::Timer::GetElapsedTime()
{
	return m_elapsedTime;
}