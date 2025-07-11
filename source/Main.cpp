#include "Renderer.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));

    Renderer renderer{};
    try
    {
        renderer.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}