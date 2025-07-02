#include "FaultFormationTerrain.hpp"
#include <random>

FaultFormationTerrain::FaultFormationTerrain(){}

FaultFormationTerrain::~FaultFormationTerrain(){}

void FaultFormationTerrain::CreateFaultFormationTerrain(float numOfIterations, float filter, float minHeight, float maxHeight)
{
    filter = std::clamp(filter, 0.0f, 1.0f);

    for(int i = 0; i < numOfIterations; i++)
    {
        float newHeight = maxHeight - ( ( maxHeight-minHeight )*i)/numOfIterations;

        Line line = GenerateRandomLine();
        glm::vec2 random = glm::vec2{line.p2 - line.p1};

        for(int z = 0; z < m_TerrainDepth; z++)
        {
            for(int x = 0; x < m_TerrainWidth; x++) 
            {
                glm::vec2 RandomToIndexVector = glm::vec2{glm::vec2{x, z} - line.p1};
                if(random.x * RandomToIndexVector.y - random.y * RandomToIndexVector.x > 0)
                {
                    float lastHeight = m_HeightMap.Get(x, z);
                    m_HeightMap.Set(lastHeight + newHeight, x, z);
                }
            }
        }
    }

    m_HeightMap.Normalize(minHeight, maxHeight);

    FilterTerrain(filter);

    
}

void FaultFormationTerrain::FilterTerrain(float filter)
{ 
    for(int z = 0; z <  m_TerrainDepth; z++)
    {
        float prevVal = m_HeightMap.Get(0, z);
        for(int x = 0; x < m_TerrainWidth; x++) 
        {
            prevVal = ApplyFIRFilter(x, z, prevVal, filter);
        }
    }

    for(int x = 0; x < m_TerrainWidth; x++)
    {
        float prevVal = m_HeightMap.Get(x, 0);
        for(int z = 0; z < m_TerrainDepth; z++) 
        {
            prevVal = ApplyFIRFilter(x, z, prevVal, filter);
        }
    }

}

float FaultFormationTerrain::ApplyFIRFilter(int x, int z, float lastVal, float filter)
{
    float curVal = m_HeightMap.Get(x, z);
    float newVal = filter * lastVal + (1.0f - filter) * curVal;
    m_HeightMap.Set(newVal, x, z);
    return newVal;
}

FaultFormationTerrain::Line FaultFormationTerrain::GenerateRandomLine()
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distX(0, m_TerrainDepth - 1);
    std::uniform_int_distribution<int> distZ(0, m_TerrainWidth - 1);

    int x1 = distX(rng);
    int z1 = distZ(rng);

    int x2 = distX(rng);
    int z2 = distZ(rng);

    if(x1 == x2 && z1 == z2)
        return GenerateRandomLine();
    
    glm::vec2 p1 = glm::vec2{x1, z1};
    glm::vec2 p2 = glm::vec2{x2, z2};
    Line line;
    line.CreateLine(p1,p2);
    return line;
}
