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
		void assignFinalexam(void);
		void markFinalexam(void);
        void resultCard(void);

};
#endif