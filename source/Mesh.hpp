#pragma once
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"

class Mesh
{
public:

    Mesh(const std::vector<float>& vertices, const std::vector<GLuint>& indices);
    ~Mesh();
    void Draw();

private:

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    VAO m_VAO;
    VBO m_VBO;
    EBO m_EBO;

    void SetupMesh();

};