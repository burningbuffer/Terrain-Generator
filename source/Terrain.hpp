#pragma once
#include "Mesh.hpp"
#include "Array2d.hpp"

class Terrain
{
public:
    Terrain();
    ~Terrain();

    void Clean();
    
    void SetTerrainScale(float scale);
    float GetTerrainScale() const;
    float GetHeight(int x, int z) const;

    void LoadHeightMapFlat();
    void LoadHeightMapFromFile(const char* fileName);
    
    void InitTerrainMesh();
    void PrintHeightMapArray();
    void SetTerrainSize(uint32_t width, uint32_t depth);
    void Draw(Shader shader);

protected:

    int m_TerrainSize = 0;
    uint32_t m_TerrainWidth = 0;
    uint32_t m_TerrainDepth = 0;
    int m_TerrainScale = 0;
    Mesh m_TerrainMesh;
    Array2d m_HeightMap;
    
};