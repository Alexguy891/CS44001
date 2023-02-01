#include <string>
#include <vector>
#include <iostream>
#include <list>

using std::cout; using std::cin;
using std::string;
using std::vector;
using std::list;

enum class DrinkType {small, medium, large};

class Drink{
public:
   // default constructor
   Drink(DrinkType type=DrinkType::small, int price=0):
      type_(type), price_(price) { }

   // getters
   virtual int getPrice() const { return price_; }
   virtual string getToppings() const;
protected:
   // price of drink
   int price_;
   // size of drink
   DrinkType type_;
   // name with toppings
   string name_;
};

string Drink::getToppings() const {
   switch(type_) {
      case DrinkType::small:
         return "small coffee with ";
      case DrinkType::medium:
         return "medium coffee with ";
      default:
         return "large coffee with ";
   }
}

class AddSugar: public Drink {
public:
   // default constructor
   AddSugar(const Drink* wrapped): wrapped_(wrapped) { }

   // getters
   int getPrice() const override {
      return 1 + wrapped_->getPrice();
   }

   string getToppings() const override {
      return wrapped_->getToppings() + "sugar, ";
   }
private:
   const Drink *wrapped_;
};

class AddCream: public Drink {
public:
   // default constructor
   AddCream(const Drink* wrapped): wrapped_(wrapped) { }

   // getters
   int getPrice() const override {
      return 2 + wrapped_->getPrice();
   }

   string getToppings() const override {
      return wrapped_->getToppings() + "cream, ";
   }
private:
   const Drink *wrapped_;
};

class AddFoam: public Drink {
public:
   // default constructor
   AddFoam(const Drink* wrapped): wrapped_(wrapped) { }

   // getters
   int getPrice() const override {
      return 3 + wrapped_->getPrice();
   }

   string getToppings() const override {
      return wrapped_->getToppings() + "foam, ";
   } 
private:
   const Drink *wrapped_;
};

class Customer;

class Barista {
public:
   // CoR constructor
   Barista(Barista *next = nullptr):
      next_(next) { }

   // CoR function
   virtual Drink* makeOrder(char choice, list<Drink *> &drinks) {
      return next_->makeOrder(choice, drinks);
   }

   // observer functions
   void registerCustomer(Customer *c) { customers_.push_back(c); }
   void deregisterCustomer(int i) { 
      customers_.erase(customers_.begin() + i); 
   }
   void notifyCustomers() const;

   // useful functions
   void completeOrder();
   string getCustomerName();
   bool done() { return customers_.empty(); }
   char askOrder();

protected:
   // customer vector
   static vector<Customer *> customers_;
   // num of customer
   int custIndex_;

private:
   // CoR ptr
   Barista *next_;
};

vector<Customer *> Barista::customers_;

class Customer {
public:
   // observer constructor
   Customer(const string &name, Barista* barista, Drink* drink):
      name_(name), barista_(barista), drink_(drink) {
         barista->registerCustomer(this);
      }
   
   // observer functions
   void notify() const;
   string getName() const { return name_; }
   Drink* getDrink() const { return drink_; }

private:
   // observer members
   string name_;
   Barista *barista_;
   Drink *drink_;
};

class JuniorBarista: public Barista {
public:
   // CoR constructor
   JuniorBarista(Barista *next = nullptr): 
      Barista(next) { }

   // CoR function
   Drink* makeOrder(char choice, list<Drink *> &drinks) override;
};

class SeniorBarista: public Barista {
public:
   // CoR constructor
   SeniorBarista(Barista *next = nullptr): 
      Barista(next) { }

   // CoR function
   Drink* makeOrder(char choice, list<Drink *> &drinks) override;
};

class Manager: public Barista {
public:
   // CoR constructor
   Manager(Barista *next = nullptr): 
      Barista(next) { }

   // CoR function
   Drink* makeOrder(char choice, list<Drink *> &drinks) override;
};

// member functions
void Barista::notifyCustomers() const {
   for(auto c: customers_) c->notify();
}

string Barista::getCustomerName() {
   return customers_[custIndex_]->getName();
}

char Barista::askOrder() {
   cout << "Would you like to add"
   << "[s]ugar, [c]ream, milk [f]oam, or [d]one? ";

   char c;
   cin >> c;

   return c;
}

void Barista::completeOrder() {
   custIndex_ = rand() % customers_.size();

   cout << customers_[custIndex_]->getName()
   << ", your " << customers_[custIndex_]->getDrink()->getToppings()
   << "is ready. It will be $" << customers_[custIndex_]->getDrink()->getPrice()
   << ", please.\n";

   this->notifyCustomers();
   this->deregisterCustomer(custIndex_);
}

Drink* JuniorBarista::makeOrder(char choice, list<Drink *> &drinks) {
   cout << "Welcome to Coffee Shack, can I get you "
   << "[l]arge, [m]edium, or [s]mall coffee? ";

   cin >> choice;

   DrinkType type;
   int price;

   switch(choice) {
      case 'l':
         type = DrinkType::large;
         price = 10;
         break;
      case 'm':
         type = DrinkType::medium;
         price = 7;
         break;
      default:
         type = DrinkType::small;
         price = 5;
         break;
   }

   drinks.push_back(new Drink(type, price));
   choice = this->askOrder(); 

   if(choice == 'd') {
      cout << "Junior Barista making order...\n";
      return drinks.back();
   }

   return Barista::makeOrder(choice, drinks);
}

Drink* SeniorBarista::makeOrder(char choice, list<Drink *> &drinks) {
   while(choice != 'f') {
      cout << "Senior Barista making order...\n";

      switch(choice) {
         case 's':
            drinks.push_back(new AddSugar(drinks.back()));
            break;
         case 'c':
            drinks.push_back(new AddCream(drinks.back()));
            break;
         case 'd':
            return drinks.back();
      }

      choice = this->askOrder();
   }

   return Barista::makeOrder(choice, drinks);
}

Drink* Manager::makeOrder(char choice, list<Drink *> &drinks) {
   while(choice != 'd') {
      cout << "Manager making order...\n";

      switch(choice) {
         case 's':
            drinks.push_back(new AddSugar(drinks.back()));
            break;
         case 'c':
            drinks.push_back(new AddCream(drinks.back()));
            break;
         case 'f':
            drinks.push_back(new AddFoam(drinks.back()));
            break;
      }

      choice = this->askOrder();
   }

   return drinks.back();
}

void Customer::notify() const {
   cout << name_ << " checks drink for "
      << barista_->getCustomerName()
      << '\n';
}