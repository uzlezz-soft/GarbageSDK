#ifndef _garbage_engine
#define _garbage_engine

#include "GarbageSDK.h"
#include <glad/glad.h>

#include "Window.h"
#include "Timer.h"

namespace garbage
{

	class GSDK GarbageEngine
	{
	public:

		GarbageEngine();
		~GarbageEngine();

		void InitializeOpenGL();

		void BindOnStartedEvent(void(*ev)());
		void BindOnUpdateEvent(void(*ev)(float));

		void Run();

	private:

		Window* m_window = nullptr;
		Timer m_updateTimer;

		void (*m_startEventHandler)();
		void (*m_updateEventHandler)(float);

		bool m_openGLInitialized = false;

		void Update();

	};

}

#endif