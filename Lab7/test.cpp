// Author:      Alex Ely
// Date:        10/24/2022
// Project:     Lab 7
// Description: Implementation of hashmap testing

#include "hashmap.hpp"
#include <string>
#include <cassert>

using std::cin; using std::cout; using std::endl;
using std::string;

// template tests hashmap inserts
template <typename Key, typename Value>
pair<const pair<const Key, Value>*, bool> test_insert(hashmap<Key, Value>& hm, Key key, Value value) {
   cout << "[*] Inserting " << key << ": " << value << "...\n";
   pair<const pair<const Key, Value>*, bool> result = hm.insert(make_pair(key, value));

   return result;
}

// template tests hashmap erases
template <typename Key, typename Value>
pair<const pair<const Key, Value>*, bool> test_erase(hashmap<Key, Value>& hm, Key key) {
   cout << "[*] Erasing " << key << "...\n";
   pair<const pair<const Key, Value>*, bool> result = hm.erase(key);

   return result;
}


int main() {

   //
   // <int, int> hashmap test
   //
   cout << endl << "testing <int, int> hashmap" << endl;
   hashmap<int, int> myHash;
   
   // test inserts
   assert(test_insert(myHash, 4, 40).second == true);
   assert(test_insert(myHash, 6, 60).second == true);
   assert(test_insert(myHash, 6, 70).second == false); // insert with a duplicate key


   // searching map
   // x will have type hashmap<int, int>::value_type*
   auto x = myHash.find(4);
   assert(x->second == 40);


   // test deletes
   auto e1 = test_erase(myHash, 4);
   assert(e1.second == true && e1.first->first == 6 && e1.first->second == 60);
   auto e2 = test_erase(myHash, 6);
   assert(e2.second == true && e2.first == nullptr);
   assert(test_erase(myHash, 7).second == false); // erase non-existent key
   

   //
   // <integer, string> hashmap test
   //
   cout << endl << "testing <int, string> hashmap" << endl;
   hashmap<int, string> employees;
   employees[123] = "Mike";
   employees[345] = "Charlie";
   employees[192] = "Joe";
   employees[752] = "Paul";
   employees[328] = "Peter";
   
   auto ins1 = test_insert<int, string>(employees, 124, "Alex");
   auto ins2 = test_insert<int, string>(employees, 123, "Mike");
   assert(ins1.second == true);
   assert(ins2.second == false);

   // searching map
   auto it = employees.find(123);
   assert(it->second == "Mike");
   auto it2 = employees.find(222);
   assert(it2 == nullptr);

   // removing from a map
   assert(test_erase(employees, 123).second == true);

   //
   // testing rehash
   //
   cout << endl << "testing rehash" << endl;
   employees.rehash(201);

   // testing if hashmap is still correct after rehash
   cout << 123 << ": " << employees[123] << endl;
   assert(employees[123] == "Mike");
   cout << 752 << ": " << employees[752] << endl;
   assert(employees[752] == "Paul");

   // testing insert
   auto ins3 = test_insert<int, string>(employees, 999, "Susan");
   assert(ins3.second == true);
}