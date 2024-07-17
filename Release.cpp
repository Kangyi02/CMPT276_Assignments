#include "Release.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream ReleaseFileStream;

Release::Release() 
{
    // Initialize requester_name with an empty string
    strcpy(release_ID, "");

    // Initialize phone_number with zeroes
    for (int i = 0; i < 11; ++i) 
    {
        phone_number[i] = 0;
    }

    // Initialize email with an empty string
    strcpy(email, "");

    // Initialize department with an empty string
    strcpy(department, "");
}

// Parameterized constructor implementation
Release::Release(const char* name, const int* phone, const char* email_addr, const char* dept) 
{
    // Initialize requester_name with the provided name, ensuring it does not exceed the max length
    strncpy(requester_name, name, sizeof(name) - 1);
    requester_name[sizeof(name) - 1] = '\0'; // Ensure null termination

    // Initialize phone_number with the provided phone number
    for(int i = 0; i < 11; ++i) 
    {
        phone_number[i] = phone[i];
    }

    // Initialize email with the provided email address, ensuring it does not exceed the max length
    strncpy(email, email_addr, sizeof(email_addr) - 1);
    email[sizeof(email_addr) - 1] = '\0'; // Ensure null termination

    // Initialize department with the provided department, ensuring it does not exceed the max length
    strncpy(department, dept, sizeof(dept) - 1);
    department[sizeof(dept) - 1] = '\0'; // Ensure null termination
}

void initRelease() {
    ReleaseFileStream.open("file location", ios::in | ios::out | ios::binary | ios::app);
    if (!ReleaseFileStream) {
        cerr << "Error: Could not open file." << endl;
    }
}

void closeRelease() {
    if (ReleaseFileStream.is_open()) {
        ReleaseFileStream.close();
    }
}

void createRelease(Release* new_release) {
    if (ReleaseFileStream.is_open()) {
        ReleaseFileStream.write(reinterpret_cast<char*>(new_release->release_ID), sizeof(char) * 9);
        ReleaseFileStream.write(reinterpret_cast<char*>(new_release->product_name), sizeof(char) * 11);
        ReleaseFileStream.write(reinterpret_cast<char*>(new_release->release_date), sizeof(char) * 11);
    } else {
        cerr << "Error: File not open." << endl;
    }
}

Release* getRelease(char* product_name) {
    if (ReleaseFileStream.is_open()) {
        seekToBeginningOfReleaseFile();
        char id[9];
        char name[11];
        char date[11];

        while (ReleaseFileStream.read(reinterpret_cast<char*>(&id), sizeof(id))) {
            ReleaseFileStream.read(reinterpret_cast<char*>(&name), sizeof(name));
            ReleaseFileStream.read(reinterpret_cast<char*>(&date), sizeof(date));

            if (strcmp(name, product_name) == 0) {
                return new Release(id, name, date);
            }
        }
    } else {
        cerr << "Error: File not open." << endl;
    }
    return nullptr;
}

void seekToBeginningOfReleaseFile() {
    if (ReleaseFileStream.is_open()) {
        ReleaseFileStream.clear(); // Clear any error flags
        ReleaseFileStream.seekg(0, ios::beg);
    } else {
        cerr << "Error: File not open." << endl;
    }
}

Release* filterRelease(char* product_name) {
    if (ReleaseFileStream.is_open()) {
        seekToBeginningOfReleaseFile();
        char id[9];
        char name[11];
        char date[11];

        while (ReleaseFileStream.read(reinterpret_cast<char*>(&id), sizeof(id))) {
            ReleaseFileStream.read(reinterpret_cast<char*>(&name), sizeof(name));
            ReleaseFileStream.read(reinterpret_cast<char*>(&date), sizeof(date));

            if (strcmp(name, product_name) == 0) {
                return new Release(id, name, date);
            }
        }
    } else {
        cerr << "Error: File not open." << endl;
    }
    return nullptr;
}