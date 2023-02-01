// Author:      Alex Ely
// Date:        09/13/2022
// Project:     Lab 2
// Description: Creates list of unqique alphanumerical words in input file and outputs words by occurrence count from lowest to highest.


#include <iostream>
#include <fstream>
#include <string>
#include "WordList.hpp" // class definitions

using std::string;
using std::cout;
using std::ifstream;

WordList readFile(ifstream &); // reads input file
bool validateFile(const ifstream&, const int&); // validates input file

int main(int argc, char *argv[]) { // main function, takes command line arguments
    ifstream file; // declaring input file

    file.open(argv[1]); // opens input file using command line argument

    if(!validateFile(file, argc)) // checks if input file is valid
        return 1;

    WordList list = readFile(file); // returns WordList created from input file

    list.print(); // prints WordList

    file.close(); // closes input file

    return 0; // exits main()
}

WordList readFile(ifstream &file) { // takes ifstream, converts each valid word to WordOccurrence, makes WordList
    WordList list; // declaring new WordList obj
    
    char c; // declaring character for file reading
    string word = ""; // empty string for file reading
    bool alphaNum = false; // determines if alphanumerical character has previously been read

    while(file.get(c)) { // loops through every character in input file
        if(isalnum(c)) { // checks if character is alphanumeric
            word += c; // adds alphanumeric character to string
            alphaNum = true; // true since alphanumeric character has been read
        }
        else if (alphaNum) { // checks if alphanumeric character was found before non-alphanumeric character
            list.addWord(word); // adds string to WordList obj as WordOccurrence
            alphaNum = false; // sets to false since non-alphanumeric found
            word = ""; // empties string for new word
        }
    }

    return list; // returns WordList obj created
}

bool validateFile(const ifstream &file, const int &argc) { // checks if filename exists or if # of arguments is correct
    if(argc != 2) { // if # of arguments incorrect, print error
        cout << "File name parameter required.\n" << "./output [filename.txt]\n"; // outputs command line requirements
        return false; // returns false for invalid arguments
    } else if(!file.is_open()) { // if file is not open, print error
        cout << "Opening file failed.\n"; // outputs to user that file was not opened
        return false; // returns false for invalid file
    }

    return true; // returns true if no errors found
}