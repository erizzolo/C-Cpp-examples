/**
 * Esempio di implementazione ricorsiva di funzioni
 * I casi classici: fattoriale, fibonacci, ...
 * GOOD LUCK !!!
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define DEBUG 1

#define TESTS 3      // number of tests
#define MAX_VALUE 40 // maximum number to try

// basic numeric type
using number = long long int;

/// prototipi delle funzioni
number getNumber(const char *prompt = "Input n: "); /// acquisisce da tastiera un numero, con prompt dato
number fattoriale(number n);
number fattorialeIterativo(number n);
number fibonacci(number n);
number fibonacciIterativo(number n);

/// the main function
int main(int argc, char *args[])
{
    srand(time(nullptr));
    for (int t = 0; t < TESTS; ++t)
    {
        number n = rand() % (MAX_VALUE + 1);
        cout << "n = " << n << endl;
        number fattIter = fattorialeIterativo(n);
        number fattRec = fattoriale(n);
        cout << n << "! = " << fattIter << " = " << fattRec << endl;
        number fibIter = fibonacciIterativo(n);
        number fibRec = fibonacci(n);
        cout << "fibonacci(" << n << ") = " << fibIter << " = " << fibRec << endl;
    }
    /// successful termination
    return 0;
}

/**
 * acquisisce da tastiera un numero, con prompt dato
 * @param   prompt  il messaggio per l'utente
 * @return  il numero acquisito da tastiera (si spera)
 */
number getNumber(const char *prompt /* = "Input n: " */)
{
    /// è comune dichiarare una variabile per il risultato
    number result;
    /// input: un numero intero non negativo
    cout << prompt;
    cin >> result;
    /// restituisce il dato acquisito
    return result;
}

number fattoriale(number n)
{
    if (DEBUG)
    {
        cout << "--> fattoriale(" << n << ")." << endl;
    }
    return n < 2 ? 1 : n * fattoriale(n - 1);
}
number fattorialeIterativo(number n)
{
    number result = 1;
    for (number factor = 2; factor <= n; ++factor)
    {
        result *= factor;
    }
    return result;
}
number fibonacci(number n)
{
    if (DEBUG)
    {
        cout << "--> fibonacci(" << n << ")." << endl;
    }
    return n < 2 ? n : fibonacci(n - 1) + fibonacci(n - 2);
}
number fibonacciIterativo(number n)
{
    if (n < 2)
    {
        return n;
    }
    else
    {
        number k = 2;               // current
        number f_k_2 = 0;           // f[k-2]
        number f_k_1 = 1;           // f[k-1]
        number f_k = f_k_1 + f_k_2; // f[k]
        while (k < n)
        {
            // compute next
            k++;
            f_k_2 = f_k_1;
            f_k_1 = f_k;
            f_k = f_k_1 + f_k_2;
        }
        return f_k;
    }
}
