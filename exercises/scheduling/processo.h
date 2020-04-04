/**
 * Purpose: basic process declarations
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
*/

// common guard to avoid multiple inclusions
#ifndef PROCESSO_H
#define PROCESSO_H

// incomplete type, will be defined in processo.cpp
struct processo;

processo generateRandom(); // generate a random process

// basic info and operations
int getRunningTime(const processo &);   // total running time
int getRemainingTime(const processo &); // remaining time: yes, we can see the future
bool isRunning(const processo &);       // true if running, false otherwise
bool isTerminated(const processo &);    // true if terminated, false otherwise
int getPriority(const processo &);      // priority
int getUserID(const processo &);        // user ID
void kill(processo &);                  // kill a process
void schedule(processo &);              // schedule i.e. let it use CPU
void suspend(processo &);               // suspend i.e. don't let it use CPU
void timeElapsed(processo &p, int);     // time elapsed

// for debug purposes
// assumes ostream & << item is defined
#include <iostream>
void print(const processo &, ostream &out = cout, bool newLine = true);

#endif