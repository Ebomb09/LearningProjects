#ifndef INI_H
#define INI_H

#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::fstream;

class INI{

    string FName;
    string* lines;
    int length;

    void Open();
    void FindSection(string Section, int& Pos, int& End);

    public:
        INI(string a);
        ~INI();
        bool Read(string Section, string Key, string& Out);
        bool Write(string Section, string Key, string In);
};

#endif