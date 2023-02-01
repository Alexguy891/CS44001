// Author:      Alex Ely
// Date:        09/21/2022
// Project:     Lab 3
// Description: Template class for singly linked list object called Collection

#include "list.hpp"
#include <iostream>

#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

using std::cout;

template <typename T> // forward class decl
class Collection;

template <typename T> // forward func decl
bool equal(const Collection<T>&, const Collection<T>&);

template <typename T> // template class
class Collection {
    public:
        Collection() { head = nullptr; } // default constructor
        void add(const T &); // adds node with data of type T to Collection
        void remove(const T&); // removes all instances of nodes with value of data matching in Collection
        T last(); // returns previously added item in Collection
        void print(); // prints all node datas in Collection
        friend bool equal<T>(const Collection&, const Collection&); // determines if all nodes have matching data in Collection
    private:
        node<T> *head; // pointer to head of Collection
};

template <typename T>
void Collection<T>::add(const T &data) { // takes data by reference
    node<T> *temp = new node<T>; // creates new temp node
    temp->setData(data); // sets temp node data to input
    temp->setNext(nullptr); // sets temp->next = nullptr

    if(head == nullptr) { // checks if Collection is empty
        head = temp; // assigns head to temp
    }
    else { // if Collection not empty
        temp->setNext(head); // set temp->next to current head
        head = temp; // set head to temp
    }
}

template <typename T>
void Collection<T>::remove(const T &data) { // takes data by reference
    if(head == nullptr) // if Collection empty, exit func
        return;

    if(head->getData() == data) { // if head->data is data to be removed
        head = head->getNext(); // set head to its next node
    }

    node<T> *temp = head; // new temp node initialized to head
    node<T> *prev = temp; // new node holds previous node before found data node


    while(temp != nullptr) { // loop through all nodes until nullptr
        if(temp->getData() == data) // if node contains same data
            prev->setNext(temp->getNext()); // set prev->next to node after found node
        else // if node does not contain same data
            prev = temp; // set prev to current node
        temp = temp->getNext(); // move current node to next node
    }
}

template <typename T>
T Collection<T>::last() {
    return head->getData(); // returns data of type T that was last added to collection
}

template <typename T>
void Collection<T>::print() { // prints all node data in Collection
    node<T> *temp = head; // temp node for loop

    while(temp != nullptr) { // loop through all nodes until nullptr
        cout << temp->getData() << " -> "; // print node data and formatting

        temp = temp->getNext(); // move current node to next node
    }

    cout << "nullptr\n"; // shows end of Collection that points to nullptr
}

template <typename T>
bool equal(const Collection<T> &c1, const Collection<T> &c2) { // takes two Collections by reference
    if(c1.head == c2.head) // checks if head pointers point to same address
        return true; // returns true, comparing collection to itself

    node<T> *temp1 = c1.head; // temp pointer for loop
    node<T> *temp2 = c2.head; // temp pointer for loop

    while(temp1 != nullptr && temp2 != nullptr) { // loop through both Collections until nullptr
        if(temp1->getData() != temp2->getData()) // if any node data is not equal
            return false; // return Collections are not equal
        
        temp1 = temp1->getNext(); // move temp pointer to next node
        temp2 = temp2->getNext(); // move temp pointer to next node
    }

    if(temp1 != nullptr || temp2 != nullptr) // if either Collection was not fully iterated
        return false; // return false, Collections not same length

    return true; // return true if no issues found
}

#endif // COLLECTION_HPP_