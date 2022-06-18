//==== libs ====//
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//==== Extra Functions ====//

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