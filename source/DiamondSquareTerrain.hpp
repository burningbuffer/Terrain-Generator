#pragma once
#include "Terrain.hpp"
#include <glm/glm.hpp>
#include <random>

class DiamondSquareTerrain : public Terrain 
{
public:
    DiamondSquareTerrain();
    ~DiamondSquareTerrain();

    void CreateDiamondSquareTerrain(float roughness, float minHeight, float maxHeight);

private:
    void DiamondSquare(int currentSize, float roughness, float currentHeight);
    void DiamondStep(int currentSize, float currentHeight);
    void SquareStep(int currentSize, float currentHeight);
    void FilterTerrain(float filter);
    float ApplyFIRFilter(int x, int z, float lastVal, float filter);
};