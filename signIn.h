#ifndef SIGNIN
#define SIGNIN
#include <string>

#pragma once

class SignIn {
public:
    int access_lvl;
    std::string student_name, student_id;  // required when access level is 3 - student
    std::string teacher_course;  // required when access level is 2 - teacher

    void accessLevel(void);
    void adminAccess(void);
    void teacherAccess(void);
    void studentAccess(void);

};

#endif