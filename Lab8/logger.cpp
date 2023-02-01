// Author:      Alex Ely
// Date:        10/26/2022
// Project:     Lab 8
// Description: Logger class using singleton design test file

#include <string>
#include <fstream>
#include <iostream>
#include "logger.hpp"

using std::string;
using std::ifstream; 
using std::cout; using std::cin;

void addUser(); // adds user input to file
void addTest(); // adds test lines to file

int main() {
    auto &log = Logger::instance(); // single instance of Logger
    addUser(); // function to add user input
    addTest(); // function to add test lines
}

void addUser() {
    auto &log = Logger::instance(); // single instance of Logger
    string s = ""; // report string

    cout << "Line to append: "; // take user input
    getline(cin, s);

    log.report(s); // reports user input to file
}

void addTest() {
    auto &log = Logger::instance(); // single instance of Logger

    log.report("Test line 1 from addTest()"); // adding test lines
    log.report("Test line 2 from addTest()");
}