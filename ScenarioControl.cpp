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

using std::cin;
using std::cout;
using std::endl;
using std::string;
//using namespace std;

bool isValidDateFormat(const char *date)
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
    char product_name[11];
    string tempProductName;

    while (true)
    {
        cout << "Enter product's name (max 10 chars): ";
        cin >> tempProductName;

        bool is10digits = tempProductName.length() > 10;
        bool isAlphabet = true;

        for (size_t i = 0; i < tempProductName.length(); i++)
        {
            if (!isalpha(tempProductName[i]))
            {
                isAlphabet = false;
                break;
            }
        }

        if (is10digits)
        {
            cout << "Product name exceeds the maximum length of 10 characters. Please enter a valid name.\n";
            continue;
        }

        if (!isAlphabet)
        {
            cout << "Product name should only contain alphabetic characters. Please enter a valid name.\n";
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
                cout << "The new product has been successfully added. \n";
            }
            break;
        }
        else if (userInput == "n" || userInput == "N")
        {
            cout << "Product addition cancelled. Returning to the main menu.\n";
            return; // Return to the main menu if user cancels
        }
        else
        {
            cout << "Invalid input. Please enter 'Y' for yes or 'N' for no.\n";
        }
    }
}

// Function to control the creation of a release done
void createReleaseControl()
{
    // Move the file pointer to the beginning of the product file
    seekToBeginningOfProductFile();
    Product product_list[20]; // Array to store a list of products
    Product temp;   // Temporary product object
    Product chosen; // Chosen product object
    bool getFlag = getNextProduct(&temp);
    if (!getFlag)
    {
        cout << "No products available. Exiting...\n";
        return;
    }

    int productCount = 0;
    while (getFlag && productCount < 20)
    {
        product_list[productCount] = temp;
        productCount++;
        getFlag = getNextProduct(&temp);
    }

    while (true)
    {
        cout << "For which product do you want to add a new release?\n";
        for (int i = 0; i < productCount; i++)
        {
            cout << i + 1 << ") " << product_list[i].product_name << "\n";
        }
        cout << productCount + 1 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int userInput;
        cin >> userInput;

        if (userInput >= 1 && userInput <= productCount)
        {
            chosen = product_list[userInput - 1];
            break;
        }
        else if (userInput == productCount + 1)
        {
            // If 'More' is selected, display the same list again
            continue;
        }
        else if (userInput == 0)
        {
            cout << "Release addition cancelled. Returning to the main menu.\n";
            return;
        }
        else
        {
            cout << "Invalid selection. Please try again.\n";
        }
    }

    char release_ID[9]; // Adjusted size to account for null-terminator
    string tempReleaseID;
    while (true)
    {
        cout << "Enter a release ID for the new release (max 8 chars): ";
        cin >> tempReleaseID;
        if (tempReleaseID.length() <= 8)
        {
            break;
        }
        else
        {
            cout << "Release ID exceeds the maximum length of 8 characters. Please enter again.\n";
        }
    }
    // Copy the string to the fixed-size character array
    tempReleaseID.copy(release_ID, tempReleaseID.length());
    release_ID[tempReleaseID.length()] = '\0';

    char release_date[11]; // Adjusted size to account for null-terminator
    string tempDate;
    while (true)
    {
        cout << "Enter a release date for the release (YYYY-MM-DD): ";
        cin >> tempDate;
        // Uncomment and implement the date validation function if needed
        // if (isValidDateFormat(tempDate) && tempDate.length() <= 10)
        // {
        //     break;
        // }
        // else
        // {
        //     cout << "Invalid release date format or exceeds the maximum length of 10 characters. Please enter again in YYYY-MM-DD format.\n";
        // }
        break;
    }
    // Copy the string to the fixed-size character array
    tempDate.copy(release_date, tempDate.length());
    release_date[tempDate.length()] = '\0';

    // Confirm adding the release
    string userConfirmation;
    while (true)
    {
        cout << "Are you sure you want to add the release " << release_ID << " (Y/N)? ";
        cin >> userConfirmation;
        if (userConfirmation == "y" || userConfirmation == "Y")
        {
            // Create new release and write to file
            Release new_release = Release(release_ID, chosen.product_name, release_date);
            if (addRelease(&new_release))
            {
                cout << "The new release has been successfully added.\n";
            }
            break;
        }
        else if (userConfirmation == "n" || userConfirmation == "N")
        {
            cout << "Release addition cancelled. Returning to the main menu.\n";
            return;
        }
        else
        {
            cout << "Invalid input. Please enter 'Y' for yes or 'N' for no.\n";
        }
    }
}


// Function to validate email format
bool isValidEmail(string email)
{
    // const regex emailPattern(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)");
    // return regex_match(email, emailPattern);
    return true;
}

// Function to validate phone number format
bool isValidPhoneNumber(const int *phone_number)
{
    if (phone_number[0] != 1)
    {
        return false;
    }
    for (size_t i = 1; i < 11; i++)
    {
        if (phone_number[i] < 0 || phone_number[i] > 9)
        {
            return false;
        }
    }
    return true;
}

// Function to validate requester name length
bool isValidRequesterNameLength(const string &name)
{
    return name.length() <= 30;
}

// Function to validate requester name format
bool isValidRequesterName(const string &name)
{
    // Split the name into last name and first name
    // size_t commaPos = name.find(',');
    // if (commaPos == string::npos)
    // {
    //     return false; // No comma found
    // }

    // string lastName = name.substr(0, commaPos);
    // string firstName = name.substr(commaPos + 2); // Skip ", "

    // // Check if both names contain only alphabetic characters
    // auto isAlphaOnly = [](const string &str) -> bool
    // {
    //     for (char c : str)
    //     {
    //         if (!isalpha(c))
    //         {
    //             return false;
    //         }
    //     }
    //     return true;
    // };

    // return isAlphaOnly(lastName) && isAlphaOnly(firstName);
    return true;
}

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

// create requester control
void createRequester(Requester chosen_requester)
{
    // Prompt user to create a new requester
    cout << "Creating a new requester:\n";
    string inputname;

    while (true)
    {
        cout << "Enter requester's name ('Last name, First name', max 30 chars): ";
        cin.ignore(); // Clear the input buffer // ??
        getline(cin, inputname);

        if (!isValidRequesterNameLength(inputname))
        {
            cout << "Requester name exceeds the maximum length of 30 characters. Please enter a valid name.\n";
            continue;
        }
        if (!isValidRequesterName(inputname))
        {
            cout << "Requester name must be in the format 'Last name, First name' with both names containing only alphabetic characters. Please enter a valid name.\n";
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
            cout << "Phone number must be exactly 11 digits. Please enter a valid number.\n";
            continue;
        }

        bool valid = true;
        for (size_t i = 0; i < 11; i++)
        {
            if (!isdigit(phone_number_input[i]))
            {
                valid = false;
                break;
            }
            //chosen_requester.phone_number[i] = phone_number_input[i] - '0';
        }

        if (!valid)
        {
            cout << "Phone number must contain only digits. Please enter a valid number.\n";
            continue;
        }

        // if (!isValidPhoneNumber(chosen_requester.phone_number))
        // {
        //     cout << "Invalid phone number. The first digit must be 1. Please enter a valid number.\n";
        //     continue;
        // }

        break;
    }

    while (true)
    {
        cout << "Enter the requester's email (max 24 chars): ";
        string email_input;
        cin >> email_input;

        if (!isValidEmail(email_input))
        {
            cout << "Invalid email format or exceeds the maximum length of 24 characters. Please enter a valid email.\n";
            continue;
        }

        strncpy(chosen_requester.email, email_input.c_str(), sizeof(chosen_requester.email) - 1);
        chosen_requester.email[sizeof(chosen_requester.email) - 1] = '\0';
        break;
    }

    cout << "Is the requester an employee (Y/N)? ";
    string user_input;
    cin >> user_input;
    if (user_input == "y" || user_input == "Y")
    {
        while (true)
        {
            cout << "Enter the requester's department (max 12 chars): ";
            string department_input;
            cin >> department_input;

            if (department_input.length() > 12)
            {
                cout << "Department name exceeds the maximum length of 12 characters. Please enter a valid department.\n";
                continue;
            }

            strncpy(chosen_requester.department, department_input.c_str(), sizeof(chosen_requester.department) - 1);
            chosen_requester.department[sizeof(chosen_requester.department) - 1] = '\0';
            break;
        }
    }

    if (addRequester(&chosen_requester))
    {
        cout << "The new requester has been successfully added.\n";
    }
}

// Create change function
void createChange(Product chosen_product, Change chosen_change)
{
    // Prompt user to create a new change
    cout << "Enter the description of the new change (max 30 chars): ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    string temp_description;
    getline(cin, temp_description);
    // description length check here
    // To do
    temp_description.copy(chosen_change.description, temp_description.length());
    chosen_change.description[temp_description.length()] = '\0';
    cout << "checking if the change description is correct" << chosen_change.description << endl; // delete
    // we set the priority here, so no need to
    chosen_change.priority = 0; // if 0 print out N/A
    string status_reported = "Reported";
    status_reported.copy(chosen_change.status, status_reported.length());
    chosen_change.status[status_reported.length()] = '\0';
    cout << "checking if the change status is correct" << chosen_change.status << endl; // delete

    // int id[7];
    // getNextCID(id); // problem here, ?? change id should be one int intead of an array of ints
    // for (int i = 0; i < sizeof(id) / 4; i++)
    // {
    //     chosen_change.change_ID[i] = id[i];
    //     cout << "checking if the change id is correct" << chosen_change.change_ID[i] << endl; // delete
    // }
    //chosen_change.change_ID = 100000;
    strcpy(chosen_change.product_name, chosen_product.product_name);
    string tempRelease_ID = "None";
    chosen_change.anticipated_release_ID[tempRelease_ID.length()] = '\0';

    tempRelease_ID.copy(chosen_change.anticipated_release_ID, tempRelease_ID.length());
    cout << "checking if the release id is correct" << tempRelease_ID << endl; // delete

    // Add to file
    if (addChange(&chosen_change))
        cout << "The new change has been successfully added. \n";
}

string createWhitespace(int length) {
    string spaces = "";
    for (int i = 0; i < length; i++) {
        spaces += " ";
    }
    return spaces;
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
        cout << "Select a requester that reports this change request: \n";
        cout << "   Requester name                " << "Phone       " << "Email                   " << "Department  \n";

        cout << "1) " << temp.requester_name << createWhitespace(30 - strlen(temp.requester_name));

        //for (int j = 0; j < 11; j++)
        cout << temp.phone_number;

        cout << " ";

        cout << temp.email << createWhitespace(24 - strlen(temp.email))
             << temp.department
             << "\n";

        for (i = 1; i < 20; i++)
        {
            if (getNextRequester(&temp) == true)
            {
                requester_list[i] = temp; // Add requester to the list
                cout << i + 1 << ") " << temp.requester_name;
                //for (int j = 0; j < 11; j++)
                cout << temp.phone_number;

                cout << temp.email
                     << temp.department
                     << "\n";
            }
            else
            {
                getRequesterFlag = false;
                break; // Exit loop if no more requesters
            }
        }

        // Display options for more requesters or to create a new one
        cout << i + 1 << ") Show more requesters\n";
        cout << "0) Create a new requester\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // Get user input for selection

        cout << user_input;
        // Check if user input is within valid range
        if (user_input >= 1 && user_input < i + 1)
        {
            chosen_requester = requester_list[user_input - 1]; // Select the chosen requester
            break;
        }
        else if (user_input == 0)
        {
            createRequester(chosen_requester);
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
        cout << "No additional records, this is the end of the file. \n";
        return;
    }

    while (getProductFlag)
    {
        product_list[0] = temp1;
        cout << "Select a product that corresponds to this change request: \n";
        cout << "   Product    \n";
        cout << "1) " << temp1.product_name << "\n";

        int i;
        for (i = 1; i < 20; i++)
        {
            if (getNextProduct(&temp1))
            {
                product_list[i] = temp1;                             // Add product to the list
                cout << i + 1 << ") " << temp1.product_name << "\n"; // Add product to the list
            }
            else
            {
                getProductFlag = false;
                break; // Exit loop if no more products
            }
        }

        // Display options for more products or exit
        cout << i + 1 << ") More\n";
        cout << "0)  Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // Get user input for selection
        // Check if user input is within valid range
        if (user_input >= 1 && user_input < i + 1)
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

    bool getChangeFlag = filterNextChange(&temp2, chosen_product.product_name);
    if (getChangeFlag == false)
    {
        createChange(chosen_product, chosen_change);
    }

    // Loop to display change list and select a change
    while (getChangeFlag)
    {
        change_list[0] = temp2;
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

        int i;
        for (i = 1; i < 20; i++)
        {
            if (filterNextChange(&temp2, chosen_product.product_name))
            {
                change_list[i] = temp2; // Add change to the list
                cout << i + 1 << ") " << temp2.description
                     << temp2.change_ID
                     << temp2.status
                     << temp2.priority
                     << temp2.anticipated_release_ID << "\n";
            }
            else
            {
                getChangeFlag = false;
                break; // Exit loop if no more changes
            }
        }
        // Display options for more changes or to create a new one
        cout << i + 1 << ") More\n";
        cout << "0) New Change\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // Get user input for selection

        if (user_input >= 1 && user_input < i + 1)
        {
            cout << "The user selects: " << i << endl;
            chosen_change = change_list[user_input - 1]; // Select the chosen change
            break;
        }
        else if (user_input == 0)
        {
            createChange(chosen_product, chosen_change);
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
        cout << "You have to create a release first!";
        return;
    }

    // Loop to display release list and select a release
    while (getReleaseFlag)
    {
        release_list[0] = temp3;
        cout << "Select a reported release that corresponds to this change request: \n";

        cout << "Release ID  "
             << "Release date\n";

        cout << "1) " << temp3.release_ID
             << temp3.release_date << "\n";

        int i;
        for (i = 1; i < 20; i++)
        {
            if (filterNextRelease(&temp3, chosen_product.product_name))
            {
                release_list[i] = temp3; // Add release to the list
                cout << i + 1 << ") " << temp3.release_ID
                     << temp3.release_date << "\n";
            }
            else
            {
                getReleaseFlag = false;
                break; // Exit loop if no more releases
            }
        }
        // Display options for more releases
        cout << i + 1 << ") More\n";
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
    cout << "Enter the request date of the change request (YYYY-MM-DD): ";
    ChangeRequest new_changeRequest;
    string temp_date;
    cin >> temp_date;
    temp_date.copy(new_changeRequest.request_date, temp_date.length());
    new_changeRequest.request_date[temp_date.length()] = '\0';

    strcpy(new_changeRequest.requester_name, chosen_requester.requester_name);
    new_changeRequest.change_ID = chosen_change.change_ID;  // problem 
    strcpy(new_changeRequest.reported_release_ID, chosen_release.release_ID);

    // Create the new change request (Write the record to the file) and confirm success
    if (addChangeRequest(&new_changeRequest))
        cout << "The new change request has been successfully created. \n";
}

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
        cout << "No additional records, this is the end of the file. \n";
        return;
    }

    while (getProductFlag == true)
    {
        product_list[0] = temp1;
        cout << "Select a product:\n";
        cout << "1) " << temp1.product_name << "\n";

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
        cout << i + 1 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // Get user input for selection

        // Check if user input is within valid range
        if (user_input >= 1 && user_input < i + 1)
        {
            chosen_product = product_list[user_input - 1]; // Select the chosen product
            break;
        }
        else if (user_input == 0)
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
        cout << "No additional records, this is the end of the file. \n";
    }

    // Loop to display change list and select a change
    while (getChangeFlag)
    {
        change_list[0] = temp2;
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
        cout << i + 1 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // Get user input for selection

        // Check if user input is within valid range
        if (user_input >= 1 && user_input < i + 1)
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
         << chosen_change.anticipated_release_ID
         << endl;
}

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
        cout << "No additional records, this is the end of the file. \n";
        return;
    }

    while (getProductFlag == true)
    {
        product_list[0] = temp1;
        cout << "Select a product that corresponds to the change you want to update: \n";
        cout << "Product    \n";
        cout << "1) " << temp1.product_name << "\n";

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
            {
                getProductFlag = false;
                break; // Exit loop if no more products
            }
        }

        cout << i + 1 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for product selection

        if (user_input >= 1 && user_input < i + 1) // Check for valid selection
        {
            chosen_product = product_list[user_input - 1]; // Assign chosen product
            break;
        }
        else if (user_input == 0)
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
        cout << "No additional records, this is the end of the file. \n";
        return; // return to the main menu if the change file is empty
    }

    // Loop to display change list and select a change
    while (getChangeFlag)
    {
        change_list[0] = temp2;
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

        cout << i + 1 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for change selection

        if (user_input >= 1 && user_input < i + 1) // Check for valid selection
        {
            chosen_change = change_list[user_input - 1]; // Assign chosen change
            break;
        }
        else if (user_input == 0) // Exit
        {
            getChangeFlag = false;
            return;
        }
    }

    // Step 3: Update the chosen change
    // Update description
    cout << "Updating the change with the change ID '" << chosen_change.change_ID << "' in the product '"
         << chosen_product.product_name << "':\n"
         << "Do you want to replace the description (Y/N)? ";
    string user_input1;
    cin >> user_input1;
    if (user_input1 == "Y" || user_input1 == "y")
    {
        cout << "Old description is: "
             << chosen_change.description
             << "\n"
             << "New description is: ";

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        string temp_description;
        getline(cin, temp_description);
        // description length check here
        // To do
        temp_description.copy(chosen_change.description, temp_description.length());
        chosen_change.description[temp_description.length()] = '\0';                      // Get new description
    }

    // Update status
    cout << "The current 'status' is " << chosen_change.status << ".\n"
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

    cout << "The updated 'status' is: " << chosen_change.status << ".\n";
    // Update priority
    cout << "The current priority is: " << chosen_change.priority << "\n"
         << "Enter a new priority, or 0 to keep the current priority: ";

    cin >> user_input2;
    if (user_input2 != 0)
        chosen_change.priority = user_input2; // Update priority

    // Update anticipated release ID
    cout << "The current 'anticipated release' is " << chosen_change.anticipated_release_ID << "\n";

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
        cout << "Select an anticipated release that you want to update to: \n";

        cout << "Release ID  "
             << "  Release date\n";

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
            {
                getReleaseFlag = false;
                break; // Exit loop if no more releases
            }
        }

        cout << i + 1 << ") More\n";
        cout << "0) Keep the current release\n"
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
         << "Description                     "
         << "change ID   "
         << "State      "
         << "Priority     "
         << "Anticipated Release\n";

    cout << chosen_change.description
         << chosen_change.change_ID
         << chosen_change.status
         << chosen_change.priority
         << chosen_change.anticipated_release_ID
         << endl;
}

// Reports control
void allChangesReportControl()
{
    // Step 1: Get the product
    Product product_list[20]; // Array to store product list
    Product temp1;            // Temporary pointer for product
    Product chosen_product;   // Pointer for chosen product

    while (true)
    {
        // Function to set file cursor to the beginning of the product file
        seekToBeginningOfProductFile();

        bool getProductFlag = getNextProduct(&temp1);
        if (getProductFlag == false)
        {
            cout << "No products available. Exiting...\n";
            return;
        }

        int productCount = 0;
        while (getProductFlag)
        {
            product_list[productCount] = temp1;
            cout << productCount + 1 << ") " << temp1.product_name << "\n"; // Display product
            productCount++;

            if (productCount >= 20 || !getNextProduct(&temp1))
            {
                getProductFlag = false;
            }
        }

        cout << productCount + 1 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for product selection

        if (user_input >= 1 && user_input <= productCount)
        {
            chosen_product = product_list[user_input - 1]; // Assign chosen product
            break;
        }
        else if (user_input == productCount + 1)
        {
            continue; // Display the list again if "More" is selected and there are no more products
        }
        else if (user_input == 0) // Exit
        {
            return;
        }
        else
        {
            cout << "Invalid selection. Please try again.\n";
        }
    }

    // Step 2: Get the changes
    Change change_list[20]; // Array to store change list
    Change temp2;           // Temporary pointer for change

    // Function to set file cursor to the beginning of the change file
    seekToBeginningOfChangeFile();

    bool getChangeFlag = filterNextChange_DoneOrCancelled(&temp2, chosen_product.product_name);
    if (getChangeFlag == false)
    {
        cout << "No changes found for the product '" << chosen_product.product_name << "'. Exiting...\n";
        return;
    }

    while (getChangeFlag)
    {
        change_list[0] = temp2;
        cout << "Change report for the product '" << chosen_product.product_name << "': \n";
        cout << "Description                     "
             << "Change ID   "
             << "State      "
             << "Priority     "
             << "Anticipated Release\n";

        cout << "1) " << temp2.description
             << temp2.change_ID
             << temp2.status
             << temp2.priority
             << temp2.anticipated_release_ID << "\n";
        int changeCount = 1;
        for (int i = 1; i < 20; i++)
        {
            if (filterNextChange_DoneOrCancelled(&temp2, chosen_product.product_name))
            {
                change_list[i] = temp2;
                cout << i + 1 << ") " << temp2.description
                     << temp2.change_ID
                     << temp2.status
                     << temp2.priority
                     << temp2.anticipated_release_ID << "\n";
                changeCount++;
            }
            else
            {
                getChangeFlag = false;
                break; // Exit loop if no more changes
            }
        }

        cout << changeCount + 1 << ") More\n";
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for navigating changes

        if (user_input == 0) // Exit
            return;
        else if (user_input == changeCount + 1)
            continue; // Display more changes if selected
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

    bool productChosen = false; // Flag to indicate if a product has been chosen
    while (!productChosen)
    {
        int productCount = 0;

        cout << "Select a product to print its report: \n";
        while (getNextProduct(&temp1))
        {
            if (productCount < 20)
            {
                product_list[productCount] = temp1;                // Store product in array
                cout << productCount + 1 << ") " << temp1.product_name << "\n"; // Display product
                productCount++;
            }
            else
            {
                break; // Exit if the product list is full
            }
        }

        if (productCount < 20) // Add a "More" option only if there might be more products
        {
            cout << productCount + 1 << ") More\n";
        }
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for product selection

        if (user_input >= 1 && user_input <= productCount)
        {
            chosen_product = product_list[user_input - 1]; // Assign chosen product
            productChosen = true;
        }
        else if (user_input == productCount + 1 && productCount == 20)
        {
            continue; // Refill the product list and display more products
        }
        else if (user_input == 0) // Exit
        {
            return;
        }
        else
        {
            cout << "Invalid selection. Please try again.\n";
        }
    }

    // Step 2: Get the changes
    Change change_list[20]; // Array to store change list
    Change temp2;           // Temporary pointer for change
    Change chosen_change;   // Pointer for chosen change

    // Function to set file cursor to the beginning of the change file
    seekToBeginningOfChangeFile();

    bool changeChosen = false; // Flag to indicate if a change has been chosen
    while (!changeChosen)
    {
        int changeCount = 0;

        cout << "Change report for the product '" << chosen_product.product_name << "': \n";
        cout << "Description                     "
             << "Change ID   "
             << "State      "
             << "Priority     "
             << "Anticipated Release\n";

        while (filterNextChange(&temp2, chosen_product.product_name))
        {
            if (changeCount < 20)
            {
                change_list[changeCount] = temp2;
                cout << changeCount + 1 << ") " << temp2.description
                     << temp2.change_ID
                     << temp2.status
                     << temp2.priority
                     << temp2.anticipated_release_ID << "\n";
                changeCount++;
            }
            else
            {
                break; // Exit if the change list is full
            }
        }

        if (changeCount < 20) // Add a "More" option only if there might be more changes
        {
            cout << changeCount + 1 << ") More\n";
        }
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for navigating changes

        if (user_input >= 1 && user_input <= changeCount)
        {
            chosen_change = change_list[user_input - 1]; // Assign chosen change
            changeChosen = true;
        }
        else if (user_input == changeCount + 1 && changeCount == 20)
        {
            continue; // Refill the change list and display more changes
        }
        else if (user_input == 0) // Exit
        {
            return;
        }
        else
        {
            cout << "Invalid selection. Please try again.\n";
        }
    }

    // Step 3: Get the releases
    Release release_list[20]; // Array to store release list
    Release temp3;            // Temporary pointer for release
    Release chosen_release;   // Pointer for chosen release

    // Function to set file cursor to the beginning of the release file
    seekToBeginningOfReleaseFile();

    bool releaseChosen = false; // Flag to indicate if a release has been chosen
    while (!releaseChosen)
    {
        int releaseCount = 0;

        cout << "Select an anticipated release that you want to update to: \n";
        cout << "Release ID"
             << "Release date\n";

        while (filterNextRelease(&temp3, chosen_product.product_name))
        {
            if (releaseCount < 20)
            {
                release_list[releaseCount] = temp3;
                cout << releaseCount + 1 << ") " << temp3.release_ID
                     << temp3.release_date << "\n";
                releaseCount++;
            }
            else
            {
                break; // Exit if the release list is full
            }
        }

        if (releaseCount < 20) // Add a "More" option only if there might be more releases
        {
            cout << releaseCount + 1 << ") More\n";
        }
        cout << "0) Exit\n";
        cout << "Enter selection: ";

        int user_input;
        cin >> user_input; // User input for release selection

        if (user_input >= 1 && user_input <= releaseCount)
        {
            chosen_release = release_list[user_input - 1]; // Assign chosen release
            releaseChosen = true;
        }
        else if (user_input == releaseCount + 1 && releaseCount == 20)
        {
            continue; // Refill the release list and display more releases
        }
        else if (user_input == 0)
        {
            return;
        }
        else
        {
            cout << "Invalid selection. Please try again.\n";
        }
    }

    // Step 4: Get the requesters
    Requester requester_list[20]; // Array to store requester list
    Requester temp4;              // Temporary pointer for requester

    // Get the change requests
    ChangeRequest changeRequest_list[20]; // Array to store change requests
    ChangeRequest temp5;                  // Temporary pointer for change request

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
         << "State: " << chosen_change.status << "\n";

    int requestCount = 0;

    while (filterNextChangeRequest(&temp5, chosen_change.change_ID))
    {
        if (requestCount < 20)
        {
            filterNextRequester(&temp4, temp5.requester_name); // Get the requester by name
            requester_list[requestCount] = temp4;
            cout << "Requester: " << temp4.requester_name
                 << " Email: " << temp4.email << "\n";
            requestCount++;
        }
        else
        {
            break; // Exit if the requester list is full
        }
    }

    if (requestCount < 20) // Add a "More" option only if there might be more requesters
    {
        cout << requestCount + 1 << ") More\n";
    }
    cout << "0) Exit\n";
    cout << "Enter selection: ";

    int user_input;
    cin >> user_input;

    if (user_input >= 1 && user_input <= requestCount)
    {
        // Process the selected requester if necessary
    }
    else if (user_input == requestCount + 1 && requestCount == 20)
    {
        // Refill the requester list and display more requesters
    }
    else if (user_input == 0)
    {
        return;
    }
    else
    {
        cout << "Invalid selection. Please try again.\n";
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
        cout << "All modules closed successfully.\n" << "\n";
        cout << "Thank you for using the Honey Walnut Issue Tracking System! \n";
    }
    else
    {
        cout << "One or more modules failed to close.\n";
    }
}

#endif
