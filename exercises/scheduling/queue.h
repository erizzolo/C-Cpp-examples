/**
 * Purpose: basic queue declarations
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
*/

// common guard to avoid multiple inclusions
#ifndef QUEUE_H
#define QUEUE_H

// incomplete type, will be defined in queue.cpp
struct queue;

// basic operations
int size(const queue &);
int capacity(const queue &);
bool insert(queue &, item);
bool remove(queue &, item &);

// for debug purposes
// assumes ostream & << item is defined
#include <iostream>
void print(const queue&, ostream &out = cout, bool newLine = true);

#endif