/**
 * Purpose: base algorithms for arrays with recursive implementation
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/01/23
 * Note:    Non tutte le funzioni sono state implementate ricorsivamente ...
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
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

void test(type v[], int dim)
{
    cout << "Test started." << endl;
    JSON(v, dim, 0, cout);
    cout << endl;
    type value = 4;
    cout << "first occurrence of " << value << ": " << firstIndexOf(v, value, dim) << endl;
    cout << "last occurrence of " << value << ": " << lastIndexOf(v, value, dim) << endl;
    cout << "first occurrence of " << value << ": " << firstIndexOfWithGuard(v, value, dim) << endl;
    cout << "last occurrence of " << value << ": " << lastIndexOfWithGuard(v, value, dim) << endl;
    cout << "min : " << min(v, dim) << endl;
    cout << "max : " << max(v, dim) << endl;
    cout << "somma : " << sum(v, dim) << endl;
    cout << "prodotto : " << prod(v, dim) << endl;
    cout << "media : " << mean(v, dim) << endl;
    cout << "ordinamento : " << isOrdered(v, dim) << endl;
    cout << "rovesciamento : ";
    reverse(v, dim);
    JSON(v, dim);
    cout << endl;
    cout << "Test finished." << endl;
}

/// main function
int main(int argc, char *argv[])
{
    srand(time(nullptr));
    {
        type v[]{1, 2, 2, 4, 4, 3, 7, 10, 15};
        constexpr int dim = sizeof(v) / sizeof(v[0]);
        test(v, dim);
    }
    {
        type v[]{1, 3, 7, 11, 13, 15, 16, 17};
        constexpr int dim = sizeof(v) / sizeof(v[0]);
        test(v, dim);
    }
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
    if (end-- > 0)
    {
        /// process a[end]
        cout << "processing a[" << end << "]" << endl;
        // process the rest
        backwardScanAll(a, end);
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
    if (begin < end)
    {
        /// process a[begin]
        cout << "processing a[" << begin << "]" << endl;
        /// process the rest
        forwardScan(a, end, begin + 1);
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
    if (end-- > begin)
    {
        /// process a[end]
        cout << "processing a[" << end << "]" << endl;
        /// process the rest
        backwardScan(a, end, begin);
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
    if (begin < end)
    {
        cout << "a[" << begin << "] = " << a[begin] << endl;
        toCout(a, end, begin + 1);
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
    if (end-- > begin)
    {
        cout << "a[" << end << "] = " << a[end] << endl;
        backwardToCout(a, end, begin);
    }
}
/**
 * Need some help here: [, ] and , are not recursive !!!
 */
void JSONHelp(const type a[], int end, int begin = 0, ostream &out = cout)
{
    if (begin < end)
    {
        out << ", " << a[begin];
        JSONHelp(a, end, begin + 1, out);
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
    if (begin < end)
    {
        out << a[begin];
        JSONHelp(a, end, begin + 1, out);
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
    if (begin < end)
    {
        a[begin] = begin;
        initIndex(a, end, begin + 1);
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
    if (begin < end)
    {
        a[begin] = min + rand() % (max - min + 1);
        initRandom(a, end, begin + 1, min, max);
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
    if (begin < end)
    {
        a[begin] = first;
        initAritmetica(a, end, begin + 1, first + delta, delta);
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
    if (begin < end)
    {
        a[begin] = first;
        initGeometrica(a, end, begin + 1, first * factor, factor);
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
    if (begin < end)
    {
        return a[begin] == value || contains(a, value, end, begin + 1);
    }
    else
    {
        return false;
    }
    // return begin >= end ? false : a[begin] == value || contains(a, value, end, begin + 1);
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
    if (begin < end)
    {
        return (a[begin] == value ? 1 : 0) + count(a, value, end, begin + 1);
    }
    else
    {
        return 0;
    }
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
    if (begin < end)
    {
        return a[begin] == value ? begin : firstIndexOf(a, value, end, begin + 1);
    }
    return end;
}
/**
 * Somewhat complicated ...
 */
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
    int result = end;
    if (end-- > begin)
    {
        if (a[end] == value)
            result = end;
        else
        {
            result = lastIndexOf(a, value, end, begin);
            if (result == end)
                result++;
        }
    }
    return result;
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
    if (++begin < end)
    {
        type other = max(a, end, begin);
        if (result < other)
            result = other;
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
    if (++begin < end)
    {
        type other = min(a, end, begin);
        if (result > other)
            result = other;
    }
    return result;
}

/**
 * Calcolo somma degli elementi da begin a end escluso: [begin, end)
 * @param a     l'array con i valori di cui calcolare la somma
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @return      la somma degli elementi, (ub se begin >= end)
 */
type sum(const type a[], int end, int begin /* = 0 */)
{
    type somma = a[begin];
    if (++begin < end)
    {
        somma += sum(a, end, begin);
    }
    return somma;
}

/**
 * Quite complicated ...
 */
/**
 * Calcolo media degli elementi da begin a end escluso: [begin, end)
 * @param a     l'array con i valori di cui calcolare la media
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @return      la media degli elementi, (ub se begin >= end)
 */
real mean(const type a[], int end, int begin /* = 0 */)
{
    /// mean of a[i] for i in [begin, end)

    real somma = a[begin];
    for (int i = ++begin; i < end; ++i)
    {
        somma = somma + a[i];
    }
    return somma / (end - begin);
}
/**
 * Calcolo prodotto degli elementi da begin a end escluso: [begin, end)
 * @param a     l'array con i valori di cui calcolare il prodotto
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 * @return      il prodotto degli elementi, (ub se begin >= end)
 */
type prod(const type a[], int end, int begin /* = 0 */)
{
    type product = 1; // empty product
    if (begin < end)
    {
        product = a[begin] * prod(a, end, begin + 1);
    }
    return product;
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
    if (begin + 1 >= end)
    { // nothing to be ordered
        return true;
    }
    return a[begin] <= a[begin + 1] && isOrdered(a, end, begin + 1);
}

/**
 * Rovescia gli elementi da begin a end escluso: [begin, end)
 * @param a     l'array con i valori da rovesciare
 * @param end   fine (esclusa) della scansione: a[end] non viene elaborato
 * @param begin inizio (incluso) della scansione: a[begin] e' il primo elemento elaborato
 */
void reverse(type a[], int end, int begin /* = 0 */)
{
    int inf = begin, sup = end - 1;
    if (inf < sup)
    {
        swap(a[inf], a[sup]);
        reverse(a, sup, inf + 1);
    }
}
/**
 * This is really stupid if recursive: we would be spreading sentinels everywhere ...
 */
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
 * same as above
 */
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
    if (DEBUG)
        cout << "Setting guard at " << begin << endl;
    type last = a[begin]; // save last element
    a[begin] = value;     // set guard
    int index = end - 1;
    while (a[index] != value)
    {
        index--; // next
    }
    if (DEBUG)
        cout << "Unsetting guard at " << begin << endl;
    a[begin] = last; // restore last element
    return a[index] == value ? index : end;
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
    if (grado == 0)
    {
        return coeff[grado];
    }
    return coeff[grado] + x * horner(coeff + 1, grado - 1, x);
    // return coeff[grado] + x * horner(&coeff[1], grado - 1, x);
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
 * really recursive, but too many conditions ...
 */
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
