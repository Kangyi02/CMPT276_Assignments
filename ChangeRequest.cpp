#include "ChangeRequest.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream changeRequestFileStream;

//constructor
ChangeRequest::ChangeRequest() : requester_name(new char[31]), request_date(new char[11]), reported_release_ID(new char[9]) {}

ChangeRequest::ChangeRequest(const char* name, const int id, const char* date, const char* releaseID) : ChangeRequest() 
{
    setRequester_name(const_cast<char*>(name));
    setChange_ID(id);
    strcpy(request_date, date);
    strcpy(reported_release_ID, releaseID);
}

ChangeRequest::ChangeRequest(const ChangeRequest& other) : ChangeRequest() 
{
    setRequester_name(other.requester_name);
    setChange_ID(other.change_ID);
    strcpy(request_date, other.request_date);
    strcpy(reported_release_ID, other.reported_release_ID);
}

//deconstructor
ChangeRequest::~ChangeRequest() 
{
    delete[] requester_name;
    delete[] request_date;
    delete[] reported_release_ID;
}

void initChangeRequest() 
{
    changeRequestFileStream.open("//file path", ios::in | ios::out | ios::binary | ios::app);
    if (!changeRequestFileStream) 
    {
        cerr << "Error: Could not open file." << endl;
    }
}

void closeChangeRequest() 
{
    if (changeRequestFileStream.is_open()) 
    {
        changeRequestFileStream.close();
    }
}

ChangeRequest* getChangeRequest() 
{
    if (changeRequestFileStream.is_open()) 
    {
        char name[31];
        int id;
        char date[11];
        char releaseID[9];

        changeRequestFileStream >> name >> id >> date >> releaseID;
        return new ChangeRequest(name, id, date, releaseID);
    } else 
    {
        cerr << "Error: File not open." << endl;
        return nullptr;
    }

    ChangeRequest* creq = new ChangeRequest();
    changeRequestFileStream.seekg(changeRequestPosition * sizeof(ChangeRequest), ios::beg);
    if (changeRequestFileStream.read(reinterpret_cast<char*>(creq), sizeof(ChangeRequest))) 
    {
        return creq;
    } else 
    {
        delete creq;
        return nullptr;
    }
}

void seekToBeginningOfChangeRequestFile() 
{
    if (changeRequestFileStream.is_open()) 
    {
        changeRequestFileStream.clear(); // Clear any error flags
        changeRequestFileStream.seekg(0, ios::beg);
    } else 
    {
        cerr << "Error: File not open." << endl;
    }
}

ChangeRequest* filter_ChangeRequest(int change_ID, char* release_ID) 
{
    if (changeRequestFileStream.is_open()) 
    {
        seekToBeginningOfChangeRequestFile();
        char name[31];
        int id;
        char date[11];
        char releaseID[9];

        while (changeRequestFileStream >> name >> id >> date >> releaseID) 
        {
            if (id == change_ID && strcmp(releaseID, release_ID) == 0) 
            {
                return new ChangeRequest(name, id, date, releaseID);
            }
        }
    } else 
    {
        cerr << "Error: File not open." << endl;
    }
    return nullptr;
}