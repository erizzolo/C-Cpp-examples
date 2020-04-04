/**
 * Purpose: basic process implementations
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
*/

#include <cstdlib>
#include <ctime>

#define MIN_RUNNING 10
#define MAX_RUNNING 100
#define MIN_USER 10
#define MAX_USER 50
#define MIN_PRIORITY 0
#define MAX_PRIORITY 4

// complete definition
struct processo
{
    int PID{0};             // process ID
    int runningTime{0};     // total running time
    int remainingTime{0};   // remaining time: yes, we can see the future
    bool running{false};    // true if running, false otherwise
    bool terminated{false}; // true if terminated, false otherwise
    int priority{0};        // priority
    int userID{0};          // user ID
};

const processo IDLE_TIME;

// generate a random process
processo generateRandom()
{
    static int newPID = IDLE_TIME.PID + 1;
    processo result;
    result.PID = newPID++;
    result.remainingTime = MIN_RUNNING + rand() % (MAX_RUNNING - MIN_RUNNING + 1);
    result.priority = MIN_PRIORITY + rand() % (MAX_PRIORITY - MIN_PRIORITY + 1);
    result.userID = MIN_USER + rand() % (MAX_USER - MIN_USER + 1);
    return result;
}

// basic info and operations
// process ID
int getPID(const processo &p)
{
    return p.PID;
}

// total running time
int getRunningTime(const processo &p)
{
    return p.runningTime;
}

// remaining time: yes, we can see the future
int getRemainingTime(const processo &p)
{
    return p.remainingTime;
}

// true if running, false otherwise
bool isRunning(const processo &p)
{
    return p.running;
}

// true if terminated, false otherwise
bool isTerminated(const processo &p)
{
    return p.terminated;
}

// priority
int getPriority(const processo &p)
{
    return p.priority;
}

// user ID
int getUserID(const processo &p)
{
    return p.userID;
}

// kill a process
void kill(processo &p)
{
    p.running = false;
    p.terminated = true;
}

// schedule i.e. let it use CPU
void schedule(processo &p)
{
    p.running = true;
}

// suspend i.e. don't let it use CPU
void suspend(processo &p)
{
    p.running = false;
}
// time elapsed
void timeElapsed(processo &p, int delta)
{
    if (p.running)
    {
        p.runningTime += delta;
        p.remainingTime -= delta;
        p.terminated = p.remainingTime <= 0;
    }
}

// for debug purposes
// assumes ostream & << item is defined
#include <iostream>
void print(const processo &p, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "Process{" << getPID(p);
    out << ", time " << getRunningTime(p);                                  // total running time
    out << "/" << getRemainingTime(p);                                      // remaining time: yes, we can see the future
    out << (isTerminated(p) ? ", terminated"                                // true if terminated, false otherwise
                            : (isRunning(p) ? ", running" : ", waiting ")); // true if running, false otherwise
    out << ", pty " << getPriority(p);                                      // priority
    out << ", user " << getUserID(p);                                       // user ID
    out << "}";
    if (newLine)
    {
        out << endl;
    }
}
