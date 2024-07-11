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

using std::ifstream;
using std::ofstream;

/*----------------------------------------------------------*/
// Exported constants/types/variables
// Define the file stream object
/*----------------------------------------------------------*/

// Product class
class Product {
private:
    char* product_name; // max 10 chars
public:
    char* release_date; // YYYY-MM-DD

    // Constructors
    Product();
    Product(const char* name, const char* date);
    Product(const Product& other);

    // Destructor
    ~Product();

    char* getProduct_name()
    {
        return product_name;
    }
};

// Initialize the product file
void initProduct();

// Shut down the product file
void closeProduct();

// Create a new product. Write the product into file. 
// Return false if it failed, otherwise true.
void createProduct(char* product_name);

// Get the product by reading from the product file 
Product* getProduct();

// Search a product in the product file from the beginning of the file
void seekToBeginningOfProductFile();
#endif 