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

#pragma once

#include <array>
#include <vector>

#include "../lib/EasyBMP/EasyBMP.h"

using pixel_t = uint8_t;

// class ImageIterator;

class Image
{
public:
    using Pixel = pixel_t;
    friend class ImageIterator;
    using iterator = class ImageIterator;

    Image();
    Image(std::string_view img_path);
    Pixel getPixel(const int x, const int y);
    Pixel operator()(const int x, const int y);
    iterator begin();
    iterator end();
    void writeToBMP(std::string_view path);

private:
    std::string img_path_;
    void printMatrix();
    void fillImageFromBMP();
    void createPadding();
    std::vector<std::vector<Pixel>> pixel_matrix_;
    std::vector<std::vector<Pixel>> padded_matrix_;

    BMP bmp_image_;
    int width_;
    int height_;
};

class ImageIterator
{
public:
    ImageIterator(Image& img, std::vector<Image::Pixel>::iterator pix);
    bool operator==(const ImageIterator& rhs) const;
    bool operator!=(const ImageIterator& rhs) const;
    ImageIterator& operator++();
    Image::Pixel operator* () const;

private:
    Image& img_;
    std::vector<Image::Pixel>::iterator curr_;
};
