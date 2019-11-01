/**
 * Programma di esempio
 * Author:  ER
 * Date:    2019/10/01
 * Note:    Il programma visualizza i parametri della riga comando
 *			Provare con: args 89ab 67, 42.78 ciccia 7.4
 *			Notare che la conversione dei valori non è molto sicura
 */

#include <stdio.h>

/// argc: numero di elementi di argv (>= 1)
/// argv: argc elementi (stringhe) con indice da 0 ad argc - 1
int main(int argc, char * argv[])
{
    /// argc >= 1 perchè argv[0] è il nome con cui è stato avviato il programma
    printf("Il programma è stato avviato con: '%s'\n", argv[0]);
    /// se argc > 1 allora sono stati usati anche dei parametri, almeno argv[1]
    if(argc > 1)
    {
        printf("I parametri sono %d:", argc - 1);
        char separator = ' ';
        for(int arg = 1, value; arg < argc; arg++) {
			printf("%c '%s'", separator, argv[arg]);
			/// (tentativo di) conversione ad intero
			if(sscanf(argv[arg], "%d", &value)) {
				printf(" = %d", value);
			}
			separator = ',';
        }
        printf(".\n");
    }
    else
    {
        printf("Non vi sono parametri.\n");
    }

    /// termine con codice 0 = successo
    return 0;
}
