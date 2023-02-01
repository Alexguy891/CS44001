#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <ctime>
#include "state.hpp"

using std::cout;
using std::vector; using std::queue; 
using std::rand; using std::time;

int main() {
    srand(time(nullptr));
    Process prototypeProcess;
    const int numProcesses = 4;
    vector<Process *> processes;
    queue<Process *> readyQ;
    queue<Process *> blockQ;

    for(int i = 0; i < numProcesses; i++)
        processes.push_back(prototypeProcess.clone());

    for(auto p: processes) {
        cout << p->report();
        p->create();
        readyQ.push(p);
    }

    cout << "\n-------- scheduler running ---------\n";

    while(!readyQ.empty() || !blockQ.empty()) {
        int choice;

        if(!readyQ.empty()) {
            choice = rand() % 3;

            Process *p = readyQ.front();
            readyQ.pop();
            cout << "dispatching...\n";
            p->dispatch();
            
            switch(choice) {
                case 0:
                    cout << "suspending...\n";
                    p->suspend();
                    readyQ.push(p);
                    break;
                case 1:
                    cout << "blocking...\n";
                    p->block();
                    blockQ.push(p);
                    break;
                case 2:
                    cout << "exiting...\n";
                    p->exit();
                    break;
                default:
                    cout << "error in rand()\n";
                    return 1;
            }

            cout << '\n';
        }

        if(!blockQ.empty()) {
            choice = rand() % 3;

            if(choice == 0) {
                cout << "unblocking...\n";
                Process *p = blockQ.front();
                blockQ.pop();
                p->unblock();
                readyQ.push(p);
                cout << '\n';
            }
        }
    }

    cout << "all processes exited.\n"
    << "--------- scheduler done ---------\n";
}