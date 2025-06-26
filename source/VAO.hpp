#pragma once

#include <GL/glew.h>
#include "VBO.hpp"

class VAO
{
public:
    GLuint m_ID;
    VAO();
    ~VAO();
    void CreateVAO();
    void LinkVBOAttributes(VBO& VBO, GLuint layout, int numOfComponents, int lineSize, int offset);
    void Bind();
    void Unbind();
    void Delete();

};