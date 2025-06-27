#pragma once
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Shader.hpp"

class Terrain;

struct Vertex
{
    glm::vec3 Pos;

    void InitVertex(const Terrain *pTerrain, int x, int z);
};

class Mesh
{
public:

    Mesh();
    ~Mesh();
    void InitMesh(const Terrain *pTerrain,int width, int depth);
    void Draw();

private:

    void FillVertices(const Terrain *pTerrain);
    void FillIndices();
    
    void CreateVAO();
    void LinkVBOAttributes(GLuint VBO, GLuint layout, int numOfComponents, int lineSize, int offset);
    void BindVAO();
    void UnbindVAO();

    void CreateAndUploadVBO();
    void BindVBO();
    void UnbindVBO();

    void CreateAndUploadEBO();
    void BindEBO();
    void UnbindEBO();

    void FillBuffers();

    std::vector<Vertex> m_Vertices;
    std::vector<GLuint> m_Indices;

    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
   
    int m_Width = 0;
    int m_Depth = 0;

};