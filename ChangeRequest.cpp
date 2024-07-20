// Version History:
// Rev. 1 - 24/07/17 Original by Group 24
// ----------------------------------------------------------
// Implement ChangeRequest.h
// ----------------------------------------------------------

#include "ChangeRequest.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream changeRequestFileStream;

//constructor
ChangeRequest::ChangeRequest()
{
    change_ID[0] = '\0';
    requester_name[0] = '\0';
    request_date[0] = '\0';
    reported_release_ID[0] = '\0';
}

ChangeRequest::ChangeRequest(const int* id, const char* name, const char* date, const char* releaseID)
{
    // Initialize all the attributes with provided data
    for(int i = 0; i < sizeof(change_ID) - 1; ++i) 
    {
        change_ID[i] = id[i];
    }

    strncpy(requester_name, name, sizeof(requester_name));
    requester_name[sizeof(requester_name) - 1] = '\0';

    strncpy(request_date, date, sizeof(request_date));
    request_date[sizeof(request_date) - 1] = '\0';

    strncpy(reported_release_ID, releaseID, sizeof(reported_release_ID));
    reported_release_ID[sizeof(reported_release_ID) - 1] = '\0';
}

// Initialize the change request file
bool initChangeRequest() 
{
    changeRequestFileStream.open("ChangeRequest.bin", ios::in | ios::out | ios::binary | ios::app);
    if (!changeRequestFileStream) 
    {
        return false;
    }
    return true;
}

// Shut down the change requst file
bool closeChangeRequest() 
{
    if(changeRequestFileStream.is_open()) 
    {
        changeRequestFileStream.close();
        if(changeRequestFileStream.is_open())
        {
            return false;
        }
        return true;
    }
    return true;
}

// Move the get pointer to the beginning of the chnage request file
void seekToBeginningOfChangeRequestFile() 
{
        changeRequestFileStream.seekg(0, ios::beg);
}

// Get a next change request
bool getNextChangeRequest(ChangeRequest* chreq) 
{
    if(changeRequestFileStream.read(reinterpret_cast<char*>(chreq), sizeof(ChangeRequest)))
    {
        return true;
    }
    return false;
}

// Add a new change request to file
bool addChangeRequest(ChangeRequest* chreq)
{
    if(changeRequestFileStream.write(reinterpret_cast<char*>(chreq), sizeof(ChangeRequest)))
    {
        return true;
    }
    return false;
}

// Search for change request with provided change ID, return one at a time. false if reach the end of the file
bool filterNextChangeRequest(ChangeRequest* chreq, int* ch_ID)
{
    while(changeRequestFileStream.read(reinterpret_cast<char*>(chreq), sizeof(ChangeRequest)))
    {
        for(int i = 0; i < sizeof(chreq->change_ID); ++i)
        {
            if(ch_ID[i] != chreq->change_ID[i])
            {
                return true;
            }
        }
    }
    return false;
}
