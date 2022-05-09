//==== libs ====//
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//==== Extra Functions ====//
int convertStrToInt(string input){
    int tempi = 0;
    stringstream temps(input);
    temps >> tempi;
    return tempi;
}

void eraseSubStr(string &mainStr, const string &toErase)
{
    // Search for the substring in string
    size_t pos = mainStr.find(toErase);
    if (pos != string::npos)
    {
        // If found then erase it from string
        mainStr.erase(pos, toErase.length());
    }
}