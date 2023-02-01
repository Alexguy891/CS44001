// Author:      Alex Ely
// Date:        10/05/2022
// Project:     Lab 4
// Description: Prints a roster of currently enrolled students

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include "student.hpp"
#include <map>
#include <set>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::list;
using std::move;
using std::string;
using std::vector;
using std::map;
using std::set;

void readRoster(set<Student> &, string); // reading a list from a fileName
string formatStr(string, char c); // formatting strings
void removeDropouts(const set<Student> &, set<Student> &); // removes dropouts
void printRoster(const set<Student> &); // printing a list out

int main(int argc, char *argv[]) { // takes in command line arguments for file names
    if (argc <= 1) { // checks if # of args meets requirements
        cout << "usage: " << argv[0]
             << " list of courses, dropouts last"
             << endl;
        exit(1);
    }

    set<Student> roster; // list of student objs

    for (int i = 1; i < argc - 1; ++i) { // reads from all files in args
        readRoster(roster, argv[i]);
    }

    set<Student> dropouts; // list of student objs for dropouts

    readRoster(dropouts, argv[argc - 1]); // reads from filename in last arg

    removeDropouts(dropouts, roster); // removes dropouts from roster

    cout << "\n\nCurrently Enrolled Students\n"; // prints for formatting

    printRoster(roster); // prints roster after dropouts removed and sorted
}

void readRoster(set<Student> &roster, string fileName) { // reading in a file of names into a list of Students
    ifstream course(fileName); // new ifstream with fileName
    string first, last; // strings to hold first and last names

    while (course >> first >> last) { // loops until end of file
        bool uniqueName = true; // determines if name is unique

        Student student(first, last); // creates new student obj

        for(auto &name: roster) { // loop through all students in roster
            if(name == student) { // if student already exists ignore
                uniqueName = false;
                break;
            }
        }

        if(uniqueName) { // if student does not exist, add student to roster
            roster.insert(student);
        }
    }

    course.close(); // closing file
}

string formatStr(string s, char c) { // substr based on char location
    string::size_type i = s.find(c); // finds location of char

    if(i == string::npos) // if location not found, return string, else substr to location
        return s;
    else
        return s.substr(0, i);
}

void removeDropouts(const set<Student> &dropouts, set<Student> &roster) { // removes dropouts
    for (const auto drop: dropouts) { // loop through all dropout student objs
        for(const auto stud: roster) { // loop through all roster student objs
            if(drop == stud) { // if students match, remove from roster
                roster.erase(stud);
                break;
            }
        }
    }
}

void printRoster(const set<Student> &roster) { // printing list of students
    cout << "firstname lastname: courses enrolled\n"; // prints for formatting
    for (const auto stud: roster) { // loop through all students in roster and print
        cout << stud.print();
        cout << '\n';
    }
}