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
    int size{0};         // actual number of elements
    int insertion{0};    // actual insertion slot
    // int removal{0}; // (insertion - size) % capacity
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
        q.data[q.insertion] = i;                       // insert into next empty position
        q.size++;                                      // one element more
        q.insertion = (q.insertion + 1) % capacity(q); // next empty position (circular)
    }
    return result;
}
bool remove(queue &q, item &i)
{
    bool result = size(q) > 0; // not empty
    if (result)
    {
        int removal = q.insertion - q.size; // next removal position (circular)
        if (removal < 0)
        {
            removal += capacity(q);
        }
        i = q.data[removal]; // extract from first non-empty position
        q.size--;            // one element less
    }
    return result;
}

// for debug purposes
// almost implementation independent
void print(const queue &q, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "Queue{ ";
    out << size(q) << "/" << capacity(q) << ", first :";
    int removal = q.insertion - q.size; // next removal position (circular)
    if (removal < 0)
    {
        removal += capacity(q);
    }
    for (int i = 0; i < size(q); i++)
    {
        // show element from first to last
        out << " " << q.data[removal]; // implementation dependent
        removal++;
        if (removal == capacity(q))
        {
            removal = 0;
        }
    }
    out << " : last}";
    if (newLine)
    {
        out << endl;
    }
}
