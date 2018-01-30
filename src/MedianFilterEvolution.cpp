// MedianFilterEvolution.cpp
// author: Daniel Kraut
// creation date: 7th of September, 2017
//
// Copyright © 2017 Daniel Kraut
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <limits>

#include "MedianFilterEvolution.hpp"

#include "../lib/EasyBMP/EasyBMP.h"

#include "CGPCircuit.hpp"

MedianFilterEvolution::MedianFilterEvolution(const std::string& original_image_path, const std::string& noise_image_path)
: original_image_ {original_image_path}, noise_image_ {noise_image_path}
{}

void MedianFilterEvolution::evolve()
{
    Population population;
    generateRandomPopulation(population);
    Individual best_unit = selectBestUnit(population);

    for (int cycle = 0; cycle < num_generations; ++cycle)
    {
        if (cycle % 50 == 0)
            std::cout << "50th cycle\n";
        generatePopulationFromParent(best_unit, population);
        best_unit = selectBestUnit(population);
    }

    std::cout << "The best solution is: " << getFitness(best_unit) << "\n";
}

void MedianFilterEvolution::generateRandomPopulation(Population& population)
{
    for (auto& p : population)
        p.initRandomly();
}

MedianFilterEvolution::Individual MedianFilterEvolution::selectBestUnit(Population& population)
{
    int best_fitness = std::numeric_limits<int>::max();
    int best_index = 0;
    for (int i = 0; i < population_size; ++i)
    {
        if (int fitness = getFitness(population[i]) <= best_fitness)
        {
            best_fitness = fitness;
            best_index = i;
        }
    }

    return population[best_index];
}

void MedianFilterEvolution::generatePopulationFromParent(Individual parent, Population& population)
{
    population[0] = parent;
    bool skip_first = true;
    for (auto& individual : population)
    {
        if (skip_first)
        {
            skip_first = false;
            continue;
        }

        individual = parent;
        individual.mutateRandomly();
    }
}

int MedianFilterEvolution::getFitness(Individual& unit)
{
    return unit.getOutput();
}
