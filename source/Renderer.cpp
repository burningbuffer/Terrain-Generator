#include "Renderer.hpp"
#include "DiamondSquareTerrain.hpp"
#include "FaultFormationTerrain.hpp"
#include "Input.hpp"
#include "Shader.hpp"
#include "Terrain.hpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <iostream>

Renderer::Renderer()
{
    if (!Init())
    {
        std::cerr << "Error initializing renderer\n";
    }

    ShowVendor();
}

Renderer::~Renderer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_Context.window);
    glfwTerminate();
}

bool Renderer::Init()
{
    glm::vec3 cameraPos   = glm::vec3(-100.0f, +400.0f, -100.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraFront = glm::vec3(0.0, 0.0, 0.0);

    m_Context.camera = Camera(cameraPos, cameraUp, cameraFront);

    if (!glfwInit())
    {
        std::cerr << "Error initializing GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Context.window = glfwCreateWindow(m_Context.width, m_Context.height, "Terrain Generator", nullptr, nullptr);

    if (!m_Context.window)
    {
        std::cerr << "Error creating window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Context.window);
    glfwSwapInterval(1);
    glfwSetInputMode(m_Context.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(m_Context.window, MouseCallback);
    glfwSetWindowUserPointer(m_Context.window, &m_Context);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Error initializing GLEW\n";
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiStyle& style                       = ImGui::GetStyle();
    style.Colors[ImGuiCol_Border]           = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TitleBg]          = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive]    = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_FrameBg]          = ImVec4(0.2f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab]       = ImVec4(0.6f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.6f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_Button]           = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered]    = ImVec4(0.6f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive]     = ImVec4(0.6f, 0.0f, 0.0f, 1.0f);

    ImGui_ImplGlfw_InitForOpenGL(m_Context.window, true);

    ImGui_ImplOpenGL3_Init("#version 450");

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
    float minHeight  = 0;
    float maxHeight  = 300.f;
    int terrainWidth = 256;
    int terrainDepth = 256;

    int iterations = 500;
    float filter   = 0.6f;
    float scale    = 4;

    float roughness = 0.5f;

    DiamondSquareTerrain terrain;
    terrain.SetTerrainScale(scale);
    terrain.SetTerrainSize(terrainWidth, terrainDepth);
    terrain.LoadHeightMapFlat();
    terrain.CreateDiamondSquareTerrain(roughness, minHeight, maxHeight);
    terrain.InitTerrainMesh();

    Shader shader{"shaders/vs.glsl", "shaders/fs.glsl"};

    glm::mat4 model      = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), static_cast<float>(m_Context.width / m_Context.height), 0.1f, 2000.0f);

    while (!glfwWindowShouldClose(m_Context.window))
    {
        float currentFrame  = static_cast<float>(glfwGetTime());
        m_Context.deltaTime = currentFrame - m_Context.lastFrame;
        m_Context.lastFrame = currentFrame;

        ProcessInput(m_Context.window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Terrain");

        ImGui::SliderInt("Iterations", &iterations, 0, 1000);
        ImGui::SliderFloat("MaxHeight", &maxHeight, 0.0f, 600.0f);
        ImGui::SliderFloat("Erosion Factor", &filter, 0.0f, 1.0f);
        ImGui::SliderInt("Terrain Width", &terrainWidth, 10.0f, 1000.0f);
        ImGui::SliderInt("Terrain Depth", &terrainDepth, 10.0f, 1000.0f);
        ImGui::SliderFloat("Terrain Scale", &scale, 1.0f, 10.0f);
        ImGui::SliderFloat("Terrain Roughness", &roughness, 0.1f, 1.5f);

        if (ImGui::Button("Generate"))
        {
            terrain.Clean();
            terrain.SetTerrainScale(scale);
            terrain.SetTerrainSize(terrainWidth, terrainDepth);
            terrain.LoadHeightMapFlat();
            terrain.CreateDiamondSquareTerrain(roughness, minHeight, maxHeight);
            terrain.InitTerrainMesh();
        }

        ImGui::End();

        ImGui::Render();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = m_Context.camera.GetViewMatrix();

        shader.useShader();
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        terrain.Draw(shader);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_Context.window);
        glfwPollEvents();
    }

    shader.deleteShader();
}
