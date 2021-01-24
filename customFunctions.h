#ifndef CUSTOMFUNCS
#define CUSTOMFUNCS
#include <string>

/*
 * ALL THE CUSTOM DEFINED FUNCTIONS
 * GO HERE SO THAT THEY CAN BE USED
 * ACROSS ALL THE FILES WHERE EVER
 * THEY ARE WANTED.
 */

int get_int(int min, std::string prompt);
bool valid_int(std::string theInput);
std::string validatestrings(std::string str);
void clear_screen(void);
int _mkdir(const std::string path);

#endif