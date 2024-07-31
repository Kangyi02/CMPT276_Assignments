// DEFINITION MODULE Requester;
// Revision History:
// Rev. 2 - 24/07/17 Modified by Group 24
//        - Add seek to beginning of file function
//        - Add filter function
//        - Update Function Naming: Rename the get function to getNext
//        - Modify Function Parameters: adjust get and filter function's parameters
// Rev. 1 - 24/07/03 Original by Group 24
// ----------------------------------------------------------
// This module encapsulates the implementation details of managing requesters.
// The exported functions provide an interface to create, initialize, and manage
// requesters, including their contact details. Each requester is identified by
// their name, phone number, and email address. This abstraction ensures that
// the underlying management of requesters is hidden, providing a clean and
// straightforward interface for interaction.
// ----------------------------------------------------------

#ifndef Requester_H
#define Requester_H

#include <cstdint>

// Requester class
class Requester 
{
public:
    char requester_name[31]; // max 30 chars: last name, first name
    int64_t phone_number; //
    char email[25]; // max 24 chars
    char department[13];

    Requester();
    Requester(const char* name, const int64_t phone, const char* email_addr, const char* dept);
};

// Initialize the requester file
bool initRequester();

// Shut down the requester file
bool closeRequester();

void seekToBeginningOfRequesterFile();

// Get requester name 
bool getNextRequester(Requester* req);

// Create a new requester
bool addRequester(Requester* req);

// Filter requester by their name
bool filterNextRequester(Requester* req, char* name);

#endif
