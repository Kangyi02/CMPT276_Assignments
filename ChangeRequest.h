
// DEFINITION MODULE ChangeRequest;
/* Revision History:
Rev. 1 - 24/07/03 Original by Group 24
----------------------------------------------------------
This module encapsulates the implementation details of managing change requests
associated with products and releases. The exported functions provide an interface to
create and manage change requests. Change requests are identified by a unique ID and
can be associated with specific products and releases. This abstraction ensures that
the underlying management of change requests is hidden, providing a clean and
straightforward interface for interaction.
----------------------------------------------------------
*/

#ifndef ChangeRequest_H
#define ChangeRequest_H

extern int changeRequestPosition;

/*
----------------------------------------------------------
// Exported constants/types/variables
*/

// Change request class
class ChangeRequest
{
public:
    //char* requester_name; // max 30 chars
    int change_ID[7];  // max 6 digits
    char requester_name[21]; // max 20 chars: last name, first name
    char request_date[9]; // YYYY-MM-DD
    char reported_release_ID[9]; // max 8 chars

    // Constructors
    ChangeRequest();
    ChangeRequest(const char* name, const int id, const char* date, const char* releaseID);
};

// Initialize the change request file
void initChangeRequest();

// Shut down the change request file
void closeChangeRequest();

// Create a new change request 
void createChangeRequest(ChangeRequest* new_cr);

// Get a single change request record
bool getNextChangeRequest(ChangeRequest* chreq);

void seekToBeginningOfChangeRequestFile();

ChangeRequest* filterChangeRequest(int change_ID, char* release_ID);
#endif