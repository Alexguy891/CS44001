// Author:      Alex Ely
// Date:        12/9/2022
// Project:     Lab 14
// Description: Sorting demonstration

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>

using std::cout; using std::endl;
using std::vector; 

class OrderedCollection;
typedef vector<int>::iterator It;  // shorthand for a vector iterator


// abstract strategy
// strategy interface, push method
class Sorter{
public:
    virtual void sort(It, It) const = 0;
};


// context using the strategies
class OrderedCollection{
public:
    void setSorter(Sorter *sorter) {sorter_ = sorter;}
    void setCollection(const vector<int> v){v_ = v;}
    const vector<int>& getCollection() const{ return v_;}
    void sort() {sorter_->sort(v_.begin(), v_.end());}
private:
    vector<int> v_;
    Sorter *sorter_; 
};


// concrete strategy using bubble sort
class BubbleSorter: public Sorter {
public:
    void sort(It begin, It end) const override {
        bool swapped;
        do{
            swapped = false;
            for(It one=begin, two = next(one, 1); two != end; ++one, ++two)
                if(*one > *two){
                    std::swap(*one, *two);
                    swapped=true;
                }
        } while(swapped);
    }
};

// concrete strategy using STL sorting alg
class StdSorter: public Sorter{
public:
   void sort(It begin, It end) const override {
        std::sort(begin, end);
   }
};

class InsertSorter: public Sorter {
    void sort(It begin, It end) const override {
        for (auto i = begin; i != end; ++i) {
            const auto key = *i;
            auto j = i;

            while (j != begin && key < *prev(j)) {
                *j = *prev(j);
                --j;
            }

            *j = key;
        }
    }
};

int main() {
    vector<int> v={3,55,2,103,27}, vc=v, vc2=v;

    OrderedCollection sortedVector;
    StdSorter ss;
    BubbleSorter bs;
    InsertSorter is;

    // 
    // sorting short vectors to demo correctness
    //

    // STL sorter
    sortedVector.setSorter(&ss);
    sortedVector.setCollection(v);
    for(auto e: v) cout << e << " "; cout << endl;

    sortedVector.sort();
    v = sortedVector.getCollection();
    cout << "STL sorted" << endl; 
    for(auto e: v) cout << e << " "; cout << endl << endl;

    
    // BubbleSort sorter
    sortedVector.setSorter(&bs);
    sortedVector.setCollection(vc);
    for(auto e: vc) cout << e << " "; cout << endl;

    sortedVector.sort();
    vc = sortedVector.getCollection();
    cout << "bubble sorted" << endl; 
    for(auto e: vc) cout << e << " "; cout << endl << endl;

    // InsertSort sorter
    sortedVector.setSorter(&is);
    sortedVector.setCollection(vc2);
    for(auto e: vc2) cout << e << " "; cout << endl;

    sortedVector.sort();
    vc2 = sortedVector.getCollection();
    cout << "insert sorted" << endl; 
    for(auto e: vc2) cout << e << " "; cout << endl << endl;
    

    // 
    // sorting large vectors to demo performance
    // 
    v.clear();
    srand(time(nullptr));

    std::generate_n(back_inserter(v), 50000, []{return rand()%100;});
    vc=v; vc2=v;

    std::chrono::time_point<std::chrono::high_resolution_clock>
        startTime, endTime; // chrono time points
    std::chrono::duration<double> duration; 
                            // chrono time interval

    // STL sorter
    sortedVector.setSorter(&ss);
    sortedVector.setCollection(v);

    startTime = std::chrono::high_resolution_clock::now();
    sortedVector.sort();
    endTime = std::chrono::high_resolution_clock::now();
    duration = endTime - startTime;
    v = sortedVector.getCollection();

    cout << "standard sort ran for " << duration.count() << " seconds" << endl;

    // bubble sort
    sortedVector.setSorter(&bs);
    sortedVector.setCollection(vc);
    
    startTime = std::chrono::high_resolution_clock::now();
    sortedVector.sort();
    endTime = std::chrono::high_resolution_clock::now();
    duration = endTime - startTime;
    vc = sortedVector.getCollection();

    cout << "bubble sort ran for " << duration.count() << " seconds" << endl;
    
    // insert sort
    sortedVector.setSorter(&is);
    sortedVector.setCollection(vc2);
    
    startTime = std::chrono::high_resolution_clock::now();
    sortedVector.sort();
    endTime = std::chrono::high_resolution_clock::now();
    duration = endTime - startTime;
    vc2 = sortedVector.getCollection();

    cout << "insert sort ran for " << duration.count() << " seconds" << endl;
    

    // confirming sorted vectors are the same
    if(v == vc && vc == vc2 && v == vc2)
        cout << "sorted vectors are the same" << endl;
    else
        cout << "sorted vectors are different" << endl;   
}