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

    int last_column_offset = (circuit_num_columns - 1) * circuit_num_rows;
    output_unit_ = (std::rand() % circuit_num_rows) + last_column_offset + circuit_num_inputs;
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
