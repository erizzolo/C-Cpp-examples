/*
    Purpose:    binomial coefficients, different implementations
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2020/01/31
    Note:		with unsigned int type:
				(35,17)=(35,18) are too big (overflow...): no function can give the correct result
				but:
				already with (13,6)=(13,7) binomLibro gives a wrong result (factorial overflow)
				already with (31,15)=(31,16) binomFaster gives a wrong result (intermediate overflow)
				with unsigned long long int type:
				(68,34) is too big (overflow...): no function can give the correct result
				but:
				already with (21,10)=(21,11) binomLibro gives a wrong result (factorial overflow)
				already with (63,31)=(63,32) binomFaster gives a wrong result (intermediate overflow)
                (132,64) = 355355941143584435781233799677835771750 overflows even with 128 bits !!!

<pre>
Using __uint128_t (limiting time of Recursive to no more than 10s)
			Recurse	Memoize	Faster	Dynamic	Libro
(1, 0): 	0.005	0.002	0.001	0.002	0.001
(2, 1): 	0.002	0.001	0.002	0.001	0.001
(3, 1): 	0.001	0.001	0.002	0.001	0.002
(4, 2): 	0.001	0.001	0.002	0.001	0.002
(5, 2): 	0.002	0.001	0.001	0.001	0.002
(6, 3): 	0.002	0.001	0.002	0.001	0.002
(7, 3): 	0.002	0.001	0.001	0.001	0.001
(8, 4): 	0.003	0.001	0.001	0.001	0.002
(9, 4): 	0.004	0.001	0.002	0.001	0.002
(10, 5): 	0.007	0.002	0.001	0.002	0.002
(11, 5): 	0.015	0.002	0.001	0.001	0.002
(12, 6): 	0.024	0.001	0.001	0.002	0.001
(13, 6): 	0.039	0.001	0.001	0.002	0.001
(14, 7): 	0.071	0.002	0.001	0.001	0.002
(15, 7): 	0.13	0.001	0.002	0.002	0.001
(16, 8): 	0.257	0.002	0.001	0.001	0.001
(17, 8): 	0.485	0.001	0.001	0.001	0.002
(18, 9): 	0.987	0.001	0.001	0.001	0.001
(19, 9): 	1.822	0.001	0.001	0.002	0.001
(20, 10): 	3.641	0.002	0.002	0.002	0.001
(21, 10): 	6.153	0.001	0.002	0.001	0.001
(22, 11): 	7.257	0.001	0.001	0.001	0
(23, 11): 	14.543	0.001	0.001	0.001	0.001
(24, 12): 	29.003	0.001	0.001	0.002	0.001
(25, 12): 	53.995	0.001	0.001	0.002	0.001
(26, 13): 	106.667	0.001	0.001	0.002	0.001
(27, 13): 	205.232	0.001	0.001	0.001	0.001
(28, 14): 	410.244	0.001	0.001	0.001	0.001
(29, 14): 	793.311	0.001	0.002	0.001	0.001
(30, 15): 	1584.98	0.001	0.001	0.002	0.001
(31, 15): 	3081.45	0.001	0.001	0.002	0.001
(32, 16): 	6124.31	0.001	0.001	0.002	0.001
(33, 16): 	11903.6	0.001	0.001	0.002	0.002
(34, 17): 	time	0.001	0		0.001	0
(35, 17): 	time	0		0.001	0.001	over
(36, 18): 	time	0.001	0		0.002	over
(37, 18): 	time	0.001	0.001	0.002	over
(38, 19): 	time	0.001	0.001	0.002	over
(39, 19): 	time	0.001	0.001	0.002	over
(40, 20): 	time	0.001	0		0.002	over
(41, 20): 	time	0.001	0		0.001	over
(42, 21): 	time	0		0		0.002	over
(43, 21): 	time	0		0.001	0.002	over
(44, 22): 	time	0.001	0.001	0.002	over
(45, 22): 	time	0.001	0.001	0.002	over
(46, 23): 	time	0.001	0.001	0.002	over
(47, 23): 	time	0		0.001	0.002	over
(48, 24): 	time	0.001	0.001	0.002	over
(49, 24): 	time	0.001	0.001	0.003	over
(50, 25): 	time	0.001	0.001	0.003	over
(51, 25): 	time	0.001	0.001	0.003	over
(52, 26): 	time	0.001	0.001	0.003	over
(53, 26): 	time	0.001	0.001	0.005	over
(54, 27): 	time	0.001	0.003	0.002	over
(55, 27): 	time	0.001	0.003	0.003	over
(56, 28): 	time	0		0.001	0.003	over
(57, 28): 	time	0.001	0.001	0.004	over
(58, 29): 	time	0		0.001	0.003	over
(59, 29): 	time	0.001	0.001	0.003	over
(60, 30): 	time	0.001	0.001	0.003	over
(61, 30): 	time	0.001	0.002	0.003	over
(62, 31): 	time	0.001	0.001	0.003	over
(63, 31): 	time	0.001	0.002	0.003	over
(64, 32): 	time	0.001	0.001	0.004	over
(65, 32): 	time	0		0.001	0.004	over
(66, 33): 	time	0.001	0.002	0.004	over
(67, 33): 	time	0		0.001	0.004	over
(68, 34): 	time	0.001	0.001	0.004	over
(69, 34): 	time	0.001	0.001	0.004	over
(70, 35): 	time	0		0.001	0.005	over
(71, 35): 	time	0		0.001	0.005	over
(72, 36): 	time	0.012	0.002	0.005	over
(73, 36): 	time	0.004	0.002	0.005	over
(74, 37): 	time	0.006	0.002	0.005	over
(75, 37): 	time	0.003	0.002	0.005	over
(76, 38): 	time	0.004	0.002	0.005	over
(77, 38): 	time	0.001	0.002	0.005	over
(78, 39): 	time	0.004	0.002	0.005	over
(79, 39): 	time	0.002	0.002	0.005	over
(80, 40): 	time	0.005	0.002	0.005	over
(81, 40): 	time	0.003	0.002	0.006	over
(82, 41): 	time	0.007	0.002	0.006	over
(83, 41): 	time	0.002	0.002	0.006	over
(84, 42): 	time	0.005	0.002	0.006	over
(85, 42): 	time	0.003	0.002	0.007	over
(86, 43): 	time	0.005	0.002	0.006	over
(87, 43): 	time	0.003	0.002	0.007	over
(88, 44): 	time	0.007	0.002	0.006	over
(89, 44): 	time	0.003	0.002	0.007	over
(90, 45): 	time	0.005	0.002	0.007	over
(91, 45): 	time	0.003	0.002	0.007	over
(92, 46): 	time	0.005	0.002	0.007	over
(93, 46): 	time	0.003	0.002	0.008	over
(94, 47): 	time	0.006	0.002	0.007	over
(95, 47): 	time	0.002	0.002	0.008	over
(96, 48): 	time	0.006	0.002	0.008	over
(97, 48): 	time	0.002	0.002	0.008	over
(98, 49): 	time	0.005	0.002	0.008	over
(99, 49): 	time	0.003	0.003	0.008	over
(100, 50): 	time	0.005	0.003	0.008	over
(101, 50): 	time	0.007	0.002	0.009	over
(102, 51): 	time	0.002	0.003	0.009	over
(103, 51): 	time	0.006	0.003	0.009	over
(104, 52): 	time	0.003	0.002	0.01	over
(105, 52): 	time	0.006	0.002	0.01	over
(106, 53): 	time	0.002	0.002	0.01	over
(107, 53): 	time	0.006	0.003	0.009	over
(108, 54): 	time	0.003	0.003	0.01	over
(109, 54): 	time	0.006	0.002	0.01	over
(110, 55): 	time	0.003	0.003	0.01	over
(111, 55): 	time	0.005	0.002	0.011	over
(112, 56): 	time	0.003	0.003	0.01	over
(113, 56): 	time	0.005	0.003	0.01	over
(114, 57): 	time	0.003	0.003	0.01	over
(115, 57): 	time	0.006	0.003	0.011	over
(116, 58): 	time	0.002	0.002	0.012	over
(117, 58): 	time	0.006	0.002	0.011	over
(118, 59): 	time	0.002	0.002	0.011	over
(119, 59): 	time	0.005	0.003	0.011	over
(120, 60): 	time	0.003	0.003	0.012	over
(121, 60): 	time	0.006	0.003	0.012	over
(122, 61): 	time	0.003	0.003	0.012	over
(123, 61): 	time	0.006	0.003	0.013	over
(124, 62): 	time	0.003	0.003	0.012	over
(125, 62): 	time	0.006	0.003	0.013	over
(126, 63): 	time	0.003	over	0.013	over
(127, 63): 	time	0.005	over	0.013	over
(128, 64): 	time	0.003	over	0.014	over
(129, 64): 	time	0.006	over	0.013	over
(130, 65): 	time	0.006	over	0.014	over
(131, 65): 	time	0.003	over	0.015	over
</pre>


*/
// directive for standard io functions
#include <iostream>
// uncomment the following line to disable assertions
// #define NDEBUG
// directive for assertions
#include <assert.h>
// directive for clock()
#include <ctime>

using namespace std;

// numeric integer type: (unsigned) int, long, long long, __uint128_t
typedef unsigned long long int int_t;
// typedef __uint128_t int_t;   // use this if your environment supports __uint128_t
typedef __uint128_t largest_t;
// function type to compute a binomial coefficient
typedef int_t binomFunction_t(const int_t, const int_t);

// test result type
typedef struct
{
    int_t n, m, result, calls; // arguments, result and n° of calls
    double time;               // ms needed
} test_t;

#define MAX_N 132

// 5+1 different ways to compute (n m)
int_t binomRecursive(const int_t n, const int_t m);
int_t binomMemoization(const int_t n, const int_t m);
int_t binomFaster(const int_t n, const int_t m);
int_t binomDynamic(const int_t n, const int_t m);
int_t binomLibro(const int_t n, const int_t m);
// +1: just a precompiled table  ;-)
int_t binomPrecomp(const int_t n, const int_t m);
// ok, there's no simple way to make a table of __uint128_t .-) because we get a lot of
// warning: integer constant is too large for its type
// Hence, I will build it at runtime
largest_t binomTable[MAX_N][MAX_N];

// global function calls counter
int_t calls = 0;

bool debug = false;

/// used to cout << __uint128_t
std::ostream &
operator<<(std::ostream &dest, largest_t value)
{
    std::ostream::sentry s(dest);
    if (s)
    {
        char buffer[128];
        char *d = std::end(buffer);
        do
        {
            --d;
            *d = "0123456789"[value % 10];
            value /= 10;
        } while (value != 0);
        int len = std::end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len)
        {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

test_t testFunction(binomFunction_t func, const int_t n, const int_t m, const char name[], bool debugMode)
{
    test_t result;
    result.n = n;
    result.m = m;
    debug = debugMode;
    // cout << "here" << endl;
    if (debug)
        cout << "Testing " << name << "(" << n << "," << m << "). Debug is " << (debug ? "on" : "off") << endl;
    calls = 0;
    clock_t inizio = clock();
    result.result = func(n, m);
    clock_t fine = clock();
    result.time = 1000.0 * (fine - inizio) / CLOCKS_PER_SEC;
    result.calls = calls;
    if (debug)
        cout << "Result = " << result.result << " in " << result.time << " ms, " << calls << " function calls." << endl;
    return result;
}

int main(int argc, char *argv[])
{
    clock_t inizio = clock();
    // build the binomTable
    binomTable[0][0] = 1;
    for (int_t n = 1; n < MAX_N; ++n)
    {
        binomTable[n][0] = 1;
        for (int_t m = 1; m < MAX_N; ++m)
        {
            binomTable[n][m] = binomTable[n - 1][m - 1] + binomTable[n - 1][m];
        }
    }
    clock_t fine = clock();
    cout << "Built binomTable in " << (1000.0 * (fine - inizio) / CLOCKS_PER_SEC) << "ms." << endl;
    cout << "binomTable[" << MAX_N - 1 << "][" << (MAX_N - 1) / 2 << "] = " << binomTable[MAX_N - 1][(MAX_N - 1) / 2] << endl;
    binomFunction_t *funcs[6] = {&binomRecursive, &binomMemoization, &binomFaster, &binomDynamic, &binomLibro, &binomPrecomp};
    char names[6][30] = {"Recurse", "Memoize", "Faster", "Dynamic", "Libro", "Table"};
    bool overflow[6] = {false, false, false, false, false, false};
    bool times[6] = {false, false, false, false, false, false};
    cout << "Debug (y/n): ";
    char d;
    cin >> d;
    debug = d == 'y';
    for (int fun = 1; fun < 6; fun++)
    {
        cout << names[fun] << "(71,35):" << (*funcs[fun])(71, 35) << endl;
    }
    cout << "\t\t";
    for (int fun = 0; fun < 6; fun++)
    {
        cout << names[fun] << "\t";
    }
    cout << endl;
    for (int_t n = 1; n < MAX_N; n += 1)
    // for (int_t n = MAX_N - 1; n > 10; n -= 10)
    {
        int_t m = n / 2;
        cout << "(" << n << ", " << m << "): \t";
        for (int fun = 0; fun < 6; fun++)
        {
            if (overflow[fun] || times[fun])
            {
                cout << (overflow[fun] ? "over\t" : "time\t");
            }
            else
            {
                test_t result = testFunction(*funcs[fun], n, m, names[fun], d == 'y');
                if (d == 'y')
                    cout << "Testing correctness ... " << endl;
                if (result.result != binomTable[n][m])
                {
                    overflow[fun] = true;
                    cout << "over\t";
                }
                else
                {
                    cout << result.time << "\t";
                    if (result.time > 10000)
                    {
                        // 1 minute
                        times[fun] = true;
                    }
                }
            }
        }
        cout << endl;
    }
    // successful termination
    return 0;
}

/**
	Versione ricorsiva (n,m) = (n-1,m-1)+(n-1,m)
*/
int_t binomRecursive(const int_t n, const int_t m)
{
    calls++;
    if (debug)
        cout << "binomRecursive(" << n << "," << m << ") called " << calls << " times." << endl;
    int_t result;
    if (n == 0 || m == 0 || m == n)
    {
        result = 1;
    }
    else
    {
        result = binomRecursive(n - 1, m - 1) + binomRecursive(n - 1, m);
    }
    return result;
}

/**
	Versione ricorsiva con memoization (n,m) = (n-1,m-1)+(n-1,m)
*/
int_t binomMemoization(const int_t n, const int_t m)
{
    calls++;
    if (debug)
        cout << "binomMemoization(" << n << "," << m << ") called " << calls << " times." << endl;
    // NOTA: memorizzo soltanto gli elementi != 1
    static int_t values[MAX_N][MAX_N];
    int_t result;
    if (n == 0 || m == 0 || m == n)
    {
        result = 1;
    }
    else
    {
        if (values[n][m] == 0)
        {
            // not computed yet :-(
            values[n][m] = binomMemoization(n - 1, m - 1) + binomMemoization(n - 1, m);
        }
        result = values[n][m]; // already computed :-)
    }
    return result;
}

/**
	Versione iterativa ottimale (n,m) = n * (n-1)/2 * (n-2)/3 * ... * (n-m+1)/m
*/
int_t binomFaster(const int_t n, const int_t m)
{
    calls++;
    if (debug)
        cout << "binomFaster(" << n << "," << m << ") called " << calls << " times." << endl;
    int_t result;
    if (n == 0 || m == 0 || m == n)
    {
        result = 1;
    }
    else
    {
        if (m > n - m)
        {
            result = binomFaster(n, n - m); // simmetria :-)
        }
        else
        {
            result = n;
            int_t factor = n - 1, divisor = 2;
            while (divisor <= m)
            {
                result = (result * factor) / divisor;
                factor--;
                divisor++;
            }
        }
    }
    return result;
}

/**
	Versione "ricorsiva" con Dynamic Programming
*/
int_t binomDynamic(const int_t n, const int_t m)
{
    calls++;
    if (debug)
        cout << "binomDynamic(" << n << "," << m << ") called " << calls << " times." << endl;
    // NOTA: memorizzo soltanto gli elementi di una riga fino all'indice <= riga
    static int_t values[MAX_N];
    int_t result;
    if (n == 0 || m == 0 || m == n)
    {
        result = 1;
    }
    else
    {
        values[0] = 1; // always 1
        values[1] = 0;
        for (int_t row = 1; row <= n; row++)
        {
            values[row + 1] = 0;
            for (int_t pos = row; pos > 0; pos--)
            {
                values[pos] += values[pos - 1];
            }
        }
        result = values[m];
    }
    return result;
}

int_t fattoriale(const int_t n);
/**
    Versione del libro di testo
*/
int_t binomLibro(const int_t n, const int_t m)
{
    calls++;
    if (debug)
        cout << "binomLibro(" << n << "," << m << ") called " << calls << " times." << endl;
    if (debug)
    {
        cout << "n! = " << fattoriale(n) << endl;
        cout << "m! = " << fattoriale(m) << endl;
        cout << "(n-m)! = " << fattoriale(n - m) << endl;
        cout << "m!(n-m)! = " << fattoriale(m) * fattoriale(n - m) << endl;
    }
    int_t num = fattoriale(n), den = fattoriale(m) * fattoriale(n - m);
    if (den == 0)
        den = 1;
    return num / den;
}
int_t fattoriale(const int_t n)
{
    int_t result = 1;
    for (int_t factor = 2; factor <= n; factor++)
    {
        result *= factor;
    }
    return result;
}
/**
	Versione che usa la tabella precompilata (n,m) = [n][m]
*/
int_t binomPrecomp(const int_t n, const int_t m)
{
    calls++;
    if (debug)
        cout << "binomPrecomp(" << n << "," << m << ") called " << calls << " times." << endl;
    return binomTable[n][m];
}
