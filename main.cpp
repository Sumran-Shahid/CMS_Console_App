#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <cctype>

#include "signIn.h"

using namespace std;


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

    SignIn sign_in;
    sign_in.accessLevel();

    //system("cls"); // Clears the console screen

    //cout << "\n\t\tCMS Console App\n\n";

    switch (sign_in.access_lvl) {
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

