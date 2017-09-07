// ComponentEvolver.hpp
// author: Daniel Kraut
// creation date: 16th of August, 2017

#pragma once

#include <string>
#include <memory>

class MedianFilterEvolution;

class ComponentEvolver
{
public:
    ComponentEvolver();
    ~ComponentEvolver();

    void addImages(const std::string& original_image_path, const std::string& noise_image_path);
    void evolve();
    void filterOriginalImageToFile(const std::string& output_image_path);

private:
    std::string original_image_path_;
    std::string noise_image_path_;
    std::unique_ptr<MedianFilterEvolution> median_filter_evolver_;
};
