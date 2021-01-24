#ifndef ADMIN
#define ADMIN
#pragma once

class Admin {
    public:
        int  choice;
        void menu(void);
        void newProgram(void);
        void viewPrograms(void);
        void newCourse(void);
        void viewCourses(void);
        void assignTeachers(void);
        void enrollStudents(void);
};

#endif 