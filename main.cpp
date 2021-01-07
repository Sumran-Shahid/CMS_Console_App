#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

#include "signIn.h"

using namespace std;


// main function starts here
int main(void) {
    /*
     * 
     *THE PROGRAM EXECUTION STARTS HERE WHEN THE EXE FILE IS OPENED.
     *THE FOLLOWING TEXT INTRODUCES THE USER TO THE PROGRAM AND ASKS
     *FOR THEIR SELECTION OF WHICH ACCESS LEVEL THEY WANT TO ENTER.
     *
     */
    cout << "\n\t\tCMS Console App\n\n";
    cout << "Login Page" << endl;

    SignIn sign_in;
    sign_in.accessLevel();

    return 0;
}  // main function ends here