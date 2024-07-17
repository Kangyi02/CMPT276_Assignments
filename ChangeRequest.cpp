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
    for(int i = 0; i < sizeof(change_ID); ++i) 
    {
        change_ID[i] = id[i];
    }

    strncpy(requester_name, name, sizeof(requester_name));

    strncpy(request_date, date, sizeof(request_date));

    strncpy(reported_release_ID, releaseID, sizeof(reported_release_ID));
}

bool initChangeRequest() 
{
    changeRequestFileStream.open("ChangeRequest.bin", ios::in | ios::out | ios::binary | ios::ate);
    if (!changeRequestFileStream) 
    {
        return false;
    }
    return true;
}

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
void seekToBeginningOfChangeRequestFile() 
{
        changeRequestFileStream.seekg(0, ios::beg);
}

bool getNextChangeRequest(ChangeRequest* chreq) 
{
    if(changeRequestFileStream.read(reinterpret_cast<char*>(chreq), sizeof(ChangeRequest)))
    {
        return true;
    }
    return false;
}

bool addChangeRequest(ChangeRequest* chreq)
{
    if(changeRequestFileStream.write(reinterpret_cast<char*>(chreq), sizeof(ChangeRequest)))
    {
        return true;
    }
    return false;
}

bool filterNextChangeRequest(ChangeRequest* chreq, int* change_ID, char* release_ID)
{

}