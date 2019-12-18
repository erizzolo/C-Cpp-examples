/**
    Purpose:    treasure hunt with teleportation, the other way round
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2019/12/01
    Note:
*/

// directive for standard io functions
#include <iostream>

using namespace std;

#define MIN_COORD 0
#define MAX_COORD 1000

#define NEITHER ('-')
#define NORTH ('N')
#define SOUTH ('S')
#define EAST ('E')
#define WEST ('W')

// update limits according to user response and returns true if exact coordinate
bool updateLimits(int &begin, int &end, const int middle, const char plusDirection, const char minusDirection, const char noDirection);

// funzione principale
int main(int argc, char *argv[])
{
    // prompt utente
    cout << "Assumptions:" << endl;
    cout << "I can move on points of integer coordinates (x,y) in a grid extending from (";
    cout << MIN_COORD << "," << MIN_COORD << ") to (" << MAX_COORD << "," << MAX_COORD << ")." << endl;
    cout << "I can move to whichever coordinates I like because I can use teleportation;" << endl;
    cout << "I will not try to move outside of the grid." << endl;
    cout << "After each move you will tell me whether the Treasure is North (N-> +y) or South (S-> -y) and East (E-> +x) or West (W->-x)." << endl;
    cout << "You will allow me to make 10 teleportations, enough to reach the treasure if my strategy is correct." << endl;
    cout << "Do you agree? [y/n] ";
    char agreement;
    cin >> agreement;
    if (agreement == 'y')
    {
        cout << "Good! Let's start..." << endl;
        // bounds
        int xBegin = MIN_COORD, yBegin = MIN_COORD, xEnd = MAX_COORD + 1, yEnd = MAX_COORD + 1, allowedMoves = 10;
        // coordinates found
        bool xExact = false, yExact = false, treasureFound = false;

        do
        {
            // best movement to middle of the available grid
            int xDelta = xEnd - xBegin, yDelta = yEnd - yBegin;
            int xStep = xDelta / 2, yStep = yDelta / 2;
            int xMiddle = xBegin + xStep, yMiddle = yBegin + yStep;
            cout << "I will beam myself at " << xMiddle << "," << yMiddle << " now!" << endl;
            // get current direction N/S and E/W if needed
            yExact = yDelta == 1 || updateLimits(yBegin, yEnd, yMiddle, NORTH, SOUTH, NEITHER);
            xExact = xDelta == 1 || updateLimits(xBegin, xEnd, xMiddle, EAST, WEST, NEITHER);
            // check if we found the treasure
            if (xExact && yExact)
            {
                cout << "Great! I got to the treasure :-) But I'm busy now and have to leave... please keep it safe for me!" << endl;
                treasureFound = true;
            }
            allowedMoves--;
        } while (allowedMoves > 0 && !treasureFound);
    }
    else
    {
        cout << "Sorry. It's been a pleasure. See you soon :-)" << endl;
    }
    // successful termination
    return 0;
}

// update limits according to user response and returns true if exact coordinate
bool updateLimits(int &begin, int &end, const int middle, const char plusDirection, const char minusDirection, const char noDirection)
{
    char direction;
    do
    {
        cout << "Please tell me if the Treasure is " << plusDirection << " or " << minusDirection << " or neither (" << noDirection << "): ";
        cin >> direction;
    } while (direction != plusDirection && direction != minusDirection && direction != noDirection);
    if (direction == plusDirection)
    {
        begin = middle + 1; // update minimum
    }
    else if (direction == minusDirection)
    {
        end = middle; // update maximum
    }
    else
    {
        end = 1 + (begin = middle); // update both
    }
    return direction == noDirection;
}