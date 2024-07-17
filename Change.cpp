#include "Change.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream ChangeFileStream;

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
    // Initialize all the attritutes with provided data
    for(int i = 0; i < sizeof(change_ID) - 1; ++i) 
    {
        change_ID[i] = id[i];
    }
    change_ID[sizeof(change_ID) - 1] = '\0'; // Ensure null termination

    for(int i = 0; i < sizeof(priority) - 1; ++i) 
    {
        priority[i] = prio[i];
    }
    priority[sizeof(priority) - 1] = '\0';

    strncpy(status, stat, sizeof(status));
    status[sizeof(status) - 1] = '\0';

    strncpy(description, desc, sizeof(description));
    description[sizeof(description) - 1] = '\0';

    strncpy(product_name, prodname, sizeof(product_name));
    product_name[sizeof(product_name) - 1] = '\0';

    strncpy(anticipated_release_ID, arid, sizeof(anticipated_release_ID));
    anticipated_release_ID[sizeof(anticipated_release_ID) - 1] = '\0';
}

// Initialize the change file
bool initChange()
{
    ChangeFileStream.open("Change.bin", ios::in | ios::out | ios::binary | ios::ate);
    if (!ChangeFileStream) 
    {
        return false;
    }
    return true;
}

// Shut down the change file
bool closeChange()
{
    if(ChangeFileStream.is_open()) 
    {
        ChangeFileStream.close();
        if(ChangeFileStream.is_open())
        {
            return false;
        }
        return true;
    }
    return true;
}

// Move the get pointer to the beginning of the change file
void seekToBeginningOfChangeFile()
{
    ChangeFileStream.seekg(sizeof(Change), ios::beg); //skip the first dummy record
}

// Get a next change 
bool getNextChange(Change* ch)
{
    if(ChangeFileStream.read(reinterpret_cast<char*>(ch), sizeof(Change)))
    {
        return true;
    }
    return false;
}

// Add a new change to file
bool addChange(Change* ch)
{
    if(ChangeFileStream.write(reinterpret_cast<char*>(ch), sizeof(Change)))
    {
        updateChangeIDrec();
        return true;
    }
    return false;
}

// Update attritube of provided change
bool updateChange(Change* ch)
{
    
}

// Filter change by product name
bool filterNextChange(Change* ch, char* prod_name)
{
    while(ChangeFileStream.read(reinterpret_cast<char*>(ch), sizeof(Change))) 
    {
        if(strcmp(ch->product_name, prod_name) == 0) 
        {
            return true;
        }        
    }
    return false;
}

// Filter change by product name, but exclude done or cancelled change
bool filterNextChange_DoneOrCancelled(Change* ch, char* prod_name)
{
    while(filterNextChange(ch, prod_name))
    {
        if(strcmp(ch->status, "Reported") == 0 || 
            strcmp(ch->status, "Evaluated") == 0 || 
            strcmp(ch->status, "In process") == 0 )
        {
            return true;
        }
    }
    return false;
}

// Get change ID for next change
bool getNextCID(int* id)
{
    Change currentChange;
    ChangeFileStream.seekg(0, ios::beg); 
    if(ChangeFileStream.read(reinterpret_cast<char*>(&currentChange), sizeof(Change)))
    {
        memcpy(id, currentChange.change_ID, sizeof(currentChange.change_ID));
        int changeIDValue = 0;
        for (int i = 0; i < 6; ++i)
        {
            changeIDValue = changeIDValue * 10 + id[i];
        }
        // Increment the change ID
        changeIDValue += 1;

        // Convert back to change_ID array
        int newID[6] = {0};
        for (int i = 5; i >= 0; --i)
        {
            id[i] = changeIDValue % 10; //now id has next change ID
            changeIDValue /= 10;
        }
        return true;
    }
    return false;
}

// Update change ID in the dummy object by incrementing
bool updateChangeIDrec()
{
    Change currentChange;
    ChangeFileStream.seekg(0, ios::beg);
    ChangeFileStream.read(reinterpret_cast<char*>(&currentChange), sizeof(Change));
    // Convert change_ID array to a single integer
    int changeIDValue = 0;
    for (int i = 0; i < 6; ++i)
    {
        changeIDValue = changeIDValue * 10 + currentChange.change_ID[i];
    }
    // Increment the change ID
    changeIDValue += 1;

    // Convert back to change_ID array
    for (int i = 5; i >= 0; --i)
    {
        currentChange.change_ID[i] = changeIDValue % 10;
        changeIDValue /= 10;
    }
    ChangeFileStream.seekg(0, ios::beg); 
    ChangeFileStream.write(reinterpret_cast<char*>(&currentChange), sizeof(Change));
}