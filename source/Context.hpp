#pragma once

#include "Camera.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Context
{
    const int width  = 1300;
    const int height = 731;

    GLFWwindow* window = nullptr;
    Camera camera;

    float deltaTime;
    float lastFrame;

    bool firstMouse = true;
    bool imguiMode  = true;
    bool mouseFlag  = false;

    float lastX = width / 2.0f;
    float lastY = height / 2.0f;
};