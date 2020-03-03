/**
 * Purpose: base game application adapted to tris
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
#define PCMOVE 'P'

enum player
{
    NONE,
    HUMAN,
    COMPUTER
};

#define BOARD_DIM (3)
#define MAX_MOVES (BOARD_DIM * BOARD_DIM)

// mossa (out format)
using mossa = char; // valid mossa '1' through '9'
#define MIN_MOVE '1'
#define MAX_MOVE '9'

// game status
struct game
{
    player turn;             // il giocatore di turno
    player board[MAX_MOVES]; // la scacchiera
    player winner{NONE};     // il vincitore
    bool over{false};        // gioco finito
    // history, not really needed
    int numMoves{0};        // il numero di mosse effettuate
    mossa moves[MAX_MOVES]; // le mosse effettuate
};

// mostra schermata di benvenuto
void showWelcomeScreen();
// nasconde schermata di benvenuto
void hideWelcomeScreen();
// carica e restituisce la configurazione dell'applicazione
configuration loadConfiguration();
// salva la configurazione dell'applicazione
void saveConfiguration(configuration);
// acquisisce comando utente
command getUserCommand(const game &g);
// elabora comando utente
void processUserCommand(command, game &g);

// aggiorna schermata
void updateView(const game &g);

// genera un nuovo game
game newGame();
// effettua una mossa se possibile
void makeMove(const mossa m, game &g);
bool isAllowedMove(const mossa m, const game &g);
mossa getComputerMove(const game &g);
// info about the game
bool isOver(const game &g);
player winner(const game &g);
player getCell(int cell, const game &g);

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

void showBoard(const game &g)
{
    for (int c = 0; c < MAX_MOVES; c++)
    {
        if (c % BOARD_DIM == 0)
        {
            cout << endl;
            cout << "-------" << endl;
            cout << "|";
        }
        switch (getCell(c, g))
        {
        case NONE:
            cout << (c + 1) << "|";
            break;
        case HUMAN:
            cout << "X|";
            break;
        case COMPUTER:
            cout << "O|";
            break;
        }
    }
    cout << endl;
    cout << "-------" << endl;
}
void updateView(const game &g)
{
    showBoard(g);
    if (isOver(g))
    {
        switch (winner(g))
        {
        case NONE:
            cout << "Nobody wins!" << endl;
            break;
        case HUMAN:
            cout << "You win!" << endl;
            break;
        case COMPUTER:
            cout << "Computer wins!" << endl;
            break;
        }
    }
    else
    {
        if (g.turn == HUMAN)
        {
            cout << "It's your turn!" << endl;
        }
    }
}

command getUserCommand(const game &g)
{
    command cmd;
    cout << QUIT << ": Exit" << endl;
    cout << NEW << ": New game" << endl;
    if (!isOver(g))
    {
        if (g.turn == HUMAN)
        {
            cout << "1..9: Try to win" << endl;
        }
        else
        {
            return PCMOVE;
        }
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
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        if (!isOver(g))
        {
            if (isAllowedMove(c, g))
            {
                makeMove(c, g);
            }
            else
            {
                cout << "Mossa non ammessa, riprova" << endl;
            }
        }
        break;
    case NEW:
        g = newGame();
        break;
    case QUIT:
        break;
    case PCMOVE:
        makeMove(getComputerMove(g), g);
        break;
    default:
        cout << "comando non disponibile" << endl;
    }
}

// genera un nuovo game
game newGame()
{
    game g;
    g.turn = rand() % 2 == 0 ? HUMAN : COMPUTER;
    for (int c = 0; c < MAX_MOVES; c++)
    {
        g.board[c] = NONE;
    }
    return g;
}

// effettua una mossa se possibile
player checkWinner(player board[], int cell)
{
    int col = cell % 3;
    int row = cell - col;
    if (board[col] == board[col + 3] && board[col] == board[col + 6])
        return board[cell];
    if (board[row] == board[row + 1] && board[row] == board[row + 2])
        return board[cell];
    if (cell % 4 == 0)
    {
        if (board[0] == board[4] && board[4] == board[8])
            return board[cell];
    }
    if (col + row / 3 == 2)
    {
        if (board[2] == board[4] && board[4] == board[6])
            return board[cell];
    }
    return NONE;
}

void makeMove(const mossa m, game &g)
{
    if (!isOver(g))
    {
        if (isAllowedMove(m, g))
        {
            int cell = m - '1';
            g.board[cell] = g.turn;
            // check victory
            g.winner = checkWinner(g.board, cell);
            g.turn = (player)(HUMAN + COMPUTER - g.turn);
            g.moves[g.numMoves] = m;
            g.numMoves++;
        }
    }
}
bool isAllowedMove(const mossa m, const game &g)
{
    int cell = m - '1';
    return g.board[cell] == NONE;
}
mossa getComputerMove(const game &g)
{
    mossa m;
    do
    {
        m = MIN_MOVE + rand() % (MAX_MOVE - MIN_MOVE + 1);
    } while (!isAllowedMove(m, g));
    return m;
}
// info about the game
bool isOver(const game &g)
{
    return g.winner != NONE || g.numMoves == MAX_MOVES;
}
player winner(const game &g)
{
    return g.winner;
}
player getCell(int cell, const game &g)
{
    return g.board[cell];
}