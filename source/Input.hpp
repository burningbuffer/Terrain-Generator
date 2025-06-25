#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Context;

void ProcessInput(GLFWwindow* window);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
