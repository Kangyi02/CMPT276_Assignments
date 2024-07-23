// Version History:
// Rev. 1 - 24/07/17 Original by Group 24
// ----------------------------------------------------------
// Implement Change.h
// ----------------------------------------------------------

#include "StartUp.h"
#include <iostream>

using namespace std;

bool initStart() {
    bool allSuccess = true;

    // Initialize Product
    bool stupProduct = initProduct();
    if (stupProduct) {
        cout << "Product module initialized successfully. \n";
    } else {
        cout << "Failed to initialize Product module. \n";
        allSuccess = false;
    }

    // Initialize Release
    bool stupRelease = initRelease();
    if (stupRelease) {
        cout << "Release module initialized successfully. \n";
    } else {
        cout << "Failed to initialize Release module. \n";
        allSuccess = false;
    }

    // Initialize Requester
    bool stupRequester = initRequester();
    if (stupRequester) {
        cout << "Requester module initialized successfully. \n";
    } else {
        cout << "Failed to initialize Requester module. \n";
        allSuccess = false;
    }

    // Initialize Change
    bool stupChange = initChange();
    if (stupChange) {
        cout << "Change module initialized successfully. \n";
    } else {
        cout << "Failed to initialize Change module. \n";
        allSuccess = false;
    }

    // Initialize Change Request
    bool stupChangeRequest = initChangeRequest();
    if (stupChangeRequest) {
        cout << "Change Request module initialized successfully. \n";
    } else {
        cout << "Failed to initialize Change Request module. \n";
        allSuccess = false;
    }

    return allSuccess;
}
