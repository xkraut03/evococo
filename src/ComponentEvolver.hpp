// ComponentEvolver.hpp
// author: Daniel Kraut
// creation date: 16th of August, 2017

#include <string>

class ComponentEvolver
{
private:
    /* data */

public:
    ComponentEvolver();
    ~ComponentEvolver();

    void addImages(const std::string& original_image_path, const std::string& noise_image_path);
    void evolve();
    void filterOriginalImageToFile(const std::string& output_image_path);
};
