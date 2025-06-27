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
    void LoadHeightMapFromFile(const char* fileName);
    void Draw(Shader shader);

private:

    int m_TerrainSize = 0;
    int m_TerrainScale = 0;
    Mesh m_TerrainMesh;
    Array2d m_HeightMap;
    
};