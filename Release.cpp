// Version History:
// Rev. 1 - 24/07/17 Original by Group 24
// ----------------------------------------------------------
// Implement Release.h
// ----------------------------------------------------------

#include "Release.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream ReleaseFileStream;

Release::Release() 
{
    release_ID[0] = '\0';
    product_name[0] = '\0';
    release_date[0] = '\0';
}

Release::Release(const char* id, const char* name, const char* date)
{
    strncpy(release_ID, id, sizeof(release_ID));
    release_ID[sizeof(release_ID) - 1] = '\0';

    strncpy(product_name, name, sizeof(product_name));
    product_name[sizeof(product_name) - 1] = '\0';

    strncpy(release_date, date, sizeof(release_date));
    release_date[sizeof(release_date) - 1] = '\0';
}

// Initialize the release file
bool initRelease()
{
    ReleaseFileStream.open("Release.bin", ios::in | ios::out | ios::binary | ios::app);
    if (!ReleaseFileStream) 
    {
        return false;
    }
    return true;
}

// Shut down the release file
bool closeRelease()
{
    if(ReleaseFileStream.is_open()) 
    {
        ReleaseFileStream.close();
        if(ReleaseFileStream.is_open())
        {
            return false;
        }
        return true;
    }
    return true;
}

// Move the get pointer to the beginning of the release file
void seekToBeginningOfReleaseFile()
{
    ReleaseFileStream.clear();
    ReleaseFileStream.seekg(0, ios::beg);
}

// Add a new release to file
bool addRelease(Release* rel)
{
    ReleaseFileStream.clear();
    if(ReleaseFileStream.write(reinterpret_cast<char*>(rel), sizeof(Release)))
    {
        ReleaseFileStream.flush();
        return true;
    }
    return false;
}

// Filter release by product name
bool filterNextRelease(Release* rel, char* prod_name)
{
    while(ReleaseFileStream.read(reinterpret_cast<char*>(rel), sizeof(Release))) 
    {
        if(strcmp(rel->product_name, prod_name) == 0) 
        {
            return true;
        }        
    }
    return false;
}
