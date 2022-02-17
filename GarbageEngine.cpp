#include "GarbageEngine.h"
#include <iostream>

#include "Shader.h"

garbage::GarbageEngine::GarbageEngine()
{
	glfwInit();
}

garbage::GarbageEngine::~GarbageEngine()
{
	delete m_window;
}

void garbage::GarbageEngine::InitializeOpenGL()
{
	if (!m_openGLInitialized)
	{
		if (gladLoadGL())
		{
			throw std::exception("Can't initialize OpenGL!");
		}

		m_openGLInitialized = true;
	}
}

void garbage::GarbageEngine::BindOnStartEvent(void(*ev)())
{
	m_startEvents.Bind(ev);
}

void garbage::GarbageEngine::BindOnUpdateEvent(void(*ev)())
{
	m_updateEvents.Bind(ev);
}

void garbage::GarbageEngine::Run()
{
	WindowContext context;

	m_window = new Window(context);
	m_window->Initialize();

	m_updateClock.Restart();

	m_startEvents.Invoke();

	Shader shader;
	switch (shader.LoadFromMasterFile("master.gbs", garbage::MSP_DiffuseMap))
	{
	case ALR_Success:
		std::cout << "Success" << std::endl;
		break;
	default:
		std::cout << "Can't load shader!" << std::endl;
		return;
		break;
	}

	shader.SetMaxNumberOfPointLights(4);
	shader.Compile();

	while (m_window->Opened())
	{
		Update();
		Render();
	}
}

void garbage::GarbageEngine::Update()
{
	float deltaTime = m_updateClock.Restart();
	//std::cout << "Delta time from last frame: " << deltaTime << std::endl;

	// Update ...
	glfwPollEvents();

	m_updateEvents.Invoke();
}

void garbage::GarbageEngine::Render()
{
	m_window->Render();
}