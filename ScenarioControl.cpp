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

// Function to control the creation of a product
void createProductControl()
{
    // Prompt user to enter the product name
    cout << "Enter product's name (max 10 chars): ";

    // Get user input for the product name
    char product_name[10];
    cin >> product_name;

    // Prompt the user to confirm adding the product
    cout << "Are you sure you want to add the product Editor(Y/N)?";
    char userInput[1];
    cin >> userInput;

    // Check user input and proceed accordingly
    if (userInput == "y" || userInput == "Y")
    {
        createProduct(product_name); // Create the product(Writing product record to the file) and confirm success
        cout << "The new product has been successfully added.";
    }
    else if (userInput == "n" || userInput == "N")
        return; // Return to the main menu if user cancels

    // Ask if the user wants to add another product
    cout << "Do you want to add another product(Y/N)? ";
    cin >> userInput;
    // If yes, call the function again to add another product
    if (userInput == "y" || userInput == "Y") 
        createProductControl();
    else if (userInput == "n" || userInput == "N")
        return; // Return to the main menu if user cancels
}

// Function to control the creation of a release
void createReleaseControl()
{
    // Array to store a list of products
    Product product_list[20]; 
    Product *temp;   // Temporary product pointer
    Product *chosen;  // Chosen product pointer

    // Move the file pointer to the beginning of the product file
    seekToBeginningOfProductFile();
    // Loop to display product list and select a product
    while (temp != NULL) // question
    {
        cout << "For which product you want to add a new release to: \n";
        cout << "Product    ";
        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp = getProduct();    // Get the next product from the file
            if (temp != NULL)
            {
                product_list[i] = *temp;    // Add product to the list
                cout << i + 1 << ") " << temp->getProduct_name() << "\n";   // Display product name
            }
            else
                break;  // Exit loop if no more products
        }
        // Display options for more products or exit
        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";    // Get user input for selection

        int user_input;
        cin >> user_input;
        // Check if user input is within valid range
        if (1 <= user_input <= i + 1)
        {
            chosen = &product_list[user_input - 1]; // Select the chosen product
            break;
        }
        else if (user_input == 0)
            return; // Return if user chooses to exit
    }

    // Prompt user to enter release ID
    cout << "Enter a release ID of the new release(max 8 chars): ";
    char release_ID[8]; // should it be global??
    cin >> release_ID;
    // Prompt user to enter release date
    cout << "Enter a release date of the release (YYYY-MM-DD): ";
    char release_date[10]; // should it be global??
    cin >> release_date;
    // Confirm adding the release
    cout << "Are you sure you want to add the release(Y/N)? ";
    // Check user input and proceed accordingly
    char sure_input[1];
    if (sure_input == "y" || sure_input == "Y")
    {   
        // Create new release and write to file
        Release new_release = Release(release_ID, chosen->getProduct_name(), release_date);
        createRelease(&new_release);
    }
    else if (sure_input == "n" || sure_input == "N")
    {
        return; // Return if user cancels
    }
}

// Function to control the creation of a change request
void createChangeRequestControl()
{
    // Array to store a list of requesters
    Requester requester_list[20];
    Requester *temp;    // Temporary requester pointer
    Requester *chosen_requester;   // Chosen requester pointer

    // Move the file pointer to the beginning of the requester file
    seekToBeginningOfRequesterFile();
    // Loop to display requester list and select a requester
    while (temp != NULL) // question
    {
        cout << "Select a requester that reports this change request: \n";
        int i;
        cout << "Requester name                " << "Phone      " << "Email                   " << "Department  ";
        for (i = 0; i < 20; i++) // problem
        {
            temp = getRequester();  // Get the next requester from the file
            if (temp != NULL)
            {
                requester_list[i] = *temp;  // Add requester to the list
                cout << i + 1 << ") " << temp->get_RequesterName()
                     << temp->phone_number
                     << temp->email
                     << temp->department
                     << "\n";
            }
            else
                break;  // Exit loop if no more requesters
        }
        // Display options for more requesters or to create a new one
        cout << i + 2 << ") Show more requesters\n";
        cout << "0) Create a new requester\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;   // Get user input for selection
        // Check if user input is within valid range
        if (1 <= user_input <= i + 1)
        {
            chosen_requester = &requester_list[user_input - 1]; // Select the chosen requester
            break;
        }
        else if (user_input == 0)
        {   
            // Prompt user to create a new requester
            cout << "Creating a new requester: \n"
                 << "Enter requester's name ('Last name, First name’, max 30 chars): ";

            // Ask for all necessary information, create a requester object, and add to file
            // cin >> requester details...


            cout << "The new requester has been successfully added. \n";
        }
    }

    // Array to store a list of products
    Product product_list[20]; 
    Product *temp1;     // Temporary product pointer
    Product *chosen_product;    // Chosen product pointer

    // Move the file pointer to the beginning of the product file
    seekToBeginningOfProductFile();
    // Loop to display product list and select a product
    while (temp1 != NULL) // question
    {
        cout << "Select a product that corresponds to this change request: \n";
        cout << "Product    ";
        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp1 = getProduct();   // Get the next product from the file
            if (temp1 != NULL)
            {
                product_list[i] = *temp1;   // Add product to the list
                cout << i + 1 << ") " << temp1->getProduct_name() << "\n"; // Add product to the list
            }
            else
                break;  // Exit loop if no more products
        }
        // Display options for more products or exit
        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // Get user input for selection
        // Check if user input is within valid range
        if (1 <= user_input <= i + 1)
        {
            chosen_product = &product_list[user_input - 1]; // Select the chosen product
            break;
        }
        else if (user_input == 0)
            return; // Return if user chooses to exit
    }

    // Array to store a list of changes
    Change change_list[20];
    Change *temp2; // Temporary change pointer
    Change *chosen_change; // Chosen change pointer
    // Move the file pointer to the beginning of the change file
    seekToBeginningOfChangeFile();

    // Loop to display change list and select a change
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
            temp2 = filterChange(chosen_product->getProduct_name());   // Filter changes by product name 
            if (temp2 != NULL)
            {
                change_list[i] = *temp2;    // Add change to the list
                // change format later
                cout << i + 1 << ") " << temp2->description
                     << temp2->getChange_ID()
                     << temp2->status
                     << temp2->priority
                     << temp2->anticipated_release_ID << "\n";
            }
            else
                break;  // Exit loop if no more changes
        }
        // Display options for more changes or to create a new one
        cout << i + 2 << ") More\n";
        cout << "0) New Change\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;  // Get user input for selection

        if (1 <= user_input <= i + 1)
        {
            chosen_change = &change_list[user_input - 1];   // Select the chosen change
            break;
        }
        else if (user_input == 0)
        {   
            // Prompt user to create a new change
            cout << "Enter the description of the new change (max 30 chars): ";
            cin >> chosen_change->description;
            chosen_change->priority = 0; // if 0 print out N/A
            chosen_change->status = "Reported";
            chosen_change->setChange_ID(); 
            chosen_change->product_name = chosen_product->getProduct_name();
            chosen_change->anticipated_release_ID = "None";
            // Confirm the creation of the new change and add to file
            cout << "The new change has been successfully created. ";
            createChange(chosen_change);
        }
    }

     // Array to store a list of releases
    Release release_list[20]; 
    Release *temp3; // Temporary release pointer
    Release *chosen_release; // Chosen release pointer

    // Move the file pointer to the beginning of the release file
    seekToBeginningOfReleaseFile();

    // Loop to display release list and select a release
    while (temp3 != NULL) // question
    {
        cout << "Select a reported release that corresponds to this change request: \n";

        // change formats later
        cout << "Release ID"
             << "Release date\n";

        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp3 = filterRelease(chosen_product->getProduct_name());   // Filter releases by product name
            if (temp2 != NULL)
            {
                release_list[i] = *temp3;   // Add release to the list
                // change format later
                cout << i + 1 << ") " << temp3->getRelease_ID()
                     << temp3->release_date << "\n";
            }
            else
                break;  // Exit loop if no more releases
        }
        // Display options for more releases
        cout << i + 2 << ") More\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;  // Get user input for selection
        // Check if user input is within valid range
        if (1 <= user_input <= i + 1)
        {
            chosen_release = &release_list[user_input - 1]; // Select the chosen release
            break;
        }
    }

    // Prompt user to enter additional information for the change request
    cout << "Enter the request date of the change request (YYYY-MM-DD): ";
    ChangeRequest *new_changeRequest;
    cin >> new_changeRequest->request_date;
    new_changeRequest->setRequester_name(chosen_requester->get_RequesterName());
    new_changeRequest->setChange_ID(chosen_change->getChange_ID());
    new_changeRequest->reported_release_ID = chosen_release->getRelease_ID();
    // Create the new change request (Write the record to the file) and confirm success
    createChangeRequest(new_changeRequest);
    cout << "The new change request has been successfully created. \n";
}

// Function to control the querying of a change
void queryChangeControl()
{
    // Array to store a list of products
    Product product_list[20]; 
    Product *temp1; // Temporary product pointer
    Product *chosen_product; // Chosen product pointer
    // Move the file pointer to the beginning of the product file
    seekToBeginningOfProductFile();

    // Loop to display product list and select a product
    while (temp1 != NULL) // question
    {
        cout << "Select a product: \n";
        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp1 = getProduct();   // Get the next product from the file
            if (temp1 != NULL)
            {
                product_list[i] = *temp1;   // Add product to the list
                cout << i + 1 << ") " << temp1->getProduct_name() << "\n";
            }
            else
                break;  // Exit loop if no more products
        }
        // Display options for more products or exit
        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";    

        int user_input;
        cin >> user_input; // Get user input for selection

        // Check if user input is within valid range
        if (1 <= user_input <= i + 1)
        {
            chosen_product = &product_list[user_input - 1]; // Select the chosen product
            break;
        }
        else if (user_input == 0)
            return; // Return if user chooses to exit
    }

    // Array to store a list of changes
    Change change_list[20]; 
    Change *temp2;  // Temporary change pointer
    Change *chosen_change;  // Chosen change pointer

    // Move the file pointer to the beginning of the change file
    seekToBeginningOfChangeFile();
    // Loop to display change list and select a change
    while (temp2 != NULL) // question
    {
        cout << "Changes in the product '" << chosen_product->getProduct_name() << "':\n";
        // change formats later
        cout << "Description                     "
             << "change ID   \n";

        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp2 = filterChange(chosen_product->getProduct_name()); // Filter changes by product name
            if (temp2 != NULL)
            {
                change_list[i] = *temp2;    // Add change to the list
                // change format later
                cout << i + 1 << ") " << temp2->description
                     << temp2->getChange_ID()
                     << "\n";
            }
            else
                break;  // Exit loop if no more changes
        }
        // Display options for more changes or exit
        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;  // Get user input for selection

         // Check if user input is within valid range
        if (1 <= user_input <= i + 1)
        {
            chosen_change = &change_list[user_input - 1];   // Select the chosen change
            break;
        }
        else if (user_input == 0)
            return;  // Return if user chooses to exit
    }
    // Display the information about the chosen change item
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
     // Step 1: Get the product
    Product product_list[20]; // Array to store product list
    Product *temp1; // Temporary pointer for product
    Product *chosen_product;    // Pointer for chosen product

    // Function to set file cursor to the beginning of the product file
    seekToBeginningOfProductFile();
    // Loop until a valid product is chosen
    while (temp1 != NULL) // question
    {
        cout << "Select a product that corresponds to the change you want to update: \n";
        cout << "Product    ";
        int i;
        // Display product options
        for (i = 0; i < 20; i++) // problem
        {
            temp1 = getProduct();   // Function to get next product
            if (temp1 != NULL)
            {
                product_list[i] = *temp1;   // Store product in array
                cout << i + 1 << ") " << temp1->getProduct_name() << "\n";  // Display product
            }
            else
                break;  // Exit loop if no more products
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;  // User input for product selection

        if (1 <= user_input <= i + 1)   // Check for valid selection
        {
            chosen_product = &product_list[user_input - 1]; // Assign chosen product
            break;
        }
        else if (user_input == 0)
            return; // Exit
    }

    // Step 2: Get the changes
    Change change_list[20]; // Array to store change list
    Change *temp2;  // Temporary pointer for change
    Change *chosen_change;  // Pointer for chosen change

    seekToBeginningOfChangeFile();  // Function to set file cursor to the beginning of the change file
    // Loop until a valid change is chosen
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
        // Display change options
        for (i = 0; i < 20; i++) // problem
        {
            temp2 = filterChange(chosen_product->getProduct_name());    // Function to filter changes by product
            if (temp2 != NULL)
            {
                change_list[i] = *temp2;    // Store change in array
                // change format later
                cout << i + 1 << ") " << temp2->description
                     << temp2->getChange_ID()
                     << temp2->status
                     << temp2->priority
                     << temp2->anticipated_release_ID << "\n";  // Display change
            }
            else
                break;  // Exit loop if no more changes
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;  // User input for change selection

        if (1 <= user_input <= i + 1)   // Check for valid selection
        {
            chosen_change = &change_list[user_input - 1];   // Assign chosen change
            break;
        }
        else if (user_input == 0)   // Exit
        {
            return;
        }
    }
    // Step 3: Update the chosen change

    // Update description
    cout << "Updating the change with the change ID '1234' in the product '"
         << chosen_product->getProduct_name() << "':\n"
         << "Do you want to replace the description (Y/N)? ";
    char user_input1[1];
    cin >> user_input1;
    if (user_input1 == "Y" || user_input1 == "y")
    {
        cout << "Old description is: "
             << chosen_change->description
             << "\n"
             << "New description is: ";
        char* new_description;
        cin >> new_description; // Get new description
        chosen_change->description = new_description; // Update description
    }

    // Update status
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
    cin >> user_input2; // User input for status selection
    switch (user_input2)
    {
    case 1:
        chosen_change->status == "Reported";    // Update status
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
        break;  // Keep current status
    }

    // Update priority
    cout << "The current priority is " << chosen_change->priority
         << "Enter a new priority, or 0 to keep the current priority: ";

    cin >> user_input2;
    if (user_input2 != 0)
        chosen_change->priority = user_input2;  // Update priority

    // Update anticipated release ID
    cout << "The current 'anticipated release' is " << chosen_change->anticipated_release_ID;

    // get release
    Release release_list[20]; // Array to store release list
    Release *temp3;     // Temporary pointer for release
    Release *chosen_release;    // Pointer for chosen release

    seekToBeginningOfReleaseFile(); // Function to set file cursor to the beginning of the release file
    // Loop until a valid release is chosen
    while (temp3 != NULL) // question
    {
        cout << "Select an anticipated release that you want to update to: \n";

        // change formats later
        cout << "Release ID"
             << "Release date\n";

        int i;
         // Display release options
        for (i = 0; i < 20; i++)
        {
            temp3 = filterRelease(chosen_product->getProduct_name()); // Function to filter releases by product
            if (temp2 != NULL)
            {
                release_list[i] = *temp3;   // Store release in array
                // change format later
                cout << i + 1 << ") " << temp3->getRelease_ID()
                     << temp3->release_date << "\n";    // Display release
            }
            else
                break;  // Exit loop if no more releases
        }

        cout << i + 2 << ") More\n";
        cout << "0) Keep the current release\n"
             << "Enter selection: ";

        int user_input;
        cin >> user_input;  // User input for release selection

        if (1 <= user_input <= i + 1)   // Check for valid selection
        {
            chosen_release = &release_list[user_input - 1]; // Assign chosen release
            // update the release id
            chosen_change->anticipated_release_ID = chosen_release->getRelease_ID();    // Update anticipated release ID
            break;
        }
        else if (user_input == 0)   // Keep current release
            break;
    }

    updateChange(chosen_change);    // Function to update the change in the system
    // Display updated change info
     cout << "Change '" << chosen_change->getChange_ID() << "' has been updated:\n"
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
void allChangesReportControl()
{
   // Step 1: Get the product
    Product product_list[20]; // Array to store product list
    Product *temp1; // Temporary pointer for product
    Product *chosen_product;    // Pointer for chosen product

    // Function to set file cursor to the beginning of the product file
    seekToBeginningOfProductFile();
    // Loop until a valid product is chosen
    while (temp1 != NULL) // question
    {
        cout << "Select a product to print its report: \n";
        int i;
         // Display product options
        for (i = 0; i < 20; i++) // problem
        {
            temp1 = getProduct();   // Function to get next product
            if (temp1 != NULL)
            {
                product_list[i] = *temp1;   // Store product in array
                cout << i + 1 << ") " << temp1->getProduct_name() << "\n";  // Display product
            }
            else
                break;  // Exit loop if no more products
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;   // User input for product selection

        if (1 <= user_input <= i + 1)
        {
            chosen_product = &product_list[user_input - 1]; // Assign chosen product
            break;
        }
        else if (user_input == 0) // Exit
            return;
    }

    // Step 2: Get the changes
    Change change_list[20]; // Array to store change list
    Change *temp2;   // Temporary pointer for change
    Change *chosen_change; // Pointer for chosen change
    // Function to set file cursor to the beginning of the change file
    seekToBeginningOfChangeFile();
    // Loop until there are no more changes to display
    while (temp2 != NULL) // question
    {
        cout << "Change report for the product '" << chosen_product->getProduct_name() << "': \n";
        // Display header for the changes report
        // change formats later
        cout << "Description                     "
             << "change ID   "
             << "State      "
             << "Priority     "
             << "Anticipated Release\n";

        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp2 = filterChange_doneOrCancelled(chosen_product->getProduct_name()); // Filter changes by product name and status
            if (temp2 != NULL)
            {
                    change_list[i] = *temp2;
                    // change format later
                    // Display each change
                    cout << i + 1 << ") " << temp2->description
                         << temp2->getChange_ID()
                         << temp2->status
                         << temp2->priority
                         << temp2->anticipated_release_ID << "\n";
            }
            else
                break;  // Exit loop if no more changes
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;   // User input for navigating changes

        if (user_input == 0)    // Exit
            return;
    }
}

// Function to control the report generation for all requesters
void allRequestersReportControl()
{
     // Step 1: Get the product
    Product product_list[20]; // Array to store product list
    Product *temp1; // Temporary pointer for product
    Product *chosen_product; // Pointer for chosen product

     // Function to set file cursor to the beginning of the product file
    seekToBeginningOfProductFile();
    // Loop until a valid product is chosen
    while (temp1 != NULL) // question
    {
        cout << "Select a product to print its report: \n";
        int i;
        // Display product options
        for (i = 0; i < 20; i++) // problem
        {
            temp1 = getProduct(); // Function to get the next product   
            if (temp1 != NULL)
            {
                product_list[i] = *temp1;   // Store product in array
                cout << i + 1 << ") " << temp1->getProduct_name() << "\n";  // Display product
            }
            else
                break;  // Exit loop if no more products
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;  // User input for product selection

        if (1 <= user_input <= i + 1)
        {
            chosen_product = &product_list[user_input - 1]; // Assign chosen product
            break;
        }
        else if (user_input == 0)   // Exit
            return;
    }

     // Step 2: Get the changes
    Change change_list[20]; // Array to store change list
    Change *temp2;  // Temporary pointer for change
    Change *chosen_change;  // Pointer for choosen change
    // Function to set file cursor to the beginning of the change file
    seekToBeginningOfChangeFile();
    // Loop until there are no more changes to display
    while (temp2 != NULL) // question
    {
        cout << "Change report for the product '" << chosen_product->getProduct_name() << "': \n";

        // change formats later
        // Display header for the changes report
        cout << "Description                     "
             << "change ID   "
             << "State      "
             << "Priority     "
             << "Anticipated Release\n";

        int i;
        for (i = 0; i < 20; i++) // problem
        {
            temp2 = filterChange(chosen_product->getProduct_name()); // Filter changes by product name
            if (temp2 != NULL)
            {
                    change_list[i] = *temp2;
                    // change format later
                    // Display each change
                    cout << i + 1 << ") " << temp2->description
                         << temp2->getChange_ID()
                         << temp2->status
                         << temp2->priority
                         << temp2->anticipated_release_ID << "\n";
            }
            else
                break; // Exit loop if no more changes
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input;  // User input for navigating changes

        if (1 <= user_input <= i + 1)
        {
            chosen_change = &change_list[user_input - 1];   // Assign chosen change
            break;
        }
        else if (user_input == 0)   // Exit
        {
            return;
        }
    }

    // Step 3: Get the releases
    Release release_list[20]; // Array to store release list
    Release *temp3; // Temporary pointer for release
    Release *chosen_release;    // Pointer for chosen release

     // Function to set file cursor to the beginning of the release file
    seekToBeginningOfReleaseFile();
     // Loop until a valid release is chosen
    while (temp3 != NULL) // question
    {
        cout << "Select an anticipated release that you want to update to: \n";

        // change formats later
        // Display header for the release options
        cout << "Release ID"
             << "Release date\n";

        int i;
        for (i = 0; i < 20; i++)
        {
            temp3 = filterRelease(chosen_product->getProduct_name());   // Filter releases by product name
            if (temp2 != NULL)
            {
                release_list[i] = *temp3;
                // change format later
                // Display each release
                cout << i + 1 << ") " << temp3->getRelease_ID()
                     << temp3->release_date << "\n";
            }
            else
                break;  // Exit loop if no more releases
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n"
             << "Enter selection: ";

        int user_input;
        cin >> user_input;   // User input for release selection

        if (1 <= user_input <= i + 1)
        {
            chosen_release = &release_list[user_input - 1]; // Assign chosen release
            break;
        }
        else if (user_input == 0)
            break;
    }

     // Step 4: Get the requesters
    Requester requester_list[20]; // Array to store requester list
    Requester *temp4;   // Temporary pointer for requester
    Requester *chosen_requester;    // Pointer for chosen requester
    // Get the change requests
    ChangeRequest changeRequester_list[20];  // Array to store change requests
    ChangeRequest *temp5;   // Temporary pointer for change request
    ChangeRequest *chosen_changeRequester;  // Pointer for chosen change request

    // Function to set file cursor to the beginning of the requester file
    seekToBeginningOfRequesterFile();
    // Function to set file cursor to the beginning of the change request file
    seekToBeginningOfChangeRequestFile();

    // Print header info
    cout << "Here is the report: \n" 
         << "Product: " << chosen_product->getProduct_name()
         << "Change description: " << chosen_change->description
         << "Change ID: " << chosen_change->getChange_ID()
         << "Release ID: " << chosen_release->getRelease_ID()
         << "State: " << chosen_change->status;

    while (temp5 != NULL) // question
    {
        int i;
        cout << "Requester" << "Email";
        for (i = 0; i < 20; i++)
        {
            temp5 = filter_ChangeRequest(chosen_change->getChange_ID(), chosen_release->getRelease_ID()); // Filter change requests by change ID and release ID
            if (temp5 != NULL)
            {
                temp4 = filer_requester(temp5->getRequester_name());    // Get the requester by name
                requester_list[i] = *temp4;
                // Display each requester
                cout << i+1 << temp4->get_RequesterName() << temp4->email;
            }
            else
                break;  // Exit loop if no more change requests
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n"
             << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= i + 1)
        {
            chosen_release = &release_list[user_input - 1];
            break;
        }
        else if (user_input == 0)
            break;
    }
}

// Function to control the shutdown process
void shutDownControl();

#endif