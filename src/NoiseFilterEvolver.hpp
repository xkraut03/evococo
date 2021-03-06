// NoiseFilterEvolver.hpp
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

#include <string_view>

#include "CGPCircuit.hpp"
#include "Image.hpp"

// evolutionary algorithm parameters
const int population_size = 40;
const int num_generations = 200;

class NoiseFilterEvolver
{
public:
    NoiseFilterEvolver(std::string_view original_image_path,
                       std::string_view noise_image_path);
    void evolve();
    void createFilteredImage(std::string_view output_path);

private:
    using Individual = CGPCircuit;
    using Population = std::array<Individual, population_size>;
    Image original_image_;
    Image noise_image_;
    Image output_image_;
    Individual best_unit_;

private:
    Population generateRandomPopulation();
    Individual selectBestUnit(Population& population);
    void mutatePopulationFromParent(Population& population, Individual parent);
    double getFitness(Individual& unit);
    long oldFitness(Individual& unit);
};
