#ifndef SIGNIN
#define SIGNIN

#pragma once

class SignIn {
public:
    int access_lvl;

    int get_num(std::string prompt);
    void accessLevel(void);
    void adminAccess(void);
    void teacherAccess(void);
    void studentAccess(void);
};

#endif