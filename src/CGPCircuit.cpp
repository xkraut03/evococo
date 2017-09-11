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

#include "CGPCircuit.hpp"

CGPCircuit::CGPCircuit()
{
    ComponentsMatrix<circuit_rows,circuit_columns> pole;
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
