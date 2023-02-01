// Author:      Alex Ely
// Date:        10/26/2022
// Project:     Lab 8
// Description: Logger class using singleton design header file

#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::ofstream;
using std::cout;

class Logger { // logger singleton class
public:
    static Logger& instance() { 
        static Logger l;
        return l;
    }

    void report(const string &s) { // appends s to out_ file
        cout << "======Report called with s = \"" << s << "\"======" << '\n';
        out_ << s << '\n';
    }
private:
    Logger() { // creates output file for appending
        cout << "======Logger default constructor called======\n\n"; 
        out_.open("test.txt", std::fstream::out | std::fstream::app);
    }
    ~Logger() { cout << "======Logger destructor called======\n\n"; out_.close(); } // closes output file
    Logger(const Logger&) = delete; // preventing copy and assignment
    Logger& operator=(const Logger&) = delete;

    ofstream out_; // output file variable
};