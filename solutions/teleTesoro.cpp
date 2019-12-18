/**
    Purpose:    treasure hunt with teleportation, the usual way
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2019/12/01
    Note:
*/

// directive for standard io functions
#include <iostream>
// rand, probably needed in windows
#include <cstdlib>
// time, probably needed in windows
#include <ctime>

using namespace std;

#define MIN_COORD 0
#define MAX_COORD 1000

#define NORTH ('N')
#define SOUTH ('S')
#define EAST ('E')
#define WEST ('W')

// prototypes
int getPosition(const char prompt[]); // Get position from user
int randomBetween(int min, int max);  // Generate random number in range [min, max]

// funzione principale
int main(int argc, char *argv[])
{
    // seed
    srand(time(NULL));
    // treasure position
    int xTreasure = randomBetween(MIN_COORD, MAX_COORD), yTreasure = randomBetween(MIN_COORD, MAX_COORD);
    // allowed moves
    int allowedMoves = 10;
    // initial info
    cout << "Hi! You're in a square grid with coordinates beween " << MIN_COORD << " and " << MAX_COORD << " included." << endl;
    cout << "You can use teleportation to move around :-), but you're allowed to move only " << allowedMoves << " times." << endl;
    // let's start playing
    bool treasureFound = false;
    do
    {
        // player position (unknown)
        int xPlayer = getPosition("Choose your x coordinate: ");
        int yPlayer = getPosition("Choose your y coordinate: ");
        // one move less
        allowedMoves--;
        // check
        treasureFound = (xPlayer == xTreasure) && (yPlayer == yTreasure);
        // info to Player
        if (!treasureFound)
        {
            // direction to player
            cout << "The treasure is ";
            if (yPlayer < yTreasure)
            {
                cout << NORTH;
            }
            else if (yPlayer > yTreasure)
            {
                cout << SOUTH;
            }
            if (xPlayer < xTreasure)
            {
                cout << EAST;
            }
            else if (xPlayer > xTreasure)
            {
                cout << WEST;
            }
            cout << " from your position. You have " << allowedMoves << " teleportations left." << endl;
        }
    } while (!treasureFound && allowedMoves > 0); // not found and moves remaining
    // check whether we win or lose
    if (treasureFound)
    {
        cout << "Congratulations! You've found the treasure. We win :-)" << endl;
    }
    else
    {
        cout << "Sorry! You've not found the treasure. We lose :-)" << endl;
    }
    // successful termination
    return 0;
}

/**
 * Get position from user
 * @param   prompt  the user prompt
 * @return one int between MIN_COORD and MAX_COORD included
 */
int getPosition(const char prompt[])
{
    int result;
    do
    {
        // prompt for teleportation site
        cout << prompt;
        cin >> result;
    } while (result < MIN_COORD || result > MAX_COORD);
    return result;
}

/**
 * Generate random number in range [min, max]
 * @param min the lower bound
 * @param max the upper bound
 * @return a random int between min and max inclusive
 */
int randomBetween(int min, int max)
{
    return min + rand() % (max - min + 1);
}
