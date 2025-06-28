#include "Terrain.hpp"
#include "Shader.hpp"
#include <iostream>

Terrain::Terrain(){}

Terrain::~Terrain(){}

void Terrain::SetTerrainScale(float scale)
{
    m_TerrainScale = scale;
}

float Terrain::GetTerrainScale() const
{
    return m_TerrainScale;
}

float Terrain::GetHeight(int x, int z) const
{
    return m_HeightMap.Get(x, z);
}

void Terrain::LoadHeightMapFlat(size_t size)
{
    m_TerrainSize = size;
    m_HeightMap.InitArray(m_TerrainSize, m_TerrainSize, 0.0f);
}

void Terrain::LoadHeightMapFromFile(const char* fileName)
{
    FILE *file;
    
    fopen_s(&file, fileName,"rb+");

    if(file == NULL)
    {
        std::cout << "ERROR: loading the file\n";
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    unsigned char* pData = (unsigned char*) malloc(size);

    size_t bytes_read = fread(pData, 1, size, file);

    if(bytes_read != size)
    {
        std::cout << "ERROR: bytes_read != file size\n";
        exit(0);
    }

    fclose(file);

    m_TerrainSize = std::sqrtf(size / sizeof(float));
    m_HeightMap.InitArray(m_TerrainSize, m_TerrainSize, pData);

}

void Terrain::InitTerrainMesh()
{
    m_TerrainMesh.InitMesh(this, m_TerrainSize, m_TerrainSize);
}

void Terrain::PrintHeightMapArray()
{
    m_HeightMap.PrintArray();
}

void Terrain::SetTerrainSize(size_t size)
{
    m_TerrainSize = size;
}

void Terrain::Draw(Shader shader)
{
    shader.useShader();
    m_TerrainMesh.Draw();
}
 