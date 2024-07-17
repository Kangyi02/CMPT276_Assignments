// DEFINITION MODULE Product;
/* Revision History:
Rev. 1 - 24/07/03 Original by Group 24
----------------------------------------------------------
This module encapsulates the implementation details of managing products and their
releases. The exported functions provide an interface to create and manage products
and their release dates. Products are identified by their name, and their associated
release dates are tracked. This abstraction ensures that the underlying management
of products is hidden, providing a clean and straightforward interface for interaction.
----------------------------------------------------------
*/

#ifndef Product_H
#define Product_H

/*----------------------------------------------------------*/
// Exported constants/types/variables
// Define the file stream object
/*----------------------------------------------------------*/

// Product class
class Product {
public:
    char product_name[11]; // max 10 chars
    char* release_date[11]; // YYYY-MM-DD

    // Constructors
    Product();
    Product(const char* name, const char* date);
};

// Initialize the product file
void initProduct();

// Shut down the product file
void closeProduct();

// Create a new product. Write the product into file. 
// Return false if it failed, otherwise true.
void addProduct(char* product_name);

// Get the product by reading from the product file 
bool getNextProduct(Product* prod);

// Search a product in the product file from the beginning of the file
void seekToBeginningOfProductFile();
#endif 