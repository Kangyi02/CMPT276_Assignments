#include "Change.h"
#include <iostream>
#include <fstream>

using namespace std;

fstream ChangeFileStream;

Change::Change() : priority(1), status(new char[10]), description(new char[31]), product_name(new char[11]), anticipated_release_ID(new char[9]) {
    setChange_ID();
    strcpy(status, "reported");
}

Change::Change(const char* id, const int prio, const char* stat, const char* desc, const char* pname, const char* arid) : Change() 
{
    setChange_ID();
    priority = prio;
    strcpy(status, stat);
    strcpy(description, desc);
    strcpy(product_name, pname);
    strcpy(anticipated_release_ID, arid);
}

Change::Change(const Change& other) : Change() 
{
    change_ID = other.change_ID;
    priority = other.priority;
    strcpy(status, other.status);
    strcpy(description, other.description);
    strcpy(product_name, other.product_name);
    strcpy(anticipated_release_ID, other.anticipated_release_ID);
}

Change::~Change() 
{
    delete[] status;
    delete[] description;
    delete[] product_name;
    delete[] anticipated_release_ID;
}

void initChange() 
{
    ChangeFileStream.open("file location", ios::in | ios::out | ios::binary | ios::app);
    if (!ChangeFileStream) 
    {
        cerr << "Error: Could not open file." << endl;
    }
}

void closeChange() 
{
    if (ChangeFileStream.is_open()) 
    {
        ChangeFileStream.close();
    }
}

Change* getChange(char* product_name) 
{
    if (ChangeFileStream.is_open()) 
    {
        seekToBeginningOfChangeFile();
        char pname[11];
        int id, prio;
        char stat[10];
        char desc[31];
        char arid[9];

        while (ChangeFileStream >> pname >> id >> prio >> stat >> desc >> arid) 
        {
            if (strcmp(pname, product_name) == 0) 
            {
                return new Change(pname, prio, stat, desc, pname, arid);
            }
        }
    } else 
    {
        cerr << "Error: File not open." << endl;
    }
    return nullptr;
}

int createChange(Change* change) 
{
    if (ChangeFileStream.is_open()) 
    {
        ChangeFileStream << change->product_name << " "
                         << change->getChange_ID() << " "
                         << change->priority << " "
                         << change->status << " "
                         << change->description << " "
                         << change->anticipated_release_ID << endl;
        return change->getChange_ID();
    } else 
    {
        cerr << "Error: File not open." << endl;
        return -1;
    }
}

void updateChange(Change* new_change) 
{
    if (ChangeFileStream.is_open()) 
    {
        // Temporary file to store updated records
        fstream tempFileStream;
        tempFileStream.open("TempChange.txt", ios::out);

        if (!tempFileStream) 
        {
            cerr << "Error: Could not create temporary file." << endl;
            return;
        }

        seekToBeginningOfChangeFile();
        char pname[11];
        int id, prio;
        char stat[10];
        char desc[31];
        char arid[9];

        while (ChangeFileStream >> pname >> id >> prio >> stat >> desc >> arid) 
        {
            if (id == new_change->getChange_ID()) 
            {
                tempFileStream << new_change->product_name << " "
                               << new_change->getChange_ID() << " "
                               << new_change->priority << " "
                               << new_change->status << " "
                               << new_change->description << " "
                               << new_change->anticipated_release_ID << endl;
            } else 
            {
                tempFileStream << pname << " " << id << " " << prio << " " << stat << " " << desc << " " << arid << endl;
            }
        }

        ChangeFileStream.close();
        tempFileStream.close();

        // Replace the old file with the updated file
        remove("Change.txt");
        rename("TempChange.txt", "Change.txt");

        // Reopen the original file stream
        ChangeFileStream.open("Change.txt", ios::in | ios::out | ios::app);
    } else 
    {
        cerr << "Error: File not open." << endl;
    }
}

void seekToBeginningOfChangeFile() 
{
    if (ChangeFileStream.is_open()) 
    {
        ChangeFileStream.clear(); // Clear any error flags
        ChangeFileStream.seekg(0, ios::beg);
    } else 
    {
        cerr << "Error: File not open." << endl;
    }
}

Change* filterChange(char* product_name) 
{
    if (ChangeFileStream.is_open()) 
    {
        seekToBeginningOfChangeFile();
        char pname[11];
        int id, prio;
        char stat[10];
        char desc[31];
        char arid[9];

        while (ChangeFileStream >> pname >> id >> prio >> stat >> desc >> arid) 
        {
            if (strcmp(pname, product_name) == 0) 
            {
                return new Change(pname, prio, stat, desc, pname, arid);
            }
        }
    } else 
    {
        cerr << "Error: File not open." << endl;
    }
    return nullptr;
}

Change* filterChange_doneOrCancelled(char* product_name) 
{
    if (ChangeFileStream.is_open()) 
    {
        seekToBeginningOfChangeFile();
        char pname[11];
        int id, prio;
        char stat[10];
        char desc[31];
        char arid[9];

        while (ChangeFileStream >> pname >> id >> prio >> stat >> desc >> arid) 
        {
            if (strcmp(pname, product_name) == 0 && (strcmp(stat, "done") == 0 || strcmp(stat, "cancelled") == 0)) 
            {
                return new Change(pname, prio, stat, desc, pname, arid);
            }
        }
    } else 
    {
        cerr << "Error: File not open." << endl;
    }
    return nullptr;
}