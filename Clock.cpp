#include "Clock.h"

garbage::Clock::Clock()
{
	m_lastTime = glfwGetTime();
}

float garbage::Clock::Restart()
{
	float time = glfwGetTime();
	m_elapsedTime = time - m_lastTime;
	m_lastTime = time;

	return m_elapsedTime;
}

float garbage::Clock::GetElapsedTime()
{
	return m_elapsedTime;
}