/**
 * Purpose: test di una retta in uno spazio bidimensionale
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
#include "retta.h"

// implementazione e completamento dichiarazioni
#include "punto.cpp"
// #include "retta.cpp"
#include "retta.cpp"

#define DEBUG 1

ostream &operator<<(ostream &os, const punto &p)
{
    print(p, os, false);
    return os;
}

ostream &operator<<(ostream &os, const retta &r)
{
    print(r, os, false);
    return os;
}

void testGetABC(coord a, coord b, coord c)
{
    cout << "Test getRetta / getA / getB / getC. " << endl;
    retta r = getRetta(a, b, c);
    cout << "retta r = getRetta(" << a << ", " << b << ", " << c << "); : " << r << endl;
    cout << "getA(r) = " << getA(r) << (getA(r) == a ? " ok" : " failed") << endl;
    cout << "getB(r) = " << getB(r) << (getB(r) == b ? " ok" : " failed") << endl;
    cout << "getC(r) = " << getC(r) << (getC(r) == c ? " ok" : " failed") << endl;
    cout << endl;
}

void testGetMQ(coord m, coord q)
{
    cout << "Test getRetta / coefficienteAngolare / intercetta. " << endl;
    retta r = getRetta(m, q);
    cout << "retta r = getRetta(" << m << ", " << q << "); : " << r << endl;
    cout << "coefficienteAngolare(r) = " << coefficienteAngolare(r) << (coefficienteAngolare(r) == m ? " ok" : " failed") << endl;
    cout << "intercetta(r) = " << intercetta(r) << (intercetta(r) == q ? " ok" : " failed") << endl;
    cout << endl;
}

void testGetP2Q(const punto &p1, const punto &p2)
{
    cout << "Test getRetta / appartiene. " << endl;
    retta r = getRetta(p1, p2);
    punto pd = getPunto(getX(p1), getY(p2));
    cout << "retta r = getRetta(" << p1 << ", " << p2 << "); : " << r << endl;
    cout << "punto pd = getPunto(getX(p1), getY(p2)); : " << pd << endl;
    cout << "appartiene(r, p1) = " << appartiene(r, p1) << (appartiene(r, p1) ? " ok" : " failed") << endl;
    cout << "appartiene(r, p2) = " << appartiene(r, p2) << (appartiene(r, p2) ? " ok" : " failed") << endl;
    cout << "appartiene(r, pd) = " << appartiene(r, pd) << ((appartiene(r, pd) == (getA(r) == 0 || getB(r) == 0)) ? " ok" : " failed") << endl;
    cout << endl;
}

void testEquals(coord a, coord b, coord c, coord k)
{
    cout << "Test getRetta / coincidenti / parallele. " << endl;
    retta r = getRetta(a, b, c);
    retta rc = getRetta(k * a, k * b, k * c);
    retta rp = getRetta(a, b, k + c);
    cout << "retta r = getRetta(" << a << ", " << b << ", " << c << "); : " << r << endl;
    cout << "retta rc = getRetta(" << k * a << ", " << k * b << ", " << k * c << "); : " << rc << endl;
    cout << "retta rp = getRetta(" << a << ", " << b << ", " << k + c << "); : " << rp << endl;
    cout << "coincidenti(r, rc) = " << coincidenti(r, rc) << (coincidenti(r, rc) == (k != 0) ? " ok" : " failed") << endl;
    cout << "coincidenti(r, rp) = " << coincidenti(r, rp) << (coincidenti(r, rp) == (k == 0) ? " ok" : " failed") << endl;
    cout << "parallele(r, rp) = " << parallele(r, rp) << (parallele(r, rp) ? " ok" : " failed") << endl;
    cout << endl;
}

void testCopia(coord a, coord b, coord c)
{
    cout << "Test getRetta / getCopia / coincidenti. " << endl;
    retta r = getRetta(a, b, c);
    retta rc = getCopia(r);
    cout << "retta r = getRetta(" << a << ", " << b << ", " << c << "); : " << r << endl;
    cout << "retta rc = getCopia(" << r << "); : " << rc << endl;
    cout << "coincidenti(r, rc) = " << coincidenti(r, rc) << (coincidenti(r, rc) ? " ok" : " failed") << endl;
    cout << endl;
}

void testParallela(const retta &r, const punto &p)
{
    cout << "Test getRetta / parallelaPer. " << endl;
    retta rp = parallelaPerPunto(r, p);
    retta rp0 = parallelaPerOrigine(r);
    punto o = getPunto(0, 0);
    retta rpo = parallelaPerPunto(r, o);
    cout << "retta r = " << r << ", punto p = " << p << ", punto o = " << o << endl;
    cout << "retta rp = parallelaPerPunto(r, p); : " << rp << endl;
    cout << "retta rp0 = parallelaPerOrigine(r); : " << rp0 << endl;
    cout << "retta rpo = parallelaPerPunto(r, o); : " << rpo << endl;
    cout << "parallele(r, rp) = " << parallele(r, rp) << (parallele(r, rp) ? " ok" : " failed") << endl;
    cout << "appartiene(rp, p) = " << appartiene(rp, p) << (appartiene(rp, p) ? " ok" : " failed") << endl;
    cout << "parallele(r, rp0) = " << parallele(r, rp0) << (parallele(r, rp0) ? " ok" : " failed") << endl;
    cout << "coincidenti(rp0, rpo) = " << coincidenti(rp0, rpo) << (coincidenti(rp0, rpo) ? " ok" : " failed") << endl;
    cout << endl;
}

void testOrtogonale(const retta &r, const punto &p)
{
    cout << "Test getRetta / ortogonalePer. " << endl;
    retta ro = ortogonalePerPunto(r, p);
    retta ro0 = ortogonalePerOrigine(r);
    punto o = getPunto(0, 0);
    retta roo = ortogonalePerPunto(r, o);
    retta rp = ortogonalePerPunto(ro, p);
    cout << "retta r = " << r << ", punto p = " << p << ", punto o = " << o << endl;
    cout << "retta ro = ortogonalePerPunto(r, p); : " << ro << endl;
    cout << "retta ro0 = ortogonalePerOrigine(r); : " << ro0 << endl;
    cout << "retta roo = ortogonalePerPunto(r, o); : " << roo << endl;
    cout << "retta rp = ortogonalePerPunto(ro, p); : " << rp << endl;
    cout << "parallele(r, ro) = " << parallele(r, ro) << (!parallele(r, ro) ? " ok" : " failed") << endl;
    cout << "appartiene(ro, p) = " << appartiene(ro, p) << (appartiene(ro, p) ? " ok" : " failed") << endl;
    cout << "parallele(r, ro0) = " << parallele(r, ro0) << (!parallele(r, ro0) ? " ok" : " failed") << endl;
    cout << "appartiene(ro0, o) = " << appartiene(ro0, o) << (appartiene(ro0, o) ? " ok" : " failed") << endl;
    cout << "coincidenti(ro0, roo) = " << coincidenti(ro0, roo) << (coincidenti(ro0, roo) ? " ok" : " failed") << endl;
    cout << "parallele(r, ro) = " << parallele(r, ro) << (!parallele(r, ro) ? " ok" : " failed") << endl;
    cout << "parallele(r, rp) = " << parallele(r, rp) << (parallele(r, rp) ? " ok" : " failed") << endl;
    cout << endl;
}

/// main function
int main(int argc, char *argv[])
{
    cout << "Test dell'implementazione del tipo di dati retta." << endl
         << "Si noti che alcuni test possono dare 'falsi positivi' se i test precedenti falliscono!!!" << endl
         << endl;

    testGetABC(1.5, 2.5, 3.5);
    testGetABC(-1.5, 0, -3.5);
    cout << "This is a fake test, ignore it..." << endl;
    testGetABC(0, 0, -3.5); // not a real line

    testGetMQ(1.5, 0);
    testGetMQ(0, 2.5);

    punto p1 = getPunto(0, 1), p2 = getPunto(1, 0), p3 = getPunto(0, 3);
    testGetP2Q(p1, p2);
    testGetP2Q(p1, p3);
    cout << "This is a fake test, ignore it..." << endl;
    testGetP2Q(p1, p1); // shoul be different points!!!

    testEquals(1.5, 2.5, 3.5, 2);
    cout << "This is a fake test, ignore it..." << endl;
    testEquals(1.5, -2.5, 0, 0);

    testCopia(1.5, 2.5, 3.5);
    testCopia(-1.5, 0, -3.5);
    cout << "This is a fake test, ignore it..." << endl;
    testCopia(0, 0, -3.5); // not a real line

    retta r1 = getRetta(2.5, -1, 3);
    retta r2 = getRetta(0, 0, 3); // not a real line

    testParallela(r1, p1);
    cout << "This is a fake test, ignore it..." << endl;
    testParallela(r2, p2);

    testOrtogonale(r1, p1);
    cout << "This is a fake test, ignore it..." << endl;
    testOrtogonale(r2, p2);

    // successful termination
    return 0;
}
