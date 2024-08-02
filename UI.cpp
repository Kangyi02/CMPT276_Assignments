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
#include <limits>

using std::cin;
using std::cout;
using std::endl;

// Main menu
void activateUI()
{
    int userInput = 1;

    while (userInput)
    {
        // Print the main menu
        cout << endl
             << "Main menu:" << endl
             << "1) Create" << endl
             << "2) Update" << endl
             << "3) Query" << endl
             << "4) Reports" << endl
             << "0) Exit" << endl
             << "Enter selection: ";

        cin >> userInput;

        // Check if the input was invalid
        if (cin.fail()) {
            // Clear the error state
            cin.clear();
            // Discard invalid input
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number between 0 and 4." << endl;
            userInput = 1;
            continue;
        }

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
        default:
            cout << "Invalid input. Enter a number between 0 and 4." << endl;
            break;
        }
    }
}

// ---------------------------------------------------------------------------------------

// Create menu
void create()
{
    // Print the create sub-menu
    cout << "Create Menu:" << endl
        << "1) Create a product" << endl
        << "2) Create a release of a product" << endl
        << "3) Create a change request" << endl
        << "0) Exit" << endl
        << "Enter selection: ";

    // Get the input
    int userInput;
    cin >> userInput;

    // Check if the input was invalid
    if (cin.fail()) 
    {
        // Clear the error state
        cin.clear();
        // Discard invalid input
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Returning to main menu." << endl;
        userInput = 0;
    }

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
    default:
        cout << "Invalid input. Returning to the main menu." << endl;
        break;
    }
}

// ---------------------------------------------------------------------------------------

// Query menu
void query()
{
    // Print the query sub-menu
    cout << "Query Menu:" << endl
         << "1) Query a change to the screen" << endl
         << "0) Exit" << endl
         << "Enter selection: ";

    // Get the input
    int userInput;
    cin >> userInput;

    // Check if the input was invalid
    if (cin.fail()) 
    {
        // Clear the error state
        cin.clear();
        // Discard invalid input
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Returning to main menu." << endl;
        userInput = 0;
    }

    // Switch cases
    switch (userInput)
    {
    case (1):
        queryChangeControl();
        break;
    case (0):
        break;
    default:
        cout << "Invalid input. Returning to the main menu." << endl;
        break;
    }
}

// ---------------------------------------------------------------------------------------

// Update menu
void update()
{
    // Print the update sub-menu
    cout << "Update Menu:" << endl
         << "1) Update a change" << endl
         << "0) Exit" << endl
         << "Enter selection: ";

    // Get the input
    int userInput;
    cin >> userInput;

    // Check if the input was invalid
    if (cin.fail()) 
    {
        // Clear the error state
        cin.clear();
        // Discard invalid input
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Returning to main menu." << endl;
        userInput = 0;
    }

    // Switch cases
    switch (userInput)
    {
    case (1):
        updateChangeControl();
        break;
    case (0):
        break;
    default:
        cout << "Invalid input. Returning to the main menu." << endl;
        break;
    }
}

// ---------------------------------------------------------------------------------------

// Reports menu
void reports()
{
    // Print the create sub-menu
    cout << "Reports Menu:" << endl
         << "1) Print a report with all changes for a product" << endl
         << "2) Print a report with requesters" << endl
         << "0) Exit" << endl
         << "Enter selection: ";

    // Get the input
    int userInput;
    cin >> userInput;

    // Check if the input was invalid
    if (cin.fail()) 
    {
        // Clear the error state
        cin.clear();
        // Discard invalid input
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Returning to main menu." << endl;
        userInput = 0;
    }

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
    default:
        cout << "Invalid input. Returning to the main menu." << endl;
        break;
    }
}
