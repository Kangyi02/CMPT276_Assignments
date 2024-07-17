// unitTestMain.cpp;
/* Revision History:
Rev. 1 - 24/07/03 Original by Group 24
----------------------------------------------------------
This cpp file unit test several of the functions in Product.h
----------------------------------------------------------
*/

#include "Product.h"
#include <iostream>

using std::cout;

int main()
{
    //  Test case 1: Create a new product
    cout << "***Test case 1: creating a new product***\n"; 
    cout << "Expected outcome: The new product has been successfully added.\n";
    cout << "Actual outcome: ";
    addProduct("Editor");

    //  Test case 2: Create a product with an exsiting product name
    cout << "***Test case 2: creating a product with an exsiting product name***\n"; 
    cout << "Expected outcome: Error! The product has existed.\n";
    cout << "Actual outcome: ";
    addProduct("Editor");
    return 0;
}