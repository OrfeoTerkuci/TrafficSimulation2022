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

bool compareTwoFilesTXT(const string &fileName1, const string &fileName2){
    ifstream file1(fileName1.c_str(), ios::in |ios::binary | ios::ate);
    ifstream file2(fileName2.c_str(), ios::in |ios::binary | ios::ate);

    if (file1.fail() || file2.fail()){
        file1.close();
        file2.close();
        return false; // one of the files couldn't be opened
    }
    else if (file1.tellg() != file2.tellg()){
        file1.close();
        file2.close();
        return false; // file sizes doesn't match
    }

    char *lin1 = NULL;
    char *lin2 = NULL;

    while (!file1.eof() && !file2.eof()){
        file1.getline(lin1, 1);
        file2.getline(lin2, 1);
        if (*lin1 != *lin2){
            file1.close();
            file2.close();
            return false;
        }
    }

    file1.close();
    file2.close();
    return true;
}