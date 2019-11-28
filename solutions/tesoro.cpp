/**
    Purpose:    treasure hunt, the usual way
    Author:     Emanuele Rizzolo
    Class:      3XIN
    Date:       2019/10/01
    Note:
*/

// directive for standard io functions
#include <iostream>
// math functions
#include <cmath>
// time
#include <ctime>

using namespace std;

#define MAX_DIM 20
#define MIN_DIM 5

#define NORTH ('N')
#define SOUTH ('S')
#define EAST ('E')
#define WEST ('W')

// prototypes
char getDirection();												 // Get direction from user
int randomBetween(int min, int max);								 // Generate random number in range [min, max]
bool isAllowed(char direction, int x, int y, int width, int height); // Check if direction is allowed
int newXPlayer(char direction, int xPlayer);						 // Compute new xPlayer
int newYPlayer(char direction, int yPlayer);						 // Compute new yPlayer
int manhattanDistance(int x1, int y1, int x2, int y2);				 // Compute Manhattan distance between two points
double euclideanDistance(int x1, int y1, int x2, int y2);			 // Compute euclidean distance between two points
// funzione principale
int main(int argc, char *argv[])
{
	// seed
	srand(time(NULL));
	// grid dimension
	int width = randomBetween(MIN_DIM, MAX_DIM), height = randomBetween(MIN_DIM, MAX_DIM);
	// player position
	int xPlayer = randomBetween(0, width - 1), yPlayer = randomBetween(0, height - 1);
	// treasure position
	int xTreasure = randomBetween(0, width - 1), yTreasure = randomBetween(0, height - 1);
	// allowed moves (allows taking the wrong direction twice)
	int allowedMoves = manhattanDistance(xPlayer, yPlayer, xTreasure, yTreasure) + 4;
	// actual number of moves
	int moves = 0;
	// initial info
	cout << "Hi! You're in a grid " << width << " wide and " << height << " high." << endl;
	cout << "You're allowed to move " << allowedMoves << " times." << endl;
	// distance from treasure
	double distance;
	// let's start playing
	do
	{
		// distance from treasure
		distance = euclideanDistance(xPlayer, yPlayer, xTreasure, yTreasure);
		// info to Player
		if (distance > 0)
		{
			cout << "You're at (" << xPlayer << "," << yPlayer << "), and you're " << distance << " away from the Treasure." << endl;
			// get direction
			char direction = getDirection();
			// check if allowed
			if (isAllowed(direction, xPlayer, yPlayer, width, height))
			{
				xPlayer = newXPlayer(direction, xPlayer);
				yPlayer = newYPlayer(direction, yPlayer);
				moves++;
			}
			else
			{
				cout << "You can't move " << direction << endl;
			}
		}
	} while (distance > 0 && moves < allowedMoves); // not found and moves remaining
	// check whether we win or lose
	if (distance == 0)
	{
		cout << "Congratulations! You've found the treasure in " << moves << " moves. We win :-)" << endl;
	}
	else
	{
		cout << "Sorry! You've not found the treasure in " << moves << " moves. We lose :-)" << endl;
	}
	// successful termination
	return 0;
}

/**
 * Get direction from user
 * @return one of N, S, E, W
 */
char getDirection()
{
	char result;
	do
	{
		cout << "In which direction do you want to move [N,S,E,W]? "; // prompt for direction
		cin >> result;
	} while (result != NORTH && result != SOUTH && result != EAST && result != WEST);
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

/**
 * Check if direction is allowed
 * @param direction the direction
 * @param x current xPlayer
 * @param y current yPlayer
 * @param width maximum xPlayer + 1
 * @param height maximum yPlayer + 1
 * @return true if move in direction is allowed, false otherwise
 */
bool isAllowed(char direction, int x, int y, int width, int height)
{
	bool result;
	switch (direction)
	{
	case NORTH:
		result = y < height - 1;
		break;
	case SOUTH:
		result = y > 0;
		break;
	case EAST:
		result = x < width - 1;
		break;
	case WEST:
		result = x > 0;
		break;
	default:
		result = false;
	}
	return result;
}

/**
 * Compute new xPlayer
 * @param direction the direction
 * @param xPlayer current xPlayer
 * @return new xPlayer position
 */
int newXPlayer(char direction, int xPlayer)
{
	int result;
	switch (direction)
	{
	case EAST:
		result = xPlayer + 1;
		break;
	case WEST:
		result = xPlayer - 1;
		break;
	default:
		result = xPlayer;
	}
	return result;
}

/**
 * Compute new yPlayer
 * @param direction the direction
 * @param yPlayer current yPlayer
 * @return new yPlayer position
 */
int newYPlayer(char direction, int yPlayer)
{
	int result;
	switch (direction)
	{
	case NORTH:
		result = yPlayer + 1;
		break;
	case SOUTH:
		result = yPlayer - 1;
		break;
	default:
		result = yPlayer;
	}
	return result;
}

/**
 * Compute Manhattan distance between two points
 * @param x1 x coordinate of the first point
 * @param y1 y coordinate of the first point
 * @param x2 x coordinate of the second point
 * @param y2 y coordinate of the second point
 * @return the Manhattan distance between the two points
 */
int manhattanDistance(int x1, int y1, int x2, int y2)
{
	// (ternary operator: <condition> ? <value if true> : <value if false>)
	return (x1 > x2 ? (x1 - x2) : (x2 - x1)) + (y1 > y2 ? (y1 - y2) : (y2 - y1));
}
/**
 * Compute euclidean distance between two points
 * @param x1 x coordinate of the first point
 * @param y1 y coordinate of the first point
 * @param x2 x coordinate of the second point
 * @param y2 y coordinate of the second point
 * @return the euclidean distance between the two points
 */
double euclideanDistance(int x1, int y1, int x2, int y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}