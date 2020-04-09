/**
 * Purpose: simulazione di scheduling di processi
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
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

    processo current[CORES]; // every core has its own current process
    int time = 0;
    int quantum[CORES]; // every process has its own quantum
    for (int core = 0; core < CORES; core++)
    {
        current[core] = IDLE_TIME;
        quantum[core] = QUANTUM[0];
    }
    queue readyQ;
    // to keep track of active processes and see if we are done
    int activeProcesses = 0;

    // generate processes
    for (int i = 0; i < 10; i++)
    {
        processo p = generateRandom();
        print(p);
        insert(readyQ, p);
    }
    // loop
    while (size(readyQ) > 0 || activeProcesses > 0)
    {
        // maybe add a new random process to the ready queue
        if (rand() % 100 == 0)
        {
            processo p = generateRandom();
            cout << time << ": new process " << p << endl;
            insert(readyQ, p);
        }
        // check for termination on every core
        for (int core = 0; core < CORES; core++)
        {
            if (getPID(current[core]) != getPID(IDLE_TIME))
            {
                quantum[core]--;
                if (isTerminated(current[core]))
                {
                    cout << time << ", core " << core << ": terminated process " << current[core] << endl;
                    current[core] = IDLE_TIME;
                    activeProcesses--; // update
                }
            }
        }
        // if RQ not empty
        if (size(readyQ) != 0)
        {
            // check every active process for quantum termination
            for (int core = 0; core < CORES; core++)
            {
                // if quantum over
                if (quantum[core] == 0 && getPID(current[core]) != getPID(IDLE_TIME))
                {
                    // suspend running process and put it back in the ready queue
                    suspend(current[core]);
                    insert(readyQ, current[core]);
                    cout << time << ", core " << core << ": suspended process " << current[core] << endl;
                    current[core] = IDLE_TIME;
                    activeProcesses--;
                }
            }
            // for every available core
            for (int core = 0; core < CORES; core++)
            {
                // if CPU is available
                if (getPID(current[core]) == getPID(IDLE_TIME))
                {
                    // schedule next process in the ready queue
                    if (remove(readyQ, current[core]))
                    {
                        schedule(current[core]);
                        cout << time << ", core " << core << ": scheduled process " << current[core] << endl;
                        quantum[core] = QUANTUM[getPriority(current[core])];
                        activeProcesses++;
                    }
                }
            }
        }
        time++;
        // update evry active process
        for (int core = 0; core < CORES; core++)
        {
            timeElapsed(current[core], 1);
        }
    }
    print(readyQ);
    // forever ...

    // successful termination
    return 0;
}
