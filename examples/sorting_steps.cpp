/**
 * Purpose: basic sorting algorithms: bubble sort derived step by step
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/02/29
 * Note:
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// operation counters
int scambi, confronti;

using type = int;

// utility functions
void JSON(const type a[], int end, int begin = 0, ostream &out = cout);               // output su out in formato JSON
void reverse(type a[], int end, int begin = 0);                                       // rovescia l'ordine degli elementi
void initRandom(type a[], int end, int begin = 0, type min = 0, type max = RAND_MAX); // a[i] = random in [min, max]

// function to start with
bool isOrdered(const type a[], int end, int begin = 0); // verifica a[i] >= a[j] per i >= j
// first step
void sortFirst(type a[], int end, int begin = 0); // ordina in modo che a[i] >= a[j] per i >= j
// full sorting, recursive
void sortRecursive(type a[], int end, int begin = 0); // ordina in modo che a[i] >= a[j] per i >= j
// full sorting, iterative
void sortIterative(type a[], int end, int begin = 0); // ordina in modo che a[i] >= a[j] per i >= j
// full sorting, iterative + optimization on end
void sortOptimized(type a[], int end, int begin = 0); // ordina in modo che a[i] >= a[j] per i >= j

// basic sorting test
void test(type v[], int dim, int which);

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    srand(time(nullptr));
    {
        int dim = 10;
        type v[dim], a[dim];
        initRandom(a, dim, 0, 0, dim); // probably with duplicates
        for (int algo = 1; algo <= 4; ++algo)
        {
            // make a copy
            for (int i = 0; i < dim; ++i)
            {
                v[i] = a[i];
            }
            test(v, dim, algo);
        }
    }
    // successful termination
    return 0;
}

/**
 * Verifica ordinamento (crescente) elementi da begin a end escluso: [begin, end)
 * @param a     l'array con i valori di cui verificare l'ordinamento
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @return      true se gli elementi sono ordinati, false altrimenti
 */
bool isOrdered(const type a[], int end, int begin /* = 0 */)
{
    for (int i = begin + 1; i < end; ++i)
    {
        if (a[i] < a[i - 1])
        {
            return false;
        }
    }
    return true;
}

/**
* Ordinamento (crescente, cioe' tale che a[i] >= a[j] per i >= j)
* elementi da begin a end escluso: [begin, end)
* @param a     l'array con i valori da ordinare
* @param end   fine (esclusa) della scansione: a[end] non viene elaborato
* @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
*/

// first step
// simply trying to fix an anomaly when we find it
void sortFirst(type a[], int end, int begin /* = 0 */)
{
    for (int i = begin + 1; i < end; ++i)
    {
        confronti++;
        if (a[i] < a[i - 1])
        {
            // something's wrong here: let's fix it
            scambi++;
            swap(a[i], a[i - 1]);
        }
    }
    // here last position is maximum element,
    // but the others might still be out of order !!!
}

// full sorting, recursive
// as before, with recursive sorting if needed
void sortRecursive(type a[], int end, int begin /* = 0 */)
{
    for (int i = begin + 1; i < end; ++i)
    {
        confronti++;
        if (a[i] < a[i - 1])
        {
            // something's wrong here: let's fix it
            scambi++;
            swap(a[i], a[i - 1]);
        }
    }
    // here last position is maximum element,
    // but the others might still be out of order !!!
    // Let's sort the rest if needed
    if (end > begin + 2)
    {
        sortRecursive(a, end - 1, begin);
    }
}

// full sorting, iterative
// changing the tail recursion into an iteration
void sortIterative(type a[], int end, int begin /* = 0 */)
{
    // end - begin > 1 : at least two elements
    while (end - begin > 1)
    {
        for (int i = begin + 1; i < end; ++i)
        {
            confronti++;
            if (a[i] < a[i - 1])
            {
                // something's wrong here: let's fix it
                scambi++;
                swap(a[i], a[i - 1]);
            }
        }
        // here last position is maximum element,
        // but the others might still be out of order !!!
        // Let's sort the rest if needed
        end = end - 1;
    }
}

// full sorting, iterative + optimization on end
// remembering last swap: the rest is ordered
void sortOptimized(type a[], int end, int begin /* = 0 */)
{
    // end - begin > 1 : at least two elements
    while (end - begin > 1)
    {
        int lastSwapped = 0;
        for (int i = begin + 1; i < end; ++i)
        {
            confronti++;
            if (a[i] < a[i - 1])
            {
                // something's wrong here: let's fix it
                scambi++;
                swap(a[i], a[i - 1]);
                lastSwapped = i;
            }
        }
        // here last position is maximum element,
        // but the others might still be out of order !!!
        // Let's sort the rest if needed
        // end = end - 1;
        end = lastSwapped;
    }
}

void sortIt(type v[], int dim, int which)
{
    cout << "Before: ";
    JSON(v, dim, 0, cout);
    cout << " ordinato: " << (isOrdered(v, dim) ? "si'" : "no") << endl;
    scambi = confronti = 0;
    switch (which)
    {
    case 1:
        sortFirst(v, dim, 0);
        break;
    case 2:
        sortRecursive(v, dim, 0);
        break;
    case 3:
        sortIterative(v, dim, 0);
        break;
    case 4:
        sortOptimized(v, dim, 0);
        break;
    }
    cout << "After : ";
    JSON(v, dim, 0, cout);
    cout << " ordinato: " << (isOrdered(v, dim) ? "si'" : "no") << ". Scambi = " << scambi << ", confronti = " << confronti << endl;
}

void test(type v[], int dim, int which)
{
    cout << "Test started." << endl;
    sortIt(v, dim, which);
    sortIt(v, dim, which);
    reverse(v, dim, which);
    sortIt(v, dim, which);
    cout << "Test finished." << endl
         << endl;
}

/**
 * Output su out in formato JSON da begin a end escluso: [begin, end)
 * @param a     the array to output
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @param out   the output stream to be used
 */
void JSON(const type a[], int end, int begin /* = 0 */, ostream &out /* = cout */)
{
    out << "[ ";
    for (int i = begin; i < end; ++i)
    {
        if (i != begin)
        {
            out << ", ";
        }
        out << a[i];
    }
    out << " ]";
}

/**
 * Rovescia gli elementi da begin a end escluso: [begin, end)
 * @param a     l'array con i valori da rovesciare
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 */
void reverse(type a[], int end, int begin /* = 0 */)
{
    for (int inf = begin, sup = end - 1; inf < sup; inf++, sup--)
    {
        swap(a[inf], a[sup]);
    }
}

/**
 * Inizializzazione con valore casuale degli elementi da begin a end escluso: [begin, end)
 * @param a     l'array da inizializzare
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @param min   valore casuale minimo
 * @param max   valore casuale massimo
 */
void initRandom(type a[], int end, int begin /* = 0 */, type min /* = 0 */, type max /* = RAND_MAX */)
{
    for (int i = begin; i < end; i++)
    {
        a[i] = min + rand() % (max - min + 1);
    }
}
