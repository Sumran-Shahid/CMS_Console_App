#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;


// All the functions are prototyped here
int accessLevel(void);
void adminAccess(void);
void teacherAccess(void);
void studentAccess(void);


// main function starts here
int main(void) {

    /*
     *THE PROGRAM EXECUTION STARTS HERE WHEN THE EXE FILE IS OPENED.
     *THE FOLLOWING TEXT INTRODUCES THE USER TO THE PROGRAM AND ASKS
     *FOR THEIR SELECTION OF WHICH ACCESS LEVEL THEY WANT TO ENTER.
     *
     */
    cout << "\n\t\tCMS Console App\n\n";
    cout << "Login Page" << endl;
    
    /* 
     * ASKING THE USER TO SELECT WHICH ACCESS LEVEL THEY WANT TO LOG 
     * IN TO AND ALSO THE access_lvl VARIABLE IS RETURNED BY THE 
     * FUNCTION SO THAT THIS VARIABLE CAN BE USED LATER IN THE PROGRAM
     * TO CHECK WHICH ACCESS LEVEL IS USER LOGGED INTO.
     * 
     */
    int access_lvl = accessLevel();

    system("clear"); // Clears the console screen

    cout << "\n\t\tCMS Console App\n\n";

    switch (access_lvl) {
        case 1:
            cout << "You have signed in as an Administrator.\n";
            break;
        case 2:
            cout << "You have signed in as a Teacher.\n";
            break;
        case 3:
            cout << "You have signed in as a Student.\n";
    }

    return 0;
}  // main function ends here


// Access Level function starts here
int accessLevel(void) {
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
    int access_lvl;
    cin >> access_lvl;

    // Now depending upon the user's input of the access level, program is diverted into the respected functions using a switch
    switch (access_lvl) {
        case (1):
            adminAccess();
            break;
        case (2):
            teacherAccess();
            break;
        case (3):
            studentAccess();
            break;
        case (4):
            exit(1);
            break;
        default:
            cout << "Please enter a number from the given choices." << endl;
            accessLevel();
            break;
    }

    return access_lvl;
}

// Administrator Access Level function starts here
void adminAccess(void) {
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
    list.open("CSVs/admins.csv");
    
    if(list.fail()) {
        cout << "File could not be opened" << endl;
    }
    
    string name,email;
    string cmsID;
    
    while(list.peek()!=EOF){  // this while loop runs through all the lines of the csv file
            bool id_found = false;  // this variable is used to check if the ID is found in the CSV or not
        while(getline(list,cmsID,',') && getline(list,name,',') && getline(list,email,'\n')) {  // this while loop gets the values in each like
            int x(0);
            stringstream num(cmsID);
            num >> x;  // this part is to actually convert the cmsID into an int variable because the values stored in a csv are always in string data type

            if (x == cms_id) { // this conditional checks each item / line in the csv file to find the required item with the cms_id entered above
                id_found = true;  // variable set to true as the ID has been found
            }
            
        } // inner while ends here
        if (!id_found) {  // if the ID is not found, i.e., this variable is still false
            cout << "ID not found! Please Enter it again.\n";
            adminAccess();
        }
    } // first while ends here

    list.close();
}

// Teacher Access Level function starts here
void teacherAccess(void) {
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
    
    if(list.fail()) {
        cout << "File could not be opened" << endl;
    }
    
    string name,email;
    string cmsID;
    
    while(list.peek()!=EOF){  // this while loop runs through all the lines of the csv file
            bool id_found = false;  // this variable is used to check if the ID is found in the CSV or not
        while(getline(list,cmsID,',') && getline(list,name,',') && getline(list,email,'\n')) {  // this while loop gets the values in each like
            int x(0);
            stringstream num(cmsID);
            num >> x;  // this part is to actually convert the cmsID into an int variable because the values stored in a csv are always in string data type

            if (x == cms_id) { // this conditional checks each item / line in the csv file to find the required item with the cms_id entered above
                id_found = true;  // variable set to true as the ID has been found
            }
            
        } // inner while ends here
        if (!id_found) {  // if the ID is not found, i.e., this variable is still false
            cout << "ID not found! Please Enter it again.\n";
            teacherAccess();
        }
    } // first while ends here

    list.close();
}

// Student Access Level function starts here
void studentAccess(void) {
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
    
    if(list.fail()) {
        cout << "File could not be opened" << endl;
    }
    
    string name,section;
    string cmsID;
    
    while(list.peek()!=EOF){  // this while loop runs through all the lines of the csv file
        bool id_found = false;  // this variable is used to check if the ID is found in the CSV or not

        while(getline(list,section,',') &&getline(list,name,',') &&getline(list,cmsID,'\n')) {  // this while loop gets the values in each like
            int x(0);
            stringstream num(cmsID);
            num >> x;  // this part is to actually convert the cmsID into an int variable because the values stored in a csv are always in string data type

            if(x==cms_id) { // this conditional checks each item / line in the csv file to find the required item with the cms_id entered above
                id_found = true;  // variable set to true as the ID has been found
            }

            
        } // inner while ends here

        if (!id_found) {  // if the ID is not found, i.e., this variable is still false
            cout << "ID not found! Please enter ID again.\n";
            studentAccess();
        }
    } // first while ends here

    list.close();
}

