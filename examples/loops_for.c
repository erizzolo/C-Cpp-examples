/**
 * Programma di esempio
 * Author:  ER
 * Date:    2019/10/01
 * Note:    Il programma esemplifica il costrutto for
 * 			sintassi generale:
 * 			for(<inizializzazione>; <condizione>; <aggiornamento>) { <blocco ripetizione> }
 * 				{ } non necessarie, ma consigliate!!!, se <blocco> è una singola istruzione
 *				Nota: <inizializzazione>, <condizione>, <aggiornamento> sono opzionali
 *					  ma se mancano probabilmente è meglio non usare il for !!!
 *				N.B. : numero di valutazioni della condizione uguale a:
 *					   numero di esecuzioni del blocco (risultato: condizione vera)
 *					   + 1 (l'ultima, con risultato: condizione falsa)
 *			Esempi di logica di ripetizione
 *			A.	In base alle operazioni residue
 *			B.	In base elle operazioni effettuate
 *			C.	In base al raggiungimento dell'obiettivo
 *			D.	... ovviamente i casi non si esauriscono qui
 *			La logica adattata al problema di stampare i primi n numeri dispari, n naturale
*/

#include <stdio.h>

/// per (dis)attivare in modo rapido output di debug
#define DEBUG 1

int main (int argc, char* args[])
{
    {
        int n = 5;
        /// A.	In base alle operazioni residue
        /// Ripetizione mentre ci sono operazioni residue
        if(DEBUG) printf("Before for:\n");
        for(int residue = n, dispari = 1; residue > 0; residue--, dispari += 2)
        {
            if(DEBUG) printf("For: Operazioni residue = %d \n", residue);
            /// effettua una operazione !
            printf("Numero dispari = %d \n", dispari);
        }
        /// fine !!!
        if(DEBUG) printf("End for:\n");
    }
    {
        int n = 5;
        /// B.	In base elle operazioni effettuate
        /// Ripetizione mentre le operazioni effettuate sono inferiori a quelle necessarie
        if(DEBUG) printf("Before for:\n");
        for(int necessarie = n, effettuate = 0, dispari = 1; effettuate < necessarie; effettuate++, dispari +=2)
        {
            if(DEBUG) printf("For: Operazioni necessarie = %d, effettuate = %d \n", necessarie, effettuate);
            /// effettua una operazione !
            printf("Numero dispari = %d \n", dispari);
        }
        /// fine !!!
        if(DEBUG) printf("End for:\n");
    }
    {
        int n = 5;
        /// C.	In base al raggiungimento dell'obiettivo
        /// Ripetizione mentre non ho raggiunto l'obiettivo
        if(DEBUG) printf("Before for:\n");
        for(int obiettivo = 2 * n - 1, raggiunto = -1, dispari = 1; raggiunto != obiettivo; raggiunto = dispari, dispari +=2)
        {
            if(DEBUG) printf("For: raggiunto = %d, obiettivo = %d \n", raggiunto, obiettivo);
            /// effettua una operazione !
            printf("Numero dispari = %d \n", dispari);
        }
        /// fine !!!
        if(DEBUG) printf("End For: \n");
    }

	/// termine con codice 0 = successo
    return 0;
}
