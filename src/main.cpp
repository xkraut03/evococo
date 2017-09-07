// main.cpp
// author: Daniel Kraut
// creation date: 30th of July, 2017

#include <iostream>

int main(int argc, char const *argv[])
{
    ComponentEvolver median_filter_evolver;
    median_filter_evolver.addImages("../images/barbara.bmp", "../images/barbara_noise.bmp");
    median_filter_evolver.evolve();
    median_filter_evolver.filterOriginalImageToFile("../images/barbara_cleared.bmp");
    
    std::cout << "Let's evolve something!" << '\n';
    return 0;
}
