// Author:      Alex Ely
// Date:        11/02/2022
// Project:     Lab 9
// Description: Car factory demonstration

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "carFactory.hpp"

using std::vector;
using std::cout; using std::endl;
using std::string;

class CarLot{
public:
    CarLot();

    Car* testDriveCar() { return lot_[carIndex_]; }
    // if a car is bought, requests a new one
    Car *buyCar(){ 
        Car *bought = lot_[carIndex_];
        lot_[carIndex_] = factories_[rand()%factories_.size()]->requestCar();
        return bought;
    }

    void nextCar() {
        carIndex_++;
        if(carIndex_ == lotSize_)
            carIndex_ = 0;
    }

    int lotSize() {
        return lotSize_;
    }
		     
private:
    int carIndex_ = 0;
    const int lotSize_ = 10;
    vector<Car*> lot_;
    vector<CarFactory *> factories_;
};


CarLot::CarLot(){
    // creates 2 Ford factories and 2 Toyota factories 
    factories_.push_back(new FordFactory());   
    factories_.push_back(new ToyotaFactory());
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());

    for(int i = 0; i < lotSize_; ++i)
        lot_.push_back(factories_[rand() % factories_.size()]->requestCar());
}



CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id){
    if (carLotPtr == nullptr)
        carLotPtr = new CarLot();

    ToyotaFactory* wantFactory = new ToyotaFactory();
    Car* wantCar = wantFactory->requestCar();

    cout << "Jill Toyoter " << id << " wants a Toyota " << wantCar->getModel() << endl;
    
    for(int i = 0; i < carLotPtr->lotSize(); ++i) {
        Car *toBuy = carLotPtr->testDriveCar(); 

        cout << "test driving " 
	        << toBuy->getMake() << " "
	        << toBuy->getModel();

        if (toBuy->getMake() == wantCar->getMake() && toBuy->getModel() == wantCar->getModel()){
            cout << " love it! buying it!" << endl;
            carLotPtr -> buyCar();
            break;
        } else {
            cout << " did not like it!" << endl;
            carLotPtr->nextCar();
        }
    }
}

// test-drives a car
// buys it if Ford
void fordLover(int id){
    if (carLotPtr == nullptr)
        carLotPtr = new CarLot(); 

    FordFactory* wantFactory = new FordFactory();
    Car* wantCar = wantFactory->requestCar();

    cout << "Jack Fordman " << id << " wants a Ford " << wantCar->getModel() << endl;

    for(int i = 0; i < carLotPtr->lotSize(); ++i) {
        Car *toBuy = carLotPtr->testDriveCar(); 

        cout << "test driving " 
	        << toBuy->getMake() << " "
	        << toBuy->getModel();

        if (toBuy->getMake() == wantCar->getMake() && toBuy->getModel() == wantCar->getModel()){
            cout << " love it! buying it!" << endl;
            carLotPtr -> buyCar();
            break;
        } else {
            cout << " did not like it!" << endl;
            carLotPtr->nextCar();
        }
    }
}



int main() {
   srand(time(nullptr));

   const int numBuyers=20;
   for(int i=0; i < numBuyers; ++i)
        if(rand()% 2 == 0)
	        toyotaLover(i);
        else
	        fordLover(i);
  
}