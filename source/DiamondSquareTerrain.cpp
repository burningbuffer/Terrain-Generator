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
}

void DiamondSquareTerrain::DiamondSquare(int currentSize, float roughness, float currentHeight)
{
    float CurHeight = (float)m_TerrainSize / 2.0f;

    while (currentSize > 1)
    {

        DiamondStep(currentSize, CurHeight);

        SquareStep(currentSize, CurHeight);

        currentSize /= 2;
        CurHeight *= glm::pow(2, -roughness);
    }

    FilterTerrain(0.5f);
}

void DiamondSquareTerrain::DiamondStep(int currentSize, float currentHeight)
{
    int halfSize = currentSize / 2;

    for (int z = 0; z < m_TerrainDepth; z += currentSize)
    {
        for (int x = 0; x < m_TerrainWidth; x += currentSize)
        {
            int next_x = (x + currentSize) % m_TerrainSize;
            int next_z = (z + currentSize) % m_TerrainSize;



            float topLeft     = m_HeightMap.Get(x, z);
            float topRight    = m_HeightMap.Get(next_x, z);
            float bottomLeft  = m_HeightMap.Get(x, next_z);
            float bottomRight = m_HeightMap.Get(next_x, next_z);

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
    int HalfSize = currentSize / 2;

    for (int z = 0; z < m_TerrainDepth; z += currentSize)
    {
        for (int x = 0; x < m_TerrainWidth; x += currentSize)
        {
            int next_x = (x + currentSize) % m_TerrainSize;
            int next_z = (z + currentSize) % m_TerrainSize;



            int mid_x = (x + HalfSize);
            int mid_z = (z + HalfSize);

            int prev_mid_x = (x - HalfSize + m_TerrainSize) % m_TerrainSize;
            int prev_mid_z = (z - HalfSize + m_TerrainSize) % m_TerrainSize;

            int next_mid_x = (mid_x + HalfSize + m_TerrainSize) % m_TerrainSize;
            int next_mid_z = (mid_z + HalfSize + m_TerrainSize) % m_TerrainSize;

            float currTopLeft  = m_HeightMap.Get(x, z);
            float currTopRight = m_HeightMap.Get(next_x, z);
            float currCenter   = m_HeightMap.Get(mid_x, mid_z);

            float prevYCenter = m_HeightMap.Get(mid_x, prev_mid_z);
            float nextYCenter = m_HeightMap.Get(mid_x, next_mid_z);

            float currBotLeft  = m_HeightMap.Get(x, next_z);
            float currBotRight = m_HeightMap.Get(next_x, next_z);

            float prevXCenter = m_HeightMap.Get(prev_mid_x, mid_z);
            float nextXCenter = m_HeightMap.Get(next_mid_x, mid_z);

            float currLeftMid = (currTopLeft + currCenter + currBotLeft + prevXCenter) / 4.0f + RandomInterval(-currentHeight, +currentHeight);
            float currTopMid  = (currTopLeft + currCenter + currTopRight + prevYCenter) / 4.0f + RandomInterval(-currentHeight, +currentHeight);

            float currRightMid  = (currTopRight + currCenter + currBotRight + nextXCenter) / 4.0f + RandomInterval(-currentHeight, +currentHeight);
            float currBottomMid = (currBotLeft + currCenter + currBotRight + nextYCenter) / 4.0f + RandomInterval(-currentHeight, +currentHeight);

            m_HeightMap.Set(currTopMid, mid_x, z);
            m_HeightMap.Set(currLeftMid, x, mid_z);

            m_HeightMap.Set(currRightMid, next_x, mid_z);
            m_HeightMap.Set(currBottomMid, mid_x, next_z);
        }
    }
}

void DiamondSquareTerrain::FilterTerrain(float filter)
{
    for (int z = 0; z < m_TerrainDepth; z++)
    {
        float prevVal = m_HeightMap.Get(0, z);
        for (int x = 0; x < m_TerrainWidth; x++)
        {
            prevVal = ApplyFIRFilter(x, z, prevVal, filter);
        }
    }

    for (int x = 0; x < m_TerrainWidth; x++)
    {
        float prevVal = m_HeightMap.Get(x, 0);
        for (int z = 0; z < m_TerrainDepth; z++)
        {
            prevVal = ApplyFIRFilter(x, z, prevVal, filter);
        }
    }
}

float DiamondSquareTerrain::ApplyFIRFilter(int x, int z, float lastVal, float filter)
{
    float curVal = m_HeightMap.Get(x, z);
    float newVal = filter * lastVal + (1.0f - filter) * curVal;
    m_HeightMap.Set(newVal, x, z);
    return newVal;
}
