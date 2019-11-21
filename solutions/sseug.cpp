/**
 * Gioco che consiste nel far indovinare al programma un numero
 * Author:  ER
 * Date:    2019/10/01
 * Note:    
 */

#include <iostream>

using namespace std;

#define DEBUG 0

/// prototypes
int getMaxNumber();               /// ottiene max dall'utente
int casualeTra(int min, int max); /// valore casuale tra min e max
bool getResult();                 /// ottiene l'esito dall'utente

int main(int argc, char *args[])
{
    /// inizializzazione gioco
    srand(time(nullptr));
    int max = getMaxNumber(); /// impostazione range [0, max]
    int tentativi = max / 2;  /// numero tentativi ammessi (il banco ha un vantaggio)

    cout << "Ok! Devo indovinare un numero tra 0 e " << max << " in " << tentativi << " tentativi." << endl;
    int effettuati = 0;                 /// numero tentativi effettuati
    unsigned long long int tentati = 0; /// bitmap per i numeri già tentati

    bool indovinato = false; /// l'utente non ha (ancora) indovinato

    /// se l'utente ha tentativi e non ha indovinato
    while ((effettuati < tentativi) && (!indovinato))
    {
        int guess; /// il tentativo
        do
        {
            guess = casualeTra(0, max);             /// valore casuale tra 0 e max
        } while ((tentati & (1ULL << guess)) != 0); /// già tentato
        effettuati++;                               /// uno in più
        tentati |= (1ULL << guess);                 /// memorizzato
        cout << "Il mio " << effettuati << "° tentativo e' " << guess << endl;
        indovinato = getResult(); /// ottiene l'esito
    }
    /// stato finale
    if (indovinato)
    {
        /// congrats
        cout << "Congratulazioni! Ho indovinato." << endl;
    }
    else
    {
        /// sorry
        cout << "Mi dispiace! Non ho indovinato: qual era il numero?" << endl;
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
 * acquisisce un numero casuale pari compreso tra 2 e 18 inclusi
 */
int getMaxNumber()
{
    int result;
    do
    {
        cout << "Dimmi il numero massimo del range: ";
        cin >> result;
    } while ((result < 2) || (result > 18) || (result % 2 != 0));
    return result;
}
/**
 * ottiene l'esito dall'utente
 */
bool getResult()
{
    bool result;
    char answer;
    do
    {
        cout << "Ho indovinato? [Y/N] ";
        cin >> answer;
    } while ((answer != 'Y') && (answer != 'N'));
    result = answer == 'Y';
    return result;
}
