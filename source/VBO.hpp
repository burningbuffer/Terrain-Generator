#pragma once
#include <GL/glew.h>
#include <vector>
class VBO 
{
public:
    GLuint m_ID;
    VBO();
    ~VBO();
    void CreateAndUploadVBO(const std::vector<GLfloat>& vertices);
    void Bind();
    void Unbind();
    void Delete();
};