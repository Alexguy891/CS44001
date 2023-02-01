// Author:      Alex Ely
// Date:        10/12/2022
// Project:     Lab 6
// Description: Uses STL Container to generate random fruit colors


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <utility>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; } // prints Apple
};

int main(){
   srand(time(nullptr));
   const double minWeight = 8.;
   const double maxWeight = 3.;

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

   // assign random weight and color to apples in the crate
   // replace with generate()
   generate(crate.begin(), crate.end(), [minWeight, maxWeight]() { 
      Apples app = Apples();
      app.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      app.color = rand() % 2 == 1 ? "green" : "red";
      
      return app;
   });


   // for_each() possibly
   cout << "all apples"<< endl;
   for_each(crate.begin(), crate.end(), [](const Apples &app) { app.print(); });
   cout << endl;

   
   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;

   // count_if()
   int cnt = count_if(crate.cbegin(), crate.cend(), [toFind](const Apples &app) { return app.weight > toFind; });
   cout << "There are " << cnt << " apples heavier than " << toFind << " oz" <<  endl;

   // find_if()
   cout << "at positions ";
   vector<Apples>::iterator it = find_if(crate.begin(), crate.end(), [toFind](const Apples &app) { return app.weight > toFind; });
   while(it != crate.end()) {
      cout << it - crate.begin() << ", ";
      it = find_if(it + 1, crate.end(), [toFind](const Apples &app) { return app.weight > toFind; });
   }
   cout << endl;
   cout << endl;


   // max_element()
   double heaviest = max_element(crate.begin(), crate.end(), [](Apples &app1, Apples &app2) { return app1.weight < app2.weight; })->weight;
   cout << "Heaviest apple weighs: " << heaviest << " oz" << endl;
   cout << endl;

   // for_each() or accumulate()
   double sum = accumulate(crate.begin(), crate.end(), 0, [](double sum, Apples &app) { return sum + app.weight; });
   cout << "Total apple weight is: " << sum << " oz" << endl;
   cout << endl;


   // transform();
   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;
   transform(crate.begin(), crate.end(), crate.begin(), [toGrow](Apples &app) { app.weight += toGrow; return app; });
   cout << endl;

   // remove_if()
   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;


   // removing small apples
   // nested loops, replace with a single loop modification idiom
   crate.erase(remove_if(crate.begin(), crate.end(), [minAccept](Apples &app) { return app.weight < minAccept; }), crate.end());
   cout << "removed " << size - crate.size() << " elements" << endl;
   cout << endl;


   // bubble sort, replace with sort()
   sort(crate.begin(), crate.end(), [](Apples &app1, Apples &app2) { return app1.weight < app2.weight; });

   // for_each() possibly
   cout << "sorted remaining apples"<< endl;
   for_each(crate.begin(), crate.end(), [](const Apples &app) { app.print(); });

   return 0;
}
