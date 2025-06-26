#include "VBO.hpp"

VBO::VBO(){}

VBO::~VBO()
{
    Delete();
}

void VBO::CreateAndUploadVBO(const std::vector<GLfloat>& vertices)
{
    glGenBuffers(1, &m_ID);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
}

void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
    glDeleteBuffers(1, &m_ID);
}
