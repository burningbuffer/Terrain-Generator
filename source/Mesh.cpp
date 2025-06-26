#include "Mesh.hpp"

Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
{
	this->vertices = vertices;
	this->indices = indices;

    SetupMesh();
}

Mesh::~Mesh()
{
    m_VAO.Delete();
    m_VBO.Delete();
    m_EBO.Delete();
}

void Mesh::Draw()
{
    m_VAO.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    m_VAO.Unbind();
}

void Mesh::SetupMesh()
{
	m_VAO.CreateVAO();
    m_VAO.Bind();

    m_VBO.CreateAndUploadVBO(vertices);
    //vertices.clear();
    m_VBO.Bind();

    m_EBO.CreateAndUploadEBO(indices);
    //indices.clear();
    m_EBO.Bind();

    //vao.LinkVBOattributes(vbo, 0, 6, 0);
    m_VAO.LinkVBOAttributes(m_VBO, 0, 3, 6, 0);
    m_VAO.LinkVBOAttributes(m_VBO, 1, 3, 6, 3);

    m_VAO.Unbind();
    m_VBO.Unbind();
    m_EBO.Unbind();
}
