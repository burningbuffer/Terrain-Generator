#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Context.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Init();
	void Run();
	void ShowVendor();
private:
    Context m_Context;
};