// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student{
public:
    Student(string firstName, string lastName): // constructor for args
        firstName_(firstName), lastName_(lastName) {}
    
    Student(Student && org):  // move constructor, not really needed, generated automatically
        firstName_(move(org.firstName_)),
        lastName_(move(org.lastName_))
    {}
    
    Student(const Student & org) = default; // force generation of default copy constructor
    
    string print() const { // print function
        string str = firstName_ + " " + lastName_ + ":"; // format string with last and first names

        for(const auto course: courses_) // add courses to str
            str += course + " ";

        return str + '\n'; // return str
    }

    void addCourse(string course) { // add course func
        courses_.push_back(course); // adds course to course vector
    }

    friend bool operator== (Student left, Student right){ // needed for unique() and for remove()
        return left.lastName_ == right.lastName_ &&
            left.firstName_ == right.firstName_;
    }

    friend bool operator< (Student left, Student right){ // needed for sort()
        return left.firstName_ < right.firstName_ ||
            (left.firstName_ == right.firstName_ && 
            left.lastName_ < right.lastName_);
    }
    
private:
   string firstName_;
   string lastName_;
   vector<string> courses_;
};


