// CGPCircuit.cpp
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

#include <cstdlib>
#include <iostream>

#include "../lib/effolkronium/random.hpp"

#include "CGPCircuit.hpp"

int CGPCircuit::indexToColumn(const int index)
{
    return index / circuit_num_rows;
}

int CGPCircuit::indexToRow(const int index)
{
    return index % circuit_num_rows;
}

void CGPCircuit::initRandomly()
{
    using Random = effolkronium::random_static;
    for (auto& row : circuit_matrix_)
    {
        int column_offset = 0;
        for (auto& unit : row)
        {
            auto random = Random::get(0, circuit_num_inputs + (column_offset * circuit_num_rows) - 1);
            unit.input1 = random;

            random = Random::get(0, circuit_num_inputs + (column_offset * circuit_num_rows) - 1);
            unit.input2 = random;

            random = Random::get(0, circtuit_num_functions - 1);
            unit.function_num = random;
            ++column_offset;
        }
    }

    output_unit_ = Random::get(0, circuit_num_rows * circuit_num_columns - 1);
}

void CGPCircuit::mutateRandomly()
{
    using Random = effolkronium::random_static;

    const int num_units = circuit_num_rows * circuit_num_columns;
    int target_unit = Random::get(0, num_units);
    if (target_unit >= num_units) // change output
    {
        // we don't allow output to be connected directly to any of the inputs
        // this can be changed in the future, but because this is mainly used for
        // filter with only one output, this seems unnecessary
        output_unit_ = Random::get(0, num_units - 1);
    }
    else
    {
        const int action = Random::get({1, 2, 3});
        const int row = indexToRow(target_unit);
        const int col = indexToColumn(target_unit);
        switch (action)
        {
            case 0: // change input 1
                circuit_matrix_[row][col].input1 =
                    Random::get(0, circuit_num_inputs + (col * circuit_num_rows) - 1);
            break;
            case 1: // change input 2
                circuit_matrix_[row][col].input2 =
                    Random::get(0, circuit_num_inputs + (col * circuit_num_rows) - 1);
            break;
            case 2: // change function
                circuit_matrix_[row][col].function_num = Random::get(0, circtuit_num_functions - 1);
            break;
        }
    }
}

void CGPCircuit::printBackwards()
{
    std::cout << output_unit_ << "\n";
    if (output_unit_ >= circuit_num_inputs)
    {

    }
}

void CGPCircuit::setInput(const std::array<uint8_t, circuit_num_inputs>& input)
{
    input_ = input;
}

uint8_t CGPCircuit::getOutput()
{
    for (int col = 0; col < circuit_num_columns; ++col)
        for (int row = 0; row < circuit_num_rows; ++row)
            circuit_matrix_[row][col].output = getComponentOutput(circuit_matrix_[row][col]);

    const int out_row = indexToRow(output_unit_);
    const int out_col = indexToColumn(output_unit_);
    return circuit_matrix_[out_row][out_col].output;
}

uint8_t CGPCircuit::getComponentOutput(const CGPComponent& unit)
{
    uint8_t x, y;
    if (unit.input1 < circuit_num_inputs)
    {
        x = input_.at(unit.input1);
    }
    else
    {
        const int row = indexToRow(unit.input1 - circuit_num_inputs);
        const int col = indexToColumn(unit.input1 - circuit_num_inputs);
        // x = circuit_matrix_[row][col].output;
        x = circuit_matrix_.at(row).at(col).output;
    }

    if (unit.input2 < circuit_num_inputs)
    {
        y = input_.at(unit.input2);
    }
    else
    {
        const int row = indexToRow(unit.input2 - circuit_num_inputs);
        const int col = indexToColumn(unit.input2 - circuit_num_inputs);
        // y = circuit_matrix_[row][col].output;
        y = circuit_matrix_.at(row).at(col).output;
    }

    return doSpecificOperation(x, y, unit.function_num);
}

uint8_t CGPCircuit::doSpecificOperation(const uint8_t x, const uint8_t y, const int function)
{
    uint8_t result = 0;
    switch (function)
    {
        case 0:
            result = 255;
        break;
        case 1:
            result = x;
        break;
        case 2:
            result = 255 - x;
        break;
        case 3:
            result = x | y;
        break;
        case 4:
            result = (255 - x) | y;
        break;
        case 5:
            result = x & y;
        break;
        case 6:
            result = 255 - (x & y);
        break;
        case 7:
            result = x ^ y;
        break;
        case 8:
            result = x >> 1;
        break;
        case 9:
            result = x >> 2;
        break;
        case 10:
            result = (x << 4) | (y >> 4);
        break;
        case 11:
            result = (x + y);
        break;
        case 12:
            result = ((int)x + (int)y) > 255 ? 255 : x + y;
        break;
        case 13:
            result = (x + y) >> 1;
        break;
        case 14:
            result = (x > y) ? x : y;
        break;
        case 15:
            result = (x < y) ? x : y;
        break;
    }

    return result;
}
