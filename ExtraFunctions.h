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
    ifstream file1, file2;

    file1.open(fileName1.c_str(), ios::binary | ios::ate);
    file2.open(fileName2.c_str(), ios::binary | ios::ate);

    if (file1.fail() || file2.fail()){
        return false; // one of the files couldn't be opened
    }
    else if (file1.tellg() != file2.tellg()){
        return false; // file sizes doesn't match
    }

    bool evaluate = true;

    char fileChar1;
    char fileChar2;

    while (evaluate){
        fileChar1 = file1.get();
        fileChar2 = file2.get();

        if (fileChar1 != fileChar2){
            cout << "files are different" << endl;
            return false;
        }
        if (fileChar1 == EOF || fileChar2 == EOF){
            evaluate = false;
        }
    }
    return true;
}