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

#include "MedianFilterEvolution.hpp"

#include "../lib/EasyBMP/EasyBMP.h"

#include "CGPCircuit.hpp"

MedianFilterEvolution::MedianFilterEvolution(const std::string& original_image_path, const std::string& noise_image_path)
{
    original_image_.ReadFromFile(original_image_path.c_str());
    noise_image_.ReadFromFile(noise_image_path.c_str());
}

using Population = int[20];
using Unit = int;

void generateFirstPopulation(Population& population)
{
    CGPCircuit new_population;
    new_population.createRandomCircuitValues();
    // for (auto unit : new_population)
    // {
    //     unit.setRowsNumber(circuit_rows);
    //     unit.setColumnsNumber(circuit_columns);
    //     unit.setLBackValue(circuit_lback);
    //     unit.setInputsNumber(circuit_inputs);
    //     unit.setOutputsNumber(circtuit_outputs);
    // }

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

    for (int cycle = 0; cycle < num_generations; ++cycle)
    {
        generatePopulationFromParent(the_best_unit, population);
        the_best_unit = selectBestUnit(population);
    }

    std::cout << "The best at the end solution is: " << the_best_unit << "\n";
}
