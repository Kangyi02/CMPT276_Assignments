#include "Release.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream ReleaseFileStream;

Release::Release() {
    release_ID[0] = '\0';
    product_name[0] = '\0';
    release_date[0] = '\0';
}

Release::Release(const char* id, const char* name, const char* date)
{
    strncpy(release_ID, id, sizeof(release_ID));

    strncpy(product_name, name, sizeof(product_name));

    strncpy(release_date, date, sizeof(release_date));
}

bool initRelease()
{
    ReleaseFileStream.open("Release.bin", ios::in | ios::out | ios::binary | ios::ate);
    if (!ReleaseFileStream) 
    {
        return false;
    }
    return true;
}


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

void seekToBeginningOfReleaseFile()
{
    ReleaseFileStream.seekg(0, ios::beg);
}

bool addRelease(Release* rel)
{
    if(ReleaseFileStream.write(reinterpret_cast<char*>(rel), sizeof(Release)))
    {
        return true;
    }
    return false;
}

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