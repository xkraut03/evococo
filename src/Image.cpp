// Image.cpp
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

#include <vector>

#include "Image.hpp"

Image::Image()
{
    width_ = -1;
    height_ = -1;
    img_path_ = "";
}

Image::Image(std::string_view img_path)
{
    bmp_image_.ReadFromFile(img_path.data());
    width_ = bmp_image_.TellWidth();
    height_ = bmp_image_.TellHeight();
    // const int padding = (window_size == 25) ? 2 : 0;
    fillImageFromBMP();
    img_path_ = img_path;
}

bool Image::isIt()
{
    if (img_path_ == "../images/barbara-small.bmp")
        printMatrix();
    return true;
}

void Image::printMatrix()
{
    for (auto row : pixel_matrix_)
    {
        for (auto pix : row)
            std::cout << (int)pix << " ";
        std::cout << "\n";
    }
}

void Image::fillImageFromBMP()
{
    for (int r = 0; r < height_; ++r)
    {
        std::vector<Image::Pixel> tmp_row;
        for (int c = 0; c < width_; ++c)
            tmp_row.push_back(bmp_image_(c,r)->Red);
        pixel_matrix_.push_back(tmp_row);
    }

    if (bmp_image_.TellHeight() != pixel_matrix_.size())
        throw std::runtime_error("image height missmatch!\n");
}

Image::Pixel Image::getPixel(const int x, const int y)
{
    return pixel_matrix_[x][y];
}

Image::Pixel Image::operator()(const int x, const int y)
{
    return getPixel(x, y);
}

Image::iterator Image::begin()
{
    return Image::iterator { *this, pixel_matrix_.front().begin() };
}

Image::iterator Image::end()
{
    return Image::iterator { *this, pixel_matrix_.back().end() };
}

ImageIterator::ImageIterator(Image& img, std::vector<Image::Pixel>::iterator pix)
    : img_ { img }, curr_ { pix }
{}

bool ImageIterator::operator==(const ImageIterator& rhs) const
{
    return (curr_ == rhs.curr_);
}

bool ImageIterator::operator!=(const ImageIterator& rhs) const
{
    return (curr_ != rhs.curr_);
}

ImageIterator& ImageIterator::operator++()
{
    ++curr_;
    for (auto row_it = img_.pixel_matrix_.begin(); row_it != img_.pixel_matrix_.end(); ++row_it)
    {
        if ((row_it + 1) != img_.pixel_matrix_.end())
        {
            if (curr_ == row_it->end())
            {
                curr_ = (row_it + 1)->begin();
                break;
            }
        }
    }

    return *this;
}

Image::Pixel ImageIterator::operator* () const
{
    return *curr_;
}
