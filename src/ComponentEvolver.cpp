// ComponentEvolver.cpp
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

#include "ComponentEvolver.hpp"

#include <string>
#include <string_view>
#include <memory>
#include <fstream>

#include "MedianFilterEvolution.hpp"

void ComponentEvolver::addImages(std::string_view original_image_path, std::string_view noise_image_path)
{
    original_image_path_ = original_image_path;
    noise_image_path_ = noise_image_path;
    median_filter_evolver_ = std::make_unique<MedianFilterEvolution>(original_image_path, noise_image_path);
}

void ComponentEvolver::evolve()
{
    median_filter_evolver_->evolve();
}

void ComponentEvolver::filterOriginalImageToFile(std::string_view output_image_path)
{
    median_filter_evolver_->createFilteredImage(output_image_path);
}
