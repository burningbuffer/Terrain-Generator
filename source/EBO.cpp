#include "EBO.hpp"

EBO::EBO(){}

EBO::~EBO()
{
    Delete();
}

void EBO::CreateAndUploadEBO(const std::vector<GLuint>& indices)
{
    glGenBuffers(1, &m_ID);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}

void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
    glDeleteBuffers(1, &m_ID);
}

