/**
 * Purpose: base algorithms for arrays
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2019/11/29
 * Note:
*/

#include <iostream>
#include <cmath>
using namespace std;

/**
 * Come già detto, gli array si elaborano elemento per elemento.
 * Vi sono degli schemi di base che si raccomandano per i compiti più tipici.
 * In questo esempio si mostrano alcuni di tali schemi.
 * La base di tutto sono le scansioni degli elementi (o di parte di essi),
 * che possono avvenire in ordine di indice crescente o decrescente.
 * Durante la scansione, si accede al singolo elemento e lo si elabora
 * secondo le necessità.
 * La scansione può eventualmente essere interrotta se si raggiunge l'obiettivo.
 * Le varianti sono ovviamente infinite.
 * Gli esempi qui illustrati valgono per array di dati di tipo generico type.
 * E' possibile sostituire a type qualunque tipo fisico (compatibile con le
 * operazioni effettuate) modificando l'istruzione using seguente.
*/

using type = int;
using real = double;

/// basic scan prototypes
void forwardScanAll(type a[], int end);  /// scansione crescente da 0 a end escluso: [0, end)
void backwardScanAll(type a[], int end); /// scansione decrescente da end escluso a 0: [0, end)
/// basic algorithms prototypes
void forwardScan(type a[], int end, int begin = 0);  /// scansione crescente da begin a end escluso: [begin, end)
void backwardScan(type a[], int end, int begin = 0); /// scansione decrescente da end escluso a begin: [begin, end)
/// applicazione delle precedenti scansioni per la visualizzazione di un array
void toCout(const type a[], int end, int begin = 0);                    /// output su cout da begin a end escluso: [begin, end)
void backwardToCout(const type a[], int end, int begin = 0);            /// output su cout da end escluso a begin: [begin, end)
void JSON(const type a[], int end, int begin = 0, ostream &out = cout); /// output su out in formato JSON
/// inizializzazione di un array
void initIndex(type a[], int end, int begin = 0);                                       /// a[i] = i
void initRandom(type a[], int end, int begin = 0, type min = 0, type max = RAND_MAX);   /// a[i] = random in [min, max]
void initAritmetica(type a[], int end, int begin = 0, type first = 0, type delta = 0);  /// a[i] = first + delta * (i - begin)
void initGeometrica(type a[], int end, int begin = 0, type first = 1, type factor = 1); /// a[i] = first * factor ^ (i - begin)
/// conteggio/ricerca occorrenze di un valore nell'array
bool contains(const type a[], const type value, int end, int begin = 0);       /// se a[i] == value per almeno un i
int count(const type a[], const type value, int end, int begin = 0);           /// conta a[i] == value
int firstIndexOf(const type a[], const type value, int end, int begin = 0);    /// minimo i per cui a[i] == value
int lastIndexOf(const type a[], const type value, int end, int begin = 0);     /// massimo i per cui a[i] == value
int firstIndexOfWithGuard(type a[], const type value, int end, int begin = 0); /// minimo i per cui a[i] == value
int lastIndexOfWithGuard(type a[], const type value, int end, int begin = 0);  /// massimo i per cui a[i] == value
/// statistics
type max(const type a[], int end, int begin = 0);       /// max a[i] for i in [begin, end)
type min(const type a[], int end, int begin = 0);       /// min a[i] for i in [begin, end)
type sum(const type a[], int end, int begin = 0);       /// sum of a[i] for i in [begin, end)
type prod(const type a[], int end, int begin = 0);      /// product of a[i] for i in [begin, end)
real mean(const type a[], int end, int begin = 0);      /// mean of a[i] for i in [begin, end)
bool isOrdered(const type a[], int end, int begin = 0); /// verifica a[i] >= a[j] per i >= j
void reverse(type a[], int end, int begin = 0);         /// reverse the array (i.e. exchanges first with last adn so on)
/// Horner's polynomial evaluation
/// valuta polinomio con i dati coefficienti per x dato
real horner(const real coeff[], int grado, real x);
/// stampa polinomio con i dati coefficienti per la variabile var
void printPolynomial(ostream &out, const real coeff[], int grado, char var = 'x');
/// trova una radice del polinomio con i dati coefficienti per x in [xmin, xmax]
real findRoot(const real coeff[], int grado, real xmin, real xmax, real tol = 1E-16, int maxIt = 100);

#define DEBUG 1

/// main function
int main(int argc, char *argv[])
{
    srand(time(nullptr));
    type v[]{1, 2, 2, 4, 4, 3, 7, 10, 15};
    constexpr int dim = sizeof(v) / sizeof(v[0]);
    JSON(v, dim);
    cout << endl;
    /// successful termination
    return 0;
}
/**
 * Basic forward scan
 * scansione crescente da 0 a end escluso: [0, end)
 * @param a     the array to scan
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 */
void forwardScanAll(type a[], int end)
{
    for (int i = 0; i < end; ++i)
    {
        /// process a[i]
        cout << "processing a[" << i << "]" << endl;
    }
}
/**
 * Basic backward scan (with default limits)
 * scansione decrescente da end escluso a 0: [0, end)
 * @param a     the array to scan
 * @param end   inizio (escluso) della scansione: a[end] non viene elaborato
 */
void backwardScanAll(type a[], int end)
{
    for (int i = end; i-- > 0;)
    {
        /// process a[i]
        cout << "processing a[" << i << "]" << endl;
    }
}

/**
 * Basic forward scan (with default limits)
 * scansione crescente da begin a end escluso: [begin, end)
 * @param a     the array to scan
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 */
void forwardScan(type a[], int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        /// process a[i]
        cout << "processing a[" << i << "]" << endl;
    }
}
/**
 * Basic backward scan (with default limits)
 * scansione decrescente da end escluso a begin: [begin, end)
 * @param a     the array to scan
 * @param end   inizio (escluso) della scansione: a[end] non viene elaborato
 * @param begin fine (inclusa) della scansione: a[begin] e' l'ultimo elemento elaborato
 */
void backwardScan(type a[], int end, int begin /* = 0 */)
{
    for (int i = end; i-- > begin;)
    {
        /// process a[i]
        cout << "processing a[" << i << "]" << endl;
    }
}

/**
 * Output su cout da begin a end escluso: [begin, end)
 * @param a     the array to output
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 */
void toCout(const type a[], int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        cout << "a[" << i << "] = " << a[i] << endl;
    }
}
/**
 * Output in ordine inverso su cout da end escluso a begin: [begin, end)
 * @param a     the array to output
 * @param end   inizio (escluso) della scansione: a[end] non viene elaborato
 * @param begin fine (inclusa) della scansione: a[begin] e' l'ultimo elemento elaborato
 */
void backwardToCout(const type a[], int end, int begin /* = 0 */)
{
    for (int i = end; i-- > begin;)
    {
        cout << "a[" << i << "] = " << a[i] << endl;
    }
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
 * Inizializzazione con valore dell'indice degli elementi da begin a end escluso: [begin, end)
 * @param a     l'array da inizializzare
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 */
void initIndex(type a[], int end, int begin /* = 0 */)
{
    for (int i = begin; i < end; ++i)
    {
        a[i] = i;
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
    for (int i = begin; i < end; ++i)
    {
        a[i] = min + rand() % (max - min + 1);
    }
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
 * Inizializzazione con valore in progressione geometrica degli elementi da begin a end escluso: [begin, end)
 * @param a         l'array da inizializzare
 * @param end       fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin     inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @param first     primo termine della progressione
 * @param factor    ragione della progressione
 */
void initGeometrica(type a[], int end, int begin /* = 0 */, type first /* = 1 */, type factor /* = 1 */)
{
    type value = first;
    for (int i = begin; i < end; ++i, value *= factor)
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
    for (int i = begin; i < end; ++i)
    {
        if (a[i] == value)
            return true;
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
    int result = 0;
    for (int i = begin; i < end; ++i)
    {
        if (a[i] == value)
            ++result;
    }
    return result;
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
    for (int i = begin; i < end; ++i)
    {
        if (a[i] == value)
            return i;
    }
    return end;
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
    for (int i = end; i-- > begin;)
    {
        if (a[i] == value)
            return i;
    }
    return end;
}
/**
 * Ricerca massimo tra elementi da begin a end escluso: [begin, end)
 * @param a     l'array in cui effettuare la ricerca
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @return      il massimo valore tra gli elementi, (ub se begin >= end)
 */
type max(const type a[], int end, int begin /* = 0 */)
{
    type result = a[begin];
    for (int i = ++begin; i < end; ++i)
    {
        if (result < a[i])
            result = a[i];
    }
    return result;
}
/**
 * Ricerca minimo tra elementi da begin a end escluso: [begin, end)
 * @param a     l'array in cui effettuare la ricerca
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @return      il minimo valore tra gli elementi, (ub se begin >= end)
 */

type min(const type a[], int end, int begin /* = 0 */)
{
    type result = a[begin];
    for (int i = ++begin; i < end; ++i)
    {
        if (result > a[i])
            result = a[i];
    }
    return result;
}
/**
 * Ricerca prima occorrenza tra elementi da begin a end escluso: [begin, end)
 * Ricerca con sentinella ... (non thread-safe ma più efficiente ... )
 * @param a     l'array in cui effettuare la ricerca
 * @param value valore da ricercare
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @return      il minimo indice i per cui a[i] == value, end se nessuno
 */
int firstIndexOfWithGuard(type a[], const type value, int end, int begin /* = 0 */)
{
    if (DEBUG)
        cout << "Setting guard at " << end - 1 << endl;
    type last = a[end - 1]; // save last element
    a[end - 1] = value;     // set guard
    int index = begin;
    while (a[index] != value)
    {
        index++; // next
    }
    if (DEBUG)
        cout << "Unsetting guard at " << end - 1 << endl;
    a[end - 1] = last; // restore last element
    return a[index] == value ? index : end;
}
/**
 * Ricerca ultima occorrenza tra elementi da begin a end escluso: [begin, end)
 * Ricerca con sentinella ... (non thread-safe ma più efficiente ... )
 * @param a     l'array in cui effettuare la ricerca
 * @param value valore da ricercare
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @return      il massimo indice i per cui a[i] == value, end se nessuno
 */
int lastIndexOfWithGuard(type a[], const type value, int end, int begin /* = 0 */)
{
}

/**
 * Valuta il polinomio con i dati coefficienti per il valore x della variabile
 * @param coeff i coefficienti coeff[i] coefficiente di grado i
 * @param grado il grado del polinomio
 * @param x     il valore della variabile per cui valutare il polinomio
 * @return      il valore di p(x)
 */
real horner(const real coeff[], int grado, real x)
{
    real result = coeff[grado];
    while (grado-- > 0)
        result = result * x + coeff[grado];
    return result;
}
/**
 * Visualizza il polinomio con i dati coefficienti per la variabile data
 * @param out   lìoutput stream su cui "visualizzare" i dati
 * @param coeff i coefficienti coeff[i] coefficiente di grado i
 * @param grado il grado del polinomio
 * @param var   il carattere che indica la variabile
 */
void printPolynomial(ostream &out, const real coeff[], int grado, char var /* = 'x' */)
{
    auto flags = out.flags(); // save flags
    while (grado > 1)
    {
        out << showpos << coeff[grado] << " " << var << "^" << noshowpos << grado << " ";
        --grado;
    }
    if (grado == 1)
        out << showpos << coeff[grado] << " " << var << " ";
    out << showpos << coeff[0];
    out.flags(flags); // restore flags
}
/**
 * Trova una radice del polinomio con i dati coefficienti per x in [xmin, xmax]
 * @param coeff i coefficienti coeff[i] coefficiente di grado i
 * @param grado il grado del polinomio
 * @param xmin  estremo inferiore dell'intervallo di ricerca
 * @param xmax  estremo superiore dell'intervallo di ricerca
 * @param tol   tolleranza relativa su |x|
 * @param maxIt numero massimo iterazioni
 * @return      un valore approssimato di x tale che p(x) = 0
 */
real findRoot(const real coeff[], int grado, real xmin, real xmax, real tol /* = 1E-16 */, int maxIt /* = 100 */)
{
    real ymin = horner(coeff, grado, xmin), ymax = horner(coeff, grado, xmax);
    while (maxIt-- > 0)
    {
        real delta = (xmax - xmin) / 2;
        real xmiddle = xmin + delta;
        real ymiddle = horner(coeff, grado, xmiddle);
        if ((ymiddle == 0.0) || (delta < tol))
            return xmiddle;
        if (signbit(ymiddle) == signbit(ymin))
            xmin = xmiddle;
        else
            xmax = xmiddle;
    }
    return NAN; // failed: not a number
}
