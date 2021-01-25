CMS_Console_App
All the code of the project is present here. It contains five different classes made in separate header and source files. To start running the project, first you will need the "data" folder becuase that folder has all the information required within the program, including the sign-in info of the users. For the first run of the program, the user will need the files containing the sign in info, so the three files namely "Students.dat" , "Teachers.dat" and "admins.dat" must be present in the "data" folder so that the user may sign in without any problem.

To build the program, if you are using the GCC MinGW compiler, run the following command to get an output executable of name "main.exe".

g++ main.cpp customFunctions.cpp signIn.cpp admin.cpp student.cpp teacher.cpp -o main

To run the program, simply open the executable file in the console.

If you are using Microsoft Visual Studio C++, then you will need to create 5 new classes. The names of the classes and the files can be seen from the code presented here. To run the project, go to Debug menu and select Start without Debugging option.
The default CMS ID of the Admin is : 770169 and this cannot be altered or change until and unless edited manually by opening the admin sign in record.
