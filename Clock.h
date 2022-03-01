#ifndef _garbage_clock
#define _garbage_clock

#include "GarbageSDK.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace garbage
{

	class GSDK Clock
	{
	public:

		Clock();

		float Restart();
		inline float GetElapsedTime();

	private:

		float m_lastTime = 0;
		float m_elapsedTime = 0;

	};

}

#endif