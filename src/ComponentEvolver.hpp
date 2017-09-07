// ComponentEvolver.h
// author: Daniel Kraut
// creation date: 16th of August, 2017

#include <string>

class ComponentEvolver
{
private:
    /* data */

public:
    ComponentEvolver();
    void addImage(const std::string& original_image_path, const std::string& noise_image_path);
    ~ComponentEvolver();
};
