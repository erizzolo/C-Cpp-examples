/**
 * Purpose: simulazione di scheduling di processi
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:    Compilare con opzione -std=C++11
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "processo.h"

// definizione del tipo di dati contenuto nella ready queue
using item = processo;

// dichiarazioni delle operazioni
#include "queue.h"

// implementazione e completamento dichiarazioni
#include "processo.cpp"

ostream &operator<<(ostream &os, const processo &p)
{
    print(p, os, false);
    return os;
}

#include "queueDAC.cpp"

#define DEBUG 1

// max simulation time
#define MAX_TIME 1000
// number of cores
#define CORES 4

// quantum duration by priority
const int QUANTUM[MAX_PRIORITY + 1]{5, 10, 15, 20, 25};

/// main function
int main(int argc, char *argv[])
{
    srand(time(nullptr));

    processo current = IDLE_TIME;
    int time = 0;
    int quantum = QUANTUM[0];
    queue readyQ;

    // generate processes
    for (int i = 0; i < 10; i++)
    {
        processo p = generateRandom();
        print(p);
        insert(readyQ, p);
    }
    // loop
    while (size(readyQ) > 0 || getPID(current) != getPID(IDLE_TIME))
    {
        // maybe add a new random process to the ready queue
        if (rand() % (400 / CORES) == 0)
        {
            processo p = generateRandom();
            cout << time << ": new process " << p << endl;
            insert(readyQ, p);
        }
        if (getPID(current) != getPID(IDLE_TIME))
        {
            quantum--;
            if (isTerminated(current))
            {
                cout << time << ": terminated process " << current << endl;
                current = IDLE_TIME;
            }
        }
        // if RQ not empty
        if (size(readyQ) != 0)
        {
            // if quantum over
            if (quantum == 0 && getPID(current) != getPID(IDLE_TIME))
            {
                // suspend running process and put it back in the ready queue
                suspend(current);
                insert(readyQ, current);
                cout << time << ": suspended process " << current << endl;
                current = IDLE_TIME;
            }
            // if CPU is available
            if (getPID(current) == getPID(IDLE_TIME))
            {
                // schedule next process in the ready queue
                if (remove(readyQ, current))
                {
                    schedule(current);
                    cout << time << ": scheduled process " << current << endl;
                    quantum = QUANTUM[getPriority(current)];
                }
            }
        }
        time++;
        timeElapsed(current, 1);
    }
    print(readyQ);
    // forever ...

    // successful termination
    return 0;
}
