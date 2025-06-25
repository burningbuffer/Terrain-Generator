#include "Input.hpp"
#include "Camera.hpp"
#include "Context.hpp"
#include <iostream>

struct Context;

void ProcessInput(GLFWwindow* window)
{
    // TODO: study c++ cast differences
    Context* context = static_cast<Context*>(glfwGetWindowUserPointer(window));

    if (!context)
    {
        std::cout << "Failed to retrieve context in ProcessInput\n";
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        context->camera.ProcessKeyboard(FORWARD, context->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        context->camera.ProcessKeyboard(BACKWARD, context->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        context->camera.ProcessKeyboard(LEFT, context->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        context->camera.ProcessKeyboard(RIGHT, context->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    Context* context = static_cast<Context*>(glfwGetWindowUserPointer(window));

    if (!context)
    {
        std::cout << "Failed to retrieve context in MouseCallback\n";
        return;
    }

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (context->firstMouse)
    {
        context->lastX = xpos;
        context->lastY = ypos;
        context->firstMouse = false;
    }

    float xoffset = xpos - context->lastX;
    float yoffset = context->lastY - ypos;

    context->lastX = xpos;
    context->lastY = ypos;

    context->camera.ProcessMouseMovement(xoffset, yoffset);
}
