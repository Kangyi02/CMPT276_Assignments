#include "Requester.h"
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

fstream requesterFileStream;

// Default constructor implementation
Requester::Requester() {
    // Initialize requester_name with an empty string
    strcpy(requester_name, "");

    // Initialize phone_number with zeroes
    for (int i = 0; i < 11; ++i) {
        phone_number[i] = 0;
    }

    // Initialize email with an empty string
    strcpy(email, "");

    // Initialize department with an empty string
    strcpy(department, "");
}

// Parameterized constructor implementation
Requester::Requester(const char* name, const int* phone, const char* email_addr, const char* dept) {
    // Initialize requester_name with the provided name, ensuring it does not exceed the max length
    strncpy(requester_name, name, sizeof(requester_name) - 1);
    requester_name[sizeof(requester_name) - 1] = '\0'; // Ensure null termination

    // Initialize phone_number with the provided phone number
    for (int i = 0; i < 11; ++i) {
        phone_number[i] = phone[i];
    }

    // Initialize email with the provided email address, ensuring it does not exceed the max length
    strncpy(email, email_addr, sizeof(email) - 1);
    email[sizeof(email) - 1] = '\0'; // Ensure null termination

    // Initialize department with the provided department, ensuring it does not exceed the max length
    strncpy(department, dept, sizeof(department) - 1);
    department[sizeof(department) - 1] = '\0'; // Ensure null termination
}

// Initialize the requester file
void initRequester() {
    requesterFileStream.open("requesters.bin", ios::in | ios::out | ios::binary | ios::app);
    if (!requesterFileStream) {
        cerr << "Error opening Requester file for initialization." << endl;
    }
}

// Shut down the requester file
void closeRequester() {
    if (requesterFileStream.is_open()) {
        requesterFileStream.close();
    }
}

// Get the next requester
Requester getNextRequester() {
    Requester req;
    requesterFileStream.read(reinterpret_cast<char*>(&req), sizeof(Requester));
    return req;
}

// Create a new requester
char createRequester() {
    char name[21], email[25], dept[13];
    int phone[11];

    cout << "Enter requester name (max 20 characters): ";
    cin.getline(name, 21);
    if (cin.fail() && !cin.eof()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter phone number (11 digits): ";
    for (int i = 0; i < 11; ++i) {
        cin >> phone[i];
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter email (max 24 characters): ";
    cin.getline(email, 25);
    if (cin.fail() && !cin.eof()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter department (max 12 characters): ";
    cin.getline(dept, 13);
    if (cin.fail() && !cin.eof()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Requester newRequester(name, phone, email, dept);
    requesterFileStream.write(reinterpret_cast<char*>(&newRequester), sizeof(Requester));

    return newRequester.requester_name;
}

void seekToBeginningOfRequesterFile() {
    requesterFileStream.seekg(0, ios::beg);
}

// Filter requesters by name
Requester filterRequester(char requester_name) {
    Requester req;
    while (requesterFileStream.read(reinterpret_cast<char*>(&req), sizeof(Requester))) {
        if (strcmp(req.requester_name, requester_name) == 0) {
            return req;
        }
    }
    return Requester(); // Return an empty requester if not found
}
