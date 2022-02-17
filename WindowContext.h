#ifndef _garbage_windowcontext
#define _garbage_windowcontext

#include "GarbageSDK.h"
#include <string>

namespace garbage
{

	class GSDK WindowContext
	{
	public:

		enum PolygonMode
		{
			PM_Point, PM_Line, PM_Fill
		};

		unsigned int OpenGLMajor;
		unsigned int OpenGLMinor;

		unsigned int RefreshRate;

		unsigned int Width;
		unsigned int Height;

		// TODO
		bool Fullscreen;
		bool Resizable;
		bool DepthTest;
		// TODO
		bool AlphaBlend;
		bool BackFaceCulling;

		PolygonMode PolygonMode;

		std::string Title;

		WindowContext();
	};

}

#endif