#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "customFunctions.h"

using namespace std;

// This function is used to validate the number input if an ambigous character is entered in the stream instead of a number or a number out of the range
int get_int(int min, string prompt) {
    int ret_integer;
    string str_number;
    while(true) {
        cout << prompt;
        getline(cin, str_number); //get string input
        stringstream convert(str_number); //turns the string into a stream
        //checks for complete conversion to integer and checks for minimum value
        if(convert >> ret_integer && !(convert >> str_number) && ret_integer >= min) { 
            return ret_integer;
        }
        cin.clear(); //just in case an error occurs with cin (eof(), etc)
        cerr << "Input must be a number >= " << min << "\nPlease enter a number from the given choices.\n";
    }
}


// validate int input
bool valid_int(string theInput) {

    while(cin.fail() || cin.eof() || theInput.find_first_not_of("0123456789") != string::npos) {

        return 0;

    }
    return 1;
}
string validatestrings(string str) {
    bool valid;
    do {
        getline(cin,str);
        valid = true;
        for (int i=0; i < str.length() && valid; ++i) {
            if (!(isalpha(static_cast<unsigned char>(str[i])) || isspace(static_cast<unsigned char>(str[i])))) {
                //checks for space and alphabetical input...
                valid = false;
                cout<<"Error!Please enter name correctly"<<endl;
                //for retaking input and breaking out of loop
                validatestrings(str);
			}
        }
    } while (!valid);
	return str;//the returned string is to be used later on... 
}
