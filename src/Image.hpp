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

#include "../lib/EasyBMP/EasyBMP.h"

const int window_size = 25;

class Image
{
public:
    Image(const std::string& img_path);
    void resetWindow();
    std::array<uint8_t, window_size> getWindow();

private:
    BMP bmp_image_;
};
