/**
 * Purpose: test di una queue di int
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// definizione del tipo di dati contenuto nello queue
using item = int;

// dichiarazioni delle operazioni
#include "queue.h"

#define CAPACITY 10

// implementazione e completamento dichiarazioni
#include "queueFLA.cpp"

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    queue s;    // variable of type queue
    item i = 1; // an item
    // fill the queue
    while (insert(s, i))
    {
        print(s);
        i++;
    }
    // empty the queue
    while (remove(s, i))
    {
        cout << "Extracted " << i << endl;
        print(s);
    }
    // successful termination
    return 0;
}
