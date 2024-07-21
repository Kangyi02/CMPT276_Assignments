#include "StartUp.h"
#include "UI.h"
#include <iostream>

int main()
{
    if (initStart()) {
        std::cout << "All modules initialized successfully. \n\n";
        activateUI();
    } else {
        std::cout << "Failed to initialize one or more modules. \n";
    }
    return 0;
}

// Coding Convention for error tracking system

// a. Module Headers
// Module name at the top of each module header file (`module.h`). The first letter of each 
// word should be captlized

// b. Revision history format: Latest version first, indented with date and brief description.

// c. Above each function, put a small dividing line. the function comment
// come right after the dividing line.

// d. Function prototypes
// all parameters for one function per line and a comment to the right.

// e. 4-character indenting of blocks

// f. Put opening braces on a line by themselves.

