#ifndef _garbage_engine
#define _garbage_engine

#include "GarbageSDK.h"
#include <glad/glad.h>

#include "Window.h"
#include "Clock.h"
#include "GarbageEvent.h"

namespace garbage
{

	class GSDK GarbageEngine
	{
	public:

		GarbageEngine();
		~GarbageEngine();

		void InitializeOpenGL();

		void BindOnStartEvent(void (*ev)());
		void BindOnUpdateEvent(void (*ev)());

		void Run();

	private:

		Window* m_window = nullptr;
		Clock m_updateClock;

		GarbageEvent m_startEvents;
		GarbageEvent m_updateEvents;

		bool m_openGLInitialized = false;

		void Update();
		void Render();

	};

}

#endif