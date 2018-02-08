// main.cpp
// author: Daniel Kraut
// creation date: 30th of July, 2017
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
//

#include <iostream>

#include "ComponentEvolver.hpp"

int main(int argc, char const *argv[])
{
    if (argc <= 1)
    {
        std::cerr << "Too few arguments\n";
        return -1;
    }
    std::cout << "Let's evolve something!" << '\n';

    ComponentEvolver median_filter_evolver;
    median_filter_evolver.addImages(argv[1], argv[2]);
    median_filter_evolver.evolve();
    median_filter_evolver.filterOriginalImageToFile("../build/barbara_cleared.bmp");

    return 0;
}
