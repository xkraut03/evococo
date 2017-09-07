// MedianFilterEvolution.cpp
// author: Daniel Kraut
// creation date: 7th of September, 2017

#include "MedianFilterEvolution.hpp"

#include "../lib/EasyBMP/EasyBMP.h"

MedianFilterEvolution::MedianFilterEvolution(const std::string& original_image_path, const std::string& noise_image_path)
{
        original_image_.ReadFromFile(original_image_path.c_str());
        noise_image_.ReadFromFile(noise_image_path.c_str());
}

using Population = int[20];
using Unit = int;

void generateFirstPopulation(Population& population)
{
    for (size_t i = 0; i < 20; ++i) {
        population[i] = i;
    }
}

Unit selectBestUnit(Population& population)
{
    return population[0];
}

void mutate(Unit& unit)
{
    unit = 42;
}

void generatePopulationFromParent(Unit parent, Population& population)
{
    for (auto& individual : population)
    {
        mutate(individual);
    }
}

void MedianFilterEvolution::evolve()
{
    Population population;
    generateFirstPopulation(population);
    Unit the_best_unit = selectBestUnit(population);
    std::cout << "The first best solution is: " << the_best_unit << "\n";

    for (int cycle = 0; cycle < number_of_generations; ++cycle)
    {
        generatePopulationFromParent(the_best_unit, population);
        the_best_unit = selectBestUnit(population);
    }

    std::cout << "The best at the end solution is: " << the_best_unit << "\n";
}
