/**
 * Purpose: basic stack implementation based on a fixed length array
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:
*/

#define CAPACITY 10

// definition of stack data type
struct stack
{
    item data[CAPACITY]; // the actual data
    // add whatever you need to implement a stack logic
};

// basic operations
int size(const stack &s)
{
    return 42;
}
int capacity(const stack &s)
{
    return CAPACITY;
}
bool push(stack &s, item i)
{
    bool result = false;
    return result;
}
bool pop(stack &s, item &i)
{
    bool result = false;
    return result;
}

// for debug purposes
// almost implementation independent
void print(const stack &s, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "Stack{ ";
    out << size(s) << "/" << capacity(s) << ", bottom :";
    for (int i = 0; i < size(s); i++)
    {
        // show element from bottom to top
        // implementation dependent
    }
    out << " : top}";
    if (newLine)
    {
        out << endl;
    }
}
