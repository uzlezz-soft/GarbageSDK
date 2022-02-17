#ifndef _garbage_engine
#define _garbage_engine

#include "GarbageSDK.h"
#include <glad/glad.h>

#include "Window.h"
#include "Timer.h"
#include "GarbageEvent.h"

namespace garbage
{

	class GSDK GarbageEngine
	{
	public:

		GarbageEngine();
		~GarbageEngine();

		void InitializeOpenGL();

		void BindOnStartedEvent(void (*ev)());
		void BindOnUpdateEvent(void (*ev)());

		void Run();

	private:

		Window* m_window = nullptr;
		Timer m_updateTimer;

		GarbageEvent m_startEvents;
		GarbageEvent m_updateEvents;

		bool m_openGLInitialized = false;

		void Update();

	};

}

#endif