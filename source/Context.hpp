#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.hpp"

struct Context
{
    const int width = 1200;
    const int height = 900;

    GLFWwindow* window = nullptr;
    Camera camera;

    bool wireframe = false;

    float deltaTime;
    float lastFrame;

    bool firstMouse = true;
    bool imguiMode = true;
    bool mouseFlag = false;

    float lastX = width / 2.0f;
    float lastY = height / 2.0f;
};