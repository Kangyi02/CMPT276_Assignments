// DEFINITION MODULE Change;
// Revision History:
// Rev. 2 - 24/07/17 Modified by Group 24
//        - Add seek to beginning of file function
//        - Add filter function
//        - Update Function Naming: Rename the get function to getNext
//        - Modify Function Parameters: adjust get and filter function's parameters
// Rev. 1 - 24/07/19 Original by Group 24
// ----------------------------------------------------------
// This module encapsulates the implementation details of managing changes
// associated with products. The exported functions provide an interface to create,
// update, and display changes. Changes are identified by a unique ID and can be
// associated with specific products and releases. The functions also allow for
// reporting the status of changes, with specific handling for changes that are not
// completed or canceled. This abstraction ensures that the underlying management
// of changes is hidden, providing a clean and straightforward interface for
// interaction. The design supports future modifications to the handling of change
// data without affecting the external interface.
// ----------------------------------------------------------

#ifndef Change_H
#define Change_H

// Change class
class Change
{
public:
    int change_ID[7]; // max 6 digits
    int priority[2]; // 1 digit from 1 to 5
    char status[11]; // 'reported’, ‘evaluate’, ‘in process’, ‘cancelled’ or ‘done’
    char description[31]; // max 30 chars
    char product_name[11]; // max 10 chars
    char anticipated_release_ID[9]; // max 8 chars

    // constructors
    Change();
    Change(const char* id, const int* prio, const char* status, const char* desc, const char* prodname, const char* arid);
};



// Initialize the change file
bool initChange();

// Shut down the change file
bool closeChange();

void seekToBeginningOfChangeFile();

// Get a next change
bool getNextChange(Change* ch);

// Create a new change for a product
bool addChange(Change* change); 

// Overwrite an existing change with provided change
bool updateChange(Change* change);

// Get a next change with the provided product name
bool filterNextChange(Change* ch, char* prod_name);

// Get a next change which is in the specified status
bool filterNextChange_DoneOrCancelled(Change* ch, char* prod_name);


bool getNextCID(int* id);

bool updateChangeIDrec();

#endif
