// Author:      Alex Ely
// Date:        10/12/2022
// Project:     Lab 6
// Description: Uses STL Container to generate random fruit colors


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

/*struct Fruit{
    Variety v;
    string color; // red, green or orange
};*/ 


int main(){
    srand(time(nullptr));
    multimap<Variety, string> fruit; // map to hold fruit
    int numFruit = rand() % 100 + 1; // generates random number of fruit to be held


    for(int i = 0; i < numFruit; i++) // fills map with random fruits
        fruit.emplace(static_cast<Variety>(rand() & 3), colors[rand() % 3]);

    // printing colors of oranges
    cout << "Colors of the oranges: ";
    for(auto f = fruit.lower_bound(Variety::orange); f != fruit.upper_bound(Variety::orange); ++f) {
            cout << f->second << ", ";
    }
    cout << endl;
}
