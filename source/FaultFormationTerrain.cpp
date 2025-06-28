#include "FaultFormationTerrain.hpp"
#include <random>

FaultFormationTerrain::FaultFormationTerrain()
{
}

FaultFormationTerrain::~FaultFormationTerrain(){}

void FaultFormationTerrain::CreateFaultFormationTerrain(float numOfIterations, float filter, float minHeight, float maxHeight)
{

    float deltaHeight = maxHeight - minHeight;
    
    for(int i = 0; i < numOfIterations; i++)
    {
        float newHeight = maxHeight - ( ( maxHeight-minHeight )*i)/numOfIterations;

        Line line = GenerateRandomLine();
        glm::vec2 random = glm::vec2{line.p2 - line.p1};

        for(int x = 0; x < m_TerrainSize; x++)
        {
            for(int z = 0; z < m_TerrainSize; z++) 
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
}

void FaultFormationTerrain::ApplyFIRFilter()
{

}

FaultFormationTerrain::Line FaultFormationTerrain::GenerateRandomLine()
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, m_TerrainSize - 1);

    int x1 = dist(rng);
    int z1 = dist(rng);

    int x2 = dist(rng);
    int z2 = dist(rng);

    if(x1 == x2 && z1 == z2)
        return GenerateRandomLine();
    
    glm::vec2 p1 = glm::vec2{x1, z1};
    glm::vec2 p2 = glm::vec2{x2, z2};
    Line line;
    line.CreateLine(p1,p2);
    return line;
}
