/**
 * Programma di esempio
 * Author:  ER
 * Date:    2019/10/01
 * Note:    Il programma esemplifica il costrutto do while
 * 			sintassi generale:
 * 			do { <blocco ripetizione> } while(<condizione>);
 * 				{ } non necessarie, ma consigliate!!!, se <blocco> è una singola istruzione
 *				Nota: <blocco ripetizione> è eseguito almeno una volta !!!
 *				N.B. : numero di valutazioni della condizione uguale a numero di esecuzioni del blocco
 *			Esempi di logica di ripetizione
 *			A.	Esecuzione operazione fino al successo
 *			B.	Scelta operazione con possibilità di termine
 *			C.	Esecuzione ripetuta fino a condizione di termine
 *			D.	... ovviamente i casi non si esauriscono qui
 *			La logica adattata al problema di stampare i primi n numeri dispari, n naturale
*/

#include <stdio.h>

int main (int argc, char* args[])
{
	/// A.	Esecuzione operazione fino al successo
	/// tipico caso: input utente con controllo
    {
        printf("Esempio di input di un dato intero < 10\n");
        printf("controllo con messaggio in caso di errore\n");
        ///    Dati input: a < 10
        int a = 10;	/// assegno un valore non valido
        do
        {
            printf("Immetti il valore di a: ");
            if(scanf("%d", &a) == 0)
            {
                /// dato non acquisito
                scanf("%*[^\n]");	/// elimina tutto fino al newline
                printf("Impossibile acquisire il dato\n");
            }
            else if(a >= 10)
            {
                printf("Dato errato: a dev'essere < 10\n");
                scanf("%*[^\n]");	/// elimina tutto fino al newline comunque?
            }
        }
        while(a >= 10);    /// while(non valido)
        printf("Il valore di a accettato e': %d \n", a);
    }
	/// B.	Scelta operazione con possibilità di termine
	/// tipico esempio: menu' di scelta con opzione di termine
    {
        int scelta = -1;
        do
        {
			printf("1. Greetings \n");
			printf("2. Quote \n");
			printf("0. Uscita \n");
            printf("Immetti la scelta: ");
            if(scanf("%d", &scelta) == 0)
            {
                /// dato non acquisito
                scanf("%*[^\n]");	/// elimina tutto fino al newline
                printf("scelta non valida\n");
            }
            else
            {
				if(scelta == 1) {
					printf("Ciao, mondo!\n");
				} else if(scelta == 2) {
					printf("I have a dream! (M.L.King)\n");
				} else if(scelta != 0) {
					printf("scelta non valida\n");
				}
            }
        }
        while(scelta != 0);    /// termine richieste
        printf("Arriverderci!\n");
    }
	/// C.	Esecuzione ripetuta fino a condizione di termine
	/// esempio: calcolo radice quadrata per approssimazioni successive
	{
		long double number = 2.0;
		long double oldSqrt, newSqrt = 1.0;
		do {
			oldSqrt = newSqrt;
			newSqrt = (oldSqrt + number / oldSqrt) / 2.0;
			/// newSqrt = (oldSqrt * oldSqrt + number) / (oldSqrt * 2.0);
			printf("sqrt(2) = %27.24Lf\n", newSqrt);
		} while(oldSqrt != newSqrt);
		printf("Finally sqrt(2) = %27.24Lf\n", newSqrt);
		printf("sqrt(2) * sqrt(2) = %27.24Lf\n", newSqrt * newSqrt);
	}

	/// termine con codice 0 = successo
    return 0;
}
