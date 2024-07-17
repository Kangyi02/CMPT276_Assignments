#include "Requester.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream requesterFileStream;

// Default constructor implementation
Requester::Requester() 
{
    requester_name[0] = '\0';
    phone_number[0] = '\0';
    email[0] = '\0';
    department[0] = '\0';
}

// Parameterized constructor implementation
Requester::Requester(const char* name, const int* phone, const char* email_addr, const char* dept) 
{
    // Initialize requester_name with the provided name, ensuring it does not exceed the max length
    strncpy(requester_name, name, sizeof(requester_name) - 1);
    requester_name[sizeof(requester_name) - 1] = '\0'; // Ensure null termination

    // Initialize phone_number with the provided phone number
    for(int i = 0; i < 11; ++i) 
    {
        phone_number[i] = phone[i];
    }

    // Initialize email with the provided email address, ensuring it does not exceed the max length
    strncpy(email, email_addr, sizeof(email) - 1);
    email[sizeof(email) - 1] = '\0'; // Ensure null termination

    // Initialize department with the provided department, ensuring it does not exceed the max length
    strncpy(department, dept, sizeof(department) - 1);
    department[sizeof(department) - 1] = '\0'; // Ensure null termination
}

// Initialize the requester file
bool initRequester() 
{
    requesterFileStream.open("Requester.bin", ios::in | ios::out | ios::binary | ios::ate);
    if (!requesterFileStream) 
    {
        return false;
    }
    return true;
}

// Shut down the requester file
bool closeRequester()
{
    if(requesterFileStream.is_open()) 
    {
        requesterFileStream.close();
        if(requesterFileStream.is_open())
        {
            return false;
        }
        return true;
    }
    return true;
}

void seekToBeginningOfRequesterFile() 
{
    requesterFileStream.seekg(0, ios::beg);
}

// Get the next requester
bool getNextRequester(Requester* req) 
{
    if(requesterFileStream.read(reinterpret_cast<char*>(req), sizeof(Requester)))
    {
        return true;
    }
    return false;
}

// Store a new requester to file
bool addRequester(Requester* req) 
{
    if(requesterFileStream.write(reinterpret_cast<char*>(req), sizeof(Requester)))
    {
        return true;
    }
    return false;
}

// Filter requesters by name
bool filterNextRequester(Requester* req, char* name) 
{
    while(requesterFileStream.read(reinterpret_cast<char*>(req), sizeof(Requester))) 
    {
        if(strcmp(req->requester_name, name) == 0) 
        {
            return true;
        }        
    }
    return false;
}
