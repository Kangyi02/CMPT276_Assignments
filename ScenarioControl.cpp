// DEFINITION MODULE ScenarioControl;
/* Revision History:
Rev. 1 - 24/07/03 Original by Group 24
----------------------------------------------------------
This module defines the control functions for managing scenarios
related to product changes, releases, change requests, queries,
updates, reports, and shutdown operations. Each function provides
an interface to perform specific actions within the application,
ensuring clear separation of concerns and ease of maintenance.
----------------------------------------------------------
*/

#ifndef ScenarioControl_H
#define ScenarioControl_H

#include <iostream>
#include <fstream>
#include "ScenarioControl.h"
#include "Product.h"
#include "Release.h"

using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;

/*----------------------------------------------------------*/
//Exported constants/types/variables
ifstream product_file;

// Create control
// Create product control
void createProductControl()
{
    // Prompt user to enter the product name
    cout << "Enter product's name (max 10 chars): ";

    // Get user input
    char product_name[10];
    cin >> product_name;

    // Check if the product exists
    int exist = seekToBeginningOfProductFile(product_name);

    char userInput[1];

    if (exist == 1) // if the product has existed
    {
        cout << "The item you entered already exists in the system.\n";
        cout << "Would you like to enter another item(Y/N)? ";
        
        cin >> userInput;

        if (userInput == "y" || userInput == "Y") // if the user wants to enter the product name again 
            createProductControl();
        else if (userInput == "n" || userInput == "N") // else get out of this function
            return;
    }
    else if (exist == 0) // if the product has not existed
    {
        cout << "Are you sure you want to add the product Editor(Y/N)?";
        char userInput[1];
        cin >> userInput;

        if (userInput == "y" || userInput == "Y")
        {
            if (createProduct(product_name) == true) // pass product name, write a new product to the file, if creation succuess 
                cout << "The new product has been successfully added.";
            else // if creation failed
            {
                cout << "The operation cannot be completed because the hard disk is full. Enter Y to retry. Enter N to return to the main menu. ";
                char userInput1[1];
                cin >> userInput1;
                if (userInput1 == "y" || userInput1 == "Y")
                    createProduct(product_name) == true; // enter y to retry the creation operation
                else if (userInput1 == "n" || userInput1 == "N")
                    return; // enter n to go back to the main menu
            }
        }  
        else if (userInput == "n" || userInput == "N")
            return; // go back to the main menu
    }

    cout << "Do you want to add another product(Y/N)? ";
    cin >> userInput;

    if (userInput == "y" || userInput == "Y") // if the user wants to add another product
        createProductControl();
    else if (userInput == "n" || userInput == "N")
        return; // back to the main menu
}

void createReleaseControl()
{
    // Get the product name
    Product product_list[20];
    Product* temp;
    Product* chosen;
    while (!product_file.eof()) // question
    {
        cout << "For which product you want to add a new release to: \n";
        for (int i=0; i<20; i++)
        {
            temp = getProduct();
            product_list[i] = *temp;
            cout << i+1 << ") " << temp->getProduct_name() << "\n";
        }

        cout << "21) More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= 20)
        {
            chosen = &product_list[user_input-1];
            break;
        }
        else if (user_input == 0)
            return;
    }

    // Enter release information
    cout << "Enter a release ID of the new release(max 8 chars): ";
    char release_ID[8]; // should it be global??
    cin >> release_ID;

    cout << "Enter a release date of the release (YYYY-MM-DD): ";
    char release_date[10]; // should it be global??
    cin >> release_date;

    cout <<  "Are you sure you want to add the release(Y/N)? ";
    char sure_input[1];
    if (sure_input == "y" || sure_input == "Y")
    {
        Release new_release = Release(release_ID, chosen->getProduct_name(), release_date);
        createRelease(&new_release);
    }
    else  if (sure_input == "n" || sure_input == "N")
    {
        return;
    }
}
void createChangeRequestControl();

// Query control
void queryChangeControl();

// Update control
void updateChangeControl();

// Reports control
void allChangesReportControl();
void allRequestersReportControl();

// ShutDown control
void shutDownControl();

#endif