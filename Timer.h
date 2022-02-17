#ifndef _garbage_timer
#define _garbage_timer

#include "GarbageSDK.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace garbage
{

	class GSDK Timer
	{
	public:

		Timer();

		float Restart();
		inline float GetElapsedTime();

	private:

		float m_lastTime = 0;
		float m_elapsedTime = 0;

	};

}

#endif