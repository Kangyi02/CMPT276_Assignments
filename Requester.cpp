#include "Requester.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string.h>

using namespace std;

fstream RequesterFileStream;

// Default constructor implementation
Requester::Requester()
{
    // initialize all the attributes
    requester_name[0] = '\0';
    phone_number = 0;
    email[0] = '\0';
    department[0] = '\0';
}

// --------------------------------------------------------------------------------------

// Parameterized constructor implementation
Requester::Requester(const char* name, const int64_t phone, const char *email_addr, const char *dept)
{
    // Initialize all the attribute with provided data
    strncpy(requester_name, name, sizeof(requester_name) - 1);
    requester_name[sizeof(requester_name) - 1] = '\0'; // Ensure null termination

    phone_number = phone;

    strncpy(email, email_addr, sizeof(email) - 1);
    email[sizeof(email) - 1] = '\0';

    strncpy(department, dept, sizeof(department) - 1);
    department[sizeof(department) - 1] = '\0';
}

// --------------------------------------------------------------------------------------

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

// --------------------------------------------------------------------------------------

// Shut down the requester file
bool closeRequester()
{
    if (RequesterFileStream.is_open())
    {
        RequesterFileStream.close();
        if (RequesterFileStream.is_open())
        {
            return false;
        }
        return true;
    }
    return true;
}

// --------------------------------------------------------------------------------------

// Move the get pointer to the beginning of the requester file
void seekToBeginningOfRequesterFile()
{
    RequesterFileStream.clear();
    RequesterFileStream.seekg(0, ios::beg);
}

// --------------------------------------------------------------------------------------

// Get a next requester
bool getNextRequester(Requester *req)
{
    RequesterFileStream.clear();
    if (RequesterFileStream.read(reinterpret_cast<char *>(req), sizeof(Requester)))
    {
        RequesterFileStream.flush();
        return true;
    }
    else
    {
        return false;
    }
}

// --------------------------------------------------------------------------------------

// Store a new requester to file
bool addRequester(Requester *req)
{
    RequesterFileStream.clear();
    if (RequesterFileStream.write(reinterpret_cast<char *>(req), sizeof(Requester)))
    {
        RequesterFileStream.flush();
        return true;
    }
    return false;
}

// --------------------------------------------------------------------------------------

// Filter requesters by name
bool filterNextRequester(Requester *req, char *req_name)
{
    while (RequesterFileStream.read(reinterpret_cast<char *>(req), sizeof(Requester)))
    {
        if (strcmp(req->requester_name, req_name) == 0)
        {
            return true;
        }
    }
    return false; // return false if reach the end of the file
}
