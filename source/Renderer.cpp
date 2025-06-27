#include "Renderer.hpp"
#include <glm/glm.hpp>
#include <memory>
#include "Shader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Input.hpp"
#include <stdexcept>
#include <vector>
#include "Terrain.hpp"

Renderer::Renderer()
{
    if (!Init())
    {
        std::cerr << "Error initializing renderer\n";
    }

    ShowVendor();
}

Renderer::~Renderer() {}

bool Renderer::Init() 
{
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, +10.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    
    m_Context.camera = Camera(cameraPos, cameraUp, cameraFront);

    if (!glfwInit())
    {
        std::cerr << "Error initializing GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Context.window = glfwCreateWindow(m_Context.width, m_Context.height, "Demo", nullptr, nullptr);

    if (!m_Context.window)
    {
        std::cerr << "Error creating the window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Context.window);
    glfwSwapInterval(1);
    glfwSetCursorPosCallback(m_Context.window, MouseCallback);
    glfwSetInputMode(m_Context.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(m_Context.window, &m_Context);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Error initializing GLEW\n";
        glfwTerminate();
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    return true;
}

void Renderer::ShowVendor()
{
    GLint GLMajorVersion = 0;
    GLint GLMinorVersion = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &GLMinorVersion);
    std::cout << "OpenGL Version  : " << GLMajorVersion << "." << GLMinorVersion << std::endl;
    std::cout << "OpenGL Vendor   : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Renderer : " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version  : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version    : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void Renderer::Run()
{
    Terrain terrain;
    terrain.SetTerrainScale(3);
    terrain.LoadHeightMapFromFile("data/heightmap.save");

    Shader shader{"shaders/vs.glsl", "shaders/fs.glsl"};

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 1000.0f);

    while (!glfwWindowShouldClose(m_Context.window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        m_Context.deltaTime = currentFrame -  m_Context.lastFrame;
        m_Context.lastFrame = currentFrame;

        ProcessInput(m_Context.window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = m_Context.camera.GetViewMatrix();

        shader.useShader();
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        terrain.Draw(shader);

        glfwSwapBuffers(m_Context.window);
        glfwPollEvents();
    }

    shader.deleteShader();
    glfwDestroyWindow(m_Context.window);
    glfwTerminate();
}
