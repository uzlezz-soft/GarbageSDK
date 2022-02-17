#include "WindowContext.h"

garbage::WindowContext::WindowContext()
{
	OpenGLMajor = 3;
	OpenGLMinor = 3;

	RefreshRate = 60;

	Width = 1280;
	Height = 720;

	Fullscreen = false;
	Resizable = false;
	DepthTest = true;
	AlphaBlend = false;
	BackFaceCulling = true;

	PolygonMode = PM_Fill;

	Title = "G3DEngine window";
}