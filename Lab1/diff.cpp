// Author:      Alex Ely
// Date:        09/01/2022
// Project:     Lab 1
// Description: Finds differences in lines between 2 text files and outputs lines and position of difference.

#include <string>
#include <iostream>
#include <fstream>

int diffPos(std::string, std::string); // calculates difference in lines position, expects 2 strings, outputs integer 
void outputDiff(std::string, std::string, std::string, std::string, int, bool); // outputs formatted lines, expects 3 strings, integer, boolean

int main(int argc, char* argv[]) {    
    std::ifstream file1; // creating input file variables
    std::ifstream file2;
    
    file1.open(argv[1]); // opening input files using passed arguments
    file2.open(argv[2]);

    int lineNum = 1; // variable for numbering file lines

    while(!file1.eof() || !file2.eof()) { // loops until end of both files has been reached
        std::string str1 = ""; // empties strings for line reads
        std::string str2 = "";

        bool str1Long = false; // used to determine which file has a longer line

        if(!file1.eof()) // reads next line of file if possible
            getline(file1, str1);

        if(!file2.eof()) // reads next line of file if possible
            getline(file2, str2);

        int pos = -1; // used to keep track of position of first difference in lines

        if(str1.length() > str2.length()) { // determines which line is shorter for diffPos input
            str1Long = true;
            
            pos = diffPos(str2, str1);
        } else {
            pos = diffPos(str1, str2);
        }

        std::string colSpc = ": "; // used for output formatting

        std::string outStr1 = argv[1] + colSpc + std::to_string(lineNum) + colSpc + str1; // concats output for easy length reading
        std::string outStr2 = argv[2] + colSpc + std::to_string(lineNum) + colSpc + str2;

        if(pos != -1) // only outputs if difference position found
            outputDiff(outStr1, outStr2, str1, str2, pos, str1Long); // used for line output

        ++lineNum; // incremenets line number counter
    }
}

int diffPos(std::string shortStr, std::string longStr) { // calculates difference in line position
    if(shortStr.empty() && !longStr.empty()) // returns first position if shorter string is empty
        return 0;
    else if(!longStr.empty()){
        for(int i = 0; i < shortStr.length(); i++) { // determines difference in lines if any
            if(shortStr[i] != longStr[i])
                return i;
        }
    }

    if(shortStr.length() != longStr.length())
        return shortStr.length(); // if lengths differ and difference not found, return pos as first position past shortStr
    else
        return -1; // if no difference found and lengths same, return negative position
}

void outputDiff(std::string outStr1, std::string outStr2, std::string str1, std::string str2, int pos, bool str1Long) {
    std::cout << outStr1 << '\n'; // prints both lines
    std::cout << outStr2 << '\n';

    if(str1Long) { // output depends on longest line
        for(int i = 0; i < outStr2.length() - (str2.length() - pos); i++) // creates spaces
            std::cout << ' ';
    } else {
        for(int i = 0; i < outStr1.length() - (str1.length() - pos); i++) // creates spaces
            std::cout << ' ';
    }

    std::cout << "^\n"; // outputs carrot indicator
}