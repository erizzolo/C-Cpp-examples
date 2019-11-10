/**
 * Gioco che consiste nel far indovinare all'utente un numero
 * Author:  ER
 * Date:    2019/10/01
 * Note:    
 */

#include <iostream>

using namespace std;

#define DEBUG 0

int main(int argc, char *args[])
{
    /// inizializzazione gioco
    int max = getMaxNumber() & 0xFFFFFFFE; /// impostazione range [0, max] con max pari
    int tentativi = max / 2;               /// numero tentativi ammessi (il banco ha un vantaggio)
    int valore = casualeTra(0, max);       /// valore casuale tra 0 e max

    printIstruzioni(max, tentativi); /// istruzioni per l'utente

    bool indovinato = false; /// l'utente non ha (ancora) indovinato

    /// se l'utente ha tentativi e non ha indovinato
    while ((tentativi > 0) && (!indovinato))
    {
        showStatus(max, tentativi);    /// mostra situazione all'utente
        int guess = getTentativo();    /// acquisisce tentativo da utente
        --tentativi;                   /// un tentativo in meno
        indovinato = guess == valore;  /// ha indovinato ?
        showResult(guess, indovinato); /// mostra l'esito
    }
    /// stato finale
    if (indovinato)
    {
        /// congrats
    }
    else
    {
        /// sorry
    }

    /// successful termination
    return 0;
}
