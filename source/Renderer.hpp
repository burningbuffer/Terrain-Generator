#pragma once
#include "Context.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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