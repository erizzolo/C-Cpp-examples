/**
 * Esempio di generazione numeri (pseudo)casuali
 * Author:  ER
 * Date:    2019/10/01
 * Note:    
 */

#include <iostream>
/// time function
#include <ctime>

using namespace std;

#define DEBUG 0

#define RAND8_MAX (255)
#define RAND16_MAX (65535)

/// prototypes
int rand8();           /// return a random number in the range [0,RAND8_MAX]
void srand8(int seed); /// sets the seed of the random generator

/**
 * return a random number in the range [0,2^16-1]
 * @return  a random number in the range [0,2^16-1]
 */
int rand16()
{
    int result;
    /// implementation missing...
    return result;
}

int main(int argc, char *args[])
{
    /// showing the range of the base rand8() function
    cout << "0 <= rand8() <= RAND8_MAX = " << RAND8_MAX << endl;
    /// see how many bits we have in a random number
    int bits = 0;
    unsigned int power = 1; /// 2^bits
    while (power < RAND8_MAX)
    {
        power <<= 1;
        ++bits;
    }
    cout << "0 <= rand8() <= RAND8_MAX = " << RAND8_MAX << " < " << power << " = 2^" << bits << endl;
    if (power == RAND8_MAX + 1)
    {
        cout << "rand8() gives exactly " << bits << " random bits." << endl;
    }
    else
    {
        cout << "rand8() gives less than " << bits << " random bits." << endl;
    }
    /// use for test: setting a given seed will give you the same random sequence
    cout << "Seeding with 42. Here are some random numbers: ";
    srand8(42);
    for (int number = 0; number < 10; ++number)
    {
        cout << rand8() << " ";
    }
    cout << endl
         << "Seeding again with 42. Here are some random numbers: ";
    srand8(42);
    for (int number = 0; number < 10; ++number)
    {
        cout << rand8() << " ";
    }
    /// use for real: setting a "random" seed will give you a random sequence
    cout << endl
         << "Seeding with current time. Here are some random numbers: ";
    srand8(time(NULL));
    for (int number = 0; number < 10; ++number)
    {
        cout << rand8() << " ";
    }
    cout << endl;
    /// checking the rand16() generator
    cout << "checking the rand16() generator..." << endl;
    int min = (1 << 16) - 1, max = 0;
    int calls = 1000000; /// should be enough ...
    while (calls > 0)
    {
        int random = rand16();
        if (min > random)
        {
            min = random;
        }
        else if (max < random)
        {
            max = random;
        }
        calls--;
    }
    cout << " found range [" << min << "," << max << "]" << endl;
    /// successful termination
    return 0;
}

/**
 * helper function
 * simple linear congruential generator;
 * @param   set     true to set the seed and return it,
 *                  false to get a random number
 * @param   newSeed the value of the new seed, if set is true, ignored otherwise
 * @return  if set is true, the seed itself, otherwise a random number in the range [0,RAND_MAX]
 */
int randHelper(bool set, int newSeed)
{
    static int seed = 0;
    const int a = 214013;
    const int c = 2531011;
    int result;
    if (set)
    {
        result = seed = newSeed;
    }
    else
    {
        result = seed = (a * seed + c) & RAND8_MAX;
    }
    return result;
}

/**
 * return a random number in the range [0,RAND8_MAX]
 * @return  a random number in the range [0,RAND8_MAX]
 */
int rand8()
{
    return randHelper(false, 0);
}

/**
 * sets the seed of the random generator
 * @param   seed    the value of the new seed
 */
void srand8(int seed)
{
    randHelper(true, seed);
}
