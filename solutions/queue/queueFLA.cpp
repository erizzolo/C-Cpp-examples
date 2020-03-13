/**
 * Purpose: basic queue implementation based on a fixed length (non circular) array
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
*/

/**
 * A simple way is to insert at the lowest free position like in a stack,
 * and remove from the other end, shifting the rest of the queue.
 * |  0|  1|  2|  3|  4|  5|  6|  7|  8|  9| 10| 11| 12| 13| 14| 15|
 * The situation after 6 insertions (A, B, C, D, E, F) and two removals (A, B)
 * |  C|  D|  E|  F|  4|  5|  6|  7|  8|  9| 10| 11| 12| 13| 14| 15|
 * size: 4
 * next_insertion: 4
 * next_removal: 0  (plus shift !!!)
 * 
*/

// definition of queue data type
struct queue
{
    item data[CAPACITY]; // the actual data
    int size{0};         // actual number of elements
};

// basic operations
int size(const queue &q)
{
    return q.size;
}
int capacity(const queue &q)
{
    return CAPACITY;
}
bool insert(queue &q, item i)
{
    bool result = size(q) < capacity(q); // not full yet
    if (result)
    {
        q.data[size(q)] = i; // insert into next empty position
        q.size++;            // one element more
    }
    return result;
}
bool remove(queue &q, item &i)
{
    bool result = size(q) > 0; // not empty
    if (result)
    {
        i = q.data[0]; // extract from first non-empty position
        q.size--;      // one element less
        // shift the rest
        for (int i = 0; i < size(q); ++i)
        {
            q.data[i] = q.data[i + 1];
        }
    }
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
        out << " " << q.data[i]; // implementation dependent
    }
    out << " : last}";
    if (newLine)
    {
        out << endl;
    }
}
