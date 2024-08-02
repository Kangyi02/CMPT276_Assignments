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
#include <cctype> // For isalpha
#include <regex>  // For regex validation
#include <limits> // For std::numeric_limits
#include <set>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::left;
using std::right;
using std::to_string;
// using namespace std;

// Function to control the creation of a product done
void createProductControl()
{
    // Prompt user to enter the product name
    char product_name[11];
    string tempProductName;
    while (true)
    {
        cout << "Enter product's name (max 10 chars): ";
        cin >> tempProductName;
        if (tempProductName.length() > 10)
        {
            cout << "Product name exceeds the maximum length of 10 characters. Please enter a valid name." << endl;
            continue;
        }

        break; // Exit the loop if the name is valid
    }
    // Copy the string to the fixed-size character array
    tempProductName.copy(product_name, tempProductName.length());
    product_name[tempProductName.length()] = '\0';

    // Prompt the user to confirm adding the product
    string userInput;
    while (true)
    {
        cout << "Are you sure you want to add the product " << product_name << " (Y/N)? ";
        cin >> userInput;

        if (userInput == "y" || userInput == "Y")
        {
            // Add the product (Writing product record to the file) and confirm success
            if (addProduct(product_name))
            {
                cout << "The new product has been successfully added." << endl;
            }
            break;
        }
        else if (userInput == "n" || userInput == "N")
        {
            cout << "Product addition cancelled. Returning to the main menu." << endl;
            return; // Return to the main menu if user cancels
        }
        else
        {
            cout << "Invalid input. Please enter 'Y' for yes or 'N' for no." << endl;
        }
    }
}

// ---------------------------------------------------------------------------------------

// Function to control the creation of a release done
void createReleaseControl()
{
    // Move the file pointer to the beginning of the product file
    seekToBeginningOfProductFile();
    // Array to store a list of products
    Product product_list[20];
    Product temp;   // Temporary product pointer
    Product chosen; // Chosen product pointer

    bool getFlag = getNextProduct(&temp);
    if (getFlag == false)
    {
        cout << "No products found. The Product file is empty." << endl;
        return;
    }
    // cout << "For which product you want to add a new release to: \n";

    while (true)
    {
        product_list[0] = temp;

        // Loop to display product list and select a product
        cout << "For which product you want to add a new release to:" << endl;
        cout << "    Product    " << endl;
        cout << " 1) " << temp.product_name << endl;

        int i;
        for (i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp) == true)
            {
                product_list[i] = temp;                             // Add product to the list
                cout << right << setw(4) << to_string(i + 1) + ") " << left << temp.product_name << endl; // Display product name
            }
            else
            {
                break; // Exit loop if no more products
            }
        }

        // Display options for more products or exit
        if (i == 20 && getNextProduct(&temp) == true)
            cout << i + 1 << ") More" << endl;

        cout << " 0) Exit" << endl;

        int userInput;
        while (true)
        {
            cout << "Enter selection: ";
            cin >> userInput;

            if (userInput < 0 || userInput > i + 1)
            {
                cout << "Invalid input. Enter again." << endl;
                continue;
            }
            break;
        }

        if (userInput >= 1 && userInput <= i)
        {
            chosen = product_list[userInput - 1];
            break;
        }
        else if (userInput == 0)
        {
            cout << "Release addition cancelled. Returning to the main menu." << endl;
            return; // Return to the main menu if user cancels
        } // Go back to the top if i+1) more
    }

    char release_ID[9]; // Adjusted size to account for null-terminator
    string tempReleaseID;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
        //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Enter a release ID for the new release (max 8 chars): ";
        getline(cin, tempReleaseID);
        if (tempReleaseID.length() <= 8)
        {
            break;
        }
        else
        {
            cout << "Release ID exceeds the maximum length of 8 characters. Please enter again." << endl;
        }
    }
    // Copy the string to the fixed-size character array
    tempReleaseID.copy(release_ID, tempReleaseID.length());
    release_ID[tempReleaseID.length()] = '\0';

    char release_date[11];
    string tempDate;
    while (true)
    {
        cout << "Enter a release date for the release (YYYY-MM-DD): ";
        cin >> tempDate;
        if (tempDate.length() > 10)
        {
            cout << "Release date exceed the manimum length of 10 characters with the format (YYYY-MM-DD). Please enter again" << endl;
            continue;
        }
        break;
    }
    // Copy the string to the fixed-size character array
    tempDate.copy(release_date, tempDate.length());
    release_date[tempDate.length()] = '\0';

    // Confirm
    string userInput;
    while (true)
    {
        cout << "Are you sure you want to add the release " << release_ID << " (Y/N)? ";
        cin >> userInput;

        if (userInput == "y" || userInput == "Y")
        {
            // Create new release and write to file
            Release new_release = Release(release_ID, chosen.product_name, release_date);
            if (addRelease(&new_release))
            {
                cout << "The new release has been successfully added." << endl;
            }
            break;        
        }
        else if (userInput == "n" || userInput == "N")
        {
            cout << "Release addition cancelled. Returning to the main menu." << endl;
            return; // Return to the main menu if user cancels
        }
        else
        {
            cout << "Invalid input. Please enter 'Y' for yes or 'N' for no." << endl;
        }
    }
}

// --------------------------------------------------------------------------------------

// Function to format the name from "Last name, First name" to "First name Last name"
void formatRequesterName(const string &input_name, char *formatted_name)
{
    char last_name[31];
    char first_name[31];

    // Split the input_name into last_name and first_name
    sscanf(input_name.c_str(), "%30[^,], %30[^\n]", last_name, first_name);

    // Ensure the total length is within 30 characters
    snprintf(formatted_name, 31, "%s %s", first_name, last_name);
}

// --------------------------------------------------------------------------------------

// create requester control
void createRequester(Requester chosen_requester)
{
    // Prompt user to create a new requester
    cout << "Creating a new requester:" << endl;
    string inputname;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
        //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Enter requester's name ('Last name, First name', max 30 chars): ";
        getline(cin, inputname);

        if (inputname.length() > 31)
        {
            cout << "Requester name exceeds the maximum length of 30 characters. Please enter a valid name." << endl;
            continue;
        }

        formatRequesterName(inputname, chosen_requester.requester_name);
        break;
    }

    while (true)
    {
        cout << "Enter the requester's phone number (11 digits, first digit is 1): ";
        string phone_number_input;
        cin >> phone_number_input;

        if (phone_number_input.length() != 11)
        {
            cout << "Phone number must be exactly 11 digits. Please enter a valid number." << endl;
            continue;
        }

        chosen_requester.phone_number = std::stol(phone_number_input);
        break;
    }

    while (true)
    {
        cout << "Enter the requester's email (max 24 chars): ";
        string email_input;
        cin >> email_input;

        if (email_input.length() > 25)
        {
            cout << "Email length must be less than 25 chars. Please enter a valid number.\n";
            continue;
        }
        strncpy(chosen_requester.email, email_input.c_str(), sizeof(chosen_requester.email) - 1);
        chosen_requester.email[sizeof(chosen_requester.email) - 1] = '\0';
        break;
    }

    string userInput;
    while (true)
    {
        cout << "Is the requester an employee (Y/N)? ";
        cin >> userInput;

        if (userInput == "y" || userInput == "Y")
        {   
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (true)
            {
                //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Enter the requester's department (max 12 chars): ";
                string department_input;
                getline(cin, department_input);

                if (department_input.length() > 13)
                {
                    cout << "Department name exceeds the maximum length of 12 characters. Please enter a valid department.\n";
                    continue;
                }

                strncpy(chosen_requester.department, department_input.c_str(), sizeof(chosen_requester.department) - 1);
                chosen_requester.department[sizeof(chosen_requester.department) - 1] = '\0';
                break;
            }
            break;
        }
        else if (userInput == "n" || userInput == "N")
        {
            // skip this process
            break;
        }
        else
        {
            cout << "Invalid input. Please enter 'Y' for yes or 'N' for no." << endl;
        }
    }

    // Write the requester to the file
    if (addRequester(&chosen_requester))
    {
        cout << "The new requester has been successfully added." << endl;
    }
    else
    {
        cout << "Failed to add the new requester to the file." << endl;
    }
}

// ---------------------------------------------------------------------------------------

// Create change function
void createChange(Product chosen_product, Change* chosen_change)
{
    // Prompt user to create a new change
    string temp_description;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
        //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Enter the description of the new change (max 30 chars): ";
        getline(cin, temp_description);

        // description length check
        if (temp_description.length() > 30)
        {
            cout << "Description length must be less than 30 chars. Please enter a valid number." << endl;
            continue;
        }

        temp_description.copy(chosen_change->description, temp_description.length());
        chosen_change->description[temp_description.length()] = '\0';
        break;
    }

    // we set the priority here
    chosen_change->priority = 0; // if 0 print out N/A
    string status_reported = "Reported";
    status_reported.copy(chosen_change->status, status_reported.length());
    chosen_change->status[status_reported.length()] = '\0';

    strcpy(chosen_change->product_name, chosen_product.product_name);
    string tempRelease_ID = "None";
    chosen_change->anticipated_release_ID[tempRelease_ID.length()] = '\0';

    tempRelease_ID.copy(chosen_change->anticipated_release_ID, tempRelease_ID.length());

    // Add to file
    if (addChange(chosen_change))
        cout << "The new change has been successfully added. \n";
}

// --------------------------------------------------------------------------------------

// Function to control the creation of a change request
void createChangeRequestControl()
{
    // Move the file pointer to the beginning of the requester file
    seekToBeginningOfRequesterFile();

    // Array to store a list of requesters
    Requester requester_list[20];
    Requester temp;             // Temporary requester
    Requester chosen_requester; // Chosen requester

    // Check if at least one requester exists
    bool getRequesterFlag = getNextRequester(&temp);
    if (!getRequesterFlag)
    {
        createRequester(chosen_requester);
    }

    // Requester exists, show list and let user select one
    int i;
    while (getRequesterFlag)
    {
        requester_list[0] = temp;
        cout << "Select a requester that reports this change request:" << endl;
        cout << left << setw(35) << "    Requester name" 
             << setw(12) << "Phone" 
             << setw(25) << "Email" 
             << setw(13) << "Department" << endl;

        cout << " 1) "
             << left 
             << setw(31) << temp.requester_name 
             << setw(12) << temp.phone_number 
             << setw(25) << temp.email
             << setw(13) << temp.department
             << endl;

        for (i = 1; i < 20; i++)
        {
            if (getNextRequester(&temp) == true)
            {
                requester_list[i] = temp; // Add requester to the list
                cout << right << setw(4) << to_string(i+1) + ") " 
                     << left
                     << setw(31) << temp.requester_name 
                     << setw(12) << temp.phone_number 
                     << setw(25) << temp.email
                     << setw(13) << temp.department
                     << endl;
            }
            else
            {
                getRequesterFlag = false;
                break; // Exit loop if no more requesters
            }
        }

        // Display options for more requesters or to create a new one
        if (i == 20 && getNextRequester(&temp))
            cout << i + 1 << ") More" << endl;

        cout << " 0) Create a new requester" << endl;

        int userInput;

        while (true)
        {
            cout << "Enter selection: ";
            cin >> userInput; // Get user input for selection    
            if (userInput < 0 || userInput > i + 1)
            {
                cout << "Invalid input. Enter again." << endl;
                continue;
            }       
            break;
        }

        if (userInput >0 && userInput < i + 1)
        {
            chosen_requester = requester_list[userInput - 1]; // Select the chosen requester
            break;
        }
        else if (userInput == 0)
        {
            createRequester(chosen_requester);
            break;
        }
    }

    // Move the file pointer to the beginning of the product file
    seekToBeginningOfProductFile();

    // Array to store a list of products
    Product product_list[20];
    Product temp1;          // Temporary product pointer
    Product chosen_product; // Chosen product pointer

    // Loop to display product list and select a product
    bool getProductFlag = getNextProduct(&temp1);
    if (getProductFlag == false)
    {
        // Terminate the operation if there is no product
        cout << "No products found. The Release file is empty." << endl;
        return;
    }

    while (getProductFlag)
    {
        product_list[0] = temp1;
        cout << "Select a product that corresponds to this change request:" << endl
             << "     Product    " << endl
             << " 1) " << temp1.product_name << endl;

        int i;
        for (i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp1))
            {
                product_list[i] = temp1;                             // Add product to the list
                cout << right << setw(4) << to_string(i + 1) + ") " << left << temp1.product_name << endl; // Add product to the list
            }
            else
            {
                getProductFlag = false;
                break; // Exit loop if no more products
            }
        }

        // Display options for more products or exit
        if (i == 20 && getNextProduct(&temp1))
            cout << i + 1 << ") More" << endl;

        cout << " 0) Exit" << endl;

        int userInput;
        while (true)
        {
            cout << "Enter selection: ";
            cin >> userInput; // Get user input for selection

            if (userInput < 0 || userInput > i + 1)
            {
                cout << "Invalid input. Enter again." << endl;
                continue;
            }
            break;
        }

        // Check if user input is within valid range
        if (userInput >= 1 && userInput < i + 1)
        {
            chosen_product = product_list[userInput - 1]; // Select the chosen product
            break;
        }
        else if (userInput == 0)
            return; // Back to main menu
    }

    // Move the file pointer to the beginning of the change file
    seekToBeginningOfChangeFile();

    // Array to store a list of changes
    Change change_list[20];
    Change temp2;         // Temporary change pointer
    Change chosen_change; // Chosen change pointer

    bool getChangeFlag = filterNextChange(&temp2, chosen_product.product_name);
    if (getChangeFlag == false)
    {
        cout << "There is no change corresponding to this product." << endl;
        createChange(chosen_product, &chosen_change);
    }

    // Loop to display change list and select a change
    while (getChangeFlag)
    {
        change_list[0] = temp2;
        cout << "Which change corresponds to the change request?" << endl;
        cout << left << setw(34) << "   Description"
             << setw(10) << "Change ID"
             << setw(11) << "State"
             << setw(9) << "Priority"
             << setw(9) << "Anticipated Release" << endl;

        cout << left << setw(3) << "1)" 
            << setw(31) << temp2.description 
            << setw(10) << temp2.change_ID 
            << setw(11) << temp2.status 
            << setw(9) << temp2.priority 
            << setw(9) << temp2.anticipated_release_ID << endl;

        int i;
        for (i = 1; i < 20; i++)
        {
            if (filterNextChange(&temp2, chosen_product.product_name))
            {
                change_list[i] = temp2; // Add change to the list
                cout << left << setw(3) << to_string(i + 1) + ")" 
                     << setw(31) << temp2.description 
                     << setw(10) << temp2.change_ID 
                     << setw(11) << temp2.status 
                     << setw(9) << temp2.priority 
                     << setw(9) << temp2.anticipated_release_ID << endl;
            }
            else
            {
                getChangeFlag = false;
                break; // Exit loop if no more changes
            }
        }

        // Display options for more changes or to create a new one
        if (i == 20 && filterNextChange(&temp2, chosen_product.product_name))
            cout << i + 1 << ") More" << endl;

        cout << "0) New Change" << endl;

        int userInput;
        while (true)
        {
            cout << "Enter selection: ";
            cin >> userInput; // Get user input for selection
            if (userInput < 0 || userInput > i + 1)
            {
                cout << "Invalid input. Enter again." << endl;
                continue;
            }
            break;
        }

        if (userInput >= 1 && userInput < i + 1)
        {
            cout << "The user selects: " << i << endl;
            chosen_change = change_list[userInput - 1]; // Select the chosen change
            break;
        }
        else if (userInput == 0)
        {
            createChange(chosen_product, &chosen_change);
            // chosen_change.change_ID = temp2.change_ID++; // what is this for ?
            break;
        }
    }

    // Array to store a list of releases
    Release release_list[20];
    Release temp3;          // Temporary release pointer
    Release chosen_release; // Chosen release pointer

    // Move the file pointer to the beginning of the release file
    seekToBeginningOfReleaseFile();

    bool getReleaseFlag = filterNextRelease(&temp3, chosen_product.product_name);

    if (getReleaseFlag == false)
    {
        cout << "No release found. The Release file is empty." << endl;
        return;
    }

    // Loop to display release list and select a release
    while (getReleaseFlag)
    {
        release_list[0] = temp3;
        cout << "Select a reported release that corresponds to this change request:" << endl
             << left << setw(14) << "   Release ID"
             << setw(13) << "Release date" << endl;

        cout << "1) " 
             << setw(11) << temp3.release_ID
             << setw(13) << temp3.release_date 
             << endl;

        int i;
        for (i = 1; i < 20; i++)
        {
            if (filterNextRelease(&temp3, chosen_product.product_name))
            {
                release_list[i] = temp3; // Add release to the list
                cout << left << setw(3) << to_string(i + 1) + ")"
                     << setw(11) << temp3.release_ID
                     << setw(13) << temp3.release_date
                     << endl;
            }
            else
            {
                getReleaseFlag = false;
                break; // Exit loop if no more releases
            }
        }
        // Display options for more releases
        if (i == 20 && filterNextRelease(&temp3, chosen_product.product_name))
            cout << i + 1 << ") More" << endl;

        cout << "Enter selection: ";
        int user_input;
        cin >> user_input; // Get user input for selection

        // Check if user input is within valid range
        if (user_input >= 1 && user_input < i + 1)
        {
            chosen_release = release_list[user_input - 1]; // Select the chosen release
            break;
        }
    }

    // Prompt user to enter additional information for the change request
    ChangeRequest new_changeRequest;

    string tempDate;
    while (true)
    {
        cout << "Enter the request date of the change request (YYYY-MM-DD): ";
        cin >> tempDate;
        if (tempDate.length() > 10)
        {
            cout << "Release date exceed the manimum length of 10 characters with the format (YYYY-MM-DD). Please enter again" << endl;
            continue;
        }
        break;        
    }

    tempDate.copy(new_changeRequest.request_date, tempDate.length());
    new_changeRequest.request_date[tempDate.length()] = '\0';

    strcpy(new_changeRequest.requester_name, chosen_requester.requester_name);
    new_changeRequest.change_ID = chosen_change.change_ID; 
    strcpy(new_changeRequest.reported_release_ID, chosen_release.release_ID);

    // Create the new change request (Write the record to the file) and confirm success
    if (addChangeRequest(&new_changeRequest))
        cout << "The new change request has been successfully added." << endl;
}

// ---------------------------------------------------------------------------------------

// Function to control the querying of a change
void queryChangeControl()
{
    // Move the file pointer to the beginning of the product file
    seekToBeginningOfProductFile();

    // Array to store a list of products
    Product product_list[20];
    Product temp1;          // Temporary product pointer
    Product chosen_product; // Chosen product pointer

    // Loop to display product list and select a product
    bool getProductFlag = getNextProduct(&temp1);
    if (getProductFlag == false)
    {
        cout << "No product found. Returning to the main menu" << endl;
        return;
    }

    while (getProductFlag)
    {
        product_list[0] = temp1;
        cout << "Select a product:" << endl;
        cout << " 1) " << temp1.product_name << endl;

        int i;
        for (i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp1))
            {
                product_list[i] = temp1; // Add product to the list
                cout << right << setw(4) << to_string(i + 1) + ") " << left << temp1.product_name << endl;
            }
            else
                break; // Exit loop if no more products
        }
        // Display options for more products or exit
        if (i == 20 && getNextProduct(&temp1))
            cout << i + 1 << ") More" << endl;
        cout << " 0) Exit" << endl;

        int userInput;
        while (true)
        {
            cout << "Enter selection: ";
            cin >> userInput; // Get user input for selection

            if (userInput < 0 || userInput > i +1)
            {
                cout << "Invalid input. Enter again." << endl;
                continue;
            }
            break;
        }

        // Do operations according to the user input
        if (userInput >= 1 && userInput < i + 1)
        {
            chosen_product = product_list[userInput - 1]; // Select the chosen product
            break;
        }
        else if (userInput == 0)
        {
            getProductFlag = false;
            return; // Return if user chooses to exit
        }
    }

    seekToBeginningOfChangeFile();
    // Array to store a list of changes
    Change change_list[20];
    Change temp2;         // Temporary change pointer
    Change chosen_change; // Chosen change pointer

    // Move the file pointer to the beginning of the change file

    bool getChangeFlag = filterNextChange(&temp2, chosen_product.product_name);
    if (getChangeFlag == false)
    {
        cout << "No change related to '" << chosen_product.product_name << "' found. Returning to the main menu" << endl;
        return;
    }

    // Loop to display change list and select a change
    while (getChangeFlag)
    {
        change_list[0] = temp2;
        cout << "Changes in the product '" << chosen_product.product_name << "':" << endl;
        cout << left << setw(35) << "    Description"
             << setw(10) << "Change ID"
             << endl;

        cout << right << setw(4) << "1) " 
            << left
            << setw(31) << temp2.description 
            << setw(10) << temp2.change_ID
            << endl;

        int i;
        for (i = 1; i < 20; i++)
        {
            if (filterNextChange(&temp2, chosen_product.product_name))
            {
                change_list[i] = temp2; // Add change to the list
                cout << left << setw(4) << to_string(i + 1) + ")" 
                     << setw(31) << temp2.description 
                     << setw(10) << temp2.change_ID
                     << endl;
            }
            else
                break; // Exit loop if no more changes
        }

        // Display options for more changes or exit
        if (i == 20 && filterNextChange(&temp2, chosen_product.product_name))
            cout << i + 1 << ") More" << endl;
        cout << " 0) Exit" << endl;
        int userInput;

        cout << "Enter selection: ";
        cin >> userInput;

        // Check if user input is within valid range
        if (userInput >= 1 && userInput < i + 1)
        {
            chosen_change = change_list[userInput - 1]; // Select the chosen change
            break;
        }
        else if (userInput == 0)
            return; // Return if user chooses to exit
    }

    // Display the information about the chosen change item
    cout << "Here is the information about the change item you queried: \n";
    cout << left << setw(11) << "Product" 
         << setw(31) << "Description"
         << setw(10) << "Change ID"
         << setw(11) << "State"
         << setw(9) << "Priority"
         << setw(9) << "Anticipated Release" 
         << endl
         << setw(11) << chosen_product.product_name
         << setw(31) << chosen_change.description
         << setw(10) << chosen_change.change_ID
         << setw(11) << chosen_change.status
         << setw(9) << chosen_change.priority
         << setw(9) << chosen_change.anticipated_release_ID
         << endl;
}

// ---------------------------------------------------------------------------------------

// Update control
void updateChangeControl()
{
    // Move the file pointer to the beginning of the product file
    seekToBeginningOfProductFile();

    // Step 1: Get the product
    Product product_list[20];
    Product temp1;          // Temporary product pointer
    Product chosen_product; // Chosen product pointer

    // Loop to display product list and select a product
    bool getProductFlag = getNextProduct(&temp1);
    if (getProductFlag == false)
    {
        cout << "No product found. The Product file is empty." << endl;
        return;
    }

    while (getProductFlag)
    {
        product_list[0] = temp1;
        cout << "Select a product that corresponds to the change you want to update:" << endl;
        cout << "    Product" << endl;
        cout << " 1) " << temp1.product_name << endl;

        int i;
        // Display product options
        for (i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp1))
            {
                product_list[i] = temp1;                             // Store product in array
                cout << right << setw(4) << to_string(i + 1) + ") " << left << temp1.product_name << endl; // Display product
            }
            else
            {
                getProductFlag = false;
                break; // Exit loop if no more products
            }
        }

        if (i == 20 && getNextProduct(&temp1))
            cout << i + 1 << ") More\n";
        cout << " 0) Exit\n";
        int userInput;
        while (true)
        {
            cout << "Enter selection: ";
            cin >> userInput;
            if (userInput < 0 || userInput > i +1)
            {
                cout << "Invalid input. Enter again." << endl;
                continue;
            }
            break;
        }

        if (userInput >= 1 && userInput < i + 1) // Check for valid selection
        {
            chosen_product = product_list[userInput - 1]; // Assign chosen product
            break;
        }
        else if (userInput == 0)
        {
            getProductFlag = false;
            return; // Exit
        }
    }

    // Step 2: Get the changes
    seekToBeginningOfChangeFile(); // Function to set file cursor to the beginning of the change file

    Change change_list[20]; // Array to store change list
    Change temp2;           // Temporary pointer for change
    Change chosen_change;   // Pointer for chosen change

    bool getChangeFlag = filterNextChange(&temp2, chosen_product.product_name);
    if (getChangeFlag == false)
    {
        cout << "No change found." << endl;
        return; // return to the main menu if the change file is empty
    }

    // Loop to display change list and select a change
    while (getChangeFlag)
    {
        change_list[0] = temp2;
        cout << "Select a change you want to update:" << endl;
        cout << left << setw(35) << "    Description"
             << setw(10) << "Change ID"
             << setw(11) << "State"
             << setw(9) << "Priority"
             << setw(9) << "Anticipated Release" 
             << endl
             << right
             << setw(4) << " 1) "  // first change
             << left
             << setw(31) << temp2.description 
             << setw(10) << temp2.change_ID 
             << setw(11) << temp2.status 
             << setw(9) << temp2.priority 
             << setw(9) << temp2.anticipated_release_ID
             << endl;

        int i;
        // Display change options
        for (i = 1; i < 20; i++)
        {
            if (filterNextChange(&temp2, chosen_product.product_name))
            {
                change_list[i] = temp2; // Store change in array
                cout << right << setw(4) << to_string(i + 1) + ") "
                     << left 
                     << setw(31) << temp2.description 
                     << setw(10) << temp2.change_ID 
                     << setw(11) << temp2.status 
                     << setw(9) << temp2.priority 
                     << setw(9) << temp2.anticipated_release_ID
                     << endl;  // Display change
            }
            else
                break; // Exit loop if no more changes
        }

        if (i == 20 && filterNextChange(&temp2, chosen_product.product_name))
            cout << i + 1 << ") More\n";
        cout << " 0) Exit\n";
        int userInput;

        cout << "Enter selection: ";
        cin >> userInput;

        if (userInput >= 1 && userInput < i + 1) // Check for valid selection
        {
            chosen_change = change_list[userInput - 1]; // Assign chosen change
            break;
        }
        else if (userInput == 0) // Exit
        {
            getChangeFlag = false;
            return;
        }
    }

    // Step 3: Update the chosen change
    // Update description
    cout << "Updating the change with the change ID '" << chosen_change.change_ID << "' in the product '"
         << chosen_product.product_name << "':" << endl;

    string userInput;
    while (true)
    {
        cout << "Do you want to replace the description (Y/N)? ";
        cin >> userInput;
        if (userInput == "Y" || userInput == "y")
        {
            string tempDescription;
            cout << "Old description is: "
                 << chosen_change.description
                 << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (true)
            {
                //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "New description is: ";
                getline(cin, tempDescription);
                if (tempDescription.length() > 30)
                {
                    cout << "The description exeeds 30 characters. Enter again." << endl;
                    continue;
                }
                break;
            }

            tempDescription.copy(chosen_change.description, tempDescription.length());
            chosen_change.description[tempDescription.length()] = '\0'; // Get new description
            break;
        }
        else if (userInput == "N" || userInput == "n")
        {
            break;
        }
    }

    // Update status
    cout << "The current 'status' is " << chosen_change.status << "." << endl
         << "Select a status that you want to update to:" << endl
         << "1) Reported" << endl
         << "2) Evaluated" << endl
         << "3) Cancelled" << endl
         << "4) In process" << endl
         << "5) Done" << endl
         << "0) Keep the current status" << endl
         << "Enter selection: ";

    int userInput2;
    cin >> userInput2; // User input for status selection

    switch (userInput2)
    {
    case 1:
        strcpy(chosen_change.status, "Reported");
        break;
    case 2:
        strcpy(chosen_change.status, "Evaluated");
        break;
    case 3:
        strcpy(chosen_change.status, "Cancelled");
        break;
    case 4:
        strcpy(chosen_change.status, "In process");
        break;
    case 5:
        strcpy(chosen_change.status, "Done");
        break;
    case 0:
        break; // Keep current status
    }

    cout << "The updated 'status' is: " << chosen_change.status << "." << endl;
    // Update priority
    cout << "The current priority is: " << chosen_change.priority << endl
         << "Enter a new priority, or 0 to keep the current priority: ";

    cin >> userInput2;
    if (userInput2 != 0)
        chosen_change.priority = userInput2; // Update priority

    // Update anticipated release ID
    cout << "The current 'anticipated release' is " << chosen_change.anticipated_release_ID << endl;

    // get release
    seekToBeginningOfReleaseFile(); // Function to set file cursor to the beginning of the release file

    Release release_list[20]; // Array to store release list
    Release temp3;            // Temporary pointer for release
    Release chosen_release;   // Pointer for chosen release

    // Loop until a valid release is chosen
    bool getReleaseFlag = filterNextRelease(&temp3, chosen_product.product_name);

    if (getReleaseFlag == false)
    {
        cout << "You have to create a release first!";
        return;
    }

    // Loop to display release list and select a release
    while (getReleaseFlag)
    {
        release_list[0] = temp3;
        cout << "Select an anticipated release that you want to update to:" << endl;

        cout << left << setw(14) << "    Release ID"
             << setw(13) << "Release date" 
             << endl
             << right
             << " 1) " 
             << left
             << setw(11) << temp3.release_ID
             << setw(13) << temp3.release_date 
             << endl;

        int i;
        // Display release options
        for (i = 1; i < 20; i++)
        {
            if (filterNextRelease(&temp3, temp1.product_name))
            {
                release_list[i] = temp3; // Store release in array
                cout << right << setw(4) << to_string(i + 1) + ")"
                     << left
                     << setw(11) << temp3.release_ID
                     << setw(13) << temp3.release_date
                     << endl;
            }
            else
            {
                getReleaseFlag = false;
                break; // Exit loop if no more releases
            }
        }

        if (i == 20 && filterNextRelease(&temp3, temp1.product_name))
            cout << i + 1 << ") More" << endl;

        cout << " 0) Keep the current release" << endl
             << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for release selection

        if (user_input >= 1 && user_input < i + 1) // Check for valid selection
        {
            chosen_release = release_list[user_input - 1]; // Assign chosen release
            // update the release id
            strcpy(chosen_change.anticipated_release_ID, chosen_release.release_ID); // Update anticipated release ID
            break;
        }
        else if (user_input == 0) // Keep current release
        {
            getReleaseFlag = false;
            break;
        }
    }

    // Function to update the change in the system
    if (updateChange(&chosen_change))
        cout << "The change has been updated successfully. \n";
    // else
    // return;

    // Display updated change info
    cout << "Change '" << chosen_change.change_ID << "' has been updated:\n"
         << left << setw(34) << "   Description"
         << setw(10) << "Change ID"
         << setw(11) << "State"
         << setw(9) << "Priority"
         << setw(9) << "Anticipated Release" 
         << endl
         << setw(3) << "1) "  // first change
         << setw(31) << chosen_change.description 
         << setw(10) << chosen_change.change_ID 
         << setw(11) << chosen_change.status 
         << setw(9) << chosen_change.priority 
         << setw(9) << chosen_change.anticipated_release_ID
         << endl;
}

// ---------------------------------------------------------------------------------------

// Reports Control
void allChangesReportControl()
{
    // Function to set file cursor to the beginning of the product file
    seekToBeginningOfProductFile();

    // Step 1: Get the product
    Product product_list[20]; // Array to store product list
    Product temp1;            // Temporary product object
    Product chosen_product;   // Chosen product object

    bool getProductFlag = getNextProduct(&temp1);
    if (!getProductFlag)
    {
        cout << "No product found. Returning to the main menu\n";
        return;
    }

    while (getProductFlag)
    {
        product_list[0] = temp1;
        cout << "Select a product:" << endl;
        cout << "1) " << temp1.product_name << endl;

        int i;
        for (i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp1))
            {
                product_list[i] = temp1; // Add product to the list
                cout << i + 1 << ") " << temp1.product_name << endl;
            }
            else
                break; // Exit loop if no more products
        }
        // Display options for more products or exit
        if (i == 20 && getNextProduct(&temp1))
            cout << i + 1 << ") More" << endl;
        cout << "0) Exit" << endl;

        int userInput;
        while (true)
        {
            cout << "Enter selection: ";
            cin >> userInput; // Get user input for selection

            if (userInput < 0 || userInput > i + 1)
            {
                cout << "Invalid input. Enter again." << endl;
                continue;
            }
            break;
        }

        // Do operations according to the user input
        if (userInput >= 1 && userInput < i + 1)
        {
            chosen_product = product_list[userInput - 1]; // Select the chosen product
            break;
        }
        else if (userInput == 0)
        {
            getProductFlag = false;
            return; // Return if user chooses to exit
        }
    }

    // Step 2: Get the changes
    Change change_list[20]; // Array to store change list
    Change temp2;           // Temporary change object

    // Function to set file cursor to the beginning of the change file
    seekToBeginningOfChangeFile();

    bool getChangeFlag = filterNextChange_DoneOrCancelled(&temp2, chosen_product.product_name);
    if (!getChangeFlag)
    {
        cout << "No changes found for the product '" << chosen_product.product_name << "'. Exiting...\n";
        return;
    }

    while (getChangeFlag)
    {
        change_list[0] = temp2;

        cout << "Change report for the product '" << chosen_product.product_name << "': \n";
        cout << left << setw(34) << "   Description"
             << setw(10) << "Change ID"
             << setw(11) << "State"
             << setw(9) << "Priority"
             << setw(9) << "Anticipated Release" << endl;

        cout << left << setw(3) << to_string(1) + ")"
             << setw(31) << temp2.description
             << setw(10) << temp2.change_ID
             << setw(11) << temp2.status
             << setw(9) << temp2.priority
             << setw(9) << temp2.anticipated_release_ID << endl;

        // int changeCount = 0;
        int i;
        for (i = 1; i < 20; i++)
        {
            if (filterNextChange_DoneOrCancelled(&temp2, chosen_product.product_name))
            {
                change_list[i] = temp2;
                cout << left << setw(3) << to_string(i + 1) + ")"
                     << setw(31) << temp2.description
                     << setw(10) << temp2.change_ID
                     << setw(11) << temp2.status
                     << setw(9) << temp2.priority
                     << setw(9) << temp2.anticipated_release_ID << endl;
                // changeCount++;
                getChangeFlag = filterNextChange_DoneOrCancelled(&temp2, chosen_product.product_name);
            }
            else
            {
                getChangeFlag = false;
                break;
            }
        }

        if (i == 20 && filterNextChange_DoneOrCancelled(&temp2, chosen_product.product_name))
        {
            cout << i + 1 << ") More\n";
        }

        cout << " 0) Exit\n";

        cout << "Enter selection: ";
        int userInput;
        cin >> userInput;

        if (userInput == 0) // Exit
            return;
        // else if (userInput == changeCount + 1 && changeCount == 20)
        // continue; // Display more changes if selected
    }
}

// ---------------------------------------------------------------------------------------

// Function to control the report generation for all requesters
void allRequestersReportControl()
{
    // Move the file pointer to the beginning of the product file
    seekToBeginningOfProductFile();

    // Array to store a list of products
    Product product_list[20];
    Product temp1;          // Temporary product pointer
    Product chosen_product; // Chosen product pointer

    // Loop to display product list and select a product
    bool getProductFlag = getNextProduct(&temp1);
    if (getProductFlag == false)
    {
        cout << "No product found. Returning to the main menu" << endl;
        return;
    }

    while (getProductFlag)
    {
        product_list[0] = temp1;
        cout << "Select a product:" << endl;
        cout << "    Product\n";
        cout << " 1) " << temp1.product_name << endl;

        int i;
        for (i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp1))
            {
                product_list[i] = temp1; // Add product to the list
                cout << right << setw(4) << to_string(i + 1) +  ") " << left << temp1.product_name << endl;
            }
            else
                break; // Exit loop if no more products
        }
        // Display options for more products or exit
        if (i == 20 && getNextProduct(&temp1))
            cout << i + 1 << ") More" << endl;
        cout << " 0) Exit" << endl;

        int userInput;
        while (true)
        {
            cout << "Enter selection: ";
            cin >> userInput; // Get user input for selection

            if (userInput < 0 || userInput > i + 1)
            {
                cout << "Invalid input. Enter again." << endl;
                continue;
            }
            break;
        }

        // Do operations according to the user input
        if (userInput >= 1 && userInput < i + 1)
        {
            chosen_product = product_list[userInput - 1]; // Select the chosen product
            break;
        }
        else if (userInput == 0)
        {
            getProductFlag = false;
            return; // Return if user chooses to exit
        }
    }

    // Step 2: Get the changes
    Change change_list[20]; // Array to store change list
    Change temp2;           // Temporary change object
    Change chosen_change;   // Chosen change object

    // Function to set file cursor to the beginning of the change file
    seekToBeginningOfChangeFile();

    bool getChangeFlag = filterNextChange(&temp2, chosen_product.product_name);
    if (getChangeFlag == false)
    {
        cout << "No change related to '" << chosen_product.product_name << "' found. Returning to the main menu" << endl;
        return;
    }

    while (getChangeFlag)
    {
        change_list[0] = temp2;
        cout << "Change report for the product '" << chosen_product.product_name << "': " << endl;
        cout << left << setw(35) << "    Description"
             << setw(10) << "Change ID"
             << setw(11) << "State"
             << setw(9) << "Priority"
             << setw(9) << "Anticipated Release"
             << endl;

        cout << left << " 1) "
                 << setw(31) << temp2.description
                 << setw(10) << temp2.change_ID
                 << setw(11) << temp2.status
                 << setw(9) << temp2.priority
                 << setw(9) << temp2.anticipated_release_ID
                 << endl; // Display change

        int i;
        for (i = 1; i < 20; i++)        
        {

            if (filterNextChange(&temp2, chosen_product.product_name))
            {
            change_list[i] = temp2;
            cout << left << setw(4) << to_string(i + 1) + ") "
                 << setw(31) << temp2.description
                 << setw(10) << temp2.change_ID
                 << setw(11) << temp2.status
                 << setw(9) << temp2.priority
                 << setw(9) << temp2.anticipated_release_ID
                 << endl; // Display change
            }
            else
            {
                getChangeFlag = false;
                break;
            }
        }

        if (i == 20 && filterNextChange(&temp2, chosen_product.product_name))
        {
            cout << i + 1 << ") More\n";
        }
        cout << " 0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for navigating changes

        if (user_input >= 1 && user_input <= i)
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
    Release temp3;            // Temporary release object
    Release chosen_release;   // Chosen release object

    // Function to set file cursor to the beginning of the release file
    seekToBeginningOfReleaseFile();

    bool getReleaseFlag = filterNextRelease(&temp3, chosen_product.product_name);

    if (getReleaseFlag == false)
    {
        cout << "No release found. The Release file is empty." << endl;
        return;
    }

    while (getReleaseFlag)
    {
        // int releaseCount = 0;

        release_list[0] = temp3;
        cout << "Select a reported release that corresponds to this change request:" << endl
             << left << setw(14) << "    Release ID"
             << setw(13) << " Release date" << endl;

        cout << " 1) "
             << setw(11) << temp3.release_ID
             << setw(13) << temp3.release_date
             << endl;

        int i;
        for (i = 1; i < 20; i++)
        {
            if (filterNextRelease(&temp3, chosen_product.product_name))
            {
                release_list[i] = temp3; // Add release to the list
                cout << right << setw(4) << to_string(i + 1) + ") "
                     << left
                     << setw(11) << temp3.release_ID
                     << setw(13) << temp3.release_date
                     << endl;
            }
            else
            {
                getReleaseFlag = false;
                break; // Exit loop if no more releases
            }
        }
        // Display options for more releases
        if (i == 20 && filterNextRelease(&temp3, chosen_product.product_name))
            cout << i + 1 << ") More" << endl;

        cout << " 0) Exit" << endl;

        cout << "Enter selection: ";
        int user_input;
        cin >> user_input; // Get user input for selection

        // Check if user input is within valid range
        if (user_input >= 1 && user_input < i + 1)
        {
            chosen_release = release_list[user_input - 1]; // Select the chosen release
            break;
        }
        else if (user_input == 0)
            return;
    }

    // Step 4: Get the requesters
    Requester requester_list[20]; // Array to store requester list
    Requester temp4;              // Temporary requester object

    // Get the change requests
    ChangeRequest changeRequest_list[20]; // Array to store change requests
    ChangeRequest temp5;                  // Temporary change request object

    // Function to set file cursor to the beginning of the requester file
    seekToBeginningOfRequesterFile();
    // Function to set file cursor to the beginning of the change request file
    seekToBeginningOfChangeRequestFile();

    // Print header info
    cout << "Here is the report: \n"
         << "Product: " << chosen_product.product_name << "\n"
         << "Change description: " << chosen_change.description << "\n"
         << "Change ID: " << chosen_change.change_ID << "\n"
         << "Release ID: " << chosen_release.release_ID << "\n"
         << "State: " << chosen_change.status << "\n";

    bool changeRequestFlag = filterNextChangeRequest(&temp5, chosen_change.change_ID);    

    while (changeRequestFlag)
    {
        int i;
        cout << "    Requester                      Email" << endl;

        filterNextRequester(&temp4, temp5.requester_name);
        requester_list[0] = temp4;
        cout << " 1) " << left << setw(31) <<  temp4.requester_name << setw(25) << temp4.email << endl;

        for (i = 1; i < 20; i++)
        {
            if (filterNextChangeRequest(&temp5, chosen_change.change_ID))
            {
                
                if (filterNextRequester(&temp4, temp5.requester_name)) // Get the requester by name
                {
                    requester_list[i] = temp4;
                    // Display each requester
                    cout << right << setw(4) << to_string(i + 1) + ") " << left << setw(31) << temp4.requester_name 
                         << setw(25) << temp4.email << endl;
                }
                else
                {
                    changeRequestFlag = false;
                    break; // Exit loop if no more change requests
                }
            }
            else
            {
                changeRequestFlag = false;
                break; // Exit loop if no more change requests
            }
        }

        if (filterNextChangeRequest(&temp5, chosen_change.change_ID) && filterNextRequester(&temp4, temp5.requester_name))
            cout << i + 1 << ") More\n";
        cout << " 0) Exit" << endl;

        cout << "Enter selection: ";
        int user_input;
        cin >> user_input;

        if (user_input == 0)
            return;
    }
}

// ---------------------------------------------------------------------------------------

// Function to control the shutdown process
void shutDownControl()
{
    bool allClosed = true;
    cout << endl;

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
        cout << "All modules closed successfully.\n"
             << endl;
        cout << "Thank you for using the Honey Walnut Issue Tracking System! \n";
    }
    else
    {
        cout << "One or more modules failed to close.\n";
    }
}

#endif
