/**
    Stampa di un numero (intero non negativo) in base 2..10
*/

#include <stdio.h>

#define DEBUG 1

/// prototype
/// prints n in radix base
void printWithBase(unsigned long long int n, unsigned long long int base);
int main(int argc, char *args[])
{
    /// input: un numero intero non negativo
    printf("Immetti un numero intero non negativo: ");
    unsigned long long int n;
    scanf("%llu", &n);
    /// verifica
    printf("n = %llu \n", n);
    /// input: base compresa tra 2 e 10 (inclusi)
    printf("Immetti la base: ");
    unsigned long long int base;
    scanf("%llu", &base);
    if ((2 <= base) && (base <= 10))
    {
        printWithBase(n, base);
    }
    else
    {
        printf("La base dev'essere compresa tra 2 e 10 inclusi\n");
    }
    /// successful termination
    return 0;
}

void printWithBase(unsigned long long int n, unsigned long long int base)
{

    unsigned long long int copia = n;   /// copia del dato di input per non modificarlo
    unsigned long long int reverse = 0; /// cifre a rovescio
    int nDigits = 0;                    /// numero di cifre da visualizzare
    /// do while perche' almeno una cifra verrà visualizzato
    do
    {
        /// prelevo la cifra meno significativo
        unsigned long long int lsd = copia % base;
        /// traslo a destra le altre
        copia /= base;
        /// faccio spazio per l'inserimento
        reverse *= base;
        /// inserisco la cifra estratta
        reverse += lsd;
        /// estratta una cifra in più
        nDigits++;
        if (DEBUG)
        {
            printf("lsd = %llu, copia = %llu, reverse = %llu, nDigits = %d \n", lsd, copia, reverse, nDigits);
        }
    } while (copia != 0);
    /// ora visualizzo nDigits cifre di reverse
    while (nDigits > 0)
    {
        /// prelevo la cifra meno significativo
        unsigned long long int lsd = reverse % base;
        /// traslo a destra le altre
        reverse /= base;
        printf("%llu", lsd);
        /// decremento numero cifre da visualizzare
        nDigits--;
    }
    printf("\n");
}