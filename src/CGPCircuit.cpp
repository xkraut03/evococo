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

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "CGPCircuit.hpp"


void CGPCircuit::createRandomCircuitValues()
{
    std::srand(std::time(0));
    for (auto row : circuit_matrix_)
    {
        int column_offset = 0;
        for (auto unit : row)
        {
            int random = std::rand() % (circuit_num_inputs + circuit_num_rows);
            unit.input1 = (random > circuit_num_inputs) ? (random + column_offset) : random;

            random = std::rand() % (circuit_num_inputs + circuit_num_rows);
            unit.input2 = (random > circuit_num_inputs) ? (random + column_offset) : random;

            unit.function_num = random % circtuit_num_functions;
            ++column_offset;
        }
    }

    output_unit_ = std::rand() % (circuit_num_rows * circuit_num_columns);
}

void CGPCircuit::randomlyMutate()
{
    std::srand(std::time(0));
    const int num_units = circuit_num_rows + circuit_num_columns;
    int target_unit = std::rand() % (num_units + circtuit_num_outputs);
    if (target_unit >= num_units) // change output
    {
        output_unit_ = std::rand() % num_units;
    }
    else
    {
        int action = std::rand() % 3;
        int row = target_unit % circuit_num_rows;
        int col = target_unit % circuit_num_columns;
        switch (action)
        {
            case 0: // change input 1
                circuit_matrix_[row][col].input1 = std::rand() % num_units;
            break;
            case 1: // change input 2
                circuit_matrix_[row][col].input2 = std::rand() % num_units;
            break;
            case 2: // change function
                circuit_matrix_[row][col].function_num = std::rand() % circtuit_num_functions;
            break;
        }
    }
}

void CGPCircuit::setInput(std::array<int, circuit_num_inputs>& input)
{
    input_ = input;
}

int CGPCircuit::getOutput(const CGPComponent& unit)
{
    int x, y;
    if (unit.input1 < circuit_num_inputs)
    {
        x = input_[unit.input1];
    }
    else
    {
        int row = unit.input1 % circuit_num_rows;
        int col = unit.input1 % circuit_num_columns;
        x = circuit_matrix_[row][col].output;
    }

    if (unit.input1 < circuit_num_inputs)
    {
        y = input_[unit.input1];
    }
    else
    {
        int row = unit.input1 % circuit_num_rows;
        int col = unit.input1 % circuit_num_columns;
        y = circuit_matrix_[row][col].output;
    }

    return doSpecificOperation(x, y, unit.function_num);
}

int CGPCircuit::doSpecificOperation(const int x, const int y, const int function)
{
    int result;
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
            result = (uint8_t)(x + y);
        break;
        case 12:
            result = (x + y) > 255 ? 255 : x + y;
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


int CGPCircuit::calculateOutput()
{
    for (int col = 0; col < circuit_num_columns; ++col)
    {
        for (int row = 0; row < circuit_num_rows; ++row)
        {
            circuit_matrix_[row][col].output = getOutput(circuit_matrix_[row][col]);
        }
    }
    return 0;
}



void CGPCircuit::setRowsNumber(const int num_rows)
{
    num_rows_ = num_rows;
}

void CGPCircuit::setColumnsNumber(const int num_columns)
{
    num_columns_ = num_columns;
}

void CGPCircuit::setLBackValue(const int l_back_value)
{
    l_back_ = l_back_value;
}

void CGPCircuit::setInputsNumber(const int num_inputs)
{
    num_inputs_ = num_inputs;
}

void CGPCircuit::setOutputsNumber(const int num_outputs)
{
    num_outputs_ = num_outputs;
}
