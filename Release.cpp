#include "Release.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream ReleaseFileStream;

Release::Release() {
    release_ID = new char[9];
    product_name = new char[11];
    release_date = new char[11];
}

Release::Release(const char* id, const char* name, const char* date) : Release() {
    strcpy(release_ID, id);
    strcpy(product_name, name);
    strcpy(release_date, date);
}

Release::Release(const Release& other) : Release() {
    strcpy(release_ID, other.release_ID);
    strcpy(product_name, other.product_name);
    strcpy(release_date, other.release_date);
}

Release::~Release() {
    delete[] release_ID;
    delete[] product_name;
    delete[] release_date;
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