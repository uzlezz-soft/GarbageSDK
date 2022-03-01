#ifndef _garbage_window
#define _garbage_window

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GarbageSDK.h"
#include "WindowContext.h"

namespace garbage
{

	class GSDK Window
	{
	public:

		Window(WindowContext Context);
		~Window();

		bool Initialize();
		void Close();
		void Render();

		inline bool Opened();

		void SetTitle(std::string title);

		void GL_SwapBuffers();

	private:

		WindowContext m_context;
		GLFWwindow* m_window;

		void Clear();
		
		void GL_MakeCurrent();

	};

}

#endif