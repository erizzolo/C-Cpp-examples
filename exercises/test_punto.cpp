/**
 * Purpose: test di un punto in uno spazio bidimensionale
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// definizione del tipo usato per le coordinate
using coord = double;

// dichiarazioni delle operazioni
#include "punto.h"

// implementazione e completamento dichiarazioni
#include "punto.cpp"

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    cout << "Test dell'implementazione del tipo di dati punto." << endl
         << "Si noti che alcuni test possono dare 'falsi positivi' se i test precedenti falliscono!!!" << endl
         << endl;
    {
        cout << "Test getPunto" << endl;
        punto p = getPunto(1.5, 2.5);
        cout << "punto p = getPunto(1.5, 2.5);" << endl;
        print(p);
    }
    {
        cout << "Test getX e getY" << endl;
        coord x = 1.5, y = 2.5;
        punto p = getPunto(x, y);
        cout << "punto p = getPunto(" << x << ", " << y << ");" << endl;
        print(p);
        cout << "getX(p) = " << getX(p) << (getX(p) == x ? " ok" : " failed") << endl;
        cout << "getY(p) = " << getY(p) << (getY(p) == y ? " ok" : " failed") << endl;
    }
    {
        cout << "Test coincidenti" << endl;
        coord x = 1.5, y = 2.5;
        punto p1 = getPunto(x, y), p2 = getPunto(x, y), p3 = getPunto(y, x);
        cout << "punto p1: ";
        print(p1);
        cout << "punto p2: ";
        print(p2);
        cout << "punto p3: ";
        print(p3);
        cout << "coincidenti(p1, p2) = " << coincidenti(p1, p2) << (coincidenti(p1, p2) ? " ok" : " failed") << endl;
        cout << "coincidenti(p1, p3) = " << coincidenti(p1, p3) << (!coincidenti(p1, p3) ? " ok" : " failed") << endl;
    }
    {
        cout << "Test distanza" << endl;
        punto p1 = getPunto(0, 2), p2 = getPunto(3, 6), p3 = getPunto(0, 2);
        cout << "punto p1: ";
        print(p1);
        cout << "punto p2: ";
        print(p2);
        cout << "punto p3: ";
        print(p3);
        cout << "distanza(p1, p2) = " << distanza(p1, p2) << (distanza(p1, p2) == 5 ? " ok" : " failed") << endl;
        cout << "distanza(p1, p3) = " << distanza(p1, p3) << (distanza(p1, p3) == 0 ? " ok" : " failed") << endl;
    }
    {
        cout << "Test distanzaDaOrigine" << endl;
        punto p1 = getPunto(0, 2), p2 = getPunto(3, 4);
        cout << "punto p1: ";
        print(p1);
        cout << "punto p2: ";
        print(p2);
        cout << "distanzaDaOrigine(p1) = " << distanzaDaOrigine(p1) << (distanzaDaOrigine(p1) == 2 ? " ok" : " failed") << endl;
        cout << "distanzaDaOrigine(p2) = " << distanzaDaOrigine(p2) << (distanzaDaOrigine(p2) == 5 ? " ok" : " failed") << endl;
    }
    {
        cout << "Test trasla" << endl;
        punto p = getPunto(0, 2), t = getPunto(2, 1);
        cout << "punto p: ";
        print(p);
        trasla(p, 2, -1);
        cout << "punto p traslato di 2, -1:";
        print(p, cout, false);
        cout << (coincidenti(p, t) ? " ok" : " failed") << endl;
    }
    {
        cout << "Test scala" << endl;
        punto p = getPunto(1, 2), t = getPunto(5, 10);
        cout << "punto p: ";
        print(p);
        scala(p, 5);
        cout << "punto p scalato di 5:";
        print(p, cout, false);
        cout << (coincidenti(p, t) ? " ok" : " failed") << endl;
    }
    {
        cout << "Altri Test ...." << endl;
        cout << " failed" << endl;
    }
    // successful termination
    return 0;
}
