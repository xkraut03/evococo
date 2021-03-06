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

#include "CGPCircuit.hpp"

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "../lib/effolkronium/random.hpp"

int CGPCircuit::indexToColumn(const int index) const
{
    return index / circuit_num_rows;
}

int CGPCircuit::indexToRow(const int index) const
{
    return index % circuit_num_rows;
}

int CGPCircuit::setLback1(int target, int curr_column)
{
    int column_diff = curr_column - indexToColumn(target);
    if (column_diff > 1) return target + ((column_diff - 1) * column_size);
    return target;
}

void CGPCircuit::initRandomly()
{
    using Random = effolkronium::random_static;
    for (auto& row : circuit_matrix_)
    {
        int curr_column = 0;
        for (auto& unit : row)
        {
            unit.input1 =
              Random::get(-circuit_num_inputs, column_size * curr_column - 1);
            if (unit.input1 >= 0)
                unit.input1 = setLback1(unit.input1, curr_column);

            unit.input2 =
              Random::get(-circuit_num_inputs, column_size * curr_column - 1);
            if (unit.input2 >= 0)
                unit.input2 = setLback1(unit.input2, curr_column);

            unit.function = Random::get(0, circuit_num_functions - 1);
            ++curr_column;
        }
    }

    output_unit_ = Random::get(0, circuit_num_rows * circuit_num_columns - 1);
    tmp_output_ = -1;
}

void CGPCircuit::mutateRandomly()
{
    using Random = effolkronium::random_static;

    int num_units = circuit_num_rows * circuit_num_columns;
    int target_unit = Random::get(0, num_units);
    if (target_unit >= num_units)  // change output
    {
        output_unit_ = Random::get(0, num_units - 1);
    }
    else
    {
        int row = indexToRow(target_unit);
        int col = indexToColumn(target_unit);
        int action = Random::get({ 1, 2, 3 });
        switch (action)
        {
            case 1:  // change input 1
                circuit_matrix_[row][col].input1 =
                  Random::get(-circuit_num_inputs, (col * column_size) - 1);
                if (circuit_matrix_[row][col].input1 >= 0)
                    circuit_matrix_[row][col].input1 =
                      setLback1(circuit_matrix_[row][col].input1, col);
                break;
            case 2:  // change input 2
                circuit_matrix_[row][col].input2 =
                  Random::get(-circuit_num_inputs, (col * column_size) - 1);
                if (circuit_matrix_[row][col].input2 >= 0)
                    circuit_matrix_[row][col].input2 =
                      setLback1(circuit_matrix_[row][col].input2, col);
                break;
            case 3:  // change function
                circuit_matrix_[row][col].function =
                  Random::get(0, circuit_num_functions - 1);
                break;
        }
    }
}

void CGPCircuit::setInput(const CGPCircuit::CGPInputArray& input)
{
    input_ = input;
}

uint8_t CGPCircuit::getOutput()
{
    int row = indexToRow(output_unit_);
    int col = indexToColumn(output_unit_);
    return getComponentOutput(circuit_matrix_[row][col]);
}

uint8_t CGPCircuit::getComponentOutput(const CGPComponent& unit) const
{
    uint8_t x, y;
    if (unit.input1 < 0)
    {
        x = input_.at((-unit.input1) - 1);
    }
    else
    {
        const int row = indexToRow(unit.input1);
        const int col = indexToColumn(unit.input1);
        x = getComponentOutput(circuit_matrix_.at(row).at(col));
    }

    if (unit.input2 < 0)
    {
        y = input_.at((-unit.input2) - 1);
    }
    else
    {
        const int row = indexToRow(unit.input2);
        const int col = indexToColumn(unit.input2);
        y = getComponentOutput(circuit_matrix_.at(row).at(col));
    }

    return doSpecificOperation(x, y, unit.function);
}

uint8_t CGPCircuit::doSpecificOperation(const uint8_t x, const uint8_t y,
                                        const int function) const
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

bool CGPCircuit::saveToFile(std::string_view path_view) const
{
    std::ofstream out_file{ path_view.data() };
    if (!out_file.is_open()) return false;

    out_file << circuit_num_rows << " " << circuit_num_columns;
    for (auto row : circuit_matrix_)
        for (auto unit : row)
            out_file << unit.input1 << " " << unit.input2 << " "
                     << unit.function << '\n';

    out_file << output_unit_ << '\n';
    return true;
}

void CGPCircuit::printBackwards() const
{
    if (output_unit_ < 0)
    {
        std::cout << "circuit is too short!\n";
        return;
    }
    else
        printBackwards(output_unit_);
}

void CGPCircuit::printBackwards(int unit_index) const
{
    if (unit_index < 0) return;

    int row = indexToRow(unit_index);
    int col = indexToColumn(unit_index);
    std::cout << circuit_matrix_[row][col].input1 << ' '
              << circuit_matrix_[row][col].input2 << ' '
              << circuit_matrix_[row][col].function << '\n';

    printBackwards(circuit_matrix_[row][col].input1);
    printBackwards(circuit_matrix_[row][col].input2);
}

bool CGPCircuit::loadFromFile(std::string_view path_view)
{
    std::ifstream in_file{ path_view.data() };
    if (!in_file.is_open()) return false;

    int width, height;
    in_file >> height >> width;
    for (int r = 0; r < circuit_num_rows; ++r)
    {
        for (int c = 0; c < circuit_num_columns; ++c)
        {
            in_file >> circuit_matrix_[r][c].input1;
            in_file >> circuit_matrix_[r][c].input2;
            in_file >> circuit_matrix_[r][c].function;
        }
    }

    in_file >> output_unit_;
    return true;
}

bool CGPCircuit::switchToLessPower()
{
    if (out_candidates.size() == 0)
    {
        if (tmp_output_ >= 0) return false;

        int out_row = indexToRow(output_unit_);
        int out_col = indexToColumn(output_unit_);
        CGPComponent& out_unit = circuit_matrix_[out_row][out_col];

        if (out_unit.input1 >= 0) out_candidates.push_back(out_unit.input1);
        if (out_unit.input2 >= 0)
            if (out_unit.input2 != out_unit.input1)
                out_candidates.push_back(out_unit.input2);
    }
    tmp_output_ = output_unit_;
    output_unit_ = out_candidates.back();
    out_candidates.pop_back();

    return true;
}

int CGPCircuit::getCircuitLength() const
{
    return indexToColumn(output_unit_) + 1;
}
