#include "Change.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream changeFileStream;

Change::Change()
{
    change_ID[0] = '\0';
    priority[0] = '\0';
    status[0] = '\0';
    description[0] = '\0';
    product_name[0] = '\0';
    anticipated_release_ID[0] = '\0';
}
    
Change::Change(const char* id, const int* prio, const char* stat, const char* desc, const char* prodname, const char* arid)
{
    for(int i = 0; i < sizeof(change_ID); ++i) 
    {
        change_ID[i] = id[i];
    }

    for(int i = 0; i < sizeof(priority); ++i) 
    {
        priority[i] = prio[i];
    }

    strncpy(status, stat, sizeof(status));

    strncpy(description, desc, sizeof(description));

    strncpy(product_name, prodname, sizeof(product_name));

    strncpy(anticipated_release_ID, arid, sizeof(anticipated_release_ID));
}

bool initChange()
{
    changeFileStream.open("Change.bin", ios::in | ios::out | ios::binary | ios::ate);
    if (!changeFileStream) 
    {
        return false;
    }
    return true;
}

bool closeChange()
{
    if(changeFileStream.is_open()) 
    {
        changeFileStream.close();
        if(changeFileStream.is_open())
        {
            return false;
        }
        return true;
    }
    return true;
}

void seekToBeginningOfChangeFile()
{
    changeFileStream.seekg(0, ios::beg);
}

bool getNextChange(Change* ch)
{
    if(changeFileStream.read(reinterpret_cast<char*>(ch), sizeof(Change)))
    {
        return true;
    }
    return false;
}

bool addChange(Change* ch)
{
    if(changeFileStream.write(reinterpret_cast<char*>(ch), sizeof(Change)))
    {
        return true;
    }
    return false;
}

bool updateChange(Change* ch)
{

}

bool filterNextChange(Change* ch, char* prod_name)
{
    while(changeFileStream.read(reinterpret_cast<char*>(ch), sizeof(Change))) 
    {
        if(strcmp(ch->product_name, prod_name) == 0) 
        {
            return true;
        }        
    }
    return false;
}

bool filterNextChange_DoneOrCancelled(Change* ch, char* product_name)
{

}