#include "StartUp.h"
#include <iostream>

using namespace std;

bool initStart() {
    bool allSuccess = true;

    // Initialize Product
    bool stupProduct = initProduct();
    if (stupProduct) {
        cout << "Product module initialized successfully." << endl;
    } else {
        cout << "Failed to initialize Product module." << endl;
        allSuccess = false;
    }

    // Initialize Release
    bool stupRelease = initRelease();
    if (stupRelease) {
        cout << "Release module initialized successfully." << endl;
    } else {
        cout << "Failed to initialize Release module." << endl;
        allSuccess = false;
    }

    // Initialize Requester
    bool stupRequester = initRequester();
    if (stupRequester) {
        cout << "Requester module initialized successfully." << endl;
    } else {
        cout << "Failed to initialize Requester module." << endl;
        allSuccess = false;
    }

    // Initialize Change
    bool stupChange = initChange();
    if (stupChange) {
        cout << "Change module initialized successfully." << endl;
    } else {
        cout << "Failed to initialize Change module." << endl;
        allSuccess = false;
    }

    // Initialize Change Request
    bool stupChangeRequest = initChangeRequest();
    if (stupChangeRequest) {
        cout << "Change Request module initialized successfully." << endl;
    } else {
        cout << "Failed to initialize Change Request module." << endl;
        allSuccess = false;
    }

    return allSuccess;
}