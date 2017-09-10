// ComponentEvolver.hpp
// author: Daniel Kraut
// creation date: 16th of August, 2017
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
