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
#include <memory>

// CGP parameters
const int circuit_num_rows = 8;
const int circuit_num_columns = 10;
const int circuit_lback_value = 1;
const int circuit_num_inputs = 25;
const int circtuit_num_outputs = 1;
const int circtuit_num_functions = 16;

struct CGPComponent
{
    int input1;
    int input2;
    int output;
    int function_num;
};

template <const size_t MatrixRows, const size_t MatrixColumns>
using ComponentsMatrix = std::array<std::array<CGPComponent, MatrixColumns>, MatrixRows>;

class CGPCircuit {
private:
    int num_rows_;
    int num_columns_;
    int l_back_;
    int num_inputs_;
    int num_outputs_;
    ComponentsMatrix<circuit_num_rows, circuit_num_columns> circuit_matrix_;
    int output_unit_;

public:
    CGPCircuit () = default;
    virtual ~CGPCircuit () = default;
    void createRandomCircuitValues();

private:
    void setRowsNumber(const int num_rows);
    void setColumnsNumber(const int num_columns);
    void setLBackValue(const int l_back_value);
    void setInputsNumber(const int num_inputs);
    void setOutputsNumber(const int num_outputs);
};
