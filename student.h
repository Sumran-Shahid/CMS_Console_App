#ifndef STUDENT
#define STUDENT
#include <string>

#pragma once

class Student {
    public:
    std::string studentName;
    std::string cms_id;
    void menu(void);
    void showResult(void);
    void showCourses(void);
};


#endif