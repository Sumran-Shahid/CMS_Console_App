#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "signIn.h"
#include "customFunctions.h"

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
    

    // The input given by the user depending on the above statements is catched in this variable
    access_lvl = get_int(1, "-->");


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
            exit(1);
            break;
        default:
            cout << "Please enter a value from the given choices.\n";
            accessLevel();
            break;
    }


} // accessLevel function ends here


// adminAccess function starts here ---------------------------------------------------------------------------------------------------
void SignIn::adminAccess(void) {
    /*
     * THIS FUNCTION IS THE CHECK FOR SIGNING IN TO ADMIN ACCESS LEVEL.
     * IT PROMPTS THE USER TO ENTER THEIR CMS ID WHICH IS THEN MATCHED
     * WITH A PRESTORED CSV FILE AND THE THE USER IS SIGNED IN
     */

    string cms_id;
    cout << "\nEnter your CMS ID:";
    getline(cin, cms_id);
    cout << endl;

    ifstream list;
    list.open("./data/admins.dat");

    if (list.fail()) {
        cout << "admin.dat file not found" << endl;
    }

    string name, email;
    string cmsID;

    while (list.peek() != EOF) {  // this while loop runs through all the lines of the csv file
        bool id_found = false;  // this variable is used to check if the ID is found in the CSV or not
        while (getline(list, cmsID, ',') && getline(list, name, ',') && getline(list, email, '\n')) {  // this while loop gets the values in each like
            
            if (cmsID == cms_id) { // this conditional checks each item / line in the csv file to find the required item with the cms_id entered above
                id_found = true; // variable set to true as the ID has been found
                cout << "You have signed in as an Admin.\n";
            }

        } // inner while ends here
        if (!id_found) {  // if the ID is not found, i.e., this variable is still false
            //system("CLS");//clears screen
            cout << "ID not found! Please enter ID again.\n";//error message 
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

    string cms_id;
    cout << "\nEnter your CMS ID:";
    getline(cin, cms_id);
    cout << endl;

    ifstream        list;
    list.open("./data/Teachers.dat");

    if (list.fail()) {
        cout << "ERROR! File not found" << endl;
    }

    string          name;
    string          course;
    string          cmsID;

    while (list.peek() != EOF) {  // this while loop runs through all the lines of the csv file
        bool id_found = false;  // this variable is used to check if the ID is found in the CSV or not
        while (getline(list, cmsID, ',') && getline(list, name, ',') && getline(list, course, '\n')) {  // this while loop gets the values in each like
           
            if (cmsID == cms_id) { // this conditional checks each item / line in the csv file to find the required item with the cms_id entered above
                id_found = true;  // variable set to true as the ID has been found
                cout << "You have signed in as a Teacher.\n";
                teacher_course = course;
            }

        } // inner while ends here
        if (!id_found) {  // if the ID is not found, i.e., this variable is still false
            cout << "ID not found! Please Enter it again.\n";
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

    string cms_id;
    cout << "\nEnter your CMS ID:";
    getline(cin, cms_id);
    cout << endl;

    ifstream list;
    list.open("./data/Students.dat");

    if (list.fail()) {
        cout << "ERROR! File not found" << endl;
    }

    string          name;
    string          section;
    string          course;
    string          cmsID;

    while (list.peek() != EOF) {  // this while loop runs through all the lines of the csv file
        bool id_found = false;  // this variable is used to check if the ID is found in the CSV or not

        while (getline(list, cmsID, ',') && getline(list, name, ',') && getline(list, course, ',') && getline(list, section, '\n')) {  // this while loop gets the values in each like
            
            if (cmsID == cms_id) { // this conditional checks each item line in the csv file to find the required item with the cms_id entered above
                id_found = true;  // variable set to true as the ID has been found
                cout << "You have signed in as a Student.\n";
                student_name = name;
                student_id = cmsID;
            }


        } // inner while ends here

        if (!id_found) {  // if the ID is not found, i.e., this variable is still false
            cout << "ID not found! Please enter ID again.\n";
            studentAccess();
        }
    } // first while ends here

    list.close();
}