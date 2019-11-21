/**
 * Gioco che consiste nel far indovinare all'utente un numero
 * Author:  ER
 * Date:    2019/10/01
 * Note:    
 */

#include <iostream>

using namespace std;

#define DEBUG 0

/// prototypes
int casualeTra(int min, int max);             /// valore casuale tra min e max
int getMaxNumber();                           /// estrae a caso in ]1, 20[
void printIstruzioni(int max, int tentativi); /// istruzioni per l'utente
void showStatus(int max, int tentativi);      /// mostra situazione all'utente
int getTentativo();                           /// acquisisce tentativo da utente
void showResult(int guess, bool indovinato);  /// mostra l'esito all'utente

int main(int argc, char *args[])
{
    /// inizializzazione gioco
    srand(time(nullptr));
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
        cout << "Congratulazioni! Hai indovinato." << endl;
    }
    else
    {
        /// sorry
        cout << "Mi dispiace! Non hai indovinato: il numero era " << valore << endl;
    }

    /// successful termination
    return 0;
}
/**
 * restiuisce un valore casuale tra min e max
 */
int casualeTra(int min, int max)
{
    return min + rand() % (max - min + 1);
}
/**
 * restituisce un numero casuale compreso tra 1 e 20 esclusi
 */
int getMaxNumber()
{
    return casualeTra(1, 9) * 2;
}
/**
 * mostra a video istruzioni per l'utente
 */
void printIstruzioni(int max, int tentativi)
{
    cout << "Devi indovinare un numero compreso tra 0 e " << max << " inclusi." << endl;
    cout << "Hai a disposizione " << tentativi << " tentativi." << endl;
    cout << endl;
}
/**
 * mostra situazione all'utente
 */
void showStatus(int max, int tentativi)
{
    cout << "Hai ancora " << tentativi << " tentativi." << endl;
}
/**
 * acquisisce tentativo da utente
 */
int getTentativo()
{
    int result;
    cout << "Fai un tentativo: ";
    cin >> result;
    return result;
}
/**
 * mostra l'esito all'utente
 */
void showResult(int guess, bool indovinato)
{
    cout << guess << (indovinato ? " e'" : " non e'") << " il numero giusto." << endl;
}
