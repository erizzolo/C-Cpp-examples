/**
 * Purpose: basic queue implementation based on a fixed length (circular) array
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
*/

/**
 * An array of 16 elements viewed in a circular way
 * |  0 |  1 |  2 |  3 |  4 |
 * | 15 |              |  5 |
 * | 14 |              |  6 |
 * | 13 |              |  7 |
 * | 12 | 11 | 10 |  9 |  8 |
 * 
 * The situation after 6 insertions (A, B, C, D, E, F)
 * and two removals (A, B)
 * |  0 |  1 |  C |  D |  E |
 * | 15 |              |  F |
 * | 14 |              |  6 |
 * | 13 |              |  7 |
 * | 12 | 11 | 10 |  9 |  8 |
 * size: 4
 * next_insertion: 6
 * [next_removal = (next_insertion - size) % capacity: 2]
 * 
*/

// definition of queue data type
struct queue
{
    item data[CAPACITY]; // the actual data
    // add whatever you need to implement a queue logic
};

// basic operations
int size(const queue &q)
{
    return 42;
}
int capacity(const queue &q)
{
    return CAPACITY;
}
bool insert(queue &q, item i)
{
    bool result = false;
    return result;
}
bool remove(queue &q, item &i)
{
    bool result = false;
    return result;
}

// for debug purposes
// almost implementation independent
void print(const queue &q, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "Queue{ ";
    out << size(q) << "/" << capacity(q) << ", first :";
    for (int i = 0; i < size(q); i++)
    {
        // show element from first to last
        // implementation dependent
    }
    out << " : last}";
    if (newLine)
    {
        out << endl;
    }
}
