#include "Product.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream productFileStream;

//constructor
Product::Product() : product_name(new char[10]), release_date(new char[8]) {}
Product::Product(const char* name, const char* date) : product_name(name), release_date(date) {}
Product::Product(const Product& other) : product_name(other.product_name), release_date(other.release_date) {}

//deconstructor
Product::~Product() 
{
    delete[] product_name;
    delete[] release_date;
}

void initProduct() 
{
    productFileStream.open(/*file path*/"", ios::in | ios::out | ios::binary | ios::app);
    if (!productFileStream) 
    {
        cerr << "Error: Could not open file." << endl;
    }
}

void closeProduct() 
{
    if (productFileStream.is_open()) 
    {
        productFileStream.close();
    }
}

void createProduct(char* product_name)
{
    //unfinished
}

Product* getProduct() 
{
    if (productFileStream.is_open()) 
    {
        char name[10];
        char date[8];

        productFileStream >> name >> date;
        return new Product(name, date);
    } else {
        cerr << "Error: File not open." << endl;
        return nullptr;
    }

    Product* prod = new Product();
    productFileStream.seekg(productPosition * sizeof(Product), ios::beg);
    if (productFileStream.read(reinterpret_cast<char*>(prod), sizeof(Product))) 
    {
        return prod;
    } else {
        delete prod;
        return nullptr;
    }
}

void seekToBeginningOfProductFile() 
{
    if (productFileStream.is_open()) 
    {
        productFileStream.clear();
        productFileStream.seekg(0, ios::beg);
    } else 
    {
        cerr << "Error: File not open." << endl;
    }
}