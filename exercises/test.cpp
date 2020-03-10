/**
 * Purpose: test di uno stack di int
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// definizione del tipo di dati contenuto nello stack
using item = int;

// dichiarazioni delle operazioni
#include "stack.h"

// implementazione e completamento dichiarazioni
#include "stackFLA.cpp"

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    srand(time(nullptr));
    stack s;
    print(s);
    push(s, 10);
    print(s);
    push(s, 5);
    print(s);
    item d;
    while (pop(s, d))
    {
        cout << "Extracted " << d << endl;
        print(s);
    }
    // successful termination
    return 0;
}
