#include "VAO.hpp"

VAO::VAO(){}

VAO::~VAO()
{
    Delete();
}

void VAO::CreateVAO()
{
    glGenVertexArrays(1, &m_ID);
}

void VAO::LinkVBOAttributes(VBO& VBO, GLuint layout, int numOfComponents, int lineSize, int offset)
{
    VBO.Bind();
    glVertexAttribPointer(layout, numOfComponents, GL_FLOAT, GL_FALSE, lineSize * sizeof(float), (void*)(offset*sizeof(float)));
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(m_ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &m_ID);
}
