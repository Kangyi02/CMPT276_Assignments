// Version History:
// Rev. 1 - 24/07/15 Original by Group 24
//----------------------------------------------------------
// This test driver verifies the creation and retrieval of 
// requester records in a file using the Requester module. 
// The test includes writing requester records to a file and 
// reading back the records to ensure data integrity.
//----------------------------------------------------------

#include <iostream>
#include <cassert>
#include <cstring>
#include "Requester.h"

// Helper function to compare Requester objects
bool compareRequesters(const Requester& r1, const Requester& r2) {
    return strcmp(r1.requester_name, r2.requester_name) == 0 &&
           memcmp(r1.phone_number, r2.phone_number, sizeof(r1.phone_number)) == 0 &&
           strcmp(r1.email, r2.email) == 0 &&
           strcmp(r1.department, r2.department) == 0;
}

int main() {
    // Initialize the requester file
    assert(initRequester());

    // Create a few requester records
    Requester requester1;
    const char name1[] = "Alice Johnson";
    const int phone1[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0};
    const char email1[] = "alice@example.com";
    const char dept1[] = "HR";
    strncpy(requester1.requester_name, name1, sizeof(requester1.requester_name) - 1);
    requester1.requester_name[sizeof(requester1.requester_name) - 1] = '\0';
    memcpy(requester1.phone_number, phone1, sizeof(phone1));
    strncpy(requester1.email, email1, sizeof(requester1.email) - 1);
    requester1.email[sizeof(requester1.email) - 1] = '\0';
    strncpy(requester1.department, dept1, sizeof(requester1.department) - 1);
    requester1.department[sizeof(requester1.department) - 1] = '\0';

    Requester requester2;
    const char name2[] = "Bob Smith";
    const int phone2[11] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0};
    const char email2[] = "bob@example.com";
    const char dept2[] = "IT";
    strncpy(requester2.requester_name, name2, sizeof(requester2.requester_name) - 1);
    requester2.requester_name[sizeof(requester2.requester_name) - 1] = '\0';
    memcpy(requester2.phone_number, phone2, sizeof(phone2));
    strncpy(requester2.email, email2, sizeof(requester2.email) - 1);
    requester2.email[sizeof(requester2.email) - 1] = '\0';
    strncpy(requester2.department, dept2, sizeof(requester2.department) - 1);
    requester2.department[sizeof(requester2.department) - 1] = '\0';

    // Write the requester records to file
    assert(addRequester(&requester1));
    assert(addRequester(&requester2));

    // Read the requester records from file
    seekToBeginningOfRequesterFile();

    Requester readRequester1;
    Requester readRequester2;

    assert(getNextRequester(&readRequester1));
    assert(getNextRequester(&readRequester2));

    // Check if the read data is the same as the written data
    assert(compareRequesters(readRequester1, requester1));
    assert(compareRequesters(readRequester2, requester2));

    // Verify that no additional records are read
    Requester dummy;
    assert(!getNextRequester(&dummy));

    // Close the requester file
    assert(closeRequester());

    std::cout << "File write and read back test: Pass" << std::endl;
    return 0;
}
