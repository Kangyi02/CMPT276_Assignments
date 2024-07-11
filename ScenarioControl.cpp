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
#include "ScenarioControl.h"
#include "Product.h"
#include "Release.h"

using std::cin;
using std::cout;

/*----------------------------------------------------------*/
// Exported constants/types/variables

// Create control
// Create product control
void createProductControl()
{
    // Prompt user to enter the product name
    cout << "Enter product's name (max 10 chars): ";

    // Get user input
    char product_name[10];
    cin >> product_name;

    // Prompt the user to ensure to add
    cout << "Are you sure you want to add the product Editor(Y/N)?";
    char userInput[1];
    cin >> userInput;

    if (userInput == "y" || userInput == "Y")
    {
        createProduct(product_name); // pass product name, write a new product to the file, if creation succuess
        cout << "The new product has been successfully added.";
    }
    else if (userInput == "n" || userInput == "N")
        return; // go back to the main menu

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
    Product product_list[20]; // sth
    Product *temp;
    Product *chosen;

    // 
    seekToBeginningOfProductFile();

    while (temp != NULL) // question
    {
        cout << "For which product you want to add a new release to: \n";
        cout << "Product    ";
        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp = getProduct();
            if (temp != NULL)
            {
                product_list[i] = *temp;
                cout << i + 1 << ") " << temp->getProduct_name() << "\n";
            }
            else
                break;
        }

        cout << i+2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= i+1)
        {
            chosen = &product_list[user_input - 1];
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

    cout << "Are you sure you want to add the release(Y/N)? ";
    char sure_input[1];
    if (sure_input == "y" || sure_input == "Y")
    {
        Release new_release = Release(release_ID, chosen->getProduct_name(), release_date);
        createRelease(&new_release);
    }
    else if (sure_input == "n" || sure_input == "N")
    {
        return;
    }
}

void createChangeRequestControl()
{
    // Get the product name
    Requester requester_list[20]; 
    Requester *temp;
    Requester *chosen_requester;

    // 
    seekToBeginningOfRequesterFile();

    while (temp != NULL) // question
    {
        cout << "Select a requester that reports this change request: \n";
        int i;
        cout << "Requester name                " << "Phone      " << "Email                   " << "Department  ";
        for (i = 0; i < 20; i++) // problem
        {
            temp = getRequester();
            if (temp != NULL)
            {
                requester_list[i] = *temp;
                cout << i + 1 << ") " << temp->get_RequesterName() 
                                      << temp->phone_number 
                                      << temp->email 
                                      << temp->department
                                      <<"\n";
            }
            else
                break;
        }

        cout << i+2 << ") Show more requesters\n";
        cout << "0) Create a new requester\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= i+1)
        {
            chosen_requester = &requester_list[user_input - 1];
            break;
        }
        else if (user_input == 0)
        {
            cout << "Creating a new requester: \n"
                << "Enter requester's name ('Last name, First name’, max 30 chars): ";
            
            // ask every thing, make a requester object, create requester
            // cin >> 
            //
            //
            cout << "The new requester has been successfully added. \n";
        }
    }

    // get product
    // Get the product name
    Product product_list[20]; // sth
    Product *temp1;
    Product *chosen_product;

    // 
    seekToBeginningOfProductFile();

    while (temp1 != NULL) // question
    {
        cout << "Select a product that corresponds to this change request: \n";
        cout << "Product    ";
        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp1 = getProduct();
            if (temp1 != NULL)
            {
                product_list[i] = *temp1;
                cout << i + 1 << ") " << temp1->getProduct_name() << "\n";
            }
            else
                break;
        }

        cout << i+2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= i+1)
        {
            chosen_product = &product_list[user_input - 1];
            break;
        }
        else if (user_input == 0)
            return;
    }

    // get changes
    Change change_list[20]; // sth
    Change *temp2;
    Change *chosen_change;

    seekToBeginningOfChangeFile();

    while (temp2 != NULL) // question
    {
        cout << "Which change corresponds to the change request? \n";
        // change formats later
        cout << "Description                     " 
            << "change ID   " 
            << "State      " 
            << "Priority     " 
            << "Anticipated Release\n";

        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp2 = filterChange(chosen_product->getProduct_name());
            if (temp2 != NULL)
            {
                change_list[i] = *temp2;
                // change format later
                cout << i + 1 << ") " << temp2->description
                                        << temp2->getChange_ID()
                                        << temp2->status
                                        << temp2->priority
                                        << temp2->anticipated_release_ID << "\n";
            }
            else
                break;
        }

        cout << i+2 << ") More\n";
        cout << "0) New Change\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= i+1)
        {
            chosen_change = &change_list[user_input - 1];
            break;
        }
        else if (user_input == 0)
        {
            cout << "Enter the description of the new change (max 30 chars): ";
            cin >> chosen_change->description;
            chosen_change->priority = 0; // if 0 print out N/A
            chosen_change->status = "Reported";
            chosen_change->setChange_ID(); //
            chosen_change->product_name = chosen_product->getProduct_name();
            chosen_change->anticipated_release_ID = "None";

            cout<< "The new change has been successfully created. ";
            createChange(chosen_change);
        }
    }

    // get release
    Release release_list[20]; // sth
    Release *temp3;
    Release *chosen_release;

    // 
    seekToBeginningOfReleaseFile();

    while (temp3 != NULL) // question
    {
        cout << "Select a reported release that corresponds to this change request: \n";

        // change formats later
        cout << "Release ID" 
            << "Release date\n";

        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp3 = filterRelease(chosen_product->getProduct_name());
            if (temp2 != NULL)
            {
                release_list[i] = *temp3;
                // change format later
                cout << i + 1 << ") " << temp3->getRelease_ID()
                                        << temp3->release_date << "\n";
            }
            else
                break;
        }

        cout << i+2 << ") More\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= i+1)
        {
            chosen_release = &release_list[user_input - 1];
            break;
        }
    }

    // get other info
    cout << "Enter the request date of the change request (YYYY-MM-DD): ";
    ChangeRequest* new_changeRequest;
    cin >> new_changeRequest->request_date;
    new_changeRequest->setRequester_name(chosen_requester->get_RequesterName());
    new_changeRequest->setChange_ID(chosen_change->getChange_ID());
    new_changeRequest->reported_release_ID = chosen_release->getRelease_ID();

    createChangeRequest(new_changeRequest);
    cout << "The new change request has been successfully created. \n";
}

// Query control
void queryChangeControl()
{
    // get product
    // Get the product name
    Product product_list[20]; // sth
    Product *temp1;
    Product *chosen_product;

    // 
    seekToBeginningOfProductFile();

    while (temp1 != NULL) // question
    {
        cout << "Select a product: \n";
        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp1 = getProduct();
            if (temp1 != NULL)
            {
                product_list[i] = *temp1;
                cout << i + 1 << ") " << temp1->getProduct_name() << "\n";
            }
            else
                break;
        }

        cout << i+2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= i+1)
        {
            chosen_product = &product_list[user_input - 1];
            break;
        }
        else if (user_input == 0)
            return;
    }

    // get changes
    Change change_list[20]; // sth
    Change *temp2;
    Change *chosen_change;

    seekToBeginningOfChangeFile();

    while (temp2 != NULL) // question
    {
        cout << "Changes in the product '"<< chosen_product->getProduct_name() << "':\n";
        // change formats later
        cout << "Description                     " 
            << "change ID   \n";

        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp2 = filterChange(chosen_product->getProduct_name());
            if (temp2 != NULL)
            {
                change_list[i] = *temp2;
                // change format later
                cout << i + 1 << ") " << temp2->description
                                        << temp2->getChange_ID()
                                        << "\n";
            }
            else
                break;
        }

        cout << i+2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= i+1)
        {
            chosen_change = &change_list[user_input - 1];
            break;
        }
        else if (user_input == 0)
            return;
    }

    cout << "Here is the information about the change item you queried: \n";
    cout << "Product    " 
        << "Description                     " 
        << "change ID   " 
        << "State      " 
        << "Priority     "
        << "Anticipated Release\n";

    cout << chosen_product->getProduct_name()
         << chosen_change->description
         << chosen_change->getChange_ID()
         << chosen_change->status
         << chosen_change->priority
         << chosen_change->anticipated_release_ID;
}

// Update control
void updateChangeControl()
{
     // get product
    // Get the product name
    Product product_list[20]; // sth
    Product *temp1;
    Product *chosen_product;

    // 
    seekToBeginningOfProductFile();

    while (temp1 != NULL) // question
    {
        cout << "Select a product that corresponds to the change you want to update: \n";
        cout << "Product    ";
        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp1 = getProduct();
            if (temp1 != NULL)
            {
                product_list[i] = *temp1;
                cout << i + 1 << ") " << temp1->getProduct_name() << "\n";
            }
            else
                break;
        }

        cout << i+2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= i+1)
        {
            chosen_product = &product_list[user_input - 1];
            break;
        }
        else if (user_input == 0)
            return;
    }

    // get changes
    Change change_list[20]; // sth
    Change *temp2;
    Change *chosen_change;

    seekToBeginningOfChangeFile();

    while (temp2 != NULL) // question
    {
        cout << "Select a change you want to update: \n";
        // change formats later
        cout << "Description                     " 
            << "change ID   " 
            << "State      " 
            << "Priority     " 
            << "Anticipated Release\n";

        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp2 = filterChange(chosen_product->getProduct_name());
            if (temp2 != NULL)
            {
                change_list[i] = *temp2;
                // change format later
                cout << i + 1 << ") " << temp2->description
                                        << temp2->getChange_ID()
                                        << temp2->status
                                        << temp2->priority
                                        << temp2->anticipated_release_ID << "\n";
            }
            else
                break;
        }

        cout << i+2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= i+1)
        {
            chosen_change = &change_list[user_input - 1];
            break;
        }
        else if (user_input == 0)
        {
            return;
        }
    }

    cout << "Updating the change with the change ID '1234' in the product '"
        << chosen_product->getProduct_name() << "':\n"
        << "Do you want to replace the description (Y/N)? ";
    char user_input1[1];
    cin >> user_input1;
    if (user_input1=="Y" || user_input1=="y")
    {
        cout << "Old description is: "
            << chosen_change->description
            << "\n"
            << "New description is: "
            << user_input1;
        chosen_change->description = user_input1;
    }

    // update status
    cout << "The current 'status' is Reported.\n"
        << "Select a status that you want to update to:\n"
        << "1) Reported\n"
        << "2) Evaluated\n"
        << "3) Cancelled\n"
        << "4) In process\n"
        << "5) Done\n"
        << "0) Keep the current status\n"
        << "Enter selection: ";

    int user_input2;
    cin >> user_input2;
    switch(user_input2)
    {
        case 1:
            chosen_change->status == "Reported";
            break;
        case 2:
            chosen_change->status == "Evaluated";
            break;
        case 3:
            chosen_change->status == "Cancelled";
            break;
        case 4:
            chosen_change->status == "In process";
            break;
        case 5:
            chosen_change->status == "Done";
            break;
        case 0:
            break;
    }

    // update priority
    cout << "The current priority is " << chosen_change->priority
        << "Enter a new priority, or 0 to keep the current priority: ";
    
    cin >> user_input2;
    if (user_input2!=0)
        chosen_change->priority = user_input2;

    // update release id
    cout << "The current 'anticipated release' is " << chosen_change->anticipated_release_ID;

    // get release
    Release release_list[20]; // sth
    Release *temp3;
    Release *chosen_release;

    // 
    seekToBeginningOfReleaseFile();

    while (temp3 != NULL) // question
    {
        cout << "Select an anticipated release that you want to update to: \n";

        // change formats later
        cout << "Release ID" 
            << "Release date\n";

        int i;
        for (i = 0; i < 20; i++) 
        {
            temp3 = filterRelease(chosen_product->getProduct_name());
            if (temp2 != NULL)
            {
                release_list[i] = *temp3;
                // change format later
                cout << i + 1 << ") " << temp3->getRelease_ID()
                                        << temp3->release_date << "\n";
            }
            else
                break;
        }

        cout << i+2 << ") More\n";
        cout << "0) Keep the current release\n"
             << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= i+1)
        {
            chosen_release = &release_list[user_input - 1];
            // update the release id
            chosen_change->anticipated_release_ID = chosen_release->getRelease_ID();
            break;
        }
        else if (user_input == 0)
            break;
    }

    updateChange(chosen_change);
    // print out the updated change info
    cout << "Change '1234' has been updated:\n"
        << "Description                     " 
        << "change ID   " 
        << "State      " 
        << "Priority     "
        << "Anticipated Release\n";

    cout << chosen_change->description
         << chosen_change->getChange_ID()
         << chosen_change->status
         << chosen_change->priority
         << chosen_change->anticipated_release_ID;
}

// Reports control
void allChangesReportControl();
void allRequestersReportControl();

// ShutDown control
void shutDownControl();

#endif