// MedianFilterEvolution.h
// author: Daniel Kraut
// creation date: 16th of August, 2017

#include <string>

class MedianFilterEvolution
{
private:
    /* data */

public:
    MedianFilterEvolution();
    void addImage(const std::string& original_image_path, const std::string& noise_image_path);
    ~MedianFilterEvolution();
};
