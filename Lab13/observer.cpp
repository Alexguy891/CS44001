// Author:      Alex Ely
// Date:        12/7/2022
// Project:     Lab 13
// Description: Keyed Registry with String

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>

using std::cout; using std::endl;
using std::map; using std::set;
using std::string;

class Observer;
class Subject;

class EventRegistry{
public:
   static void registerObserver(string, Observer*);
   static void deregisterObserver(string, Observer*);
   static void handleMessage(string);
private:
   static map<string, set<Observer*>> observerMap_;
};

// initialize the static map
map<string, set<Observer*>> EventRegistry::observerMap_;


class Observer{
public:
   Observer(const string &name): name_(name) {}
   string getName() const {return name_;}
   void subscribe(string name) {EventRegistry::registerObserver(name, this);}
   void unsubscribe(string name){EventRegistry::deregisterObserver(name, this);}
   void handleMessage(string);
private:
   string name_;
};

class Subject{
public:
   Subject(const string &name): name_(name) {}
   string getName() const {return name_;}
   void generateMessage(){
      cout << name_ << " sent a message" << endl;
      EventRegistry::handleMessage(name_);}
private:
   string name_;
};

void EventRegistry::registerObserver(string name, Observer* o){
   observerMap_[name].insert(o);
   cout << o->getName() << " subscribed to " << name << endl;
}

void EventRegistry::deregisterObserver(string name, Observer* o){
   observerMap_[name].erase(o);
   cout << o->getName() << " unsubscribed from " << name << endl;
}

void EventRegistry::handleMessage(string name){
   for (auto e: observerMap_[name])
      e->handleMessage(name);
}

void Observer::handleMessage(string name) {
   cout << name_ << " received message from " << name << endl;
}


int main() {
   Observer olaf("Observer Olaf"), olga("Observer Olga");
   Subject  sue("Subject Sue"),  steve("Subject Steve");

   olaf.subscribe(sue.getName()); olaf.subscribe(steve.getName());
   olga.subscribe(sue.getName());

   cout << endl;


   sue.generateMessage();
   steve.generateMessage();
   cout << endl;
   
   olga.unsubscribe(sue.getName());
   sue.generateMessage();
}