// MedianFilterEvolution.hpp
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

#pragma once

#include "../lib/EasyBMP/EasyBMP.h"

#include "CGPCircuit.hpp"

// evolutionary algorithm parameters
const int population_size = 20;
const int num_generations = 500;

class MedianFilterEvolution
{
public:
    MedianFilterEvolution(const std::string& original_image_path, const std::string& noise_image_path);
    ~MedianFilterEvolution(){};
    void evolve();

private:
    using Unit = CGPCircuit;
    using Population = Unit[population_size];
    BMP original_image_;
    BMP noise_image_;

private:
    void generateFirstPopulation(Population& population);
    Unit selectBestUnit(Population& population);
    void mutate(Unit& unit);
    void generatePopulationFromParent(Unit parent, Population& population);
    int getFitness(const Unit& unit);
};
