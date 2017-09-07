// MedianFilterEvolution.hpp
// author: Daniel Kraut
// creation date: 7th of September, 2017

#pragma once

// evolutionary algorithm parameters
const int population_size = 20;
const int number_of_generations = 500;
// CGP parameters
const int circuit_rows = 8;
const int circuit_columns = 10;
const int circuit_lback = 1;

#include "../lib/EasyBMP/EasyBMP.h"

class MedianFilterEvolution
{
public:
    MedianFilterEvolution(const std::string& original_image_path, const std::string& noise_image_path);
    ~MedianFilterEvolution(){};
    void evolve();

private:
    BMP original_image_;
    BMP noise_image_;
};
