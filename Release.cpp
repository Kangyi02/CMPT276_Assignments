#include "Release.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream ReleaseFileStream;

Release::Release() {
    release_ID[0] = '\0';
    product_name[0] = '\0';
    release_date[0] = '\0';
}

// Parameterized constructor implementation
Release::Release(const char* relID, const char* prodname, const char* reldate) 
{
    
}

bool initRelease() {
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
        ReleaseFileStream.write(reinterpret_cast<char*>(new_release->getRelease_ID()), sizeof(char) * 9);
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