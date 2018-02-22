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
    resetWindow();
}

Image::Image(std::string_view img_path)
{
    bmp_image_.ReadFromFile(img_path.data());
    width_ = bmp_image_.TellWidth();
    height_ = bmp_image_.TellHeight();
    img_path_ = img_path;
    fillImageFromBMP();
    createPadding();
    resetWindow();
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

    // if (bmp_image_.TellHeight() != pixel_matrix_.size())
        // throw std::runtime_error("image height missmatch!\n");
}

void sidesPadding(std::vector<Image::Pixel>& row)
{
    row.insert(row.begin(), 2, row.front());
    row.insert(row.end(), 2, row.back());
}

void Image::createPadding()
{
    // for now, window is 5x5, so padding is +2 lines
    std::vector<Image::Pixel> top = pixel_matrix_.front();
    sidesPadding(top);
    padded_matrix_.push_back(top);
    padded_matrix_.push_back(top);

    for (auto row : pixel_matrix_)
    {
        sidesPadding(row);
        padded_matrix_.push_back(row);
    }

    std::vector<Image::Pixel> bottom = pixel_matrix_.back();
    sidesPadding(bottom);
    padded_matrix_.push_back(bottom);
    padded_matrix_.push_back(bottom);
}

void Image::writeToBMP(std::string_view path)
{
    BMP img;
    img.SetSize(padded_matrix_.front().size(), padded_matrix_.size());
    int x = 0;
    int y = 0;
    for (auto row : padded_matrix_)
    {
        for (auto pix : row)
        {
            img(x,y)->Red = pix;
            img(x,y)->Green = pix;
            img(x,y)->Blue = pix;
            ++x;
        }
        x = 0;
        ++y;
    }
    img.WriteToFile(std::string(path).c_str());
}

void Image::matrixToBMP(std::string_view path)
{
    BMP img;
    img.SetSize(pixel_matrix_.front().size(), pixel_matrix_.size());
    int x = 0;
    int y = 0;
    for (auto row : pixel_matrix_)
    {
        for (auto pix : row)
        {
            img(x,y)->Red = pix;
            img(x,y)->Green = pix;
            img(x,y)->Blue = pix;
            ++x;
        }
        x = 0;
        ++y;
    }
    img.WriteToFile(std::string(path).c_str());
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


Image::Window Image::getNextWindow()
{
    if (width_ >= 5 && height_ >= 5)
    {
        if (window_is_valid_)
        {
            for (int x = 0; x < 5; ++x)
                for (int y = 0; y < 5; ++y)
                    win_[x][y] = padded_matrix_[x + win_x_][y + win_y_];

            ++win_y_;
            if (win_y_ >= width_)
            {
                win_y_ = 0;
                ++win_x_;
            }
            if (win_x_ >= height_)
            {
                window_is_valid_ = false;
            }
        }
    }

    return win_;
}

bool Image::isWindowValid()
{
    return window_is_valid_;
}

void Image::resetWindow()
{
    win_x_ = 0;
    win_y_ = 0;
    if (width_ >= 5 && height_ >= 5)
    {
        for (int x = 0; x < 5; ++x)
            for (int y = 0; y < 5; ++y)
                win_[x][y] = padded_matrix_[x][y];

        window_is_valid_ = true;
    }
    else
    {
        window_is_valid_ = false;
    }
}

int Image::getWidth() const
{
    return width_;
}

int Image::getHeight() const
{
    return height_;
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

Image::Pixel& ImageIterator::operator* () const
{
    return *curr_;
}
