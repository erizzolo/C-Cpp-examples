/**
 * Programma di esempio
 * Author:  ER
 * Date:    2019/10/01
 * Note:    Il programma esemplifica il costrutto switch
 * 			sintassi generale:
 * 			switch(<espressione>) {
 *				case <valore 1>:
 *					<blocco per caso 1>
 *					break;
 *				case <valore 2>:
 *					<blocco per caso 2>
 *					break;
 *					... e così via
 *				case <valore n>:
 *					<blocco per caso n>
 *					break;
 *				default:
 *					<blocco per casi rimanenti>
 *			}
 * 			N.B. : 	l'espressione dev'essere un risultato intero
 * 					il caso default è opzionale
 *					unico caso in cui ammissibile usare break
 *					senza break l'esecuzione continua col blocco per il caso successivo
 *					( a volte è utile: vedere esempio mesi )
 */

#include <stdio.h>

int main(int argc, char * argv[])
{
    /// Assegnazione numero di giorni in base al mese
    /// 1 = gennaio, ..., 12 = dicembre
    for(int mese = 0; mese <= 12; mese++)
    {
        int giorni;
        switch(mese)
        {
        case 1:	/// fall-through
        case 3:	/// fall-through
        case 5:	/// fall-through
        case 7:	/// fall-through
        case 8:	/// fall-through
        case 10:	/// fall-through
        case 12:	/// fall-through
            giorni = 31;
            break;
        case 2:
            giorni = 28;	/// anno non bisestile
            break;
        case 4:	/// fall-through
        case 6:	/// fall-through
        case 9:	/// fall-through
        case 11:	/// fall-through
            giorni = 30;
            break;
        default:
            giorni = 0;
        }
        printf("Il mese %d ha %d giorni\n", mese, giorni);
    }
    /// menu' di scelta con opzione di termine
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
            switch(scelta)
            {
            case 1:
                printf("Ciao, mondo!\n");
                break;
            case 2:
                printf("I have a dream! (M.L.King)\n");
                break;
            case 0:
                break;
            default:
                printf("scelta non valida\n");
            }
        }
    }
    while(scelta != 0);    /// termine richieste
    printf("Arriverderci!\n");

    /// termine con codice 0 = successo
    return 0;
}
