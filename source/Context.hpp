#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.hpp"

struct Context
{
    const int width = 800;
    const int height = 600;

    GLFWwindow* window = nullptr;
    Camera camera;
    float deltaTime;
    float lastFrame;

    bool firstMouse = true;

    float lastX = width / 2.0f;
    float lastY = height / 2.0f;
};