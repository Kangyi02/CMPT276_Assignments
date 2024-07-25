// DEFINITION MODULE ScenarioControl;
// Revision History:
// Rev. 1 - 24/07/17 Original by Group 24
// ----------------------------------------------------------
// Implement ScenarioControl.h
// ----------------------------------------------------------

#ifndef ScenarioControl_H
#define ScenarioControl_H

#include <iostream>
#include <cstring>
#include <string>
#include "ScenarioControl.h"
#include "Requester.h"
#include "Product.h"
#include "Release.h"
#include "ChangeRequest.h"
#include "Change.h"

using namespace std;

bool isValidDateFormat(const char* date)
{
    // Check length
    if (strlen(date) != 10)
        return false;

    // Check format YYYY-MM-DD
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7) // Check for dashes
        {
            if (date[i] != '-')
                return false;
        }
        else // Check for digits
        {
            if (!isdigit(date[i]))
                return false;
        }
    }

    return true;
}
// Function to control the creation of a product done
void createProductControl()
{
    // Prompt user to enter the product name
    cout << "Enter product's name (max 10 chars): ";

    // Get user input for the product name
    char product_name[100];
    cin >> product_name;
    // product_name[11] = '\0';

    cout << product_name;
    // Check if the input exceeds the character limit
    if (strlen(product_name) >= 10)
    {
        cout << "Product name exceeds the maximum length of 10 characters. Returning to the main menu.\n";
        return;
    }


    // Check if the product name contains only alphabetic characters
    for (int i = 0; i < strlen(product_name); i++)
    {
        if (!isalpha(product_name[i]))
        {
            cout << "Product name should only contain alphabetic characters. Returning to the main menu.\n";
            return;
        }
    }

    // Prompt the user to confirm adding the product
    cout << "Are you sure you want to add the product " << product_name << "(Y/N)? ";
    char userInput[2];
    cin >> userInput;

    // Check user input and proceed accordingly
    if (strcmp(userInput, "y") == 0 || strcmp(userInput, "Y") == 0)
    {
        // add the product(Writing product record to the file) and confirm success
        if (addProduct(product_name))
            cout << "The new product has been successfully added. \n";
    }
    else
        return; // Return to the main menu if user cancels
}

// Function to control the creation of a release done
void createReleaseControl()
{
    // Move the file pointer to the beginning of the product file
    seekToBeginningOfProductFile();

    // Array to store a list of products
    Product product_list[20];
    Product temp;   // Temporary product pointer
    Product chosen; // Chosen product pointer
    //*chosen.product_name = NULL;

    bool getFlag = getNextProduct(&temp);
    if (getFlag == false)
    {
        cout << "No additional records, this is the end of the product file. \n";
        return;
    }

    while (getFlag == true)
    {
        product_list[0] = temp;

        // Loop to display product list and select a product
        cout << "For which product you want to add a new release to: \n";
        cout << "   Product    \n";
        cout << "1) " << temp.product_name << "\n";

        int i;
        for (i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp) == true)
            {
                product_list[i] = temp;                             // Add product to the list
                cout << i + 1 << ") " << temp.product_name << "\n"; // Display product name
            }
            else
            {
                getFlag == false;
                break; // Exit loop if no more products
            }
        }

        // Display options for more products or exit
        cout << i + 1 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: "; // Get user input for selection

        int user_input;
        cin >> user_input;

        // Check if user input is within valid range
        if (user_input >= 1 && user_input <= i + 1)
        {
            chosen = product_list[user_input - 1]; // Select the chosen product
            break;
        }
        else
            return; // Return if user chooses to exit
    }

    // Prompt user to enter release ID
    cout << "Enter a release ID of the new release(max 8 chars): ";
    char release_ID[8]; // should it be global??
    cin >> release_ID;

     if (strlen(release_ID) > 8)
    {
        cout << "Release ID exceeds the maximum length of 8 characters. Returning to the main menu.\n";
        return;
    }

    // Prompt user to enter release date
    cout << "Enter a release date of the release (YYYY-MM-DD): ";
    char release_date[10]; // should it be global??
    cin >> release_date;

    // Validate release date format
    if (!isValidDateFormat(release_date))
    {
        cout << "Invalid release date format. Please enter in YYYY-MM-DD format. Returning to the main menu.\n";
        return;
    }

    if (strlen(release_date) > 10)
    {
        cout << "Release date exceeds the maximum length of 10 characters. Returning to the main menu.\n";
        return;
    }

    // Confirm adding the release
    cout << "Are you sure you want to add the release(Y/N)? ";
    // Check user input and proceed accordingly
    char sure_input[2];
    cin >> sure_input;

    if (strcmp(sure_input, "y") == 0 || strcmp(sure_input, "Y") == 0)
    {
        // Create new release and write to file
        Release new_release = Release(release_ID, chosen.product_name, release_date);
        if (addRelease(&new_release))
            cout << "The new release has been successfully added.\n";
    }
    else if (sure_input == "n" || sure_input == "N")
    {
        return; // Return to the main menu if user cancels
    }
}

// Function to control the creation of a change request
void createChangeRequestControl()
{
    // Move the file pointer to the beginning of the requester file
    seekToBeginningOfRequesterFile();

    // Array to store a list of requesters
    Requester requester_list[20];
    Requester temp;             // Temporary requester pointer
    Requester chosen_requester; // Chosen requester pointer

    // Loop to display requester list and select a requester
    int i;

    bool getFlag = getNextRequester(&temp);
    if (getFlag == false)
    {
        // Prompt user to create a new requester
        cout << "Creating a new requester: \n"
             << "Enter requester's name ('Last name, First name', max 30 chars): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cin.getline(chosen_requester.requester_name, 31);

        // Ask for phone number
        cout << "Enter the requester's phone number (11 digits, first digit is 1): ";
        cin.getline((char*)chosen_requester.phone_number, 12);

        // Ask for email
        cout << "Enter the requester's email (max 24 chars): ";
        cin.getline(chosen_requester.email, 25);

        // Ask if it's employee
        cout << "Is the requester an employee (Y/N)? ";
        char user_input[2];
        cin.getline(user_input, 2);

        if (strcmp(user_input, "y") == 0 || strcmp(user_input, "Y") == 0)
        {
            cout << "Enter new requester's department (max 12 chars): ";
            cin.getline(chosen_requester.department, 13);
        } else {
            strcpy(chosen_requester.department, "NULL");
        }

        cout << "Requester details:\n";
        cout << "Name: " << chosen_requester.requester_name << "\n"
             << "Phone Number: " << (int)*chosen_requester.phone_number << "\n"
             << "Email: " << chosen_requester.email << "\n"
             << "Department: " << chosen_requester.department << "\n";

        if (addRequester(&chosen_requester)) {
            cout << "The new requester has been successfully added.\n";
        }
        return;
    }

    while (getFlag == true)
    {
        requester_list[0] = temp;
        cout << "Select a requester that reports this change request: \n";
        cout << "Requester name                " << "Phone      " << "Email                   " << "Department  ";

        cout << "1) " << temp.requester_name
             << temp.phone_number
             << temp.email
             << temp.department
             << "\n";

        for (i = 1; i < 20; i++)
        {
            if (getNextRequester(&temp) == true)
            {
                requester_list[i] = temp; // Add requester to the list
                cout << i + 1 << ") " << temp.requester_name
                     << temp.phone_number
                     << temp.email
                     << temp.department
                     << "\n";
            }
            else
            {
                getFlag == false;
                break; // Exit loop if no more requesters
            }
        }
        // Display options for more requesters or to create a new one
        cout << i + 2 << ") Show more requesters\n";
        cout << "0) Create a new requester\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // Get user input for selection

        // Check if user input is within valid range
        if (user_input >= 1 && user_input <= i + 1)
        {
            chosen_requester = requester_list[user_input - 1]; // Select the chosen requester
            break;
        }
        else if (user_input == 0)
        {
            // Prompt user to create a new requester
            cout << "Creating a new requester: \n"
                 << "Enter requester's name ('Last name, First name', max 30 chars): ";
            cin >> chosen_requester.requester_name;

            // Ask for phone number
            cout << "Enter the requester's phone number (11 digits, first digit is 1): ";
            cin >> *chosen_requester.phone_number; // ??

            // Ask for email
            cout << "Enter the requester's email (max 24 chars): ";
            cin >> chosen_requester.email;

            // Ask if it's employee
            char user_input[1];
            cin >> user_input;
            if (user_input == "y" || user_input == "Y")
            {
                cout << "Enter new requester's department (max 12 chars): ";
                cin >> chosen_requester.department;
            }

            if (addRequester(&chosen_requester))
                cout << "The new requester has been successfully added. \n";
        }
    }

    // Move the file pointer to the beginning of the product file
    seekToBeginningOfProductFile();

    // Array to store a list of products
    Product product_list[20];
    Product temp1;          // Temporary product pointer
    Product chosen_product; // Chosen product pointer

    // Loop to display product list and select a product
    while (getNextProduct(&temp1))
    {
        product_list[0] = temp1;
        cout << "Select a product that corresponds to this change request: \n";
        cout << "Product    ";
        cout << "1) " << temp1.product_name;

        for (int i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp1))
            {
                product_list[i] = temp1;                             // Add product to the list
                cout << i + 1 << ") " << temp1.product_name << "\n"; // Add product to the list
            }
            else
                break; // Exit loop if no more products
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
            chosen_product = product_list[user_input - 1]; // Select the chosen product
            break;
        }
        else if (user_input == 0)
            return; // Return if user chooses to exit
    }

    // Move the file pointer to the beginning of the change file
    seekToBeginningOfChangeFile();

    // Array to store a list of changes
    Change change_list[20];
    Change temp2;         // Temporary change pointer
    Change chosen_change; // Chosen change pointer

    // Loop to display change list and select a change
    while (filterNextChange(&temp2, temp1.product_name))
    {
        cout << "Which change corresponds to the change request? \n";
        cout << "Description                     "
             << "change ID   "
             << "State      "
             << "Priority     "
             << "Anticipated Release\n";

        cout << "1) " << temp2.description
             << temp2.change_ID
             << temp2.status
             << temp2.priority
             << temp2.anticipated_release_ID << "\n";

        for (i = 1; i < 20; i++)
        {
            if (filterNextChange(&temp2, temp1.product_name))
            {
                change_list[i] = temp2; // Add change to the list
                cout << i + 1 << ") " << temp2.description
                     << temp2.change_ID
                     << temp2.status
                     << temp2.priority
                     << temp2.anticipated_release_ID << "\n";
            }
            else
                break; // Exit loop if no more changes
        }
        // Display options for more changes or to create a new one
        cout << i + 2 << ") More\n";
        cout << "0) New Change\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // Get user input for selection

        if (1 <= user_input <= i + 1)
        {
            chosen_change = change_list[user_input - 1]; // Select the chosen change
            break;
        }
        else if (user_input == 0)
        {
            // Prompt user to create a new change
            cout << "Enter the description of the new change (max 30 chars): ";
            cin >> chosen_change.description;
            *chosen_change.priority = 0; // if 0 print out N/A
            *chosen_change.status = *"Reported";
            int id[7];
            getNextCID(id);
            *chosen_change.change_ID = *id;
            *chosen_change.product_name = *chosen_product.product_name;
            *chosen_change.anticipated_release_ID = *"None";

            // Add to file
            if (addChange(&chosen_change))
                cout << "The new change has been successfully added. ";
        }
    }

    // Array to store a list of releases
    Release release_list[20];
    Release temp3;          // Temporary release pointer
    Release chosen_release; // Chosen release pointer

    // Move the file pointer to the beginning of the release file
    seekToBeginningOfReleaseFile();

    // Loop to display release list and select a release
    while (filterNextRelease(&temp3, temp1.product_name))
    {
        release_list[0] = temp3;
        cout << "Select a reported release that corresponds to this change request: \n";

        cout << "Release ID"
             << "Release date\n";

        cout << "1) " << temp3.release_ID
             << temp3.release_date << "\n";

        int i;
        for (i = 1; i < 20; i++)
        {
            if (filterNextRelease(&temp3, temp1.product_name))
            {
                release_list[i] = temp3; // Add release to the list
                cout << i + 1 << ") " << temp3.release_ID
                     << temp3.release_date << "\n";
            }
            else
                break; // Exit loop if no more releases
        }
        // Display options for more releases
        cout << i + 2 << ") More\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // Get user input for selection
        // Check if user input is within valid range
        if (1 <= user_input <= i + 1)
        {
            chosen_release = release_list[user_input - 1]; // Select the chosen release
            break;
        }
    }

    // Prompt user to enter additional information for the change request
    cout << "Enter the request date of the change request (YYYY-MM-DD): ";
    ChangeRequest new_changeRequest;
    cin >> new_changeRequest.request_date;
    *new_changeRequest.requester_name = *chosen_requester.requester_name;
    *new_changeRequest.change_ID = *chosen_change.change_ID;
    *new_changeRequest.reported_release_ID = *chosen_release.release_ID;

    // Create the new change request (Write the record to the file) and confirm success
    if (addChangeRequest(&new_changeRequest))
        cout << "The new change request has been successfully created. \n";
}

// Function to control the querying of a change
void queryChangeControl()
{
    // Array to store a list of products
    Product product_list[20];
    Product temp1;          // Temporary product pointer
    Product chosen_product; // Chosen product pointer

    // Loop to display product list and select a product
    while (getNextProduct(&temp1))
    {
        product_list[0] = temp1;
        cout << "Select a product:\n";
        cout << "1) " << temp1.product_name;

        int i;
        for (i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp1))
            {
                product_list[i] = temp1; // Add product to the list
                cout << i + 1 << ") " << temp1.product_name << "\n";
            }
            else
                break; // Exit loop if no more products
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
            chosen_product = product_list[user_input - 1]; // Select the chosen product
            break;
        }
        else if (user_input == 0)
            return; // Return if user chooses to exit
    }

    // Array to store a list of changes
    Change change_list[20];
    Change temp2;         // Temporary change pointer
    Change chosen_change; // Chosen change pointer

    // Move the file pointer to the beginning of the change file
    seekToBeginningOfChangeFile();

    // Loop to display change list and select a change
    while (filterNextChange(&temp2, chosen_product.product_name))
    {
        cout << "Changes in the product '" << chosen_product.product_name << "':\n";
        cout << "Description                     "
             << "change ID   \n";

        cout << "1) " << temp2.description
             << temp2.change_ID
             << "\n";

        int i;
        for (i = 1; i < 20; i++)
        {
            if (filterNextChange(&temp2, chosen_product.product_name))
            {
                change_list[i] = temp2; // Add change to the list
                cout << i + 1 << ") " << temp2.description
                     << temp2.change_ID
                     << "\n";
            }
            else
                break; // Exit loop if no more changes
        }
        // Display options for more changes or exit
        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // Get user input for selection

        // Check if user input is within valid range
        if (1 <= user_input <= i + 1)
        {
            chosen_change = change_list[user_input - 1]; // Select the chosen change
            break;
        }
        else if (user_input == 0)
            return; // Return if user chooses to exit
    }
    // Display the information about the chosen change item
    cout << "Here is the information about the change item you queried: \n";
    cout << "Product    "
         << "Description                     "
         << "change ID   "
         << "State      "
         << "Priority     "
         << "Anticipated Release\n";

    cout << chosen_product.product_name
         << chosen_change.description
         << chosen_change.change_ID
         << chosen_change.status
         << chosen_change.priority
         << chosen_change.anticipated_release_ID;
}

// Update control
void updateChangeControl()
{
    // Step 1: Get the product
    Product product_list[20];
    Product temp1;          // Temporary product pointer
    Product chosen_product; // Chosen product pointer

    // Loop to display product list and select a product
    while (getNextProduct(&temp1))
    {
        product_list[0] = temp1;
        cout << "Select a product that corresponds to the change you want to update: \n";
        cout << "Product    ";
        cout << "1) " << temp1.product_name;

        int i;
        // Display product options
        for (i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp1))
            {
                product_list[i] = temp1;                             // Store product in array
                cout << i + 1 << ") " << temp1.product_name << "\n"; // Display product
            }
            else
                break; // Exit loop if no more products
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for product selection

        if (1 <= user_input <= i + 1) // Check for valid selection
        {
            chosen_product = product_list[user_input - 1]; // Assign chosen product
            break;
        }
        else if (user_input == 0)
            return; // Exit
    }

    // Step 2: Get the changes
    seekToBeginningOfChangeFile(); // Function to set file cursor to the beginning of the change file

    Change change_list[20]; // Array to store change list
    Change temp2;           // Temporary pointer for change
    Change chosen_change;   // Pointer for chosen change

    // Loop until a valid change is chosen
    while (filterNextChange(&temp2, chosen_product.product_name))
    {
        cout << "Select a change you want to update: \n";
        cout << "Description                     "
             << "change ID   "
             << "State      "
             << "Priority     "
             << "Anticipated Release\n";
        cout << "1) " << temp2.description
             << temp2.change_ID
             << temp2.status
             << temp2.priority
             << temp2.anticipated_release_ID << "\n";

        int i;
        // Display change options
        for (i = 1; i < 20; i++)
        {
            if (filterNextChange(&temp2, chosen_product.product_name))
            {
                change_list[i] = temp2; // Store change in array
                cout << i + 1 << ") " << temp2.description
                     << temp2.change_ID
                     << temp2.status
                     << temp2.priority
                     << temp2.anticipated_release_ID << "\n"; // Display change
            }
            else
                break; // Exit loop if no more changes
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for change selection

        if (1 <= user_input <= i + 1) // Check for valid selection
        {
            chosen_change = change_list[user_input - 1]; // Assign chosen change
            break;
        }
        else if (user_input == 0) // Exit
        {
            return;
        }
    }
    // Step 3: Update the chosen change

    // Update description
    cout << "Updating the change with the change ID '1234' in the product '"
         << chosen_product.product_name << "':\n"
         << "Do you want to replace the description (Y/N)? ";
    char user_input1[1];
    cin >> user_input1;
    if (user_input1 == "Y" || user_input1 == "y")
    {
        cout << "Old description is: "
             << chosen_change.description
             << "\n"
             << "New description is: ";
        char *new_description;
        cin >> new_description;                        // Get new description
        *chosen_change.description = *new_description; // Update description
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
        chosen_change.status == "Reported"; // Update status
        break;
    case 2:
        chosen_change.status == "Evaluated";
        break;
    case 3:
        chosen_change.status == "Cancelled";
        break;
    case 4:
        chosen_change.status == "In process";
        break;
    case 5:
        chosen_change.status == "Done";
        break;
    case 0:
        break; // Keep current status
    }

    // Update priority
    cout << "The current priority is " << chosen_change.priority
         << "Enter a new priority, or 0 to keep the current priority: ";

    cin >> user_input2;
    if (user_input2 != 0)
        *chosen_change.priority = user_input2; // Update priority

    // Update anticipated release ID
    cout << "The current 'anticipated release' is " << chosen_change.anticipated_release_ID;

    // get release
    Release release_list[20]; // Array to store release list
    Release temp3;            // Temporary pointer for release
    Release chosen_release;   // Pointer for chosen release

    seekToBeginningOfReleaseFile(); // Function to set file cursor to the beginning of the release file
    // Loop until a valid release is chosen
    while (filterNextRelease(&temp3, temp1.product_name))
    {
        cout << "Select an anticipated release that you want to update to: \n";

        cout << "Release ID"
             << "Release date\n";

        cout << "1) " << temp3.release_ID
             << temp3.release_date << "\n"; // Display release

        int i;
        // Display release options
        for (i = 1; i < 20; i++)
        {
            if (filterNextRelease(&temp3, temp1.product_name))
            {
                release_list[i] = temp3; // Store release in array
                cout << i + 1 << ") " << temp3.release_ID
                     << temp3.release_date << "\n"; // Display release
            }
            else
                break; // Exit loop if no more releases
        }

        cout << i + 2 << ") More\n";
        cout << "0) Keep the current release\n"
             << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for release selection

        if (1 <= user_input <= i + 1) // Check for valid selection
        {
            chosen_release = release_list[user_input - 1]; // Assign chosen release
            // update the release id
            *chosen_change.anticipated_release_ID = *chosen_release.release_ID; // Update anticipated release ID
            break;
        }
        else if (user_input == 0) // Keep current release
            break;
    }

    updateChange(&chosen_change); // Function to update the change in the system
                                  // Display updated change info
    cout << "Change '" << chosen_change.change_ID << "' has been updated:\n"
         << "Description                     "
         << "change ID   "
         << "State      "
         << "Priority     "
         << "Anticipated Release\n";

    cout << chosen_change.description
         << chosen_change.change_ID
         << chosen_change.status
         << chosen_change.priority
         << chosen_change.anticipated_release_ID;
}

// Reports control
void allChangesReportControl()
{
    // Step 1: Get the product
    Product product_list[20]; // Array to store product list
    Product temp1;            // Temporary pointer for product
    Product chosen_product;   // Pointer for chosen product

    // Function to set file cursor to the beginning of the product file
    seekToBeginningOfProductFile();

    // Loop until a valid product is chosen
    while (getNextProduct(&temp1))
    {
        cout << "Select a product to print its report: \n";
        cout << "1) " << temp1.product_name << "\n"; // Display product

        int i;
        // Display product options
        for (i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp1))
            {
                product_list[i] = temp1;                             // Store product in array
                cout << i + 1 << ") " << temp1.product_name << "\n"; // Display product
            }
            else
                break; // Exit loop if no more products
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for product selection

        if (1 <= user_input <= i + 1)
        {
            chosen_product = product_list[user_input - 1]; // Assign chosen product
            break;
        }
        else if (user_input == 0) // Exit
            return;
    }

    // Step 2: Get the changes
    Change change_list[20]; // Array to store change list
    Change temp2;           // Temporary pointer for change
    Change chosen_change;   // Pointer for chosen change

    // Function to set file cursor to the beginning of the change file
    seekToBeginningOfChangeFile();

    // Loop until there are no more changes to display
    while (filterNextChange_DoneOrCancelled(&temp2, chosen_product.product_name))
    {
        cout << "Change report for the product '" << chosen_product.product_name << "': \n";
        // Display header for the changes report
        cout << "Description                     "
             << "change ID   "
             << "State      "
             << "Priority     "
             << "Anticipated Release\n";

        cout << "1) " << temp2.description
             << temp2.change_ID
             << temp2.status
             << temp2.priority
             << temp2.anticipated_release_ID << "\n";
        int i;
        for (i = 1; i < 20; i++)
        {
            if (filterNextChange_DoneOrCancelled(&temp2, chosen_product.product_name))
            {
                change_list[i] = temp2;
                // Display each change
                cout << i + 1 << ") " << temp2.description
                     << temp2.change_ID
                     << temp2.status
                     << temp2.priority
                     << temp2.anticipated_release_ID << "\n";
            }
            else
                break; // Exit loop if no more changes
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for navigating changes

        if (user_input == 0) // Exit
            return;
    }
}

// Function to control the report generation for all requesters
void allRequestersReportControl()
{
    // Step 1: Get the product
    Product product_list[20]; // Array to store product list
    Product temp1;            // Temporary pointer for product
    Product chosen_product;   // Pointer for chosen product

    // Function to set file cursor to the beginning of the product file
    seekToBeginningOfProductFile();

    // Loop until a valid product is chosen
    while (getNextProduct(&temp1))
    {
        cout << "Select a product to print its report: \n";
        cout << "1) " << temp1.product_name << "\n"; // Display product

        int i;
        // Display product options
        for (i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp1))
            {
                product_list[i] = temp1;                             // Store product in array
                cout << i + 1 << ") " << temp1.product_name << "\n"; // Display product
            }
            else
                break; // Exit loop if no more products
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for product selection

        if (1 <= user_input <= i + 1)
        {
            chosen_product = product_list[user_input - 1]; // Assign chosen product
            break;
        }
        else if (user_input == 0) // Exit
            return;
    }

    // Step 2: Get the changes
    Change change_list[20]; // Array to store change list
    Change temp2;           // Temporary pointer for change
    Change chosen_change;   // Pointer for choosen change

    // Function to set file cursor to the beginning of the change file
    seekToBeginningOfChangeFile();

    // Loop until there are no more changes to display
    while (filterNextChange(&temp2, chosen_product.product_name))
    {
        cout << "Change report for the product '" << chosen_product.product_name << "': \n";

        // Display header for the changes report
        cout << "Description                     "
             << "change ID   "
             << "State      "
             << "Priority     "
             << "Anticipated Release\n";

        cout << "1) " << temp2.description
             << temp2.change_ID
             << temp2.status
             << temp2.priority
             << temp2.anticipated_release_ID << "\n";
        int i;
        for (i = 1; i < 20; i++)
        {
            if (filterNextChange(&temp2, chosen_product.product_name))
            {
                change_list[i] = temp2;
                // Display each change
                cout << i + 1 << ") " << temp2.description
                     << temp2.change_ID
                     << temp2.status
                     << temp2.priority
                     << temp2.anticipated_release_ID << "\n";
            }
            else
                break; // Exit loop if no more changes
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for navigating changes

        if (1 <= user_input <= i + 1)
        {
            chosen_change = change_list[user_input - 1]; // Assign chosen change
            break;
        }
        else if (user_input == 0) // Exit
        {
            return;
        }
    }

    // Step 3: Get the releases
    Release release_list[20]; // Array to store release list
    Release temp3;            // Temporary pointer for release
    Release chosen_release;   // Pointer for chosen release

    // Function to set file cursor to the beginning of the release file
    seekToBeginningOfReleaseFile();

    // Loop until a valid release is chosen
    while (filterNextRelease(&temp3, chosen_product.product_name))
    {
        cout << "Select an anticipated release that you want to update to: \n";

        // Display header for the release options
        cout << "Release ID"
             << "Release date\n";

        cout << "1) " << temp3.release_ID
             << temp3.release_date << "\n";

        int i;
        for (i = 1; i < 20; i++)
        {
            if (filterNextRelease(&temp3, chosen_product.product_name))
            {
                release_list[i] = temp3;
                // Display each release
                cout << i + 1 << ") " << temp3.release_ID
                     << temp3.release_date << "\n";
            }
            else
                break; // Exit loop if no more releases
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n"
             << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for release selection

        if (1 <= user_input <= i + 1)
        {
            chosen_release = release_list[user_input - 1]; // Assign chosen release
            break;
        }
        else if (user_input == 0)
            break;
    }

    // Step 4: Get the requesters
    Requester requester_list[20]; // Array to store requester list
    Requester temp4;              // Temporary pointer for requester
    Requester chosen_requester;   // Pointer for chosen requester

    // Get the change requests
    ChangeRequest changeRequester_list[20]; // Array to store change requests
    ChangeRequest temp5;                    // Temporary pointer for change request
    ChangeRequest chosen_changeRequester;   // Pointer for chosen change request

    // Function to set file cursor to the beginning of the requester file
    seekToBeginningOfRequesterFile();
    // Function to set file cursor to the beginning of the change request file
    seekToBeginningOfChangeRequestFile();

    // Print header info
    cout << "Here is the report: \n"
         << "Product: " << chosen_product.product_name
         << "Change description: " << chosen_change.description
         << "Change ID: " << chosen_change.change_ID
         << "Release ID: " << chosen_release.release_ID
         << "State: " << chosen_change.status;

    while (filterNextChangeRequest(&temp5, chosen_change.change_ID))
    {
        int i;
        cout << "Requester" << "Email";
        filterNextRequester(&temp4, temp5.requester_name);
        requester_list[0] = temp4;
        cout << "1) " << temp4.requester_name << temp4.email;

        for (i = 1; i < 20; i++)
        {
            if (filterNextChangeRequest(&temp5, chosen_change.change_ID))
            {
                filterNextRequester(&temp4, temp5.requester_name); // Get the requester by name
                requester_list[i] = temp4;
                // Display each requester
                cout << i + 1 << ") " << temp4.requester_name << temp4.email;
            }
            else
                break; // Exit loop if no more change requests
        }

        cout << i + 2 << ") More\n";
        cout << "0) Exit\n"
             << "Enter selection: ";

        int user_input;
        cin >> user_input;

        if (1 <= user_input <= i + 1)
        {
            chosen_release = release_list[user_input - 1];
            break;
        }
        else if (user_input == 0)
            break;
    }
}

// Function to control the shutdown process
void shutDownControl()
{
    bool allClosed = true;
    cout << "\n";

    // Close Change
    if (closeChange())
    {
        cout << "Change module closed successfully.\n";
    }
    else
    {
        cout << "Failed to close Change module.\n";
        allClosed = false;
    }

    // Close Change Request
    if (closeChangeRequest())
    {
        cout << "Change Request module closed successfully.\n";
    }
    else
    {
        cout << "Failed to close Change Request module.\n";
        allClosed = false;
    }

    // Close Product
    if (closeProduct())
    {
        cout << "Product module closed successfully.\n";
    }
    else
    {
        cout << "Failed to close Product module.\n";
        allClosed = false;
    }

    // Close Release
    if (closeRelease())
    {
        cout << "Release module closed successfully.\n";
    }
    else
    {
        cout << "Failed to close Release module.\n";
        allClosed = false;
    }

    // Close Requester
    if (closeRequester())
    {
        cout << "Requester module closed successfully.\n";
    }
    else
    {
        cout << "Failed to close Requester module.\n";
        allClosed = false;
    }

    // Overall status
    if (allClosed)
    {
        cout << "All modules closed successfully.\n";
    }
    else
    {
        cout << "One or more modules failed to close.\n";
    }
}

#endif
