// Author:      Alex Ely
// Date:        11/30/2022
// Project:     Lab 12
// Description: Genealogy tree program for determining friends or relativces

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::cin; using std::endl;
using std::string; 
using std::vector;
using std::getline;

class Person{ // component
public:
   Person(string firstName, Person *spouse, Person *father, Person *mother):
      firstName_(firstName), spouse_(spouse), father_(father), mother_(mother){}
   const string & getFirstName(){return firstName_;}
   Person *getSpouse(){return spouse_;}
   void setSpouse(Person *spouse){spouse_=spouse;}
   Person *getFather(){return father_;}
   Person *getMother(){return mother_;}

   virtual void accept(class PersonVisitor *)=0;  
   virtual ~Person(){}
private:
   const string firstName_;
   Person *spouse_;
   Person *father_;
   Person *mother_;
};


// leaf
// man has a last name 
class Man: public Person{
public:
   Man(string lastName, string firstName, Person *spouse, 
       Person *father, Person *mother): 
      lastName_(lastName), 
      Person(firstName, spouse, father, mother){}
   const string & getLastName() const {return lastName_;}
   void accept(class PersonVisitor *visitor) override;
private:
   const string lastName_;
};

// composite
// woman has a list of children
class Woman: public Person{
public: 
   Woman(vector<Person *> children, 
       string firstName, 
       Person *spouse, 
       Person *father, Person *mother): 
       children_(children),
       Person(firstName, spouse, father, mother){}
   const vector<Person *> & getChildren() const {return children_;}
   void setChildren(const vector<Person *> &children){ children_ = children;}
   void accept(class PersonVisitor *visitor) override;
private:
   vector<Person *> children_;
}; 

// abstract visitor
class PersonVisitor{
public:
   virtual void visit(Man*)=0;
   virtual void visit(Woman*)=0;
   virtual ~PersonVisitor(){}
};

// composite methods that define traversal
void Man::accept(PersonVisitor *visitor) {
    visitor->visit(this);
}

void Woman::accept(PersonVisitor *visitor){ 
   // children traversal through mother only
   // father's children are not traversed so as not 
   // to traverse them twice: for mother and father

   visitor->visit(this);

   // traversing descendants
   for(auto child : children_) 
      child->accept(visitor);   
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not

class FindPerson: public PersonVisitor{
public:
   FindPerson(string name): name_(name), toFind_(nullptr) { }

   void visit(Man *m) override {
      string name = m->getFirstName();
      name += " ";
      name += m->getLastName();
   
      if(checkName(name)) 
         toFind_ = m;
   }

   void visit(Woman *w) override {
      string name = w->getFirstName();
      name += " ";

      if(w->getSpouse() != nullptr)
         name += static_cast<Man*>(w->getSpouse())->getLastName();
      else if(w->getFather() != nullptr)
         name += static_cast<Man*>(w->getFather())->getLastName();
      else
         name += "Doe"; 
      
      if(checkName(name))
         toFind_ = w;
   }
   
   Person* getToFind() { return toFind_; }
private:
   string name_;
   Person *toFind_;
   bool checkName(string name) {
      return name == name_;
   }
};

class CloseRelative: public PersonVisitor {
public:
   CloseRelative(Person *c1, Person *c2): c1_(c1), c2_(c2), isClose_(false) { }
   void visit(Man *m) override {
      if(m == c1_)
         isClose_ = checkRelatives(c1_, c2_);
      else if(m == c2_)
         isClose_ = checkRelatives(c2_, c1_);
   }

   void visit(Woman *w) override {
       if(w == c1_)
         isClose_ = checkRelatives(c1_, c2_);
      else if(w == c2_)
         isClose_ = checkRelatives(c2_, c1_);
   }

   bool getIsClose() { return isClose_; }
private:
   Person *c1_;
   Person *c2_;
   bool isClose_;
   bool checkRelatives(Person *a, Person *b) {
      if(a == nullptr || b == nullptr)
         return true;
      if(a == b)
         return true;
      if(a->getFather() == b->getFather() && a->getFather() != nullptr)
         return true;
      if(a->getMother() == b->getMother() && a->getMother() != nullptr)
         return true;
      if(a->getMother() == b || a->getFather() == b)
         return true;
      if(b->getMother() == a || b->getFather() == a)
         return true;
      
      Woman *motherA = static_cast<Woman*>(a->getMother());

      if(motherA != nullptr) {
         Woman *grannyA = static_cast<Woman*>(motherA->getMother());

         if(grannyA != nullptr) {
            vector<Person *> grannyAKids = grannyA->getChildren();

            for(Person *e: grannyAKids)
               if(e == b) return true;
         }
      }

      Woman *motherB = static_cast<Woman*>(b->getMother());

      if(motherB != nullptr) {
         Woman *grannyB = static_cast<Woman*>(motherB->getMother());

         if(grannyB != nullptr) {
            vector<Person *> grannyBKids = grannyB->getChildren();

            for(Person *e: grannyBKids)
               if(e == a) return true;
         }
      }

      return false;
   }
};

// demonstrating the operation
int main(){

   // setting up the genealogical tree      
   // the tree is as follows
   //    
   //
   //       James Smith  <--spouse-->   Mary 
   //	                                  |
   //	                                 children -------------------------
   //	                                  |              |                |
   //	                                  |              |                |
   //	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
   //	                                  |
   //	                                 children------------
   //	                                  |                 |
   //                                     |                 |
   //	   Jennifer  <--spouse-->  Michael Johnson      Barbara
   //	       |
   //	     children
   //	       |
   //          |
   //	     Susan


   // first generation
   Man *js = new Man("Smith", "James", nullptr, nullptr, nullptr);
   Woman *ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
   ms->setSpouse(js); js->setSpouse(ms);

   // second generation
   Woman *ps = new Woman({}, "Patricia",  nullptr, js, ms);
   Man *wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
   ps->setSpouse(wj); wj->setSpouse(ps);

   vector<Person *> marysKids  = {ps,
			          new Man("Smith", "Robert", nullptr, js, ms),
			          new Woman({}, "Linda", nullptr, js, ms)};
   ms->setChildren(marysKids);

   // third generation
   Man *mj = new Man("Johnson", "Michael", nullptr, wj, ps);
   vector<Person *> patsKids   = {mj, new Woman({}, "Barbara", nullptr, wj, ps)}; 
   ps->setChildren(patsKids);

   Woman *jj = new Woman({}, "Jennifer", mj, nullptr, nullptr);
   vector<Person *> jensKids = {new Woman({}, "Susan", nullptr, mj ,jj)};

   jj->setSpouse(mj); mj->setSpouse(jj);
   jj->setChildren(jensKids);
   
   string name1;
   string name2;

   cout << "Enter first candidate: ";
   getline(cin, name1);

   FindPerson *fp1 = new FindPerson(name1);
   ms->accept(fp1);
   Person *a = fp1->getToFind();

   cout << "Enter second candidate: ";
   getline(cin, name2);

   FindPerson *fp2 = new FindPerson(name2);
   ms->accept(fp2);
   Person *b = fp2->getToFind();

   CloseRelative *cr = new CloseRelative(a, b);
   ms->accept(cr);
   
   if(cr->getIsClose())
      cout << "\nThey are close relatives.\n";
   else
      cout << "\nThey are just friends.\n";

}