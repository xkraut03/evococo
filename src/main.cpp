// main.cpp
// author: Daniel Kraut
// creation date: 30th of July, 2017

#include <iostream>

#include "ComponentEvolver.hpp"

int main(int argc, char const *argv[])
{
    if (argc <= 1)
    {
        std::cerr << "Too few arguments\n";
        return -1;
    }
    std::cout << "Let's evolve something!" << '\n';

    ComponentEvolver median_filter_evolver;
    median_filter_evolver.addImages(argv[1], argv[2]);
    median_filter_evolver.evolve();
    median_filter_evolver.filterOriginalImageToFile("../images/barbara_cleared.bmp");

    return 0;
}
