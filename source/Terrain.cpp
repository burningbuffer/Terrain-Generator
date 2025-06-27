#include "Terrain.hpp"
#include "Shader.hpp"
#include <iostream>

Terrain::Terrain(){}

Terrain::~Terrain()
{
}

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

void Terrain::LoadHeightMapFromFile(const char* fileName)
{
    FILE *file;
    
    fopen_s(&file, fileName,"rb+");

    if(file == NULL)
    {
        std::cout << "ERROR loading the file\n";
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    unsigned char* pData = (unsigned char*) malloc(size);

    size_t bytes_read = fread(pData, 1, size, file);

    if(bytes_read != size)
    {
        std::cout << "ERROR bytes_read != file size\n";
        exit(0);
    }

    fclose(file);

    m_TerrainSize = std::sqrtf(size / sizeof(float));

    std::cout << "STEP1" << std::endl;
    m_HeightMap.InitArray(m_TerrainSize, m_TerrainSize, pData);
    std::cout << "STEP2" << std::endl;
    m_TerrainMesh.InitMesh(this, m_TerrainSize, m_TerrainSize);
    std::cout << "STEP3" << std::endl;
}

void Terrain::Draw(Shader shader)
{
    shader.useShader();
    m_TerrainMesh.Draw();
}
 