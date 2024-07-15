// DEFINITION MODULE Change;
/* Revision History:
Rev. 2 - 24/07/02 Modified by Group 24
       - to add one parameter to displaySingleChange.
Rev. 1 - 24/07/19 Original by Group 24
----------------------------------------------------------
This module encapsulates the implementation details of managing changes
associated with products. The exported functions provide an interface to create,
update, and display changes. Changes are identified by a unique ID and can be
associated with specific products and releases. The functions also allow for
reporting the status of changes, with specific handling for changes that are not
completed or canceled. This abstraction ensures that the underlying management
of changes is hidden, providing a clean and straightforward interface for
interaction. The design supports future modifications to the handling of change
data without affecting the external interface.
----------------------------------------------------------
*/

#ifndef Change_H
#define Change_H

#include "Release.h"
#include "ChangeRequest.h"
#include "Product.h"

/*
----------------------------------------------------------
//Exported constants/types/variables
*/
int CID = 0;

// Change class
class Change
{
private:
    int change_ID; // max 6 digits
public:
    int priority; // 1 digit from 1 to 5
    char* status; // 'reported’, ‘evaluate’, ‘in process’, ‘cancelled’ or ‘done’
    char* description; // max 30 chars
    char* product_name; // max 10 chars
    char* anticipated_release_ID; // max 8 chars

    // constructors
    Change();
    Change(const char* id, const int prio, const char* status, const char* desc, const char* pname, const char* arid);
    Change(const Change& other);
    // destructor
    ~Change();

    int getChange_ID()
    {
        return change_ID;
    }

    int setChange_ID()
    {
        change_ID = CID++;
    }
};

// Initialize the change file
void initChange();

// Shut down the change file
void closeChange();

// Get change ID
Change* getChange(char* product_name);

// Create a new change for a product
int createChange(Change* change);  

// Update a change except for its release ID
void updateChange(Change* new_change);

void seekToBeginningOfChangeFile();

Change* filterChange(char* product_name);

Change* filterChange_DoneOrCancelled(char* product_name);
#endif