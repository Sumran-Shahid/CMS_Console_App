#include <iostream>
#include <cstdlib>

#include "customFunctions.h"
#include "signIn.h"
#include "admin.h"
#include "student.h"
#include "teacher.h"

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

    cout << "Press Return to continue.\n";
    cin.get();


    if (sign_in.access_lvl == 1) {
        Admin admin;
        while (1) {
            clear_screen();
            admin.menu();
            cout << "Press Return to continue.\n";
            cin.clear();
            cin.ignore();
            cin.get();
        }
    }
    else if (sign_in.access_lvl == 2) {
        Teacher teacher;
        teacher.course = sign_in.teacher_course;
        while (1) {
            clear_screen();
            teacher.menu();
            cout << "Press Return to continue.\n";
            cin.clear();
            cin.ignore();
            cin.get();
        }
    }
    else if (sign_in.access_lvl == 3) {
        Student student;
        student.studentName = sign_in.student_name;
        student.cms_id = sign_in.student_id;
        while(1) {
            clear_screen();
            student.menu();
            cout << "Press Return to continue.\n";
            cin.clear();
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}  // main function ends here