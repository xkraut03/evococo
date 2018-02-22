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
#include <typeinfo>
#include <cassert>

#include "MedianFilterEvolution.hpp"

#include "Image.hpp"
#include "CGPCircuit.hpp"

MedianFilterEvolution::MedianFilterEvolution(std::string_view original_image_path, std::string_view noise_image_path)
: original_image_ {original_image_path}, noise_image_ {noise_image_path}, output_image_ {original_image_path}
{}

void MedianFilterEvolution::evolve()
{
    Population population;
    generateRandomPopulation(population);
    Individual best_unit = selectBestUnit(population);

    for (int cycle = 1; cycle <= num_generations; ++cycle)
    {
        std::cout << cycle << "th cycle, best population = " << getFitness(best_unit) << '\n';
        generatePopulationFromParent(best_unit, population);
        best_unit = selectBestUnit(population);
    }

    best_unit_ = best_unit;
    std::cout << "The best solution is: " << getFitness(best_unit) << "\n";
    best_unit_.saveToFile("circuit.cgp");
}

void MedianFilterEvolution::generateRandomPopulation(Population& population)
{
    for (auto& p : population)
        p.initRandomly();
}

MedianFilterEvolution::Individual MedianFilterEvolution::selectBestUnit(Population& population)
{
    double best_fitness = 0.0;
    int best_index = 0;
    for (int i = 0; i < population_size; ++i)
    {
        if (double fitness = getFitness(population[i]);
            fitness >= best_fitness)
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
        individual.mutateRandomly();
        individual.mutateRandomly();
        individual.mutateRandomly();
        individual.mutateRandomly();
    }
}

double PSNR(long dif_sq, long width, long height)
{
    const long pixel_max = 255 * 255;
    const long dimensions = width * height;
    return 10 * std::log10(pixel_max / ((1.0 / dimensions) * dif_sq));
}

double MedianFilterEvolution::getFitness(Individual& unit)
{
    noise_image_.resetWindow();
    Image::Window win = noise_image_.getNextWindow();
    std::array<Image::Pixel, 25> cinput;
    long fitness = 0;

    for (auto pix : original_image_)
    {
        std::copy(win[0].begin(), win[0].end(), cinput.begin());
        std::copy(win[1].begin(), win[1].end(), cinput.begin() + 5);
        std::copy(win[2].begin(), win[2].end(), cinput.begin() + 10);
        std::copy(win[3].begin(), win[3].end(), cinput.begin() + 15);
        std::copy(win[4].begin(), win[4].end(), cinput.begin() + 20);
        unit.setInput(cinput);

        auto new_pix = unit.getOutput();
        // fitness += (pix >= new_pix) ? (pix - new_pix) : (new_pix - pix);
        long difference = pix - new_pix;
        fitness += difference * difference;
        win = noise_image_.getNextWindow();
    }

    return PSNR(fitness, original_image_.getWidth(), original_image_.getHeight());
}

void MedianFilterEvolution::createFilteredImage(std::string_view output_path)
{
    noise_image_.resetWindow();
    Image::Window win = noise_image_.getNextWindow();
    std::array<Image::Pixel, 25> cinput;

    for (auto it = output_image_.begin(); it != output_image_.end(); ++it)
    {
        std::copy(win[0].begin(), win[0].end(), cinput.begin());
        std::copy(win[1].begin(), win[1].end(), cinput.begin() + 5);
        std::copy(win[2].begin(), win[2].end(), cinput.begin() + 10);
        std::copy(win[3].begin(), win[3].end(), cinput.begin() + 15);
        std::copy(win[4].begin(), win[4].end(), cinput.begin() + 20);
        best_unit_.setInput(cinput);
        (*it) = best_unit_.getOutput();
        win = noise_image_.getNextWindow();
    }

    output_image_.matrixToBMP(output_path);
}
