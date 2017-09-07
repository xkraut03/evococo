// ComponentEvolver.cpp
// author: Daniel Kraut
// creation date: 16th of August, 2017

#include "ComponentEvolver.hpp"

#include <string>
#include <memory>

#include "MedianFilterEvolution.hpp"

ComponentEvolver::ComponentEvolver()
{}

ComponentEvolver::~ComponentEvolver()
{}

void ComponentEvolver::addImages(const std::string& original_image_path, const std::string& noise_image_path)
{
    original_image_path_ = original_image_path;
    noise_image_path_ = noise_image_path;
    median_filter_evolver_ = std::make_unique<MedianFilterEvolution>(original_image_path, noise_image_path);
}

void ComponentEvolver::evolve()
{
    median_filter_evolver_->evolve();
}

void ComponentEvolver::filterOriginalImageToFile(const std::string& output_image_path){}
