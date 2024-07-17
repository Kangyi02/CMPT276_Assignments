// Version History:
// Rev. 1 - 24/07/14 Original by Group 24
//----------------------------------------------------------
// This test driver verifies the creation and updating of 
// change records in a file using the Change module. The test 
// includes writing a change record to a file, updating it, 
// and reading back the records to ensure data integrity.
//----------------------------------------------------------

#include <iostream>
#include <cassert>
#include <cstring>
#include "Change.h"

// Helper function to compare Change objects
bool compareChanges(const Change& c1, const Change& c2) {
    return memcmp(c1.change_ID, c2.change_ID, sizeof(c1.change_ID)) == 0 &&
           memcmp(c1.priority, c2.priority, sizeof(c1.priority)) == 0 &&
           strcmp(c1.status, c2.status) == 0 &&
           strcmp(c1.description, c2.description) == 0 &&
           strcmp(c1.product_name, c2.product_name) == 0 &&
           strcmp(c1.anticipated_release_ID, c2.anticipated_release_ID) == 0;
}

int main() {
    // Initialize the change file
    assert(initChange());

    // Create a new change
    Change change1;
    int changeID1[7] = {0, 0, 0, 0, 0, 1};
    memcpy(change1.change_ID, changeID1, sizeof(changeID1));
    int priority1[2] = {3};
    memcpy(change1.priority, priority1, sizeof(priority1));
    strncpy(change1.status, "Reported", sizeof(change1.status) - 1);
    change1.status[sizeof(change1.status) - 1] = '\0';
    strncpy(change1.description, "Memory leak", sizeof(change1.description) - 1);
    change1.description[sizeof(change1.description) - 1] = '\0';
    strncpy(change1.product_name, "Editor", sizeof(change1.product_name) - 1);
    change1.product_name[sizeof(change1.product_name) - 1] = '\0';
    strncpy(change1.anticipated_release_ID, "R4.3B", sizeof(change1.anticipated_release_ID) - 1);
    change1.anticipated_release_ID[sizeof(change1.anticipated_release_ID) - 1] = '\0';

    assert(addChange(&change1));  // Create the change

    // Verify the change was written to the file
    seekToBeginningOfChangeFile();
    Change retrievedChange;
    assert(getNextChange(&retrievedChange));
    assert(compareChanges(change1, retrievedChange));

    // Update the change (without changing change_ID and product_name)
    int priority2[2] = {4};
    memcpy(retrievedChange.priority, priority2, sizeof(priority2));
    strncpy(retrievedChange.status, "In process", sizeof(retrievedChange.status) - 1);
    retrievedChange.status[sizeof(retrievedChange.status) - 1] = '\0';
    strncpy(retrievedChange.description, "Memory leak getting fixed", sizeof(retrievedChange.description) - 1);
    retrievedChange.description[sizeof(retrievedChange.description) - 1] = '\0';
    strncpy(retrievedChange.anticipated_release_ID, "R4.4B", sizeof(retrievedChange.anticipated_release_ID) - 1);
    retrievedChange.anticipated_release_ID[sizeof(retrievedChange.anticipated_release_ID) - 1] = '\0';

    assert(updateChange(&retrievedChange));  // Update the change

    // Verify the change was updated
    seekToBeginningOfChangeFile();
    Change updatedRetrievedChange;
    assert(getNextChange(&updatedRetrievedChange));
    assert(compareChanges(retrievedChange, updatedRetrievedChange));

    // Shut down the change file
    assert(closeChange());

    std::cout << "File write and read back test: Pass" << std::endl;
    return 0;
}
