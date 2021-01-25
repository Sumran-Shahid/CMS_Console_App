#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "customFunctions.h"
#include "teacher.h"

using namespace std;

void makeAssignment(void);
void makeQuiz(void);
void markAssignment(void);
void markQuiz(void);
void resultCard(void);

void Teacher::menu(void) {

	cout << "What action do you want to perform?\n"
		 << "[1] - Assign an assignment.\n"
		 << "[2] - Assign a quiz.\n"
		 << "[3] - Mark an assignment.\n"
		 << "[4] - Mark a quiz.\n"
		 << "[5] - Assign Final exam.\n"
		 << "[6] - Mark Final exam.\n"
		 << "[7] - Visualize the result card.\n"
		 << "[8] - Return to main menu.\n"
		 << "[9] - Exit the program.\n"
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
		makeAssignment();
		break;
	case 2:
		makeQuiz();
		break;
	case 3:
		markAssignment();
		break;
	case 4:
		markQuiz();
		break;
	case 5:
		assignFinalexam();
		break;
	case 6:
		markFinalexam();
		break;
	case 7:
		resultCard();
		break;
	case 8:
		break;
	case 9:
		cout << "Exiting the program...\n";
		exit(1);
		break;
    default:
        clear_screen();
        cout << "Please give an input from the given choices.\n";
        menu();
	}
}


// makeAssignment function starts here=================================================================================================
void Teacher::makeAssignment(void) {
	string          program;
	ifstream        programs("./data/Programs.dat");//reading of program file
	string          courseIDs[30], courseNames[30], Shortforms[30]; // these variables read data from Programs.dat to check if the entered program name exists


	if (programs.fail()) {
		cerr << "Programs.dat file not found.\n";
	}

	if (!programs.fail()) { // this conditional reads data from Programs.dat to check if the entered program name exists
		int iterator = 0;
		while (programs.peek()!=EOF) {
			getline(programs, courseIDs[iterator], ',');
			getline(programs, Shortforms[iterator], ',');
			getline(programs, courseNames[iterator], '\n');//storing data in array
			iterator++;}
		cout << "Which degree program you want to make assignment of?\n";
		cout << "Available degree programs are :\n[ ";
		for (int i = 0; i < iterator; i++) {
			cout << courseNames[i] << " ";
		}
		cout << " ]\n";
		bool chk=false;
		do
		{
			getline(cin,program);
			for(int i=0;i<iterator;i++)
			{if(program == courseNames[i])
			{chk=true;
			break;}
			else
				continue;
			}
			if(chk)
				break;
			else
			{cout<<"Please enter an existing degree program"<<endl;
			continue;
			}
		}while(1);//degree porgram validation loop
	}
	programs.close();  // closing the programs.dat file after validating

	string          section;
	string          secname[3]; // this variable takes the names of the sections from the sectionslist.dat
	string          path_of_sectionlist = "./data/" + program + "/Sectionlist.dat";
	ifstream        sections(path_of_sectionlist.c_str());


	int iterator = 0;
	if(sections.fail()) {
		cerr<<"Sections file couldnt be opened"<<endl;
	}
	else {
		while(sections.peek()!=EOF){   //reading name of sections and storing in section array
			getline(sections,secname[iterator],'\n');
			iterator++;
		}

		cout<<"Enter name of section from the given options"<<"\n[";
		for(int i=0;i<iterator;i++)
			cout<<secname[i]<<" ";

		cout<<"]"<<endl;
		bool check=false;
		do{
			getline(cin,section);
			for(int i=0;i<iterator;i++)
			{
				if (section==secname[i])
				{
					check=true;
					break;
				}
				else	
					continue;
			}
			if(check)
				break;
			else 
				cout<<"Please enter a section from given choices"<<endl;
			continue;
		} while(1);//section validation loop
	}

	string          coursePath = "./data/" + program + "/" + section + "/" + course; // path of the folder of the course
	string          assignmentRecordPath = "./data/" + program + "/" + section + "/" + course + "/assignments.dat"; // path of the assignments.dat file that takes general record of the assignments
	string          assignmentName; // name of the assignment taken from the teacher
	fstream         assignments_record(assignmentRecordPath.c_str(), ios::app); // assignments.dat for general record of the assignments created

	cout << "Please enter the name of the assignment.\n";
	getline(cin, assignmentName);

	if (assignments_record.fail()) {
		cerr << "File assignments.dat not found.\n";
	}
	else {
		assignments_record << assignmentName << endl;
	}

	string          assignmentPath = "./data/" + program + "/" + section + "/" + course + "/" + assignmentName + ".dat"; // path of the assignment file to be made
	string          studentsPath = "./data/" + program + "/" + section + "/students.dat";
	ofstream        assignmentFile(assignmentPath.c_str()); // this is the main file to store the data of the assignment created by the teacher
	fstream         students(studentsPath.c_str());
	string          studentName;  // following three variables are to take the data of all the students from the list of the students from the csv file
	string          studentID;
	string          studentProgram;
	string          maxMarks_str;   // maximum marks for the assignment are stored in this variable for validation before conversion
	int             maxMarks;   // maximum marks for the assignment are stored in this variable

	cout << "Enter the maximum marks for the assignment.\nShould be a positive number less than or equal to 20\n";
	do {
		getline(cin, maxMarks_str);
		if (valid_int(maxMarks_str)) {
			stringstream maxMarksStream(maxMarks_str);
			maxMarksStream >> maxMarks;
			if ((maxMarks < 0) || (maxMarks > 20)) {
				cout << "Please enter a number within the given range.\n";
				continue;
			}
			break;
		}
		else {
			cout << "Please enter a valid number within the given range.\n";
			continue;
		}
	} while(1);

	if (assignmentFile.fail()) {
		cerr << "Assignment file could not be made / opened.\n";
	}
	else {
		if (students.fail()) {
			cerr << "File students.dat in section folder couldnt be opened\n";
		}
		else {
			while(students.peek() != EOF) {
				getline(students, studentID, ',');
				getline(students, studentName, ',');
				getline(students, studentProgram, '\n');
				assignmentFile << studentID << "," << studentName << ',' << maxMarks << ",-1"<< endl;
			}
		}
	}


} // makeassignment function ends here


// makeQuiz function starts here=================================================================================================
void Teacher::makeQuiz(void) {
	string          program;
	ifstream        programs("./data/Programs.dat");//reading of program file
	string          courseIDs[30], courseNames[30], Shortforms[30]; // these variables read data from Programs.dat to check if the entered program name exists


	if (programs.fail()) {
		cerr << "Programs.dat file not found.\n";
	}

	if (!programs.fail()) { // this conditional reads data from Programs.dat to check if the entered program name exists
		int iterator = 0;
		while (programs.peek()!=EOF) {
			getline(programs, courseIDs[iterator], ',');
			getline(programs, Shortforms[iterator], ',');
			getline(programs, courseNames[iterator], '\n');//storing data in array
			iterator++;}
		cout << "Which degree program you want to make quiz of?\n";
		cout << "Available degree programs are :\n[ ";
		for (int i = 0; i < iterator; i++) {
			cout << courseNames[i] << " ";
		}
		cout << " ]\n";
		bool chk=false;
		do
		{
			getline(cin,program);
			for(int i=0;i<iterator;i++)
			{if(program == courseNames[i])
			{chk=true;
			break;}
			else
				continue;
			}
			if(chk)
				break;
			else
			{cout<<"Please enter an existing degree program"<<endl;
			continue;
			}
		}while(1);//degree porgram validation loop
	}
	programs.close();  // closing the programs.dat file after validating

	string          section;
	string          secname[3]; // this variable takes the names of the sections from the sectionslist.dat
	string          path_of_sectionlist = "./data/" + program + "/Sectionlist.dat";
	ifstream        sections(path_of_sectionlist.c_str());


	int iterator = 0;
	if(sections.fail()) {
		cerr<<"Sections file couldnt be opened"<<endl;
	}
	else {
		while(sections.peek()!=EOF){   //reading name of sections and storing in section array
			getline(sections,secname[iterator],'\n');
			iterator++;
		}

		cout<<"Enter name of section from the given options"<<"\n[";
		for(int i=0;i<iterator;i++)
			cout<<secname[i]<<" ";

		cout<<"]"<<endl;
		bool check=false;
		do{
			getline(cin,section);
			for(int i=0;i<iterator;i++)
			{
				if (section==secname[i])
				{
					check=true;
					break;
				}
				else	
					continue;
			}
			if(check)
				break;
			else 
				cout<<"Please enter a section from given choices"<<endl;
			continue;
		} while(1);//section validation loop
	}

	string          coursePath = "./data/" + program + "/" + section + "/" + course; // path of the folder of the course
	string          quizRecordPath = "./data/" + program + "/" + section + "/" + course + "/quizes.dat"; // path of the assignments.dat file that takes general record of the quizes
	string          quizName; // name of the quiz taken from the teacher
	ofstream        quiz_record(quizRecordPath.c_str(),ios::app); // quizes.dat for general record of the quizes created

	cout << "Please enter the name of the quiz.\n";
	getline(cin, quizName);

	if (quiz_record.fail()) {
		cerr << "File quizes.dat not found.\n";
	}
	else {
		quiz_record << quizName << endl;
	}

	string          quizPath = "./data/" + program + "/" + section + "/" + course + "/" + quizName + ".dat"; // path of the quiz file to be made
	string          studentsPath = "./data/" + program + "/" + section + "/students.dat";
	ofstream        quizFile(quizPath.c_str(),ios::app); // this is the main file to store the data of the quiz created by the teacher
	ifstream        students(studentsPath.c_str());
	string          studentName[70];  // following three variables are to take the data of all the students from the list of the students from the csv file
	string          studentID[70];
	string          studentProgram[20];
	string          maxMarks_str;   // maximum marks for the quizes are stored in this variable for validation before conversion
	int             maxMarks;   // maximum marks for the quizes are stored in this variable

	cout << "Enter the maximum marks for the quiz.\nShould be a positive number less than or equal to 20\n";
	do {
		getline(cin, maxMarks_str);
		if (valid_int(maxMarks_str)) {
			stringstream maxMarksStream(maxMarks_str);
			maxMarksStream >> maxMarks;
			if ((maxMarks < 0) || (maxMarks > 20)) {
				cout << "Please enter a number within the given range.\n";
				continue;
			}
			break;
		}
		else {
			cout << "Please enter a valid number within the given range.\n";
			continue;
		}
	}
while(1);

	if (quizFile.fail()) {
		cerr << "Quiz file could not be made / opened.\n";
	}
	else {
		if (students.fail()) {
			cerr << "File students.dat in section folder couldnt be opened\n";
		}
		else {
			int iterator=0;
			while(students.peek() != EOF) {
				getline(students,studentID[iterator],',');
				getline(students,studentName[iterator],',');
				getline(students,studentProgram[iterator],'\n');
				iterator++;
			}
			students.close();
			for(int i=0;i<iterator;i++)
			{
				quizFile<<studentID[i]<<","<<studentName[i]<<","<<maxMarks<<",-1"<<endl;
			}
		}
	}
}



// markAssignment function starts here=================================================================================================
void Teacher::markAssignment(void) {
	string          program;
	ifstream        programs("./data/Programs.dat");//reading of program file
	string          courseIDs[30], courseNames[30], Shortforms[30]; // these variables read data from Programs.dat to check if the entered program name exists
	string          section;
    string          assignname;
    string          assigndir;

	if (programs.fail()) {
		cerr << "Programs.dat file not found.\n";
	}

	if (!programs.fail()) { // this conditional reads data from Programs.dat to check if the entered program name exists
		int iterator = 0;
		while (programs.peek()!=EOF) {
			getline(programs, courseIDs[iterator], ',');
			getline(programs, Shortforms[iterator], ',');
			getline(programs, courseNames[iterator], '\n');//storing data in array
			iterator++;}
		cout << "Which degree program you want to mark Assignments of?\n";
		cout << "Available degree programs are :\n[ ";
		for (int i = 0; i < iterator; i++) {
			cout << courseNames[i] << " ";
		}
		cout << " ]\n";
		bool chk=false;
		do
		{
			getline(cin,program);
			for(int i=0;i<iterator;i++)
			{if(program == courseNames[i])
			{chk=true;
			break;}
			else
				continue;
			}
			if(chk)
				break;
			else
			{cout<<"Please enter an existing degree program"<<endl;
			continue;
			}
		}while(1);  //degree porgram validation loop
    }
	string          secname[3]; // this variable takes the names of the sections from the sectionslist.dat
	string          path_of_sectionlist = "./data/" + program + "/Sectionlist.dat";
	ifstream        sections(path_of_sectionlist.c_str());


	int iterator = 0;
	if(sections.fail()) {
		cerr<<"Sections file couldnt be opened"<<endl;
	}
	else {
		while(sections.peek()!=EOF){   //reading name of sections and storing in section array
			getline(sections,secname[iterator],'\n');
			iterator++;
		}

		cout<<"Enter name of section from the given options"<<"\n[";
		for(int i=0;i<iterator;i++)
			cout<<secname[i]<<" ";

		cout<<"]"<<endl;
		bool check=false;
		do{
			getline(cin,section);
			for(int i=0;i<iterator;i++)
			{
				if (section==secname[i])
				{
					check=true;
					break;
				}
				else	
					continue;
			}
			if(check)
				break;
			else 
				cout<<"Please enter a section from given choices"<<endl;
			continue;
		} while(1);//section validation loop
	}
	sections.close();
	string          assiassignments_record="./data/"+program+"/"+section+"/"+course+"/assignments.dat";//directory of assignment record
	string          assignments[20];
	ifstream        assignments_record(assiassignments_record.c_str());//reading assignment record
	if(assignments_record.fail()) {
		cerr<<"Assignment.dat could not be opened"<<endl;
    }
    else {
        iterator=0;
        while(assignments_record.peek()!=EOF){   //reading name of sections and storing in section array
            getline(assignments_record, assignments[iterator],'\n');
            iterator++;
        }

        cout << "Previously made assignments are :\n[ ";
        for (int j = 0; j < iterator; j++) { // read comment below
            j != iterator - 1 ?cout << assignments[j] << " ":cout << assignments[j] << " ]\n";   // this thing is just for cosmetic purpose of the output
        }
        

        bool chk=false;
        do {
            cout<<"Please enter name of an assigned assignment"<<endl;
            getline(cin,assignname);
            for(int i=0;i<iterator;i++)
            {
                if(assignname == assignments[i]) {
                    chk=true;
                    break;
                }
                else {
                    continue;
                }
            }
            if(chk){
                break;
            }
            else
            {
                continue;
            }
        } while(1);//assignment validation loop
        assignments_record.close();
        
        assigndir="./data/"+program+"/"+section+"/"+course+"/"+assignname+".dat";//directory of assignment file
        ifstream        readassigndata(assigndir.c_str());
        
        if(readassigndata.fail()) {
            cerr<<"Assignment data file could not be opened"<<endl;
        }
        else{
            string cms_id[60],studentname[60],max_marks[60],enteredmarks,maxmarks[60];
            iterator=0;
            while (readassigndata.peek()!=EOF) { // this while loop reads data from the files and stores inside the arrays
                getline(readassigndata, cms_id[iterator], ',');
                getline(readassigndata, studentname[iterator], ',');
                getline(readassigndata, max_marks[iterator], ',');    //storing data in array
				getline(readassigndata, enteredmarks,'\n');
                iterator++;
            }
			readassigndata.close();
			iterator=0;
			do{
				if(enteredmarks=="-1") {//check if assignment is marked
				ifstream readassigndata1(assigndir.c_str());
				while (readassigndata1.peek()!=EOF) { // this while loop reads data from the files and stores inside the arrays
                getline(readassigndata1, cms_id[iterator], ',');
                getline(readassigndata1, studentname[iterator], ',');
                getline(readassigndata1, maxmarks[iterator], ',');    //storing data in array
                getline(readassigndata1, enteredmarks, '\n');    //storing data in array
                iterator++;
            }
            cout<<"Please enter marks of the following students:"<<endl;
            cout<<"CMS ID\t\tSTUDENT NAME\t\tMAX MARKS\t\tENTERED MARKS\n";
            string entered_marks[60];
            
            for(int i=0;i<iterator;i++) {
				cout <<cms_id[i]<<"\t\t";
				cout.width(24);
                cout<<std::left<<studentname[i]<<maxmarks[i]<<"\t\t\t";
                do{
                    getline(cin,entered_marks[i]);

                    if(valid_int(entered_marks[i])) {
                        stringstream marks_str(entered_marks[i]);
                        int marks;
                        marks_str>>marks;
                        stringstream maxmarks_str(maxmarks[i]);
                        int max_marks;
                        maxmarks_str>>max_marks;
                        if(marks<0||marks>max_marks){
                            cout<<"Please enter marks within the set maximum marks"<<endl;
                            continue;
                        }
                        else
                            break;
							
                    }
                } while(1);
            }

            ofstream writeassigndata(assigndir.c_str(),ios::out);
            if(writeassigndata.fail()){
                cerr<<"Assignment file could not be opened in writing marks"<<endl;
            }
            else {
                for(int i=0;i<iterator;i++) {
                    writeassigndata<<cms_id[i]<<","<<studentname[i]<<","<<maxmarks[i]<<","<<entered_marks[i]<<endl;
                }
            }
			break;
			}
			else {
				cout<<"This assignment is already marked.Please enter the name of an un-marked assignment"<<endl;
			}
        
		cin.clear();
		cin.get();
		}while(1);//assignemnt marking check loop
		
		}
	}
}


// markQuiz function starts here=================================================================================================
void Teacher::markQuiz(void) {
	string          program;
	ifstream        programs("./data/Programs.dat");//reading of program file
	string          courseIDs[30], courseNames[30], Shortforms[30]; // these variables read data from Programs.dat to check if the entered program name exists
	string          section;
    string          quizname;
    string          quizdir;

	if (programs.fail()) {
		cerr << "Programs.dat file not found.\n";
	}

	if (!programs.fail()) { // this conditional reads data from Programs.dat to check if the entered program name exists
		int iterator = 0;
		while (programs.peek()!=EOF) {
			getline(programs, courseIDs[iterator], ',');
			getline(programs, Shortforms[iterator], ',');
			getline(programs, courseNames[iterator], '\n');//storing data in array
			iterator++;}
		cout << "Which degree program you want to mark Quiz of?\n";
		cout << "Available degree programs are :\n[ ";
		for (int i = 0; i < iterator; i++) {
			cout << courseNames[i] << " ";
		}
		cout << " ]\n";
		bool chk=false;
		do
		{
			getline(cin,program);
			for(int i=0;i<iterator;i++)
			{if(program == courseNames[i])
			{chk=true;
			break;}
			else
				continue;
			}
			if(chk)
				break;
			else
			{cout<<"Please enter an existing degree program"<<endl;
			continue;
			}
		}while(1);  //degree porgram validation loop
    }
	string          secname[3]; // this variable takes the names of the sections from the sectionslist.dat
	string          path_of_sectionlist = "./data/" + program + "/Sectionlist.dat";
	ifstream        sections(path_of_sectionlist.c_str());


	int iterator = 0;
	if(sections.fail()) {
		cerr<<"Sections file couldnt be opened"<<endl;
	}
	else {
		while(sections.peek()!=EOF){   //reading name of sections and storing in section array
			getline(sections,secname[iterator],'\n');
			iterator++;
		}

		cout<<"Enter name of section from the given options"<<"\n[";
		for(int i=0;i<iterator;i++)
			cout<<secname[i]<<" ";

		cout<<"]"<<endl;
		bool check=false;
		do{
			getline(cin,section);
			for(int i=0;i<iterator;i++)
			{
				if (section==secname[i])
				{
					check=true;
					break;
				}
				else	
					continue;
			}
			if(check)
				break;
			else 
				cout<<"Please enter a section from given choices"<<endl;
			continue;
		} while(1);//section validation loop
	}
	sections.close();
	string          quizzes_record_path="./data/"+program+"/"+section+"/"+course+"/quizes.dat";//directory of assignment record
	string          quizzes[20];
	ifstream        quizzes_record(quizzes_record_path.c_str());//reading assignment record
	if(quizzes_record.fail()) {
		cerr<<"Quizes.dat could not be opened"<<endl;
    }
    else {
        iterator=0;
        while(quizzes_record.peek()!=EOF){   //reading name of sections and storing in section array
            getline(quizzes_record, quizzes[iterator],'\n');
            iterator++;
        }

        cout << "Previously made quizzes are :\n[ ";
        for (int j = 0; j < iterator; j++) { // read comment below
            cout<<quizzes[j]<<" ";   // this thing is just for cosmetic purpose of the output
        }
        cout<<" ]\n";

        bool chk=false;
        do {
            cout<<"Please enter name of an assigned quizzes"<<endl;
            getline(cin,quizname);
            for(int i=0;i<iterator;i++)
            {
                if(quizname == quizzes[i]) {
                    chk=true;
                    break;
                }
                else {
                    continue;
                }
            }
            if(chk){
                break;
            }
            else
            {
                continue;
            }
        } while(1);//assignment validation loop
        quizzes_record.close();
        
        quizdir="./data/"+program+"/"+section+"/"+course+"/"+quizname+".dat";//directory of assignment file
        ifstream        readassigndata(quizdir.c_str());
        
        if(readassigndata.fail()) {
            cerr<<"Quiz data file could not be opened"<<endl;
        }
        else{
            string cms_id[60],studentname[60],max_marks[60],enteredmarks,maxmarks[60];
            iterator=0;
            while (readassigndata.peek()!=EOF) { // this while loop reads data from the files and stores inside the arrays
                getline(readassigndata, cms_id[iterator], ',');
                getline(readassigndata, studentname[iterator], ',');
                getline(readassigndata, max_marks[iterator], ',');    //storing data in array
				getline(readassigndata, enteredmarks,'\n');
                iterator++;
            }
            readassigndata.close();//closes the file after reading the data and putting in the array
			do{
				if(enteredmarks=="-1"){
					iterator=0;
					ifstream readassigndata1(quizdir.c_str());
				 	while (readassigndata1.peek()!=EOF) { // this while loop reads data from the files and stores inside the arrays
                getline(readassigndata1, cms_id[iterator], ',');
                getline(readassigndata1, studentname[iterator], ',');
                getline(readassigndata1, maxmarks[iterator], '\n');    //storing data in array
                iterator++;
            }

            cout<<"Please enter marks of the following students:"<<endl;
            cout<<"CMS ID\t\tSTUDENT NAME\t\tMAX MARKS\t\tENTERED MARKS\n";
            string entered_marks[60];
            
            for(int i=0;i<iterator;i++) {
                cout <<cms_id[i]<<"\t\t";
				cout.width(24);
                cout<<std::left<<studentname[i]<<maxmarks[i]<<"\t\t\t";
                do{
                    getline(cin,entered_marks[i]);

                    if(valid_int(entered_marks[i])) {
                        stringstream marks_str(entered_marks[i]);
                        int marks;
                        marks_str>>marks;
                        stringstream maxmarks_str(maxmarks[i]);
                        int max_marks;
                        maxmarks_str>>max_marks;
                        if(marks<0||marks>max_marks){
                            cout<<"Please enter marks within the set maximum marks"<<endl;
                            continue;
                        }
                        else
                            break;
                    }
                } while(1);
            }

            ofstream writeassigndata(quizdir.c_str(),ios::out);
            if(writeassigndata.fail()){
                cerr<<"Quiz file could not be opened in writing marks"<<endl;
            }
            else {
                for(int i=0;i<iterator;i++) {
                    writeassigndata<<cms_id[i]<<","<<studentname[i]<<","<<maxmarks[i]<<","<<entered_marks[i]<<endl;
                }
            }
			break;
			}
			else {
				cout<<"This quiz is already marked.Please enter a different name"<<endl;
			}

	}while(1);
		}
		
}
}
// markQuiz function ends here


void Teacher::assignFinalexam(void)
{
	string          program;
	ifstream        programs("./data/Programs.dat");//reading of program file
	string          courseIDs[30], courseNames[30], Shortforms[30]; // these variables read data from Programs.dat to check if the entered program name exists


	if (programs.fail()) {
		cerr << "Programs.dat file not found.\n";
	}

	if (!programs.fail()) { // this conditional reads data from Programs.dat to check if the entered program name exists
		int iterator = 0;
		while (programs.peek()!=EOF) {
			getline(programs, courseIDs[iterator], ',');
			getline(programs, Shortforms[iterator], ',');
			getline(programs, courseNames[iterator], '\n');//storing data in array
			iterator++;}
		cout << "Which degree program you want to assign Final exam of?\n";
		cout << "Available degree programs are :\n[ ";
		for (int i = 0; i < iterator; i++) {
			cout << courseNames[i] << " ";
		}
		cout << " ]\n";
		bool chk=false;
		do
		{
			getline(cin,program);
			for(int i=0;i<iterator;i++)
			{if(program == courseNames[i])
			{chk=true;
			break;}
			else
				continue;
			}
			if(chk)
				break;
			else
			{cout<<"Please enter an existing degree program"<<endl;
			continue;
			}
		}while(1);//degree porgram validation loop
	}
	programs.close();  // closing the programs.dat file after validating

	string          section;
	string          secname[3]; // this variable takes the names of the sections from the sectionslist.dat
	string          path_of_sectionlist = "./data/" + program + "/Sectionlist.dat";
	ifstream        sections(path_of_sectionlist.c_str());


	int iterator = 0;
	if(sections.fail()) {
		cerr<<"Sections file couldnt be opened"<<endl;
	}
	else {
		while(sections.peek()!=EOF){   //reading name of sections and storing in section array
			getline(sections,secname[iterator],'\n');
			iterator++;
		}

		cout<<"Enter name of section from the given options"<<"\n[";
		for(int i=0;i<iterator;i++)
			cout<<secname[i]<<" ";

		cout<<"]"<<endl;
		bool check=false;
		do{
			getline(cin,section);
			for(int i=0;i<iterator;i++)
			{
				if (section==secname[i])
				{
					check=true;
					break;
				}
				else	
					continue;
			}
			if(check)
				break;
			else 
				cout<<"Please enter a section from given choices"<<endl;
			continue;
		} while(1);//section validation loop
	}


	string          finalexampath = "./data/" + program + "/" + section + "/" + course + "/finalexam.dat"; // path of the finalexam file to be made
	string          studentsPath = "./data/" + program + "/" + section + "/students.dat";
	ofstream        finalexamFile(finalexampath.c_str(), ios::app); // this is the main file to store the data of the assignment created by the teacher
	fstream         students(studentsPath.c_str());
	string          studentName;  // following three variables are to take the data of all the students from the list of the students from the csv file
	string          studentID;
	string          studentProgram;
	string          maxMarks_str;   // maximum marks for the assignment are stored in this variable for validation before conversion
	int             maxMarks;   // maximum marks for the assignment are stored in this variable

	cout << "Enter the maximum marks for the Final exam (Max Marks:50-70)"<<endl;
	do {
		getline(cin, maxMarks_str);
		if (valid_int(maxMarks_str)) {
			stringstream maxMarksStream(maxMarks_str);
			maxMarksStream >> maxMarks;
			if ((maxMarks < 50) || (maxMarks > 70)) {
				cout << "Please enter a number within the given range.\n";
				continue;
			}
			break;
		}
		else {
			cout << "Please enter a valid number within the given range.\n";
			continue;
		}
	} while(1);

	if (finalexamFile.fail()) {
		cerr << "Assignment file could not be made / opened.\n";
	}
	else {
		if (students.fail()) {
			cerr << "File students.dat in section folder couldnt be opened\n";
		}
		else {
			while(students.peek() != EOF) {
				getline(students, studentID, ',');
				getline(students, studentName, ',');
				getline(students, studentProgram, '\n');
				finalexamFile << studentID << "," << studentName << ',' << maxMarks << ",-1" << endl;
			}
			finalexamFile.close();
		}
	}




}


//markFinalexam function starts here
void Teacher::markFinalexam(void){
	string          program;
	ifstream        programs("./data/Programs.dat");//reading of program file
	string          courseIDs[30], courseNames[30], Shortforms[30]; // these variables read data from Programs.dat to check if the entered program name exists
	string          section;
    string          assignname;
    string          assigndir;

	if (programs.fail()) {
		cerr << "Programs.dat file not found.\n";
	}

	if (!programs.fail()) { // this conditional reads data from Programs.dat to check if the entered program name exists
		int iterator = 0;
		while (programs.peek()!=EOF) {
			getline(programs, courseIDs[iterator], ',');
			getline(programs, Shortforms[iterator], ',');
			getline(programs, courseNames[iterator], '\n');//storing data in array
			iterator++;}
		cout << "Which degree program you want to mark Final Exam of?\n";
		cout << "Available degree programs are :\n[ ";
		for (int i = 0; i < iterator; i++) {
			cout << courseNames[i] << " ";
		}
		cout << " ]\n";
		bool chk=false;
		do
		{
			getline(cin,program);
			for(int i=0;i<iterator;i++)
			{if(program == courseNames[i])
			{chk=true;
			break;}
			else
				continue;
			}
			if(chk)
				break;
			else
			{cout<<"Please enter an existing degree program"<<endl;
			continue;
			}
		}while(1);  //degree porgram validation loop
    }
	string          secname[3]; // this variable takes the names of the sections from the sectionslist.dat
	string          path_of_sectionlist = "./data/" + program + "/Sectionlist.dat";
	ifstream        sections(path_of_sectionlist.c_str());


	int iterator = 0;
	if(sections.fail()) {
		cerr<<"Sections file couldnt be opened"<<endl;
	}
	else {
		while(sections.peek()!=EOF){   //reading name of sections and storing in section array
			getline(sections,secname[iterator],'\n');
			iterator++;
		}

		cout<<"Enter name of section from the given options"<<"\n[";
		for(int i=0;i<iterator;i++)
			cout<<secname[i]<<" ";

		cout<<"]"<<endl;
		bool check=false;
		do{
			getline(cin,section);
			for(int i=0;i<iterator;i++)
			{
				if (section==secname[i])
				{
					check=true;
					break;
				}
				else	
					continue;
			}
			if(check)
				break;
			else 
				cout<<"Please enter a section from given choices"<<endl;
			continue;
		} while(1);//section validation loop
	}
	sections.close();
        
        assigndir="./data/"+program+"/"+section+"/"+course+"/"+"finalexam.dat";//directory of Final exam
        ifstream        readfinalexamdata(assigndir.c_str());
        
        if(readfinalexamdata.fail()) {
            cerr<<"Final exam data file could not be opened"<<endl;
        }
        else{
            string cms_id[60],studentname[60],max_marks,enteredmarks,maxmarks[60];
            iterator=0;
            while (readfinalexamdata.peek()!=EOF) { // this while loop reads data from the files and stores inside the arrays
                getline(readfinalexamdata, cms_id[iterator], ',');
                getline(readfinalexamdata, studentname[iterator], ',');
                getline(readfinalexamdata, max_marks, ',');    //storing data in array
				getline(readfinalexamdata,enteredmarks,'\n');
                iterator++;
            }
			if(max_marks=="")
				cout<<"Final exam has not been assigned to this section"<<endl;
			else{
			readfinalexamdata.close();
			iterator=0;
			do{
				if(enteredmarks=="-1"){
				ifstream readfinalexamdata1(assigndir.c_str());
				while (readfinalexamdata1.peek()!=EOF) { // this while loop reads data from the files and stores inside the arrays
                getline(readfinalexamdata1, cms_id[iterator], ',');
                getline(readfinalexamdata1, studentname[iterator], ',');
                getline(readfinalexamdata1, maxmarks[iterator], ',');    //storing data in array
                getline(readfinalexamdata1, enteredmarks, '\n');    //storing data in array
                iterator++;
            }
            cout<<"Please enter marks of the following students in Final exam:"<<endl;
            cout<<"CMS ID\t\tSTUDENT NAME\t\tMAX MARKS\t\tENTERED MARKS\n";
            string entered_marks[60];
            
            for(int i=0;i<iterator;i++) {
                cout <<cms_id[i]<<"\t\t";
				cout.width(24);
                cout<<std::left<<studentname[i]<<maxmarks[i]<<"\t\t\t";
                do{
                    getline(cin,entered_marks[i]);

                    if(valid_int(entered_marks[i])) {
                        stringstream marks_str(entered_marks[i]);
                        int marks;
                        marks_str>>marks;
                        stringstream maxmarks_str(maxmarks[i]);
                        int max_marks;
                        maxmarks_str>>max_marks;
                        if(marks<0||marks>max_marks){
                            cout<<"Please enter marks within the set maximum marks"<<endl;
                            continue;
                        }
                        else
                            break;
                    }
                } while(1);
            }

			ofstream writeFinalexamdata(assigndir.c_str(),ios::out);
            if(writeFinalexamdata.fail()){
                cerr<<"Assignment file could not be opened in writing marks"<<endl;
            }
            else {
                for(int i=0;i<iterator;i++) {
                    writeFinalexamdata<<cms_id[i]<<","<<studentname[i]<<","<<maxmarks[i]<<","<<entered_marks[i]<<endl;
                }
            }
			break;
				}
				else {
					cout<<"This Final exam is already marked."<<endl;
					break;
				}
        }
		while(1);//assignemnt marking check loop
		
	}
		}
		
}


// resultCard function starts here=================================================================================================
void Teacher::resultCard(void) {
    string          program;  // name of the program required
    string          section;  // name of the section required
    ifstream        programs("./data/Programs.dat");//reading of program file
	string          courseIDs[30], courseNames[30], Shortforms[30]; // these variables read data from Programs.dat to check if the entered program name exists


	if (programs.fail()) {
		cerr << "Programs.dat file not found.\n";
	}

	if (!programs.fail()) { // this conditional reads data from Programs.dat to check if the entered program name exists
		int iterator = 0;
		while (programs.peek()!=EOF) {
			getline(programs, courseIDs[iterator], ',');
			getline(programs, Shortforms[iterator], ',');
			getline(programs, courseNames[iterator], '\n');//storing data in array
			iterator++;}
	    cout << "Which degree program you want to see result of?\n";
		cout << "Available degree programs are :\n[ ";
		for (int i = 0; i < iterator; i++) {
			cout << courseNames[i] << " ";
		}
		cout << " ]\n";
		bool chk=false;
		do
		{
			getline(cin,program);
			for(int i=0;i<iterator;i++)
			{if(program == courseNames[i])
			{chk=true;
			break;}
			else
				continue;
			}
			if(chk)
				break;
			else
			{cout<<"Please enter an existing degree program"<<endl;
			continue;
			}
		}while(1);  //degree porgram validation loop
    }

    string          secname[3]; // this array takes the names of the sections from the sectionslist.dat
	string          path_of_sectionlist = "./data/" + program + "/Sectionlist.dat";
	ifstream        sections(path_of_sectionlist.c_str());

	int iterator = 0;
	if(sections.fail()) {
		cerr<<"Sections file couldnt be opened"<<endl;
	}
	else {
		while(sections.peek()!=EOF){   //reading name of sections and storing in section array
			getline(sections,secname[iterator],'\n');
			iterator++;
		}

		cout<<"Enter name of section from the given options"<<"\n[";
		for(int i=0;i<iterator;i++)
			cout<<secname[i]<<" ";

		cout<<"]"<<endl;
		bool check=false;
		do{
			getline(cin,section);
			for(int i=0;i<iterator;i++)
			{
				if (section==secname[i])
				{
					check=true;
					break;
				}
				else	
					continue;
			}
			if(check)
				break;
			else 
				cout<<"Please enter a section from given choices"<<endl;
			continue;
		} while(1);//section validation loop
	}

    string          assignments_path = "./data/" + program + "/" + section + "/" + course + "/assignments.dat";
    ifstream        assignments_file(assignments_path.c_str());
    string          assignments[20]; // this array stores the names of all the assignments by taking them in from the assignments_file
    
    int ass_iterator = 0; // iterator variable was already declared above in this function
    if (assignments_file.fail()) {
        cerr << "File assignments.dat not found / could not be opened.\n";
    }
    else {
        while (assignments_file.peek() != EOF) {
            getline(assignments_file, assignments[ass_iterator], '\n');
            ass_iterator++;
        }
    }
    
    
    string          quizes_path = "./data/" + program + "/" + section + "/" + course + "/quizes.dat";
    ifstream        quizes_file(quizes_path.c_str());
    string          quizzes[20]; // this array stores the names of all the quizzes by taking them in from the quizes_file

    int quiz_iterator = 0; // iterator variable was already declared above in this function
    if (quizes_file.fail()) {
        cerr << "File quizes.dat not found / could not be opened.\n";
    }
    else {
        while (quizes_file.peek() != EOF) {
            getline(quizes_file, quizzes[iterator], '\n');
            quiz_iterator++;
        }
    }

    // now we have the record of all the quizzes and assignments present in the course folder and assignments.dat , quizes.dat files
    cout << "\nPreviously made assignments are :\n[ ";

    for (int j = 0; j < ass_iterator; j++) {
        cout << assignments[j] << " ";
    }
    cout << " ]\n";

    cout << "Previously made quizzes are :\n[ ";

    for (int j = 0; j < quiz_iterator; j++) {
        cout << quizzes[j] << " ";
    }
    cout << " ]\n\n";

    string          choice;
    string          nameOfComponent; // name of the component (assignment / quiz) - this name will be used later to make the path of the file to be opened
    
    do {
        cout << "What do you see the result of?\n"
            << "[1] - Assignment\n"
            << "[2] - Quiz\n"
			<< "[3] - FinalExam\n";
        cin >> choice;
        
        if (choice == "1") {
            cout << "Select an assignment from the available options to see its result.\n";
            cin >> nameOfComponent;
            bool check = 0;
            for (int i = 0; i < ass_iterator+1; i++) {
                if (nameOfComponent == assignments[i]) { // to check if the entered value is present in the choices
                    check = 1; 
                }
            }
            if (!check) {
                cout << "Please enter an option from the given choices.\n";
                continue;
            }
            break;
        }
        else if (choice == "2") {
            cout << "Select an quiz from the available options to see its result.\n";
            cin >> nameOfComponent;
            bool check = 0;
            for (int i = 0; i < quiz_iterator+1; i++) {
                if (nameOfComponent == quizzes[i]) { // to check if the entered value is present in the choices
                    check = 1; 
                }
            }
            if (!check) {
                cout << "Please enter an option from the given choices.\n";
                continue;
            }
            break;
        }
		else if (choice == "3") {
			nameOfComponent="finalexam";
            break;
        }
        else {
            cout << "Please enter a valid input from the given choices.\n";
        }
    } while(1);
    // closing the files
    assignments_file.close();
    quizes_file.close();

    // now creating the path for the quiz / assignment file to be opened
    string          componentFilePath = "./data/" + program + "/" + section + "/" + course + "/" + nameOfComponent + ".dat";
    ifstream        componentFile(componentFilePath.c_str());  // this is the file from which we will take input to visualize the result card
    string          cmsIDs[60];  // creating arrays to store the information from the file
    string          names[60];
    string          givenMarks[60];
    string          grades[60];
    int             percentages[60];
    string          maxMarks[60];

    int result_iterator = 0;
    while (componentFile.peek() != EOF) {
        getline(componentFile, cmsIDs[result_iterator], ',');
        getline(componentFile, names[result_iterator], ',');
        getline(componentFile, maxMarks[result_iterator], ',');
        getline(componentFile, givenMarks[result_iterator], '\n');
		result_iterator++;
    }

    stringstream    maxMarksStream(maxMarks[0]);
    int             maxMarks_int;
    int             givenMarks_int;  // to be used in the loop when calculating the grades and percentage
    int             percentage;  // to be used in the loop when calculating the grades and percentage
    maxMarksStream >> maxMarks_int;

    // calculating the grades and percentages and storing in the arrays
    for (int x = 0; x < result_iterator; x++) {
        stringstream givenMarksStream(givenMarks[x]);
        givenMarksStream >> givenMarks_int;
        percentage = ((double(givenMarks_int) / double(maxMarks_int)) * 100.0);
        percentages[x] = percentage;
        // Grades -->  (A (>85) B+(75-85) B(65-75) C+(55-65) C(45-55) F(<45))
        if (percentage > 85.0) {  // A grade
            grades[x] = "A";
        }
        else if ((percentage < 85.0) && (percentage >= 75.0)) {  // B+ grade
            grades[x] = "B+";
        }
        else if ((percentage < 75.0) && (percentage >= 65.0)) {  // B grade
            grades[x] = "B";
        }
        else if ((percentage < 65.0) && (percentage >= 55.0)) {   // C+ grade
            grades[x] = "C+";
        }
        else if ((percentage < 55.0) && (percentage >= 45.0)) {   // C grade
            grades[x] = "C";
        }
        else {   // F grade
            grades[x] = "F";
        }
    }

    cout << "CMS IDs" <<"\t\t"<< "NAMES" << "\t\t\t\t" << "OBTAINED MARKS" << "\t\t" << "MAX MARKS" << "\t\t" << "PERCENTAGE" << "\t\t" << "GRADE\n";
    for (int x = 0; x < result_iterator; x++) {
        cout << cmsIDs[x]<<"\t\t";
		cout.width(30);
        cout << std::left << names[x] <<"\t\t"<< givenMarks[x] << "\t\t   " << maxMarks[x] << "\t\t\t   " << percentages[x] << "%\t\t\t  " << grades[x] << "\n";
    }
	cin.get();

}