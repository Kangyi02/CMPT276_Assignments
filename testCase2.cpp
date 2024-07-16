#include <iostream>
#include <cassert>
#include <cstring>
#include "change.h"

// Helper function to compare Change objects
bool compareChanges(const Change& c1, const Change& c2) {
    return c1.priority == c2.priority &&
           strcmp(c1.status, c2.status) == 0 &&
           strcmp(c1.description, c2.description) == 0 &&
           strcmp(c1.product_name, c2.product_name) == 0 &&
           strcmp(c1.anticipated_release_ID, c2.anticipated_release_ID) == 0;
}

int main() {
    // Initialize the change file
    initChange();

    // Create a new change
    Change change1("0", 3, "Reported", "Initial change description", "ProductA", "R1");
    change1.setChange_ID();  // Set a unique change ID
    createChange(&change1);  // Create the change

    // Verify the change was written to the file
    seekToBeginningOfChangeFile();
    Change* retrievedChange = getChange(change1.product_name);
    assert(retrievedChange != nullptr && compareChanges(change1, *retrievedChange));

    // Update the change
    Change updatedChange("0", 4, "In process", "Updated change description", "ProductA", "R2");
    updatedChange.setChange_ID();  // Keep the same change ID for update
    updateChange(&updatedChange);  // Update the change

    // Verify the change was updated
    seekToBeginningOfChangeFile();
    Change* updatedRetrievedChange = getChange(updatedChange.product_name);
    assert(updatedRetrievedChange != nullptr && compareChanges(updatedChange, *updatedRetrievedChange));

    // Shut down the change file
    closeChange();

    std::cout << "Pass" << std::endl;
    return 0;
}
