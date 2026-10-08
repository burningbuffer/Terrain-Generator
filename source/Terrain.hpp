#pragma once
#include "Heightmap2d.hpp"
#include "Mesh.hpp"

class Terrain
{
public:
    Terrain();
    ~Terrain();

    void Clean();

    void SetTerrainScale(float scale);
    float GetTerrainScale() const;
    float GetHeight(int x, int z) const;

    float RandomInterval(float a, float b);
    int RandomInterval(int a, int b);

    void LoadHeightMapFlat();
    void LoadHeightMapFromFile(const char* fileName);

    void InitTerrainMesh();
    void PrintHeightMapArray();
    void SetTerrainSize(uint32_t width, uint32_t depth);
    void Draw(Shader shader);

protected:
    void FilterTerrain(float filter);
    float ApplyFIRFilter(int x, int z, float lastVal, float filter);
    int m_TerrainSize       = 0;
    uint32_t m_TerrainWidth = 0;
    uint32_t m_TerrainDepth = 0;
    int m_TerrainScale      = 0;
    Mesh m_TerrainMesh;
    Heightmap2d m_HeightMap;
};