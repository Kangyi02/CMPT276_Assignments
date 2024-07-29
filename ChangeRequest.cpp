// Version History:
// Rev. 1 - 24/07/17 Original by Group 24
// ----------------------------------------------------------
// Implement ChangeRequest.h
// ----------------------------------------------------------

#include "ChangeRequest.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream ChangeRequestFileStream;

//constructor
ChangeRequest::ChangeRequest()
{
    change_ID = 0;
    requester_name[0] = '\0';
    request_date[0] = '\0';
    reported_release_ID[0] = '\0';
}

ChangeRequest::ChangeRequest(const int32_t id, const char* name, const char* date, const char* releaseID)
{
    // Initialize all the attributes with provided data
    change_ID = id;

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
    ChangeRequestFileStream.open("ChangeRequest.bin", ios::in | ios::out | ios::binary | ios::app);
    if (!ChangeRequestFileStream) 
    {
        return false;
    }
    return true;
}

// Shut down the change requst file
bool closeChangeRequest() 
{
    if(ChangeRequestFileStream.is_open()) 
    {
        ChangeRequestFileStream.close();
        if(ChangeRequestFileStream.is_open())
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
    ChangeRequestFileStream.clear();
    ChangeRequestFileStream.seekg(0, ios::beg);
}

// Get a next change request
bool getNextChangeRequest(ChangeRequest* chreq) 
{
    ChangeRequestFileStream.clear();
    if(ChangeRequestFileStream.read(reinterpret_cast<char*>(chreq), sizeof(ChangeRequest)))
    {
        return true;
    }
    return false;
}

// Add a new change request to file
bool addChangeRequest(ChangeRequest* chreq)
{
    ChangeRequestFileStream.clear();
    if(ChangeRequestFileStream.write(reinterpret_cast<char*>(chreq), sizeof(ChangeRequest)))
    {
        ChangeRequestFileStream.flush();
        return true;
    }
    return false;
}

// Search for change request with provided change ID, return one at a time. false if reach the end of the file
bool filterNextChangeRequest(ChangeRequest* chreq, int32_t ch_ID)
{
    while(ChangeRequestFileStream.read(reinterpret_cast<char*>(chreq), sizeof(ChangeRequest)))
    {
        if (chreq->change_ID == ch_ID)
        {
            return true;
        }
    }
    return false;
}
