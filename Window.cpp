#include "Window.h"

garbage::Window::Window(garbage::WindowContext Context)
{
	m_context = Context;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_context.OpenGLMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_context.OpenGLMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, m_context.Resizable);
	glfwWindowHint(GLFW_REFRESH_RATE, m_context.RefreshRate);
}

garbage::Window::~Window()
{
	glfwDestroyWindow(m_window);
}

bool garbage::Window::Initialize()
{
	m_window = glfwCreateWindow(m_context.Width, m_context.Height, m_context.Title.c_str(), NULL, NULL);
	GL_MakeCurrent();

	static bool gladLoaded = false;

	if (!gladLoaded)
	{
		gladLoadGL();
		gladLoaded = true;
	}

	if (m_context.DepthTest)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	if (m_context.BackFaceCulling)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	switch (m_context.PolygonMode)
	{
	case WindowContext::PM_Point:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	}
	case WindowContext::PM_Line:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	}
	case WindowContext::PM_Fill:
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
	default:
		break;
	}

	if (m_window == NULL)
	{
		glfwTerminate();
		return false;
	}

	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwGetFramebufferSize(m_window, &framebufferWidth, &framebufferHeight);
	glViewport(0, 0, framebufferWidth, framebufferHeight);

	return true;
}

void garbage::Window::Close()
{
	glfwSetWindowShouldClose(m_window, true);
}

void garbage::Window::Render()
{
	Clear();

	//GL_SwapBuffers();
}

void garbage::Window::SetTitle(std::string title)
{
	GL_MakeCurrent();

	glfwSetWindowTitle(m_window, title.c_str());
}

bool garbage::Window::Opened()
{
	return !glfwWindowShouldClose(m_window);
}

void garbage::Window::Clear()
{
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void garbage::Window::GL_SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void garbage::Window::GL_MakeCurrent()
{
	glfwMakeContextCurrent(m_window);
}