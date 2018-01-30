// Image.hpp
// author: Daniel Kraut
// creation date: 5th of October, 2017
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

#include <array>
#include <vector>
#include <iostream>

#include "../lib/EasyBMP/EasyBMP.h"

const int window_size = 25;

template<typename T>
class ImageWrapper
{
private:
    std::vector<std::vector<T>> image_;
    int width_;
    int height_;

public:
    ImageWrapper() : width_ {0}, height_ {0}
    {
        printDimensions();
    }

    ImageWrapper(const int width, const int height) :
        width_ {width}, height_ {height}
    {
        printDimensions();
        std::vector<T> row(width);
        row.shrink_to_fit();
        for (int i = 0; i < height_; ++i)
            image_.push_back(row);
        image_.shrink_to_fit();
    }

    void printDimensions() const { std:: cout << "image size: ["
        << width_ << "," << height_ << "]\n"; }

    T& operator()(const int x, const int y)
    {
        if (x < 0 || y < 0)
             throw std::out_of_range( "received negative value" );
        if (x < height_)
            if (y < width_)
                return image_[x][y];


        return image_[0][0];
    }
};

class Image
{
public:
    using Pixel = uint8_t;
    using Window = std::array<Pixel, window_size>;

    Image(const std::string& img_path);
    void resetWindowPosition();
    const Window& getNextWindow();
    Pixel getPixel(const int x, const int y);
    Pixel operator()(const int x, const int y);

private:
    std::vector<std::vector<Pixel>> pixel_matrix_;
    BMP bmp_image_;
    int width_;
    int height_;
    ImageWrapper<Pixel> image_;
    int window_pos_;
    Window window_;
};
