// CGPCircuit.hpp
// author: Daniel Kraut
// creation date: 10th of September, 2017
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

#include <array>

// CGP parameters
const int circuit_num_rows = 8;
const int circuit_num_columns = 10;
// const int circuit_lback_value = 1; lback is max for now
const int circuit_num_inputs = 25;
const int circtuit_num_outputs = 1;
const int circtuit_num_functions = 16;

struct CGPComponent
{
    int input1;
    int input2;
    int function_num;
    uint8_t output;
};

template <const size_t MatrixRows, const size_t MatrixColumns>
using ComponentsMatrix = std::array<std::array<CGPComponent, MatrixColumns>, MatrixRows>;

class CGPCircuit
{
private:
    ComponentsMatrix<circuit_num_rows, circuit_num_columns> circuit_matrix_;
    int output_unit_;
    std::array<uint8_t, circuit_num_inputs> input_;

public:
    void initRandomly();
    void mutateRandomly();
    void setInput(std::array<uint8_t, circuit_num_inputs>& input);
    uint8_t getOutput();

private:
    uint8_t doSpecificOperation(const uint8_t x, const uint8_t y, const int function);
    uint8_t getComponentOutput(const CGPComponent& unit);
    int indexToRow(const int index);
    int indexToColumn(const int index);
};
