/**
    Purpose:    treasure hunt, the other way round
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2019/10/01
    Note:
*/

// directive for standard io functions
#include <iostream>
// math functions
#include <cmath>

using namespace std;

#define NOWHERE (0)
#define NORTH (1)
#define SOUTH (2)
#define EAST (4)
#define WEST (8)

#define OUT_NORTH ('N')
#define OUT_SOUTH ('S')
#define OUT_EAST ('E')
#define OUT_WEST ('W')

typedef unsigned char dir_t;
typedef int coord_t;

// returns if the direction is allowed from x,y, given a grid of width w annd height h
bool isAllowed(const dir_t direction, const coord_t x, const coord_t y, const coord_t w, const coord_t h);
// returns the character indicating the direction
char symbolOfDirection(const dir_t direction);
// changes the position according to direction
void move(const dir_t direction, coord_t &x, coord_t &y);
// compute distance between two points
double distanceBetween(const int x1, const int y1, const int x2, const int y2);

// funzione principale
int main(int argc, char *argv[])
{
    // prompt utente
    cout << "Assumptions:" << endl;
    cout << "I can move on points of integer coordinates (x,y) in a grid extending from (0,0) to (width-1,height-1);" << endl;
    cout << "I can move either North (N-> +y), South (S-> -y), East (E-> +x) or West (W->-x);" << endl;
    cout << "I will not try to move outside of the grid;" << endl;
    cout << "you will tell me the width and height of the grid and my starting position x and y coordinates;" << endl;
    cout << "before each move you will tell me the distance between me and the treasure with at least two decimal digits of precision;" << endl;
    cout << "you will allow me to make a fair number of moves, enough to reach the treasure if my strategy is correct." << endl;
    cout << "Do you agree? [y/n] ";
    char agreement;
    cin >> agreement;
    if (agreement == 'y')
    {
        cout << "Good! Let's start..." << endl;
        // grid dimensions
        int width, height;
        do
        {
            cout << "Please tell me how wide and high is the grid: ";
            cin >> width >> height;
        } while ((width <= 0) || (height <= 0));
        // possible treasure location
        bool possible[width][height];
        int countPossible = width * height;
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                possible[x][y] = true;
            }
        }
        // starting coordinates
        int xStart, yStart;
        do
        {
            cout << "Please tell me my starting coordinates (x y): ";
            cin >> xStart >> yStart;
        } while ((xStart < 0) || (xStart >= width) || (yStart < 0) || (yStart >= height));
        // allowed moves
        int allowedMoves;
        do
        {
            cout << "Please tell me how many moves you allow me to make: ";
            cin >> allowedMoves;
        } while (allowedMoves <= 0);
        // Let's start playing
        int moves = 0;
        bool gameOver = false;
        // distance from treasure
        double distance = INFINITY, oldDistance;
        // directions
        unsigned char direction = NOWHERE;
        do
        {
            oldDistance = distance;
            // get current distance
            do
            {
                cout << "Please tell me how distant I am from the treasure: ";
                cin >> distance;
            } while (distance < 0);
            // check if we found the treasure
            if (distance == 0)
            {
                cout << "Great! I got to the treasure :-) But I'm busy now and have to leave... please keep it safe for me!" << endl;
                gameOver = true;
            }
            else
            {
                // not yet ... see how many possible locations left
                int xPossible, yPossible;
                // cout << "Possible locations:";
                for (int x = 0; x < width; x++)
                {
                    for (int y = 0; y < height; y++)
                    {
                        if (possible[x][y])
                        {
                            if (fabs(distanceBetween(x, y, xStart, yStart) - distance) < 0.01 * distance)
                            {
                                // cout << "(" << x << "," << y << ") ";
                                xPossible = x;
                                yPossible = y;
                            }
                            else
                            {
                                possible[x][y] = false;
                                countPossible--;
                            }
                        }
                    }
                }
                // cout << countPossible << "." << endl;
                if (countPossible == 0)
                {
                    cout << "What the hell! You don't know how to compute a distance???" << endl;
                }
                else
                {
                    if (xPossible > xStart)
                    {
                        direction = EAST;
                    }
                    else if (xPossible < xStart)
                    {
                        direction = WEST;
                    }
                    else if (yPossible > yStart)
                    {
                        direction = NORTH;
                    }
                    else if (yPossible < yStart)
                    {
                        direction = SOUTH;
                    }
                    else
                    {
                        direction = NOWHERE;
                    }
                }
                if (countPossible == 1)
                {
                    cout << "I know where the treasure is :-) it's at " << xPossible << "," << yPossible << endl;
                }
                // if not first move
                if (moves > 0)
                {
                    if (distance < oldDistance)
                    {
                        cout << "Good, I'm getting nearer to the treasure :-)" << endl;
                    }
                    else if (distance > oldDistance)
                    {
                        cout << "That was a bad move, I'm getting farther from the treasure :-(" << endl;
                    }
                    else
                    {
                        cout << "That's absolutely unfair... I moved without changing the distance: what kind of planet is this ?? !!!" << endl;
                    }
                }
                moves++;
                // make it
                cout << "My move is: " << symbolOfDirection(direction) << endl;
                move(direction, xStart, yStart);
            }
        } while (moves < allowedMoves && !gameOver);
    }
    else
    {
        cout << "Sorry. It's been a pleasure. See you soon :-)" << endl;
    }
    // successful termination
    return 0;
}

// returns if the direction is allowed from x,y, given a grid of width w annd height h
bool isAllowed(const dir_t direction, const coord_t x, const coord_t y, const coord_t w, const coord_t h)
{
    bool allowed;
    switch (direction)
    {
    case NORTH:
        allowed = y < (h - 1);
        break;
    case SOUTH:
        allowed = y > 0;
        break;
    case EAST:
        allowed = x < (w - 1);
        break;
    case WEST:
        allowed = x > 0;
        break;
    }
    return allowed;
}

// returns the character indicating the direction
char symbolOfDirection(const dir_t direction)
{
    char symbol;
    switch (direction)
    {
    case NORTH:
        symbol = OUT_NORTH;
        break;
    case SOUTH:
        symbol = OUT_SOUTH;
        break;
    case EAST:
        symbol = OUT_EAST;
        break;
    case WEST:
        symbol = OUT_WEST;
        break;
    }
    return symbol;
}

// changes the position according to direction
void move(const dir_t direction, coord_t &x, coord_t &y)
{
    switch (direction)
    {
    case NORTH:
        y++;
        break;
    case SOUTH:
        y--;
        break;
    case EAST:
        x++;
        break;
    case WEST:
        x--;
        break;
    }
}

// compute distance between two points
double distanceBetween(const int x1, const int y1, const int x2, const int y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
