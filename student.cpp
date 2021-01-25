#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "customFunctions.h"
#include "student.h"

using namespace std;


// menu function==========================================================================================================
void Student::menu(void) {

    cout << "What action do you want to perform?\n"
		 << "[1] - Show enrolled courses.\n"
		 << "[2] - Show result card of current semester.\n"
		 << "[3] - Return to main menu.\n"
		 << "[4] - Exit the program.\n"
         << "--> ";

    string choice_str;
	
	do {
		getline(cin, choice_str);
		if (valid_int(choice_str)) {
			stringstream choicestream(choice_str);
			choicestream >> choice;
			break;
		}
		else {
			cout << "Please enter a valid choice from the given options.\n";
			continue;
		}
	} while (1);

    switch (choice) {
    case 1:
		showCourses();
		break;
	case 2:
		showResult();
		break;
	case 3:
		break;
	case 4:
		cout << "Exiting Program...\n";
        exit(1);
		break;
    default:
        clear_screen();
        cout << "Please give an input from the given choices.\n";
        menu();
	}
} // menu function ending here


// showCourses function starts here ===============================================================================================
void Student::showCourses(void) {
    string          program;
    ifstream        programs("./data/Programs.dat");//reading of program file
    string          programIDs[30], programNames[30], Shortforms[30]; // these variables read data from Programs.dat to check if the entered program name exists


	if (programs.fail()) {
		cerr << "Programs.dat file not found.\n";
	}

	if (!programs.fail()) { // this conditional reads data from Programs.dat to check if the entered program name exists
		int iterator = 0;
		while (programs.peek()!=EOF) {
			getline(programs, programIDs[iterator], ',');
			getline(programs, Shortforms[iterator], ',');
			getline(programs, programNames[iterator], '\n');//storing data in array
			iterator++;}
        cout << "Enter the name of your degree program.\n";
        cout << "Available degree programs are :\n[ ";
		for (int i = 0; i < iterator; i++) {
			cout << programNames[i] << " ";
		}
		cout << " ]\n";
    	bool chk=false;
		do
		{
			getline(cin,program);
			for(int i=0;i<iterator;i++)
			{if(program == programNames[i])
			{chk=true;
			break;}
			else
				continue;
			}
			if(chk)
				break;
			else
			{
                cout<<"Please enter an existing degree program"<<endl;
			    continue;
			}
		}while(1);//degree porgram validation loop
	}
	programs.close();  // closing the programs.dat file after validating

    string          coursesFilePath = "./data/" + program + "/courses.dat";
    ifstream        courses(coursesFilePath);
    string          courseID;
    string          courseName;
    
    cout << "Course IDs\t\tCourse Names\n";

    if (courses.fail()) {
        cerr << "File courses.dat not found / could not be opened.\n";
    }
    else {
        int i = 0;
        while(courses.peek() != EOF) {
            getline(courses, courseID, ',');
            getline(courses, courseName, '\n');
            cout << courseID << "\t\t\t" << courseName << endl;
            i++;
        }
    }
    courses.close();
}


// showResult function starts here ===============================================================================================
void Student::showResult(void) {
    string          program;
    ifstream        programs("./data/Programs.dat");//reading of program file
    string          programIDs[30], programNames[30], Shortforms[30]; // these variables read data from Programs.dat to check if the entered program name exists


	if (programs.fail()) {
		cerr << "Programs.dat file not found.\n";
	}

	if (!programs.fail()) { // this conditional reads data from Programs.dat to check if the entered program name exists
		int iterator = 0;
		while (programs.peek()!=EOF) {
			getline(programs, programIDs[iterator], ',');
			getline(programs, Shortforms[iterator], ',');
			getline(programs, programNames[iterator], '\n');//storing data in array
			iterator++;}
        cout << "Enter your degree program name.\n";
        cout << "Available degree programs are :\n[ ";
		for (int i = 0; i < iterator; i++) {
			cout << programNames[i] << " ";
		}
		cout << " ]\n";
    	bool chk=false;
		do
		{
			getline(cin,program);
			for(int i=0;i<iterator;i++)
			{if(program == programNames[i])
			{chk=true;
			break;}
			else
				continue;
			}
			if(chk)
				break;
			else
			{
                cout<<"Please enter an existing degree program"<<endl;
			    continue;
			}
		}while(1);//degree porgram validation loop
	}
	programs.close();  // closing the programs.dat file after validating

    string          section;
    string          sectionsFilePath = "./data/" + program + "/Sectionlist.dat";
    ifstream        sectionslist(sectionsFilePath.c_str());//reading of program file
    string          sections[3];


	if (sectionslist.fail()) {
		cerr << "Sectionlist.dat file not found.\n";
	}

	if (!sectionslist.fail()) { // this conditional reads data from Programs.dat to check if the entered program name exists
		int iterator = 0;
		while (sectionslist.peek()!=EOF) {
			getline(sectionslist, sections[iterator], '\n');
			iterator++;
        }
        cout << "Enter your section name.\n[ ";

        for (int i = 0; i < iterator; i++) {
            cout << sections[i] << " ";
        }
        cout << "]" << endl;

        bool check=false;
		do
		{
			getline(cin,section);
			for(int i=0;i<iterator;i++)
			{if(section == sections[i])
			{check=true;
			break;}
			else
				continue;
			}
			if(check)
				break;
			else
			{
                cout<<"Please enter an existing section name."<<endl;
			    continue;
			}
		}while(1);//degree porgram validation loop
	}
	sectionslist.close();  // closing the file after validating


    clear_screen();
    cout << "\nName of Student\t: " << studentName << endl;
    cout << "CMS ID\t\t: " << cms_id << endl << endl;

    string          courseNamesPath = "./data/" + program + "/courses.dat";
    ifstream        courseNamesFile(courseNamesPath.c_str());

    if(courseNamesFile.fail()) {
        cerr << "Files courses.dat could not be opened / not found.\n";
    }
    else {

        string          courseName;
        string          courseID;
        getline(courseNamesFile, courseID, ',');
        getline(courseNamesFile, courseName, '\n');
        // now we have the name of the degree program of the student, course name and the section of the student
        // so we can open the files present in this course folder one by one and print their result

        cout << "Course Name\t: " << courseName << endl << endl;
        cout << "Tasks\t\tObtained\tMax Marks\tPercentage\tGrade\n";

        string          assignmentsRecordPath = "./data/" + program + "/" + section + "/" + courseName + "/assignments.dat";
        ifstream        assignmentsRecord(assignmentsRecordPath.c_str());

        if (assignmentsRecord.fail()) {
            cerr << "No assignments record was found.\n";
        }
        else {
            while(assignmentsRecord.peek() != EOF) { // this while loop loops through the assignment record file and then opens each of the assignments files whose record is present
                string          assignmentName;
                getline(assignmentsRecord, assignmentName, '\n');
                // now this is the path of the assignment file we need to open to fetch student data
                string          assignmentFilepath = "./data/" + program + "/" + section + "/" + courseName + "/" + assignmentName + ".dat";
                ifstream        assignmentFile(assignmentFilepath.c_str());
                if (!(assignmentFile.fail()))
                {
                    // now these variable are to store the information of the data of the student from the file
                    string          id;
                    string          name;
                    string          maxMarks_str;
                    string          obtained_str;
                    // now reading the assignment file and checking the line by line info and matching with the student info
                    while(assignmentFile.peek() != EOF) {
                        getline(assignmentFile, id, ',');
                        getline(assignmentFile, name, ',');
                        getline(assignmentFile, maxMarks_str, ',');
                        getline(assignmentFile, obtained_str, '\n');
                        if (id == cms_id) { // cms_id is the already defined class attribute
                            break;
                        }
                        else {
                            continue;
                        }
                    }
                    // after breaking out from the while loop, we have the student data now
                    int             maxMarks_int;
                    int             obtained_int;
                    double          percentage;
                    string          grade;

                    // converting max marks to int object using stringstream pointer
                    stringstream *maxMarksStream_ptr = new stringstream;
                    maxMarksStream_ptr->str(maxMarks_str);
                    *maxMarksStream_ptr >> maxMarks_int;
                    delete(maxMarksStream_ptr);

                    // converting obtained marks to int object using stringstream pointer
                    stringstream *obtMarksStream_ptr = new stringstream;
                    obtMarksStream_ptr->str(obtained_str);
                    *obtMarksStream_ptr >> obtained_int;
                    delete(obtMarksStream_ptr);

                    // calculating percentage and grade now
                    percentage = (double(obtained_int) / double(maxMarks_int)) * 100.0;
                    // Grades -->  (A (>85) B+(75-85) B(65-75) C+(55-65) C(45-55) F(<45))
                    if (percentage > 85.0) {  // A grade
                        grade = "A";
                    }
                    else if ((percentage < 85.0) && (percentage >= 75.0)) {  // B+ grade
                        grade = "B+";
                    }
                    else if ((percentage < 75.0) && (percentage >= 65.0)) {  // B grade
                        grade = "B";
                    }
                    else if ((percentage < 65.0) && (percentage >= 55.0)) {   // C+ grade
                        grade = "C+";
                    }
                    else if ((percentage < 55.0) && (percentage >= 45.0)) {   // C grade
                        grade = "C";
                    }
                    else {   // F grade
                        grade = "F";
                    }

                    // at this point we have the cms id, name, assignment name, max marks, obtained marks, percentage and grade
		cout <<assignmentName<<"\t   ";
		cout.width(2);
        cout << std::left << obtained_int << "\t\t   " << maxMarks_int << "\t\t    " << percentage << "\t\t   " << grade << endl;
                }
                assignmentFile.close();
                continue; // continue to the next assignment file
            }
        }// else block of assignment record ending here
        assignmentsRecord.close();
        cout << endl;

        // now doing the same thing as above for quizzes

        string          quizzesRecordPath = "./data/" + program + "/" + section + "/" + courseName + "/quizes.dat";
        ifstream        quizzesRecord(quizzesRecordPath.c_str());

        if (quizzesRecord.fail()) {
            cerr << "No quiz record was found.\n";
        }
        else {
            while(quizzesRecord.peek() != EOF) { // this while loop loops through the assignment record file and then opens each of the assignments files whose record is present
                string          quizName;
                getline(quizzesRecord, quizName, '\n');
                // now this is the path of the assignment file we need to open to fetch student data
                string          quizFilepath = "./data/" + program + "/" + section + "/" + courseName + "/" + quizName + ".dat";
                ifstream        quizFile(quizFilepath.c_str());
                if (!(quizFile.fail())) {
                    // now these variable are to store the information of the data of the student from the file
                    string          id;
                    string          name;
                    string          maxMarks_str;
                    string          obtained_str;
                    // now reading the assignment file and checking the line by line info and matching with the student info
                    while(quizFile.peek() != EOF) {
                        getline(quizFile, id, ',');
                        getline(quizFile, name, ',');
                        getline(quizFile, maxMarks_str, ',');
                        getline(quizFile, obtained_str, '\n');
                        if (id == cms_id) { // cms_id is the already defined class attribute
                            break;
                        }
                        else {
                            continue;
                        }
                    }
                    // after breaking out from the while loop, we have the student data now
                    int             maxMarks_int;
                    int             obtained_int;
                    double          percentage;
                    string          grade;

                    // converting max marks to int object using stringstream pointer
                    stringstream *maxMarksStream_ptr = new stringstream;
                    maxMarksStream_ptr->str(maxMarks_str);
                    *maxMarksStream_ptr >> maxMarks_int;
                    delete(maxMarksStream_ptr);

                    // converting obtained marks to int object using stringstream pointer
                    stringstream *obtMarksStream_ptr = new stringstream;
                    obtMarksStream_ptr->str(obtained_str);
                    *obtMarksStream_ptr >> obtained_int;
                    delete(obtMarksStream_ptr);

                    // calculating percentage and grade now
                    percentage = (double(obtained_int) / double(maxMarks_int)) * 100.0;
                    // Grades -->  (A (>85) B+(75-85) B(65-75) C+(55-65) C(45-55) F(<45))
                    if (percentage > 85.0) {  // A grade
                        grade = "A";
                    }
                    else if ((percentage < 85.0) && (percentage >= 75.0)) {  // B+ grade
                        grade = "B+";
                    }
                    else if ((percentage < 75.0) && (percentage >= 65.0)) {  // B grade
                        grade = "B";
                    }
                    else if ((percentage < 65.0) && (percentage >= 55.0)) {   // C+ grade
                        grade = "C+";
                    }
                    else if ((percentage < 55.0) && (percentage >= 45.0)) {   // C grade
                        grade = "C";
                    }
                    else {   // F grade
                        grade = "F";
                    }

                    // at this point we have the cms id, name, assignment name, max marks, obtained marks, percentage and grade
		cout <<quizName<<"\t   ";
		cout.width(2);
        cout << std::left << obtained_int << "\t\t   " << maxMarks_int << "\t\t    " << percentage << "\t\t   " << grade << endl;
                }
                quizFile.close();
                continue; // continue to the next assignment file
            }
        } // else block of quiz record ending here
        quizzesRecord.close();


	//doing the same thing for Final exam

                string          FinalexamFilepath = "./data/" + program + "/" + section + "/" + courseName + "/finalexam.dat";
                ifstream        FinalexamFile(FinalexamFilepath.c_str());
                if (FinalexamFile.fail()) {
                    cerr << "No Final-exam record was found!\n";
                }
                else {
                    // now these variable are to store the information of the data of the student from the file
                    string          id;
                    string          name;
                    string          maxMarks_str;
                    string          obtained_str;
                    // now reading the assignment file and checking the line by line info and matching with the student info
                    while(FinalexamFile.peek() != EOF) {
                        getline(FinalexamFile, id, ',');
                        getline(FinalexamFile, name, ',');
                        getline(FinalexamFile, maxMarks_str, ',');
                        getline(FinalexamFile, obtained_str, '\n');
                        if (id == cms_id) { // cms_id is the already defined class attribute
                            break;
                        }
                        else {
                            continue;
                        }
                    }
                    // after breaking out from the while loop, we have the student data now
                    int             maxMarks_int;
                    int             obtained_int;
                    int             percentage;
                    string          grade;

                    // converting max marks to int object using stringstream pointer
                    stringstream *maxMarksStream_ptr = new stringstream;
                    maxMarksStream_ptr->str(maxMarks_str);
                    *maxMarksStream_ptr >> maxMarks_int;
                    delete(maxMarksStream_ptr);

                    // converting obtained marks to int object using stringstream pointer
                    stringstream *obtMarksStream_ptr = new stringstream;
                    obtMarksStream_ptr->str(obtained_str);
                    *obtMarksStream_ptr >> obtained_int;
                    delete(obtMarksStream_ptr);

                    // calculating percentage and grade now
                    percentage = (double(obtained_int) / double(maxMarks_int)) * 100.0;
                    // Grades -->  (A (>85) B+(75-85) B(65-75) C+(55-65) C(45-55) F(<45))
                    if (percentage > 85.0) {  // A grade
                        grade = "A";
                    }
                    else if ((percentage < 85.0) && (percentage >= 75.0)) {  // B+ grade
                        grade = "B+";
                    }
                    else if ((percentage < 75.0) && (percentage >= 65.0)) {  // B grade
                        grade = "B";
                    }
                    else if ((percentage < 65.0) && (percentage >= 55.0)) {   // C+ grade
                        grade = "C+";
                    }
                    else if ((percentage < 55.0) && (percentage >= 45.0)) {   // C grade
                        grade = "C";
                    }
                    else {   // F grade
                        grade = "F";
                    }

                    // at this point we have the cms id, name, assignment name, max marks, obtained marks, percentage and grade

                cout <<"FinalExam"<<"\t   ";
                cout.width(2);
                cout << std::left << obtained_int << "\t\t   " << maxMarks_int << "\t\t    " << percentage << "\t\t   " << grade << endl;
                }
            FinalexamFile.close();
        } // else block of quiz record ending here
		courseNamesFile.close();
    }  // else block of coursenamesrecord file ends here

// show result card function ends here


/*
this is the pattern of the result card
Name of Student : ___
CMS ID          : ___
Course Name     : ___
Tasks           Obtained Marks          Max Marks           Percentage            Grade
assings         .                       .                   .                     .
assings         .                       .                   .                     .
assings         .                       .                   .                     .
quizzes         .                       .                   .                     .
quizzes         .                       .                   .                     .
quizzes         .                       .                   .                     .
Course Name     : ___
Tasks           Obtained Marks          Max Marks           Percentage            Grade
assings         .                       .                   .                     .
assings         .                       .                   .                     .
assings         .                       .                   .                     . 
quizzes         .                       .                   .                     .
quizzes         .                       .                   .                     .
quizzes         .                       .                   .                     .
*/