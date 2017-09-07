// ComponentEvolver.cpp
// author: Daniel Kraut
// creation date: 16th of August, 2017

#include "ComponentEvolver.hpp"

#include <string>

#include "../lib/EasyBMP/EasyBMP.h"

ComponentEvolver::ComponentEvolver()
{}

ComponentEvolver::~ComponentEvolver()
{}

void ComponentEvolver::addImages(const std::string& original_image_path, const std::string& noise_image_path)
{
    BMP original_image;
    BMP noise_image;
    original_image.ReadFromFile(original_image_path.c_str());
    noise_image.ReadFromFile(noise_image_path.c_str());
}

void ComponentEvolver::evolve(){}
void ComponentEvolver::filterOriginalImageToFile(const std::string& output_image_path){}
