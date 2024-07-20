#include "Requester.h"
#include <iostream>
#include <fstream>
#include <cstring> // Add this line

using namespace std;

fstream RequesterFileStream;

// Default constructor implementation
Requester::Requester() 
{
    //initialize all the attributes
    requester_name[0] = '\0';
    phone_number[0] = '\0';
    email[0] = '\0';
    department[0] = '\0';
}

// Parameterized constructor implementation
Requester::Requester(const char* name, const int* phone, const char* email_addr, const char* dept) 
{
    // Initialize all the attribute with provided data
    strncpy(requester_name, name, sizeof(requester_name) - 1);
    requester_name[sizeof(requester_name) - 1] = '\0'; // Ensure null termination

    for(int i = 0; i < 11; ++i) 
    {
        phone_number[i] = phone[i];
    }

    strncpy(email, email_addr, sizeof(email) - 1);
    email[sizeof(email) - 1] = '\0';

    strncpy(department, dept, sizeof(department) - 1);
    department[sizeof(department) - 1] = '\0'; 
}

// Initialize the requester file
bool initRequester() 
{
    RequesterFileStream.open("Requester.bin", ios::in | ios::out | ios::binary | ios::app);
    if (!RequesterFileStream) 
    {
        return false;
    }
    return true;
}

// Shut down the requester file
bool closeRequester()
{
    if(RequesterFileStream.is_open()) 
    {
        RequesterFileStream.close();
        if(RequesterFileStream.is_open())
        {
            return false;
        }
        return true;
    }
    return true;
}

// Move the get pointer to the beginning of the requester file
void seekToBeginningOfRequesterFile() 
{
    RequesterFileStream.seekg(0, ios::beg);
}

// Get a next requester
bool getNextRequester(Requester* req) 
{
    if(RequesterFileStream.read(reinterpret_cast<char*>(req), sizeof(Requester)))
    {
        return true;
    }
    else
    {
        cout << "No additional records, this is the end of the file." << endl;
        return false;
    }
}

// Store a new requester to file
bool addRequester(Requester* req) 
{
    if(RequesterFileStream.write(reinterpret_cast<char*>(req), sizeof(Requester)))
    {
        RequesterFileStream.flush();
        return true;
    }
    return false;
}

// Filter requesters by name
bool filterNextRequester(Requester* req, char* req_name) 
{
    while(RequesterFileStream.read(reinterpret_cast<char*>(req), sizeof(Requester))) 
    {
        if(strcmp(req->requester_name, req_name) == 0) 
        {
            return true;
        }        
    }
    cout << "No additional records, this is the end of the file." << endl;
    return false; //return false if reach the end of the file
}
