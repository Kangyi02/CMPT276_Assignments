#include "Product.h"
#include <iostream>
#incldue <fstream>

using namespace std;

fstream productFileStream;

// Default constructor implementation
Product::Product() 
{
    product_name[0] = '\0';
    release_date[0] = '\0';
}

// Parameterized constructor implementation
Product::Product(const char* name, const char* date)
{
    //initialize fields with provided parameters, ensuring max length is not exceeded
    strncpy(product_name, name, sizeof(name) - 1);
    product_name[sizeof(name) - 1] = '\0';

    strncpy(release_date, date, sizeof(date) - 1);
    product_name[sizeof(date) - 1] = '\0';
}

//deconstructor
Product::~Product() 
{
    delete[] product_name;
    delete[] release_date;
}

// Initialize the product file
//FIX FILE PATH BEFORE SUBMITTING
bool initProduct() 
{
    productFileStream.open(/*file path*/, ios::in | ios::out | ios::binary | ios::ate);
    if (!productFileStream) 
    {
        return false;
    }
    return true;
}

// Shut down the product file
bool closeProduct() 
{
    if (productFileStream.is_open()) 
    {
        productFileStream.close();
        if (productFileStream.is_open())
        {
            return false;
        }
        return true;
    }
    return true;
}

void seekToBeginningOfProductFile() 
{
    productFileStream.seekg(0, ios::beg);
}

// Store a new product to file
bool addProduct(char* product_name)
{
    if (productFileStream.write(reinterpret_cast<char*>(product_name), sizeof(Product)))
    {
        return true;
    }
    return false;
}

// Get the next product
bool getNextProduct(Product* prod) 
{
    if (productFileStream.read(reinterpret_cast<char*>(prod), sizeof(Product))) 
    {
        return true;
    }
    return false;
}