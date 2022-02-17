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

void garbage::GarbageEngine::BindOnStartedEvent(void(*ev)())
{
	m_startEventHandler = ev;
}

void garbage::GarbageEngine::BindOnUpdateEvent(void(*ev)(float))
{
	m_updateEventHandler = ev;
}

void garbage::GarbageEngine::Run()
{
	WindowContext context;

	m_window = new Window(context);
	m_window->Initialize();

	m_updateTimer.Restart();

	if (m_startEventHandler) m_startEventHandler();

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
	}
}

void garbage::GarbageEngine::Update()
{
	float deltaTime = m_updateTimer.Restart();
	//std::cout << "Delta time from last frame: " << deltaTime << std::endl;

	// Update ...
	glfwPollEvents();

	if (m_updateEventHandler) m_updateEventHandler(deltaTime);

	m_window->Render();
}