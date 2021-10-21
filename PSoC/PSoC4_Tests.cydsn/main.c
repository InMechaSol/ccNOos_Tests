/** \file main.c
*   \brief PSoC4 Implementation of ccNOos Tests

   Copyright 2021 InMechaSol, Inc

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/
#include "project.h"                            // all things psoc4
#include "../../ccNOos/tests/ccNOos_tests.h"    // all things ccNOos w/tests

// Define psoc4 io devices and serialization

// Define psoc4 compute modules and entry points

// Create Cross Platform Execution System
struct executionSystemStruct psoc4ccNOosTests; 


int main(void)
{    
    CyGlobalIntEnable; /* Enable global interrupts. */

    // Initialize Execution System Data Structure
    psoc4ccNOosTests = CreateExecutionSystemStruct();

    return Execute(&psoc4ccNOosTests);
}

/* [] END OF FILE */
