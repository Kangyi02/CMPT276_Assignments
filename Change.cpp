// Version History:
// Rev. 1 - 24/07/17 Original by Group 24
// ----------------------------------------------------------
// Implement Change.h
// ----------------------------------------------------------

#include "Change.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>  // Needed this library for Windows

using namespace std;

fstream ChangeFileStream;

Change::Change()
{
    change_ID = 100000;
    priority = 0;
    status[0] = '\0';
    description[0] = '\0';
    product_name[0] = '\0';
    anticipated_release_ID[0] = '\0';
}

Change::Change(const int32_t id, const int32_t prio, const char* stat, const char* desc, const char* prodname, const char* arid)
{
    // Initialize all the attritutes with provided data
    change_ID = id;

    priority = prio;

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
    ifstream fileCheck("Change.bin");
    bool fileExists = fileCheck.good();
    fileCheck.close();

    // CAUSING PROBLEM HERE
    if (!fileExists)
    {
        // File does not exist, initialize the change file
        ChangeFileStream.open("Change.bin", ios::out | ios::app | ios::binary);

        Change dummy;
        ChangeFileStream.write(reinterpret_cast<char*>(&dummy), sizeof(Change));

        ChangeFileStream.close();
    }

    // Now open the file in the desired mode.
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
    ChangeFileStream.clear();
    ChangeFileStream.seekg(sizeof(Change), ios::beg); //skip the first dummy record
}

// Get a next change 
bool getNextChange(Change* ch)
{
    ChangeFileStream.clear();
    if(ChangeFileStream.read(reinterpret_cast<char*>(ch), sizeof(Change)))
    {
        return true;
    }
    return false;
}

// Add a new change to file
bool addChange(Change* ch)
{
    ChangeFileStream.clear();

    ch->change_ID = getNextCID();

    if(ch->change_ID == -1)
    {
        return false;
    }

    ChangeFileStream.seekp(0, ios::end); 

    if(ChangeFileStream.write(reinterpret_cast<char*>(ch), sizeof(Change)))
    {
        ChangeFileStream.flush();
        
        return true;
    }
    return false;
}

// Helper function of updateChange() that check if two int array is same
// Precondition: two array need to have the same length
bool intArrayEqual(int* arr1, int* arr2)
{
    for(int i = 0; i < sizeof(arr1); ++i)
    {
        if(arr1[i] != arr2[i])
        {
            return false;
        }
    }
    return true;
}

// Update attritube of provided change
bool updateChange(Change* ch)
{
    Change currentChange;
    ChangeFileStream.clear();
    ChangeFileStream.seekg(1, ios::beg); // set g to the beginning skipping dummy
    int position = 1; // counter for offset
    // loop until reach the end of file
    while(ChangeFileStream.read(reinterpret_cast<char*>(&currentChange), sizeof(Change)))
    {
        // start manipulation if change ID match
        if(currentChange.change_ID == ch->change_ID)
        {
            ChangeFileStream.seekp(position * sizeof(Change), ios::beg);
            ChangeFileStream.write(reinterpret_cast<const char*>(&currentChange), sizeof(Change));
            if (!ChangeFileStream) 
            {
            cout << "Error writing to file." << endl;
            return false;
            }
            return true;
        }
        position += 1;
    }
    return false;
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
// Return the next available change ID
// So you don't have to increment after calling this function.
int32_t getNextCID()
{
    Change dummy;
    ChangeFileStream.seekg(0, ios::beg);
    if(ChangeFileStream.read(reinterpret_cast<char*>(&dummy), sizeof(Change)))
    {
        cout << "in getnextcid" << dummy.change_ID;
        int32_t id = dummy.change_ID + 1;
        dummy.change_ID += 1;
        ChangeFileStream.seekp(0, ios::beg); 
        ChangeFileStream.write(reinterpret_cast<char*>(&dummy), sizeof(Change));
        ChangeFileStream.seekp(sizeof(Change), ios::beg);
        return id;
    }
    return -1;
}