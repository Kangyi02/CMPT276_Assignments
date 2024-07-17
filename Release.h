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

/*
----------------------------------------------------------
// Exported constants/types/variables
*/

// Release class
class Release
{
public:
    char release_ID[9]; // max 8 chars
    char product_name[11]; // max 10 chars
    char release_date[11]; // YYYY-MM-DD

    Release();
    Release(const char* id, const char* name, const char* date);
};

// Initialize the release file
bool initRelease();

// Shut down the release file
bool closeRelease();

void seekToBeginningOfReleaseFile();

// Create a new release for a product
bool addRelease(Release* new_release);

// Get release ID 
bool getNextRelease(char* product_name);

<<<<<<< HEAD
void seekToBeginningOfReleaseFile();

Release* filterRelease(char* product_name);
=======
bool filterNextRelease(Release rel, char* product_name);
>>>>>>> 04d3e2bad9b3c0ca70fbe826e72de0be4b263b44
#endif