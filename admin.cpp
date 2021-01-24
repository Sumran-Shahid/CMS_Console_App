#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <filesystem>
#include <stdio.h>

#include "customFunctions.h"
#include "admin.h"

using namespace std;


// menu function starts here============================================================================================
void Admin::menu(void) {
    string  choice_str;
	int choice;
	cout << "What action do you want to perform?\n"
		<< "[1] - Create a Degree Program.\n"
		<< "[2] - View available Degree Programs.\n"
		<< "[3] - Create a course.\n"
		<< "[4] - View available Courses.\n"
		<< "[5] - Assign Teachers to courses\n"
		<< "[6] - Enroll new students to courses and sections\n"
		<< "[7] - Exit Program.\n"
		<< "--> ";
	getline(cin, choice_str);
	cout << endl;
	if (valid_int(choice_str)) {
		stringstream choicestream(choice_str);
		choicestream >> choice;
	}
	else {
		clear_screen();
		cout << "Please give a valid input from the given choices.\n\n";
		menu();
	}

	switch (choice) {
	case 1:
		newProgram();
		break;
	case 2:
		viewPrograms();
		break;
	case 3:
		newCourse();
		break;
	case 4:
		viewCourses();
		break;
	case 5:
		assignTeachers();
		break;
	case 6:
		enrollStudents();
		break;
	case 7:
		exit(1);
		break;
	default:
		clear_screen();
		cout << "Please give a valid input from the given choices.\n\n";
		menu();
	}
}  // menu function ends here


// newProgram function starts here============================================================================================
void Admin::newProgram() {
	string shortForm, programID_str, program_entered, parent= "./data/"; //parent directory for folder

	_mkdir("./data");

	cin.clear();
	cout<<"Enter degree program:"<<endl;
	getline(cin, program_entered);
	cout << "Short form for the program name :\n";
	getline(cin, shortForm);
	cout << "Enter 3-digit degree program code :" << endl;
	do {

		getline(cin,programID_str);
		if(programID_str.size() != 3) { // this loop keeps taking input from the user until he enters a 3 digit number
			cout << "Please enter a 3-digit degree program code.\n";//restriction on course id...
			continue;
		}
		// now this part is to check if the entered code already exists or not
		string check_course_id, check_course_name;
		ifstream courses("./data/Programs.csv");
		if (courses.fail())
			cout << "Failed to open Program.csv file.\n";

		bool check = false;
		if(!courses.fail()) {
			while(getline(courses,check_course_id,',') && getline(courses,check_course_name,'\n')) {
				if (programID_str == check_course_id) {
					check = true;
				}
			}

			if (check) {
				cout<<"This degree program already exists.Enter a different course ID."<<endl;
				continue;
			}

			else {
				ofstream programs("./data/Programs.csv",ios::app);
				programs << programID_str <<','<<shortForm<<','<<program_entered<<endl;//writing of new course in append mode
				cout << "The new degree program has been created." << endl;
				break;
				courses.close();
			}
		}
	} while(1);
	string p = parent + program_entered;

	if (_mkdir(p.c_str()) != 0) {
		cerr<<"Failed to create program directory."<<endl;  // failsafe in case folder is not created 
	}
	string l,h,ref;
	int n;
	cout << "Enter the number of sections you wish to create(1-3)" << endl;

	do {
		cin >> n;
		if( n < 1 || n > 3) {
			cout<<"Please enter upto 3 sections..."<<endl;
			cin.clear();
			cin.ignore();
		}
		else {
			break;
		}
	} while(true);

	for(int j=n;j>=1;j--) {	 //loop for section input
		l = p;
		cout << "Enter name of section..." << endl;
		cin >> ref;	
		string secdir=p+"/Sectionlist.csv";
		ofstream sectionrecord(secdir.c_str(),ios::app);//file for section record
		sectionrecord<<ref<<endl;
				h = "Section " + ref;
		l = p + "/" + ref;  //directory for sections stored in string
		_mkdir(l.c_str());  //c.str converts strings into char based readable format
		string courses="./data/"+program_entered+"/Courses.csv";
		ifstream cor("./data/Courses.csv");//cor==courses for reading
		if(cor.good())
		{   string course_id1; //variable for getline
		string course_name1; //variable for getline
		string course_id[10];
		string course_name[10];
		int i=0;

		while(!(cor.eof()))
		{
			getline(cor,course_name1,',');
			getline(cor,course_id1,'\n');
			course_id[i]=course_id1;
			course_name[i]=course_name1;
			i++;
		}
		for(int k=0;k<i;k++)
		{
			string f=l+"/"+course_id[k];
			_mkdir(f.c_str());
			string q=f+"/quizes.csv";//for quizes
			string a=f+"/assignments.csv";//for assignments
			ofstream quiz(q.c_str());
			ofstream assign(a.c_str());
		} // newProgram function ends here
		}
		cor.close();
	}
} // newProgram function ends here


// vewPrograms function starts here============================================================================================
void Admin::viewPrograms(void){
	ifstream programs("./data/Programs.csv");
	string courseIDs[30], shortForms[30], courseNames[30];
	if (!programs.fail()) {
		int iterator = 0;
		while (!programs.eof()) {
			getline(programs, courseIDs[iterator], ',');
			getline(programs, shortForms[iterator], ',');
			getline(programs, courseNames[iterator], '\n');
			iterator++;
		}
		cout << "\n" << "Course IDs\tShort Forms\tName of Course\n";
		for (int i = 0; i < iterator; i++) {
			cout << courseIDs[i] << "\t\t" << shortForms[i] << "\t\t" << courseNames[i] << endl;
		}
	}
	programs.close();
} // viewCourses function ends here


// newCourse function starts here============================================================================================
void Admin::newCourse(void) {
	std::string courseID_str, course_entered,program_entered;//declaring variables
	cout<<"Please enter the name of the degree program for new course"<<endl;//input for degree name
	ifstream programs("./data/Programs.csv");//reading of program file
	string courseIDs[30], shortForms[30], courseNames[30];
	if (!programs.fail()) {
		int iterator = 0;
		while (!programs.eof()) {
			getline(programs, courseIDs[iterator], ',');
			getline(programs, shortForms[iterator], ',');
			getline(programs, courseNames[iterator], '\n');//storing data in array
			iterator++;}
		bool chk=false;
		do
		{getline(cin,program_entered);
		for(int i=0;i<iterator;i++)
		{if(program_entered==courseNames[i])
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
		}while(1);//degree program validation loop
	}//verification of degree program
	cout<<"Enter the name of new course:"<<endl;//name of course
	getline(cin, course_entered);
	string course_dir="./data/"+program_entered+"/Courses.csv";
	ofstream newcourse(course_dir.c_str(),ios::app);//for creating a course.csv file for courses
	cout << "Enter 4-digit course code :" << endl;
	do {
		getline(cin, courseID_str);
		if (courseID_str.size() != 4) { // this loop keeps taking input from the user until he enters a 4 digit number
			cout << "Please enter a 4-digit course code.\n";//restriction on course id...
			continue;

		}

		// now this part is to check if the entered code already exists or not
		string check_course_id, check_course_name;
		ifstream courses(course_dir.c_str());
		if (courses.fail())
			cout << "Failed to open Course.csv file.\n";

		bool check = false;
		if(!courses.fail()) {
			while(getline(courses,check_course_id,',') && getline(courses,check_course_name,'\n')) {
				if (courseID_str == check_course_id) {
					check = true;
				}
			}

			if (check) {
				cout<<"This course already exists.Enter a different course ID."<<endl;
				continue;
			}

			else {
				string coursedirectory="./data/"+program_entered+"/"+"Courses.csv";
				ofstream programs(coursedirectory.c_str(), ios::app);//specific record of courses
				ofstream generalcourses("./data/Courses.csv",ios::app);//general record of courses
				programs << courseID_str <<','<< course_entered << endl;//writing of new course in append mode
				generalcourses<< courseID_str <<','<< course_entered << endl;
				cout << "The new course has been created." << endl;
				programs.close();
				generalcourses.close();
				break;
			}
		}
	} while(1);//course id validation loop
	string sectiondir="./data/"+program_entered+"/Sectionlist.csv";//directory of section list
	string secname[3];//array for sections
	ifstream sectionlist(sectiondir.c_str());//reading section file of the degree programme
	int iterator=0;
	if(sectionlist.fail())
		cerr<<"File couldnt be opened"<<endl;
	else
		while(sectionlist.peek()!=EOF){//reading name of sections and storing in section array
		getline(sectionlist,secname[iterator],'\n');
		iterator++;
	}
	for(int i=0;i<iterator;i++)//loop for running the section array
	{
		string newdir="./data/"+program_entered+"/"+secname[i]+"/"+course_entered;//directory for new course in each section
		_mkdir(newdir.c_str());//make directory function
		string quizdir=newdir+"/quizes.csv";//directory for respective quizes
		string assigndir=newdir+"/assignments.csv";//directory for respective assignments
		ofstream quizes(quizdir.c_str(),ios::app);//creating a file of quizes.csv
		ofstream assignments(assigndir.c_str(),ios::app);//creating an assignment file
	}
} // newCourses func ends here


// viewCourses function starts here============================================================================================
void Admin::viewCourses(void) {
	string program_entered;
	cout<<"Please enter the name of the degree program whose courses u wish to view:"<<endl;//input for degree name
	ifstream programs("./data/Programs.csv");//reading of program file
	string courseIDs[30], shortForms[30], courseNames[30];
	if (!programs.fail()) {
		int iterator = 0;
		while (!programs.eof()) {
			getline(programs, courseIDs[iterator], ',');
			getline(programs, shortForms[iterator], ',');
			getline(programs, courseNames[iterator], '\n');//storing data in array
			iterator++;}
		bool chk=false;
		do
		{getline(cin,program_entered);
		for(int i=0;i<iterator;i++)
		{if(program_entered==courseNames[i])
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
		}while(1);//degree program validation loop
		string course_id,course_name;
		string course_dir="./data/"+program_entered+"/Courses.csv";
		ifstream courses(course_dir.c_str());
		cout << "Course ID\tCourse name\n";
		if(!courses.fail()) {
			while(getline(courses,course_id,',')&&getline(courses,course_name,'\n'))
				cout << course_id << "\t\t" << course_name << endl;
			cout << endl;
		}
	}
} // viewCourses func ends here


// assign teacher function==================================================================================
void Admin::assignTeachers(){
	ofstream teachers("./data/Teachers.csv",ios::app);
	if(teachers.fail())
		cerr<<"File could not be opened."<<endl;
string cms_id,name,course_entered;
cout<<"Please enter the teacher's 6-digit cms id:\n";
do {
		getline(cin,cms_id);
		if (cms_id.size()!= 6) // this loop keeps taking input from the user until he enters a 4 digit number
			{cout << "Please enter a 6-digit course code.\n";//restriction on course id...
			continue;}
		else 
			break;

		}
		while(1);
cout<<"Please enter the teacher's name:\n";
getline(cin,name);
cout<<"Please enter the teacher's subject/course:\n";
	cout<<"Please enter the name of the course/subject u wish to assign"<<endl;//input for degree name
	ifstream programs("./data/Courses.csv");//reading of program file
	string courseIDs[30],courseNames[30];
	if (!programs.fail()) {
		int iterator = 0;
		while (programs.peek()!=EOF) {
			getline(programs, courseIDs[iterator], ',');
			getline(programs, courseNames[iterator], '\n');//storing data in array
			iterator++;}
		bool chk=false;
		do
		{getline(cin,course_entered);
		for(int i=0;i<iterator;i++)
		{if(course_entered==courseNames[i])
		{chk=true;
		break;}
		else
			continue;
		}
		if(chk)
			break;
		else
		{cout<<"Please enter an existing course"<<endl;
		continue;
		}
		}while(1);//course validation loop
teachers<<cms_id<<","<<name<<","<<course_entered<<"\n";//writing to teachers record...
teachers.close();
}
}


// assign student function==================================================================================
void Admin::enrollStudents(){
	string name,cms_id,degreeprogram,section,program_entered;
	cout<<"Please enter the name of the new student"<<endl;
	getline(cin,name);
	cout<<"Please enter the 6 digit cms_id of the studnet"<<endl;
	do {
		getline(cin,cms_id);
		if (cms_id.size()!= 6) // this loop keeps taking input from the user until he enters a 4 digit number
			{cout << "Please enter a 6-digit course code.\n";//restriction on course id...
			continue;}
		else 
			break;

		}
		while(1);//6 digit cms validation

	cout<<"Please enter the name of degree program of student:"<<endl;
	ifstream programs("./data/Programs.csv");//reading of program file
	string courseIDs[30],courseNames[30],Shortforms[30];
	if (!programs.fail()) {
		int iterator = 0;
		while (programs.peek()!=EOF) {
			getline(programs, courseIDs[iterator], ',');
			getline(programs, Shortforms[iterator], ',');
            getline(programs, courseNames[iterator], '\n');//storing data in array
			iterator++;}
		bool chk=false;
		do
		{getline(cin,program_entered);
		for(int i=0;i<iterator;i++)
		{if(program_entered==courseNames[i])
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
        programs.close();
		string sectiondir="./data/"+program_entered+"/Sectionlist.csv";
		string secname[3];
		ifstream sections(sectiondir.c_str());
		iterator=0;
		if(sections.fail()) {
			cerr<<"File Sectionlist.csv in program folder couldnt be opened"<<endl;
		}
		else {
			while(sections.peek()!=EOF){//reading name of sections and storing in section array
				getline(sections,secname[iterator],'\n');
				iterator++;
			}
			
			cout<<"Enter name of section from the given options"<<"(";
			for(int i=0;i<iterator;i++)
				cout<<secname[i]<<" ";
			
			cout<<")"<<endl;
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
			cout<<"The student "<<name<<" has been successfully enrolled"<<endl;
			//writing to students general record
			ofstream studentrecord("./data/Students.csv",ios::app);//for keeping general record of students
			studentrecord<<cms_id<<","<<name<<","<<program_entered<<","<<section << endl;
			studentrecord.close();
			string sectionStudentsRecordPath = "./data/" + program_entered + "/" + section + "/students.csv";
			ofstream sectionstudents(sectionStudentsRecordPath.c_str());
			sectionstudents << cms_id << "," << name << "," << program_entered << endl;

			//retreiving course name from course.csv in degree program
			
			string c_id[20],c_name[20];
			string coursedir="./data/"+program_entered+"/Courses.csv";
			ifstream courses(coursedir.c_str());
			if(courses.fail())
				cerr<<"File courses.csv could not be opened"<<endl;
			iterator=0;
			while(courses.peek()!=EOF)
			{
				getline(courses,c_id[iterator],',');
				getline(courses,c_name[iterator],'\n');
				iterator++;
			} // retrieving name of courses
			for(int i=0;i<iterator;i++)
			{
				string studentdir1="./data/"+program_entered+"/"+section+"/"+c_name[i]+"/assignments.csv";//path for assignment and quizes file
				string studentdir2="./data/"+program_entered+"/"+section+"/"+c_name[i]+"/quizes.csv";
				ofstream eia(studentdir1.c_str());//eia=entry in assignments.csv
				eia<<cms_id<<","<<name<<"\n";
				eia.close();
				ofstream eiq(studentdir2.c_str());//eiq=entry in quizes.csv
				eiq<<cms_id<<","<<name<<"\n";
				eiq.close();
			}
		}
	}
}