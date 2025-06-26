#pragma once

#include <GL/glew.h>
#include <vector>

class EBO
{
public:
    GLuint m_ID;
    EBO();
    ~EBO();
    void CreateAndUploadEBO(const std::vector<GLuint>& indices);
    void Bind();
    void Unbind();
    void Delete();

};