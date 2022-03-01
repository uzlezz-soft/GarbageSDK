#include "GarbageEngine.h"
#include <iostream>
#include "Shader.h"
#include "Texture.h"

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
		WindowContext context;
		context.PolygonMode = WindowContext::PM_Fill;

		m_window = new Window(context);
		m_window->Initialize();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);

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

void garbage::GarbageEngine::BindOnRenderEvent(void(*ev)(Window*))
{
	m_renderEvents.Bind(ev);
}

void garbage::GarbageEngine::Run()
{
	m_updateClock.Restart();

	Shader shader;
	shader.LoadFromFile("emmisive.gbs");
	shader.Compile();
	shader.Bind();

	shader.SetInt("tex", 1);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_startEvents.Invoke();

	while (m_window->Opened())
	{
		Update();
		Render();

		
		shader.Bind();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		
	}
}

void garbage::GarbageEngine::Update()
{
	float deltaTime = m_updateClock.Restart();
	//std::cout << "Delta time from last frame: " << deltaTime << std::endl;

	// Update ...
	glfwPollEvents();

	static int framesCount = 0;
	framesCount++;

	if (framesCount > 25)
	{
		m_window->SetTitle(std::string("FPS: ").append(std::to_string(1 / deltaTime)));
		framesCount = 0;
	}

	m_updateEvents.Invoke();
}

void garbage::GarbageEngine::Render()
{
	m_window->Render();

	m_renderEvents.Invoke(m_window);

	m_window->GL_SwapBuffers();
}
