#include "DiamondSquareTerrain.hpp"

DiamondSquareTerrain::DiamondSquareTerrain()
{
}

DiamondSquareTerrain::~DiamondSquareTerrain()
{
}

void DiamondSquareTerrain::CreateDiamondSquareTerrain(float roughness, float minHeight, float maxHeight)
{
    int currentSize     = m_TerrainDepth;
    float currentHeight = m_TerrainDepth / 2.0f;

    DiamondSquare(currentSize, roughness, currentHeight);

    m_HeightMap.Normalize(minHeight, maxHeight);

    FilterTerrain(0.5f);
}

void DiamondSquareTerrain::DiamondSquare(int currentSize, float roughness, float currentHeight)
{
    while (currentSize > 1)
    {

        DiamondStep(currentSize, currentHeight);

        SquareStep(currentSize, currentHeight);

        currentSize /= 2;
        currentHeight *= glm::pow(2, -roughness);
    }
}

void DiamondSquareTerrain::DiamondStep(int currentSize, float currentHeight)
{
    int halfSize = currentSize / 2;

    for (int z = 0; z < m_TerrainDepth; z += currentSize)
    {
        for (int x = 0; x < m_TerrainWidth; x += currentSize)
        {
            int nextX = (x + currentSize) % m_TerrainSize;
            int nextZ = (z + currentSize) % m_TerrainSize;

            float topLeft     = m_HeightMap.Get(x, z);
            float topRight    = m_HeightMap.Get(nextX, z);
            float bottomLeft  = m_HeightMap.Get(x, nextZ);
            float bottomRight = m_HeightMap.Get(nextX, nextZ);

            int midPointX = (x + halfSize);
            int midPointZ = (z + halfSize);

            float averageVal = ((topLeft + topRight + bottomLeft + bottomRight) / 4.0f);
            float finalVal   = averageVal + RandomInterval(-currentHeight, +currentHeight);

            m_HeightMap.Set(finalVal, midPointX, midPointZ);
        }
    }
}

void DiamondSquareTerrain::SquareStep(int currentSize, float currentHeight)
{
    int halfSize = currentSize / 2;

    for (int z = 0; z < m_TerrainDepth; z += currentSize)
    {
        for (int x = 0; x < m_TerrainWidth; x += currentSize)
        {
            int nextX = (x + currentSize) % m_TerrainSize;
            int nextZ = (z + currentSize) % m_TerrainSize;

            int midX = (x + halfSize);
            int midZ = (z + halfSize);

            int prevMidX = (x - halfSize + m_TerrainSize) % m_TerrainSize;
            int prevMidZ = (z - halfSize + m_TerrainSize) % m_TerrainSize;

            float currTopLeft  = m_HeightMap.Get(x, z);
            float currTopRight = m_HeightMap.Get(nextX, z);
            float currBotLeft  = m_HeightMap.Get(x, nextZ);

            float currCenter   = m_HeightMap.Get(midX, midZ);
            float prevYCenter  = m_HeightMap.Get(midX, prevMidZ);
            float prevXCenter  = m_HeightMap.Get(prevMidX, midZ);

            // Left Edge Midpoint (x, midZ)
            float currLeftMid = (currTopLeft + currCenter + currBotLeft + prevXCenter) / 4.0f + RandomInterval(-currentHeight, +currentHeight);
            
            // Top Edge Midpoint (midX, z)
            float currTopMid  = (currTopLeft + currCenter + currTopRight + prevYCenter) / 4.0f + RandomInterval(-currentHeight, +currentHeight);

            m_HeightMap.Set(currTopMid, midX, z);
            m_HeightMap.Set(currLeftMid, x, midZ);
        }
    }
}
