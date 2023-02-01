#include "coffeeShack.hpp"
#include <ctime>
#include <random>

int main() {
    srand(time(nullptr));

    const int custNum = 3; // num of customers in shop
    JuniorBarista *bp = new JuniorBarista(new SeniorBarista(new Manager));
    int customers = 0;

    while(customers != custNum || !bp->done()) {
        int finish = rand() % 2;

        if(finish == 0 && customers != custNum) {
            char choice;
            list<Drink *> drinks;
            string name;

            bp->makeOrder(choice, drinks);

            cout << "Can I get your name? ";
            cin >> name;

            Customer *customer = new Customer(name, bp, drinks.back());
            customers++;
        } else if (finish == 1 && !bp->done())
            bp->completeOrder();
    }

    return 0;
}