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
#include <iterator>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using namespace std::placeholders;

struct Peaches{
   double weight; // oz
   bool ripe;  // ripe or not
   void print() const { cout << (ripe ? "ripe" : "green") << ", " <<  weight << endl; }
};

class weightFunc {
private:
   double weightToJam;
public:
    weightFunc(double n): weightToJam(n) { }
  
    bool operator() (const Peaches &p) const {
        return p.weight < weightToJam;
    }
};

int main(){
   srand(time(nullptr));
   const double minWeight = 8.;
   const double maxWeight = 3.;

   cout << "Input basket size: ";
   int size;
   cin >> size;

   vector <Peaches> basket(size);

   // assign random weight and ripeness peaches in the basket
   // replace with generate()
   generate(basket.begin(), basket.end(), [minWeight, maxWeight]() { 
      Peaches p = Peaches();
      p.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      p.ripe = rand() % 2;
      
      return p;
   });

   
   // for_each() possibly
   cout << "all peaches"<< endl;
   for_each(basket.begin(), basket.end(), [](const Peaches &p) { p.print(); });
   cout << endl;

   // moving all the ripe peaches from basket to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Peaches> peck;
   remove_copy_if(basket.begin(), basket.end(), back_inserter(peck), [](const Peaches &p){ return !p.ripe; });

   // for_each() possibly
   cout << "peaches remainng in the basket"<< endl;
   for_each(basket.begin(), basket.end(), [](const Peaches &p) { p.print(); });
   cout << endl;

   cout << endl;

   // for_each() possibly
   cout << "peaches moved to the peck"<< endl;
   for_each(peck.begin(), peck.end(), [](const Peaches &p) { p.print(); });
   cout << endl;


   // prints every "space" peach in the peck
   const int space=3; 
   cout << "\nevery " << space << "\'d peach in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no explicit iterator arithmetic
   auto it=peck.cbegin();
   while(it < peck.cend()) {
      advance(it, space);
      if(it < peck.end())
         it->print();
   }

   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   const double weightToJam = 10.0;
   weightFunc func(weightToJam);
   auto boundFunc = bind(func, _1);

   double jamWeight = 0;

   it = peck.begin();
   int i = 0;
   while(count_if(peck.begin(), peck.end(), boundFunc) != i) {
      if(it->weight < weightToJam) {
         jamWeight += it->weight;
         i++;
         it++;
      }
   }
   remove_if(peck.begin(), peck.end(), boundFunc);
   cout << "Weight of jam is: " << jamWeight << endl;
}
