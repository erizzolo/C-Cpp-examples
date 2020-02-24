/**
 * Purpose: base search algorithms for arrays with dichotomy
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/02/24
 * Note:
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

/**
 * La tecnica di ricerca dicotomica si può applicare quando:
 * - lo spazio di ricerca è ordinato !!!
 * - non solo alle ricerche su array !!!
*/

using type = int;

/// applicazione delle precedenti scansioni per la visualizzazione di un array
void JSON(const type a[], int end, int begin = 0, ostream &out = cout); /// output su out in formato JSON
/// inizializzazione di un array
void initAritmetica(type a[], int end, int begin = 0, type first = 0, type delta = 0); /// a[i] = first + delta * (i - begin)
/// conteggio/ricerca occorrenze di un valore nell'array
bool contains(const type a[], const type value, int end, int begin = 0);    /// se a[i] == value per almeno un i
int count(const type a[], const type value, int end, int begin = 0);        /// conta a[i] == value
int countOpt(const type a[], const type value, int end, int begin = 0);     /// conta a[i] == value optimized
int firstIndexOf(const type a[], const type value, int end, int begin = 0); /// minimo i per cui a[i] == value
int lastIndexOf(const type a[], const type value, int end, int begin = 0);  /// massimo i per cui a[i] == value

#define DEBUG 1

void test(type v[], int dim)
{
    cout << "Test started." << endl;
    JSON(v, dim, 0, cout);
    cout << endl;
    type value = 4;
    cout << "presence of " << value << ": " << contains(v, value, dim) << endl;
    cout << "first occurrence of " << value << ": " << firstIndexOf(v, value, dim) << endl;
    cout << "last occurrence of " << value << ": " << lastIndexOf(v, value, dim) << endl;
    cout << "count of occurrences: " << value << " occurs " << count(v, value, dim) << " time(s)." << endl;
    cout << "count of occurrences: " << value << " occurs " << countOpt(v, value, dim) << " time(s)." << endl;
    cout << "Test finished." << endl;
}

/// main function
int main(int argc, char *argv[])
{
    srand(time(nullptr));
    {
        type v[]{1, 2, 2, 4, 4, 6, 7, 10, 15};
        constexpr int dim = sizeof(v) / sizeof(v[0]);
        test(v, dim);
    }
    {
        int dim = 30;
        type v[dim];
        initAritmetica(v, dim, 0, 1, 3);
        test(v, dim);
    }
    /// successful termination
    return 0;
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
 * Inizializzazione con valore in progressione aritmetica degli elementi da begin a end escluso: [begin, end)
 * @param a     l'array da inizializzare
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @param first primo termine della progressione
 * @param delta ragione della progressione
 */
void initAritmetica(type a[], int end, int begin /* = 0 */, type first /* = 0 */, type delta /* = 0 */)
{
    type value = first;
    for (int i = begin; i < end; ++i, value += delta)
    {
        a[i] = value;
    }
}
/**
 * Test esistenza tra elementi da begin a end escluso: [begin, end)
 * @param a     l'array in cui effettuare la ricerca
 * @param value valore da ricercare
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @return      true se il valore esiste, false altrimenti
 */
bool contains(const type a[], const type value, int end, int begin /* = 0 */)
{
    while (end > begin)
    {
        int middle = begin + (end - begin) / 2; // (begin + end) / 2
        // begin = 0, end = 11; middle = 5 oppure 5
        // begin = 10, end = 22; middle = 16 oppure 16
        // begin = 2000000000, end = 2000000001; middle = 2000000000 oppure -xxxxx
        if (a[middle] == value)
        {
            return true;
        }
        else if (a[middle] < value)
        {
            begin = middle + 1;
        }
        else
        {
            end = middle;
        }
    }
    return false;
}
/**
 * Conteggio occorrenze tra elementi da begin a end escluso: [begin, end)
 * @param a     l'array in cui effettuare la ricerca
 * @param value valore da ricercare
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @return      il numero di occorrenze di value
 */
int count(const type a[], const type value, int end, int begin /* = 0 */)
{
    // with already implemented searches
    int first = firstIndexOf(a, value, end, begin);
    if (first == end)
    {
        return 0; // nothing
    }
    else
    {
        return lastIndexOf(a, value, end, first) - first + 1;
    }
}
int countOpt(const type a[], const type value, int end, int begin /* = 0 */)
{
    // starting with first search and optimizing second search
    while (end > begin)
    {
        int middle = begin + (end - begin) / 2;
        if (a[middle] == value)
        {
            // found, but it might occur before and after !
            int first = firstIndexOf(a, value, middle, begin);
            int last = lastIndexOf(a, value, end, middle);
            return last - first + 1;
        }
        else if (a[middle] < value)
        {
            begin = middle + 1; // definitely not in [begin, middle]
        }
        else
        {
            end = middle; // definitely not in [middle, end)
        }
    }
    return 0; // nothing
}
/**
 * Ricerca prima occorrenza tra elementi da begin a end escluso: [begin, end)
 * @param a     l'array in cui effettuare la ricerca
 * @param value valore da ricercare
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @return      il minimo indice i per cui a[i] == value, end se nessuno
 */
int firstIndexOf(const type a[], const type value, int end, int begin /* = 0 */)
{
    int result = end; // guess we're not lucky
    while (end > begin)
    {
        int middle = begin + (end - begin) / 2;
        if (a[middle] == value)
        {
            result = middle; // found, but it might occur before !
            end = middle;    // result = end = middle;
        }
        else if (a[middle] < value)
        {
            begin = middle + 1; // definitely not in [begin, middle]
        }
        else
        {
            end = middle; // definitely not in [middle, end)
        }
    }
    return result;
}
/**
 * Ricerca ultima occorrenza tra elementi da begin a end escluso: [begin, end)
 * @param a     l'array in cui effettuare la ricerca
 * @param value valore da ricercare
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @return      il massimo indice i per cui a[i] == value, end se nessuno
 */
int lastIndexOf(const type a[], const type value, int end, int begin /* = 0 */)
{
    int result = end; // guess we're not lucky
    while (end > begin)
    {
        int middle = begin + (end - begin) / 2;
        if (a[middle] == value)
        {
            result = middle; // found, but it might occur after !
            begin = middle + 1;
        }
        else if (a[middle] < value)
        {
            begin = middle + 1; // definitely not in [begin, middle]
        }
        else
        {
            end = middle; // definitely not in [middle, end)
        }
    }
    return result;
}
