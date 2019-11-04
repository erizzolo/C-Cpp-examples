/**
    Stampa di un numero (intero non negativo) in formato binario
*/

#include <stdio.h>

#define DEBUG 1

int main (int argc, char* args[])
{
    /// input: un numero intero non negativo
    printf("Immetti un numero intero non negativo: ");
    unsigned long long int n;
    scanf("%llu", &n);
    /// verifica
    printf("n = %llu \n", n);
    unsigned long long int copia = n;		/// copia del dato di input per non modificarlo
    unsigned long long int reverse = 0;	/// bit a rovescio
    int nBits = 0;		/// numero di bits da visualizzare
    /// do while perche' almeno un bit verrà visualizzato
    do
    {
        /// prelevo il bit meno significativo
        unsigned long long int lsb = copia & 1;	// copia % 2
        /// traslo a destra gli altri
        copia >>= 1;			// copia = copia / 2;
        /// faccio spazio per l'inserimento
        reverse <<= 1;			// reverse = reverse * 2
        /// inserisco il bit estratto
        reverse |= lsb;			// reverse = reverse + lsb;
        /// estratto un bit in più
        nBits++;
        if(DEBUG)
        {
            printf("LSB = %llu, copia = %llu, reverse = %llu, nBits = %d \n", lsb, copia, reverse, nBits);
        }
    }
    while (copia != 0);
    /// ora visualizzo nBits cifre di reverse
    while(nBits > 0)
    {
        /// prelevo il bit meno significativo
        unsigned long long int lsb = reverse & 1;  /// reverse % 2
        /// traslo a destra gli altri
        reverse >>= 1; /// reverse = reverse / 2;
        printf("%llu", lsb);
        /// decremento numero bits da visualizzare
        nBits--;
    }
    printf("\n");
    /// successful termination
    return 0;
}

