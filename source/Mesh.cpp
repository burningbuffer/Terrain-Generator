#include "Mesh.hpp"
#include "Terrain.hpp"

Mesh::Mesh(){}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_EBO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
    m_Vertices.clear();
    m_Indices.clear();
}

void Mesh::InitMesh(const Terrain *pTerrain,int width, int depth)
{
    m_Width = width;
    m_Depth = depth;

    FillVertices(pTerrain);
    FillIndices();
    FillBuffers();

    
}

void Mesh::DeleteMesh()
{
    glDeleteBuffers(1, &m_EBO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
    m_Vertices.clear();
    m_Indices.clear();
}

void Mesh::FillVertices(const Terrain *pTerrain)
{
    m_Vertices.resize(m_Width * m_Depth);

    int Index = 0;
    for(int z = 0; z < m_Depth; z++)
    {
        for(int x = 0; x < m_Width; x++)
        {
            m_Vertices[Index].InitVertex(pTerrain, x, z);
            Index++;
        }
    }
}

void Vertex::InitVertex(const Terrain *pTerrain, int x, int z)
{
    float y = pTerrain->GetHeight(x, z); 
    float Scale = pTerrain->GetTerrainScale();
    Pos = glm::vec3(x * Scale, y, z * Scale);
}
 
void Mesh::FillIndices()
{
    int NumOfQuads = (m_Width - 1) * (m_Depth - 1);
    m_Indices.resize(NumOfQuads * 6);

    GLint Index = 0;

    for(int z = 0; z < m_Depth - 1; z++)
    {
        for(int x = 0; x < m_Width - 1; x++)
        {
            GLuint IndexBottomLeft = z * m_Width + x;
            GLuint IndexTopLeft = (z + 1) * m_Width + x;
            GLuint IndexTopRight = (z + 1) * m_Width + x + 1;
            GLuint IndexBottomRight = z * m_Width + x + 1;

            m_Indices[Index++] = IndexBottomLeft;
            m_Indices[Index++] = IndexTopLeft;
            m_Indices[Index++] = IndexTopRight;

            m_Indices[Index++] = IndexBottomLeft;
            m_Indices[Index++] = IndexTopRight;
            m_Indices[Index++] = IndexBottomRight;

        }
    }
}

void Mesh::FillBuffers()
{
    CreateVAO();
    BindVAO();

    CreateAndUploadVBO();
    BindVBO();

    CreateAndUploadEBO();
    BindEBO();

    LinkVBOAttributes(m_VBO, 0, 3, 3, 0);

    UnbindVAO();
    UnbindVBO();
    UnbindEBO();
}

void Mesh::CreateAndUploadVBO()
{
    glGenBuffers(1, &m_VBO);
    BindVBO();
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices[0]) * m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);
}

void Mesh::BindVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}

void Mesh::UnbindVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::CreateVAO()
{
    glGenVertexArrays(1, &m_VAO);
}

void Mesh::LinkVBOAttributes(GLuint VBO, GLuint layout, int numOfComponents, int lineSize, int offset)
{
    BindVBO();
    glVertexAttribPointer(layout, numOfComponents, GL_FLOAT, GL_FALSE, lineSize * sizeof(float), (void*)(offset*sizeof(float)));
    glEnableVertexAttribArray(layout);
    UnbindVBO();
}

void Mesh::BindVAO()
{
    glBindVertexArray(m_VAO);
}

void Mesh::UnbindVAO()
{
    glBindVertexArray(0);
}

void Mesh::CreateAndUploadEBO()
{
    glGenBuffers(1, &m_EBO);
    BindEBO();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), &m_Indices[0], GL_STATIC_DRAW);
}

void Mesh::BindEBO()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void Mesh::UnbindEBO()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Draw()
{
    BindVAO();
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
    UnbindVAO();
}
