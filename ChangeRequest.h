
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
private:
    //char* requester_name; // max 30 chars
    int change_ID;  // max 6 digits
public:
    char requester_name[21]; // max 20 chars: last name, first name
    char* request_date; // YYYY-MM-DD
    char* reported_release_ID; // max 8 chars

    // Constructors
    ChangeRequest();
    ChangeRequest(const char* name, const int id, const char* date, const char* releaseID);
    ChangeRequest(const ChangeRequest& other);

    // Destructor
    ~ChangeRequest();

    //will move to cpp file
    

    void setChange_ID(int c_ID)
    {
        change_ID = c_ID;
    }

    int getChange_ID()
    {
        return change_ID;
    }
};

// Initialize the change request file
void initChangeRequest();

// Shut down the change request file
void closeChangeRequest();

// Create a new change request 
void createChangeRequest(ChangeRequest* new_cr);

// Get a single change request record
ChangeRequest* getChangeRequest();

void seekToBeginningOfChangeRequestFile();

ChangeRequest* filterChangeRequest(int change_ID, char* release_ID);
#endif