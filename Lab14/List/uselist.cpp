// Author:      Alex Ely
// Date:        12/9/2022
// Project:     Lab 14
// Description: Node smart pointer demonstration

#include <iostream>
#include <memory>
#include "list.hpp" // list template

using std::cout; using std::endl;
using std::shared_ptr; using std::weak_ptr; using std::make_shared;

int main(){
   // 
   // integer list manipulation
   // 

   // first node
   shared_ptr<node<int>>head = make_shared<node<int>>();
   head->setData(1);


   shared_ptr<node<int>> currentPtr = make_shared<node<int>>();
   currentPtr->setData(2);

   head->setNext(currentPtr); // list contains two nodes

   cout << head->getData() << " "; // printing head node

   // deallocating head node
   currentPtr = head;
   head = head->getNext();
   currentPtr.reset();

   // printing the last element and deallocating
   cout << head->getData() << endl;
   head.reset();


   // 
   // character list manipulation
   // 
   
   // allocating head node
   shared_ptr<node<char>> charHead = make_shared<node<char>>();
   shared_ptr<node<char>> current = charHead;
   current->setData('A');

   // creating list
   for(char letter = 'B'; letter <= 'Z'; ++letter){
      shared_ptr<node<char>> newNode = make_shared<node<char>>();
      newNode->setData(letter);
      current->setNext(newNode);
      current = newNode;
   }


   for(current = charHead;  current != nullptr; current = current->getNext())
      cout << current->getData() << ' ';
   cout << endl;
}