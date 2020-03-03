/**
 * Purpose: base game application adapted to connect 4
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

#define BOARD_ROWS (6)
#define BOARD_COLUMNS (7)
#define MAX_MOVES (BOARD_ROWS * BOARD_COLUMNS)

// mossa (out format)
using mossa = char; // valid mossa '1' through '7'
#define MIN_MOVE '1'
#define MAX_MOVE '7'

// game status
struct game
{
    player turn;                  // il giocatore di turno
    int numPieces[BOARD_COLUMNS]; // how many pieces in a column
    int pieces[BOARD_COLUMNS];    // the pieces as bit 0 = HUMAN, 1 = COMPUTER
    player winner{NONE};          // il vincitore
    bool over{false};             // gioco finito
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
player getCell(int column, int row, const game &g);

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
    for (int row = BOARD_ROWS; row-- > 0;)
    {
        cout << endl;
        // cout << "---------------" << endl;
        cout << "|";
        for (int column = 0; column < BOARD_COLUMNS; column++)
        {
            switch (getCell(column, row, g))
            {
            case NONE:
                cout << " |";
                break;
            case HUMAN:
                cout << "X|";
                break;
            case COMPUTER:
                cout << "O|";
                break;
            }
        }
    }
    cout << endl;
    cout << "---------------" << endl;
    cout << "|";
    for (int column = 0; column < BOARD_COLUMNS; column++)
    {
        cout << (column + 1) << "|";
    }
    cout << endl;
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
            cout << "1..7: Try to win" << endl;
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
    for (int c = 0; c < BOARD_COLUMNS; c++)
    {
        g.numPieces[c] = g.pieces[c] = 0;
    }
    return g;
}

int countMore(const game &g, int row, int column, int deltaRow, int deltaColumn)
{
    int result = 0;
    for (int c = column - deltaColumn, r = row - deltaRow; c >= 0 && c < BOARD_COLUMNS && r >= 0 && r < g.numPieces[c] && getCell(c, r, g) == g.turn; c -= deltaColumn, r -= deltaRow)
    {
        result++;
    }
    for (int c = column + deltaColumn, r = row + deltaRow; c >= 0 && c < BOARD_COLUMNS && r >= 0 && r < g.numPieces[c] && getCell(c, r, g) == g.turn; c += deltaColumn, r += deltaRow)
    {
        result++;
    }
    return result;
}
// effettua una mossa se possibile
player checkWinner(const game &g, int column)
{
    if (countMore(g, g.numPieces[column] - 1, column, 1, 0) >= 3)
    {
        return g.turn;
    }
    if (countMore(g, g.numPieces[column] - 1, column, 0, 1) >= 3)
    {
        return g.turn;
    }
    if (countMore(g, g.numPieces[column] - 1, column, 1, 1) >= 3)
    {
        return g.turn;
    }
    if (countMore(g, g.numPieces[column] - 1, column, 1, -1) >= 3)
    {
        return g.turn;
    }
    return NONE;
}

void makeMove(const mossa m, game &g)
{
    if (!isOver(g))
    {
        if (isAllowedMove(m, g))
        {
            int column = m - '1';
            if (g.turn == COMPUTER)
            {
                g.pieces[column] |= 1 << g.numPieces[column];
            }
            g.numPieces[column]++;
            // check victory
            g.winner = checkWinner(g, column);
            g.turn = (player)(HUMAN + COMPUTER - g.turn);
            g.moves[g.numMoves] = m;
            g.numMoves++;
        }
    }
}
bool isAllowedMove(const mossa m, const game &g)
{
    int column = m - '1';
    return g.numPieces[column] < BOARD_ROWS;
}
mossa getComputerMove(const game &g)
{
    // check for winning moves
    for (mossa m = MIN_MOVE; m <= MAX_MOVE; m++)
    {
        // make a copy of the game
        game test = g;
        makeMove(m, test);
        if (winner(test) != NONE)
        {
            // it's me ...
            return m;
        }
    }
    // check for other player winning moves
    for (mossa m = MIN_MOVE; m <= MAX_MOVE; m++)
    {
        // make a copy of the game
        game test = g;
        test.turn = HUMAN;
        makeMove(m, test);
        if (winner(test) != NONE)
        {
            // it's him ...
            return m;
        }
    }
    mossa m;
    do
    {
        m = MIN_MOVE + rand() % (4) + rand() % 4; // central columns are better !!
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
player getCell(int column, int row, const game &g)
{
    if (row < g.numPieces[column])
    {
        return (g.pieces[column] & (1 << row)) == 0 ? HUMAN : COMPUTER;
    }
    return NONE;
}