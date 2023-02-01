// Author:      Alex Ely
// Date:        09/13/2022
// Project:     Lab 2
// Description: Defines WordOccurrence and WordList classes plus related functions

#include <string>
#include <iostream>
#include <algorithm>

using std::string;
using std::cout;
using std::sort;


class WordOccurrence {
public:
    WordOccurrence(const string& word="", int num=0); // default constructor
    bool matchWord(const string &); // returns true if word matches stored
    void increment(); // increments number of occurrences
    string getWord() const; // returns string value of word_
    int getNum() const; // returns int value of num_

private:
    string word_; // holds string value of word
    int num_; // holds number of occurrences
};

class WordList{
public:
    // add copy constructor, destructor, overloaded assignment
    WordList() { size_ = 0; wordArray_ = new WordOccurrence[size_]; } // default constructor
    ~ WordList() { delete[] wordArray_; } // destructor releases dynamic array memory
    WordList(const WordList &); // copy constructor
    WordList operator=(WordList); // overloaded assignment

    // implement comparison as friend
    friend bool equal(const WordList&, const WordList&); // compares two WordLists, returns true or false

    void addWord(const string &); // adds string to WordList as WordOccurrence
    void print(); // prints all WordOccurrence string values in WordList

private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_; // int size of wordArray_
};

bool sortWords(const WordOccurrence &, const WordOccurrence &); // compares two WordOccurrences

WordOccurrence::WordOccurrence(const string &word, int num) {
    word_ = word; // assigns string to WordOccurrence.word_
    num_ = num; /// assigns int to WordOccurrence.num_
}

bool WordOccurrence::matchWord(const string &word) {
    return word_ == word; // returns true if strings are equal, false if not
}

void WordOccurrence::increment() {
    num_++; // increments num_ value by 1
}

string WordOccurrence::getWord() const {
    return word_; // returns the string value of word_
}

int WordOccurrence::getNum() const {
    return num_; // returns the int value of num_
}

bool equal(const WordList &list1, const WordList &list2) {
    if(list1.size_ == list2.size_) { // checks if size_ values are same, returns false if not
        for(int i = 0; i < list1.size_; i++) { // increments through every value in wordArray_ for WordLists
            if(!list1.wordArray_[i].matchWord(list2.wordArray_[i].getWord())) // checks if matchWord() for each WordOccurrence in wordArray_ is false and returns if so
                return false;
        }

        return true; // returns true if matchWord() is never false for all WordOccurrences in both WordLists
    } else {
        return false;
    }
}

WordList::WordList(const WordList &rhs) {
    size_ = rhs.size_; // asigns size to rhs size

    wordArray_ = new WordOccurrence[size_]; // allocates new empty WordOccurrence array of with size of rhs array

    for(int i = 0; i < size_; i++) { // loops through every WordOccurrence obj in rhs array
        wordArray_[i] = rhs.wordArray_[i]; // assigns rhs array values to same index in current wordArray_
    }
}

WordList WordList::operator=(WordList rhs) {
    if(equal(*this, rhs)) // returns itself if objects are the same
        return *this; 

    delete[] wordArray_; // deallocated current wordArray_ memory
    
    size_ = rhs.size_; // sets size_ to new rhs.size_
    wordArray_ = new WordOccurrence[size_]; // allocates new empty WordOccurrence array of with size of rhs array

    for(int i = 0; i < size_; i++) // loops through every WordOccurrence obj in rhs array
        wordArray_[i] = rhs.wordArray_[i]; // assigns rhs array values to same index in current wordArray_

    return *this; // returns newly assigned obj
}

void WordList::addWord(const string &str) {
    for(int i = 0; i < size_; i++) { // loops through all WordOccurrences in wordArray_
        if(wordArray_[i].matchWord(str)) { // if str matches WordOccurrence.word_ in wordArray_, increment WordOccurrence.num_ and exit function
            wordArray_[i].increment();
            return;
        }
    }

    size_++; // increments size_ by 1
    WordOccurrence* tempArray = new WordOccurrence[size_]; // allocates temp WordOccurrence array of size_

    for(int i = 0; i < size_ - 1; i++) { // loops through all values of wordArray_
        tempArray[i] = wordArray_[i]; // assigns each index of tempArray to wordArray_ leaving last index untouched
    }

    tempArray[size_ - 1] = WordOccurrence(str, 1); // assigns last index of tempArray to WordOccurence with value of string being added

    delete[] wordArray_; // deallocates current wordArray_
    
    wordArray_ = tempArray; // assigns wordArray_ to tempArray_
}

void WordList::print() {
    sort(wordArray_, wordArray_ + size_, sortWords); // sorts all WordOccurrences in wordArray_ by num_

    cout << "[occurrences, word]\n"; // outputs formatting explanation

    for(int i = 0; i < size_; i++) { // loops through all WordOccurrences in wordArray_
        cout << "[" << wordArray_[i].getNum() << " | " << wordArray_[i].getWord() << "]\n"; // outputs [WordOccurrence.num_ | WordOccurrence.word_]
    }
}

bool sortWords(const WordOccurrence &w1, const WordOccurrence &w2) { // compares WordOccurrence.num_ of two obj, returns rarest of the 2
    return w1.getNum() < w2.getNum();
}