// Author:      Alex Ely
// Date:        11/02/2022
// Project:     Lab 9
// Description: Car factory implementation

#include <array>
#include <cstdlib>
#include "carFactory.hpp"


// product methods

Ford::Ford(){
    static const std::array<std::string, 4>
        models = {"Focus", "Mustang", "Explorer", "F-150"};
    make_ = "Ford";
    model_ = models[rand() % models.size()];
}

Toyota::Toyota(){
    static const std::array<std::string, 5>
        models = {"Corolla", "Camry", "Prius", "4Runner", "Yaris"};
    make_ = "Toyota";
    model_ = models[rand() % models.size()];
}


// factory methods
Car* CarFactory::requestCar() {
	++numCarsInProduction_;
	return makeCar();
}

Car* FordFactory::makeCar() {
	return new Ford();
}

Car* ToyotaFactory::makeCar() {
	return new Toyota();
}