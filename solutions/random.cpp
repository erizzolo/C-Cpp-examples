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
    // simple, but not random enough
    result = (rand8() << 8) + rand8();
    // use 1 bit from every call to rand8() (not very efficient but maybe more random)
    result = 0;
    for (int b = 0; b < 16; b++)
    {
        result = (result << 1) + (rand8() >= RAND8_MAX / 2 ? 0 : 1);
    }
    // some bit juggling
    int r1 = rand8(), r2 = rand8();
    // r1 = a7 a6 a5 a4 a3 a2 a1 a0
    // r2 = b7 b6 b5 b4 b3 b2 b1 b0
    result = ((r1 & 0xAA) << 8)   // a7 0  a5 0  a3 0  a1 0  0  0  0  0  0  0  0  0
             | ((r2 & 0xAA) << 7) // 0  b7 0  b5 0  b3 0  b1 0  0  0  0  0  0  0  0
             | ((r1 & 0x55) << 1) // 0  0  0  0  0  0  0  0  a6 0  a4 0  a2 0  a0 0
             | (r2 & 0x55);       // 0  0  0  0  0  0  0  0  0  b6 0  b4 0  b2 0  b0
                                  // a7 b7 a5 b5 a3 b3 a1 b1 a6 b6 a4 b4 a2 b2 a0 b0

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
    int calls = 10000000; /// should be enough ...
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
