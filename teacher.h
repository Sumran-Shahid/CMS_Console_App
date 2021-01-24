#ifndef TEACHER
#define TEACHER
#pragma once
#include <string>

class Teacher {
    public:
        std::string course;
        void menu(void);
        void makeAssignment(void);
        void makeQuiz(void);
        void markAssignment(void);
        void markQuiz(void);
        void resultCard(void);
};


#endif