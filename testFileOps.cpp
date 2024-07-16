// testFileOps.cpp

#include <iostream>
#include <cassert>
#include <cstring>
#include "requester.h"

// Helper function to compare Requester objects
bool compareRequesters(const Requester& r1, const Requester& r2) {
    return (strcmp(r1.requester_name, r2.requester_name) == 0 &&
            memcmp(r1.phone_number, r2.phone_number, sizeof(r1.phone_number)) == 0 &&
            strcmp(r1.email, r2.email) == 0 &&
            strcmp(r1.department, r2.department) == 0);
}

void testRequesterFileOps() {
    // Initialize the requester file
    initRequester();

    // Create a few requester records
    int phone1[11] = {1,2,3,4,5,6,7,8,9,0,0};
    int phone2[11] = {9,8,7,6,5,4,3,2,1,0,0};
    
    Requester requester1("Alice Johnson", phone1, "alice@example.com", "HR");
    Requester requester2("Bob Smith", phone2, "bob@example.com", "IT");

    // Manually set requester data for the test
    strcpy(requester1.requester_name, "Alice Johnson");
    for (int i = 0; i < 11; ++i) requester1.phone_number[i] = phone1[i];
    strcpy(requester1.email, "alice@example.com");
    strcpy(requester1.department, "HR");

    strcpy(requester2.requester_name, "Bob Smith");
    for (int i = 0; i < 11; ++i) requester2.phone_number[i] = phone2[i];
    strcpy(requester2.email, "bob@example.com");
    strcpy(requester2.department, "IT");

    // Write the requester records to file
    createRequester();  // Assuming this function writes the current requester
    createRequester();  // Call it twice for two records

    // Read the requester records from file
    seekToBeginningOfRequesterFile();

    Requester readRequester1 = getNextRequester();
    Requester readRequester2 = getNextRequester();

    // Check if the read data is the same as the written data
    assert(compareRequesters(readRequester1, requester1));
    assert(compareRequesters(readRequester2, requester2));

    // Verify that no additional records are read
    Requester dummy = getNextRequester();
    assert(std::string(dummy.requester_name) == "");

    std::cout << "Pass" << std::endl;

    // Close the requester file
    closeRequester();
}

int main() {
    testRequesterFileOps();
    return 0;
}
