// DEFINITION UI.cpp;
// Revision History:
// Rev. 1 - 24/07/03 Original by Group 24
// ----------------------------------------------------------
// This module defines the main menu functions for managing
// various aspects related to product changes, releases,
// change requests, requesters, and reports within the application.
// Each function provides an interface to navigate through
// different menus and actions, ensuring user interaction
// and system management are well-structured and intuitive.
// ----------------------------------------------------------

#include "UI.h"
#include "ScenarioControl.h"
#include <iostream>

using std::cin;
using std::cout;

// Main menu
void activateUI()
{
    int userInput = 1;

    while (userInput)
    {
        // Print the main menu
        cout << "Main menu:\n";
        cout << "1) Create\n";
        cout << "2) Update\n";
        cout << "3) Query\n";
        cout << "4) Reports\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        cin >> userInput;

        switch (userInput)
        {
        case (1):
            create();
            break;
        case (2):
            update();
            break;
        case (3):
            query();
            break;
        case (4):
            reports();
            break;
        case (0):
            userInput = 0;
            shutDownControl();
            break;
        }
    }
}

// Create menu
void create()
{
    // Print the create sub-menu
    cout << "Create Menu:\n";
    cout << "1) Create a product\n";
    cout << "2) Create a release of a product\n";
    cout << "3) Create a change request\n";
    cout << "0) Exit\n";
    cout << "Enter selection: ";

    // Get the input
    int userInput;
    cin >> userInput;

    // Switch cases
    switch (userInput)
    {
    case (1):
        createProductControl();
        break;
    case (2):
        createReleaseControl();
        break;
    case (3):
        createChangeRequestControl();
        break;
    case (0):
        break;
    }
}

// Query menu
void query()
{
    // Print the query sub-menu
    cout << "Query Menu:\n";
    cout << "1) Query a change to the screen\n";
    cout << "0) Exit\n";
    cout << "Enter selection: ";

    // Get the input
    int userInput;
    cin >> userInput;

    // Switch cases
    switch (userInput)
    {
    case (1):
        queryChangeControl();
        break;
    case (0):
        break;
    }
}

// Update menu
void update()
{
    // Print the update sub-menu
    cout << "Update Menu:\n";
    cout << "1) Update a change\n";
    cout << "0) Exit\n";
    cout << "Enter selection: ";

    // Get the input
    int userInput;
    cin >> userInput;

    // Switch cases
    switch (userInput)
    {
    case (1):
        updateChangeControl();
        break;
    case (0):
        break;
    }
}

// Reports menu
void reports()
{
    // Print the create sub-menu
    cout << "Reports Menu:\n";
    cout << "1) Print a report with all changes for a product\n";
    cout << "2) Print a report with requesters\n";
    cout << "0) Exit\n";
    cout << "Enter selection: ";

    // Get the input
    int userInput;
    cin >> userInput;

    // Switch cases
    switch (userInput)
    {
    case (1):
        allChangesReportControl();
        break;
    case (2):
        allRequestersReportControl();
        break;
    case (0):
        break;
    }
}