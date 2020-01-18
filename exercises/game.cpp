/**
 * Purpose: base game application
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/01/15
 * Note:
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define DEBUG 1

// logic data types to be precised (maybe later)
using configuration = int;
using command = char;
#define QUIT 'X'
#define NEW 'N'
#define TRY 'T'
#define SHOW 'S'

#define MAX_TENTATIVI 10

// data to be guessed
using guess = char;
// game status
struct game
{
    guess secret;                   // il segreto da indovinare
    int numTentativi{0};            // il numero di tentativi effettuati
    guess tentativi[MAX_TENTATIVI]; // i tentativi effettuati
    bool indovinato{false};         // l'utente ha indovinato
    bool hidden{true};              // lettera nascosta/mostrata all'utente
};

// mostra schermata di benvenuto
void showWelcomeScreen();
// nasconde schermata di benvenuto
void hideWelcomeScreen();
// carica e restituisce la configurazione dell'applicazione
configuration loadConfiguration();
// salva la configurazione dell'applicazione
void saveConfiguration(configuration);
// aggiorna schermata
void updateView(game);
// acquisisce comando utente
command getUserCommand(game);
// elabora comando utente
void processUserCommand(command, game &);
// genera un nuovo game
game newGame();
// chiede il tentativo all'utente e lo restituisce
guess askGuess();
// verifica se il tentativo � corretto
bool checkGuess(guess tentativo, game g);

/// main function
int main(int argc, char *argv[])
{
    srand(time(nullptr));
    showWelcomeScreen();
    configuration config = loadConfiguration();
    hideWelcomeScreen();
    command cmd;
    game g = newGame();
    do
    {
        updateView(g);
        cmd = getUserCommand(g);
        processUserCommand(cmd, g);
    } while (cmd != QUIT);
    saveConfiguration(config);
    /// successful termination
    return 0;
}
void showWelcomeScreen()
{
    cout << "Welcome to the game!!!" << endl;
}
void hideWelcomeScreen()
{
    cout << "Let's start!!!" << endl;
}
configuration loadConfiguration()
{
    cout << "Loading configuration..." << endl;
    return 42;
}
void saveConfiguration(configuration c)
{
    cout << "Saving configuration " << c << endl;
}

void updateView(game g)
{
    if (g.indovinato)
    {
        cout << "Hai indovinato al " << g.numTentativi << "° tentativo." << endl;
    }
    else if (g.hidden)
    {
        if (g.numTentativi >= MAX_TENTATIVI)
        {
            cout << "Non hai indovinato nei " << MAX_TENTATIVI << " tentativi concessi." << endl;
        }
        else
        {
            cout << "Non hai ancora indovinato: hai ancora " << MAX_TENTATIVI - g.numTentativi << " tentativi a disposizione." << endl;
        }
    }
    else
    {
        cout << "Non hai indovinato; come saprai, il segreto da indovinare era " << g.secret << "." << endl;
    }
}

command getUserCommand(game g)
{
    command cmd;
    cout << QUIT << ": Exit" << endl;
    cout << NEW << ": New game" << endl;
    if (g.hidden && !g.indovinato)
    {
        if (g.numTentativi < MAX_TENTATIVI)
        {
            cout << TRY << ": Try to guess the secret" << endl;
        }
        cout << SHOW << ": Show the secret" << endl;
    }
    cout << "Immetti scelta: ";
    cin >> cmd;
    return cmd;
}

void processUserCommand(command c, game &g)
{
    if (DEBUG)
        cout << "processing command " << c << endl;
    switch (c)
    {
    case TRY:
        if (g.hidden && !g.indovinato && g.numTentativi < MAX_TENTATIVI)
        {
            guess tentativo = askGuess();
            if (checkGuess(tentativo, g))
            {
                cout << "Hai indovinato" << endl;
                g.indovinato = true;
            }
            else
            {
                cout << "Non hai indovinato, riprova" << endl;
            }
            g.tentativi[g.numTentativi] = tentativo;
            g.numTentativi++;
        }
        break;
    case NEW:
        g = newGame();
        break;
    case SHOW:
        if (g.hidden && !g.indovinato)
        {
            cout << "Il segreto da indovinare era " << g.secret << endl;
            g.hidden = false;
        }
        break;
    case QUIT:
        break;
    default:
        cout << "comando non disponibile" << endl;
    }
}
game newGame()
{
    game g;
    g.secret = 'a' + rand() % ('z' - 'a' + 1);
    if (DEBUG)
        cout << "new game " << g.secret << endl;
    return g;
}
guess askGuess()
{
    guess result;
    cout << "Immetti il tentativo: ";
    cin >> result;
    return result;
}
bool checkGuess(guess tentativo, game g)
{
    return tentativo == g.secret;
}
