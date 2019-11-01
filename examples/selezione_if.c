/**
 * Programma di esempio
 * Author:  ER
 * Date:    2019/10/01
 * Note:    Il programma esemplifica il costrutto if - else
 * 			sintassi generale:
 * 			if(<condizione>) { <blocco se vera> } [ else { <blocco se falsa> }]
 * 				[ parte opzionale ]
 * 				{ } non necessarie, ma consigliate!!!, se <blocco> è una singola istruzione
 */

#include <stdio.h>

int main(int argc, char * argv[])
{
    /// Per gli esempi, saranno utilizzati 3 interi
    /// lettura tre numeri interi a, b e c
    printf("Immetti tre numeri a, b e c: ");
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    /// Esempio 1: selezione senza alternativa
    {
        if(a > 0)
        {
            printf("Il valore a = %d e' positivo\n", a);
        }
    }
    /// Esempio 2: selezione con alternativa
    {
        if(b < 0)
        {
            printf("Il valore b = %d e' negativo\n", b);
        }
        else
        {
            printf("Il valore b = %d e' positivo o nullo\n", b);
        }
    }
    /// Esempio 3: selezione con alternativa = selezione
    {
        if(a < b)
        {
            printf("Il valore a = %d e' minore del valore b = %d\n", a, b);
        }
        else if(a == b)
        {
            printf("Il valore a = %d e' uguale al valore b = %d\n", a, b);
        }
        else
        {
            printf("Il valore a = %d e' maggiore del valore b = %d\n", a, b);
        }
    }
    /// Esempio 4: selezione con condizione composta &&
    {
        /// test appartenenza ad intervallo [min, max]
        int min = 1, max = 10;
        if((min <= c) && (c <= max))
        {
            printf("Il valore c = %d appartiene all'intervallo [%d, %d]\n", c, min, max);
        }
    }
    /// Esempio 4b: selezione con condizione composta && trasformata in doppio if
    {
        /// test appartenenza ad intervallo [min, max]
        int min = 1, max = 10;
        if(min <= c)
        {
            if (c <= max)
            {
                printf("Il valore c = %d appartiene all'intervallo [%d, %d]\n", c, min, max);
            }
        }
    }
    /// termine con codice 0 = successo
    return 0;
}
