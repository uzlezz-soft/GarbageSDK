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
		void BindOnRenderEvent(void (*ev)(Window*));

		void Run();

	private:

		Window* m_window = nullptr;
		Clock m_updateClock;

		GarbageEvent m_startEvents;
		GarbageEvent m_updateEvents;
		GarbageEventP<Window*> m_renderEvents;
		
		bool m_openGLInitialized = false;

		void Update();
		void Render();

		float vertices[32] = 
		{
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};

		unsigned int indices[6] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;

	};

}

#endif