#pragma once
#include "Mesh.hpp"
#include "Array2d.hpp"

class Terrain
{
public:
    Terrain();
    ~Terrain();
    
    void SetTerrainScale(float scale);
    float GetTerrainScale() const;
    float GetHeight(int x, int z) const;

    void LoadHeightMapFlat(size_t size);
    void LoadHeightMapFromFile(const char* fileName);
    
    void InitTerrainMesh();
    void PrintHeightMapArray();
    void SetTerrainSize(size_t size);
    void Draw(Shader shader);

protected:

    int m_TerrainSize = 0;
    int m_TerrainScale = 0;
    Mesh m_TerrainMesh;
    Array2d m_HeightMap;
    
};