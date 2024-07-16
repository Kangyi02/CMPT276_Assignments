// DEFINITION MODULE Requester;
/* Revision History:
Rev. 1 - 24/07/03 Original by Group 24
----------------------------------------------------------
This module encapsulates the implementation details of managing requesters.
The exported functions provide an interface to create, initialize, and manage
requesters, including their contact details. Each requester is identified by
their name, phone number, and email address. This abstraction ensures that
the underlying management of requesters is hidden, providing a clean and
straightforward interface for interaction.
----------------------------------------------------------
*/

#ifndef Requester_H
#define Requester_H

extern int requesterPosition;

/*
----------------------------------------------------------
// Exported constants/types/variables
*/

// Requester class
class Requester {
public:
    char requester_name[21]; // max 20 chars: last name, first name
    int phone_number[11]; // YYYY-MM-DD
    char email[25]; // max 24 chars
    char department[13];

    Requester();
};

// Initialize the requester file
void initRequester();

// Shut down the requester file
void closeRequester();

// Get requester name 
Requester getNextRequester();

// Create a new requester
char createRequester();

void seekToBeginningOfRequesterFile();

Requester filterRequester(char requester_name);
#endif