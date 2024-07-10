// DEFINITION MODULE Release;
/* Revision History:
Rev. 1 - 24/07/03 Original by Group 24
----------------------------------------------------------
This module encapsulates the implementation details of managing releases
associated with products. The exported functions provide an interface to
create, initialize, and manage product releases. Each release is identified
by a unique ID and is associated with a specific product and release date.
This abstraction ensures that the underlying management of releases is hidden,
providing a clean and straightforward interface for interaction.
----------------------------------------------------------
*/

#ifndef Release_H
#define Release_H

#include "Product.h"
#include "ChangeRequest.h"
#include "Change.h"

/*
----------------------------------------------------------
// Exported constants/types/variables
*/

// Release class
class Release
{
private:
    char* release_ID; // max 8 chars
public:
    char* product_name; // max 10 chars
    char* release_date; // YYYY-MM-DD

    // Constructors
    Release();
    Release(const char* id, const char* name, const char* date);
    Release(const Release& other);
    
    // Destructor
    ~Release();
};

// Initialize the release file
void initRelease();

// Shut down the release file
void closeRelease();

// Create a new release for a product
void createRelease(Release* new_release);

// Get release ID 
Release* getRelease(char* product_name);
#endif