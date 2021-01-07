#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "signIn.h"

using namespace std;



// accessLevel function starts here ---------------------------------------------------------------------------------------------------
void SignIn::accessLevel(void) {
    /*
     * THIS FUNCTION TAKES INPUT FROM TO SELECT THE ACCESS LEVEL HE WANTS TO
     * LOG IN TO AND THEN CALLS THE RELEVENT FUNCTION.
     * ALSO IT LIMITS THE USER TO SELECT THE INPUT FROM THE GIVE
     * CHOICES TO IT USING RECURSION.
     */

    cout << "Which access level do you want to sign in to?\n";
    cout << "[1] - Administrator Level\n";
    cout << "[2] - Teacher Level\n";
    cout << "[3] - Student Level\n";
    cout << "[4] - Exit The Program\n";
    cout << "--> ";

    // The input given by the user depending on the above statements is catched in this variable
    cin >> access_lvl;

    switch (access_lvl) {
    case 1:
        adminAccess();
        break;
    case 2:
        teacherAccess();
        break;
    case 3:
        studentAccess();
        break;
    case 4:
        cout << "Exiting program..." << endl;
        exit(1);    
    default:
        cout << "Please enter a value from the given choices.\n\n";
        accessLevel();
        break;
    }
    // int new_entry;
    // cout << "\nDo you want to make a new account or sign in an existing account?\n";
    // cout << "[1] - Make a new account.\n"
}


// adminAccess function starts here ---------------------------------------------------------------------------------------------------
void SignIn::adminAccess(void) {
    /*
     * THIS FUNCTION IS THE CHECK FOR SIGNING IN TO ADMIN ACCESS LEVEL.
     * IT PROMPTS THE USER TO ENTER THEIR CMS ID WHICH IS THEN MATCHED
     * WITH A PRESTORED CSV FILE AND THE THE USER IS SIGNED IN
     */

    int cms_id;
    cout << "\nEnter your CMS ID:";
    cin >> cms_id;
    cout << endl;

    ifstream list;
    list.open("CSvs/admins.csv");

    if (list.fail()) {
        cout << "File could not be opened" << endl;
    }

    string name, email;
    string cmsID;

    while (list.peek() != EOF) {  // this while loop runs through all the lines of the csv file
        bool id_found = false;  // this variable is used to check if the ID is found in the CSV or not
        while (getline(list, cmsID, ',') && getline(list, name, ',') && getline(list, email, '\n')) {  // this while loop gets the values in each like
            int x(0);
            stringstream num(cmsID);
            num >> x;  // this part is to actually convert the cmsID into an int variable because the values stored in a csv are always in string data type

            if (x == cms_id) { // this conditional checks each item / line in the csv file to find the required item with the cms_id entered above
                id_found = true; // variable set to true as the ID has been found
                cout << "You have signed in as an Admin.\n";
            }

        } // inner while ends here
        if (!id_found) {  // if the ID is not found, i.e., this variable is still false
            //system("CLS");//clears screen
            cout << "ID not found! Please enter ID again.\n";//error message 
            cin.clear();//clears error on cin
            cin.ignore(123, '\n');//ignores non numeric input and goes to next line 
            adminAccess();  //goes to recurssiion of this same function
        }
    } // first while ends here

    list.close();//closes csv file
}


// teacherAccess function starts here ---------------------------------------------------------------------------------------------------
void SignIn::teacherAccess(void) {
    /*
     * THIS FUNCTION IS THE CHECK FOR SIGNING IN TO TEACHER ACCESS LEVEL.
     * IT PROMPTS THE USER TO ENTER THEIR CMS ID WHICH IS THEN MATCHED
     * WITH A PRESTORED CSV FILE AND THE THE USER IS SIGNED IN
     */

    int cms_id;
    cout << "\nEnter your CMS ID:";
    cin >> cms_id;
    cout << endl;

    ifstream list;
    list.open("CSVs/teachers.csv");

    if (list.fail()) {
        cout << "File could not be opened" << endl;
    }

    string name, email;
    string cmsID;

    while (list.peek() != EOF) {  // this while loop runs through all the lines of the csv file
        bool id_found = false;  // this variable is used to check if the ID is found in the CSV or not
        while (getline(list, cmsID, ',') && getline(list, name, ',') && getline(list, email, '\n')) {  // this while loop gets the values in each like
            int x(0);
            stringstream num(cmsID);
            num >> x;  // this part is to actually convert the cmsID into an int variable because the values stored in a csv are always in string data type

            if (x == cms_id) { // this conditional checks each item / line in the csv file to find the required item with the cms_id entered above
                id_found = true;  // variable set to true as the ID has been found
                cout << "You have signed in as a Teacher.\n";
            }

        } // inner while ends here
        if (!id_found) {  // if the ID is not found, i.e., this variable is still false
            cout << "ID not found! Please Enter it again.\n";
            cin.clear();
            cin.ignore(123, '\n');
            teacherAccess();
        }
    } // first while ends here

    list.close();
}


// studentAccess function starts here ---------------------------------------------------------------------------------------------------
void SignIn::studentAccess(void) {
    /*
     * THIS FUNCTION IS THE CHECK FOR SIGNING IN TO STUDENT ACCESS LEVEL.
     * IT PROMPTS THE USER TO ENTER THEIR CMS ID WHICH IS THEN MATCHED
     * WITH A PRESTORED CSV FILE AND THE THE USER IS SIGNED IN
     */

    int cms_id;
    cout << "\nEnter your CMS ID:";
    cin >> cms_id;
    cout << endl;

    ifstream list;
    list.open("CSVs/SecCList.csv");

    if (list.fail()) {
        cout << "File could not be opened" << endl;
    }

    string name, section;
    string cmsID;

    while (list.peek() != EOF) {  // this while loop runs through all the lines of the csv file
        bool id_found = false;  // this variable is used to check if the ID is found in the CSV or not

        while (getline(list, section, ',') && getline(list, name, ',') && getline(list, cmsID, '\n')) {  // this while loop gets the values in each like
            int x(0);
            stringstream num(cmsID);
            num >> x;  // this part is to actually convert the cmsID into an int variable because the values stored in a csv are always in string data type

            if (x == cms_id) { // this conditional checks each item line in the csv file to find the required item with the cms_id entered above
                id_found = true;  // variable set to true as the ID has been found
                cout << "You have signed in as a Student.\n";
            }


        } // inner while ends here

        if (!id_found) {  // if the ID is not found, i.e., this variable is still false
            cout << "ID not found! Please enter ID again.\n";
            cin.clear();
            cin.ignore(123, '\n');
            studentAccess();
        }
    } // first while ends here

    list.close();
}