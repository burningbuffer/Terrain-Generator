#pragma once
#include "Terrain.hpp"
#include <glm/glm.hpp>

class FaultFormationTerrain : public Terrain
{
public:
    FaultFormationTerrain();
    ~FaultFormationTerrain();
    void CreateFaultFormationTerrain(float numOfIterations, float filter, float min, float max);

private:
    struct Line
    {
    public:
        glm::vec2 p1;
        glm::vec2 p2;

        void CreateLine(glm::vec2 a, glm::vec2 b)
        {
            p1 = a;
            p2 = b;
        }

        void PrintLine()
        {
            std::cout << "p1 " << p1.x << " " << p1.y << std::endl;
            std::cout << "p2 " << p1.x << " " << p1.y << std::endl;
        }
    };

    Line GenerateRandomLine();
};
