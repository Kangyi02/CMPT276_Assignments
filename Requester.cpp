#include "Requester.h"
#include <fstream>
#include <iostream>

using namespace std;

fstream requesterFileStream;

// Constructor for Requester
Requester::Requester() : requester_name(nullptr), phone_number(0), email(nullptr), department(nullptr) {}

Requester::Requester(const char* name, int phone, const char* email) {
    requester_name = new char[strlen(name) + 1];
    strcpy(requester_name, name);
    this->phone_number = phone;
    this->email = new char[strlen(email) + 1];
    strcpy(this->email, email);
    this->department = nullptr;
}

Requester::Requester(const Requester& other) {
    requester_name = new char[strlen(other.requester_name) + 1];
    strcpy(requester_name, other.requester_name);
    phone_number = other.phone_number;
    email = new char[strlen(other.email) + 1];
    strcpy(email, other.email);
    department = other.department ? new char[strlen(other.department) + 1] : nullptr;
    if (department) {
        strcpy(department, other.department);
    }
}

// Destructor for Requester
Requester::~Requester() {
    delete[] requester_name;
    delete[] email;
    delete[] department;
}

char* Requester::get_RequesterName() {
    return requester_name;
}

void initRequester()
{
    requesterFileStream.open("requesters.bin", ios::out | ios::trunc | ios::binary);
    if (!requesterFileStream) {
        cerr << "Error opening Requester file for initialization." << endl;
    }
}

void closeRequester()
{
    if (requesterFileStream.is_open()) {
        requesterFileStream.close();
    }
}

Requester* getRequester()
{
    Requester* req = new Requester();
    requesterFileStream.seekg(requesterPosition * sizeof(Requester), ios::beg);
    if (requesterFileStream.read(reinterpret_cast<char*>(req), sizeof(Requester))) {
        return req;
    } else {
        delete req;
        return nullptr;
    }
}

char* createRequester()
{
    char name[21], email[25];
    int phone;

    cout << "Enter requester name (max 20 characters): ";
    cin.getline(name, 21);
    if (cin.fail() && !cin.eof()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter phone number: ";
    cin >> phone;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter email (max 24 characters): ";
    cin.getline(email, 25);
    if (cin.fail() && !cin.eof()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Requester* newRequester = new Requester(name, phone, email);
    requesterFileStream.write(reinterpret_cast<char*>(newRequester), sizeof(Requester));

    return newRequester->get_RequesterName();
}

void seekToBeginningOfRequesterFile()
{
    requesterFileStream.seekg(0, ios::beg);
}

//filter?
Requester* filer_requester(char* requester_name)
{

}