/**
 * Purpose: basic stack implementation based on a singly linked list
 * Author:  Emanuele Rizzolo
 * Class:   3XIN
 * Date:    2020/03/04
 * Note:    item must be defined as a valid data type (e.g. with using item = int;)
 *          CAPACITY need not be defined as a valid costant positive integer
*/

// definition of node data type
struct node
{
    item info;           // one and only one item per node
    node *next{nullptr}; // link to next node (in removal order)
};

// definition of stack data type
struct stack
{
    node *top{nullptr}; // link to top node
    int size{0};        // actual size of the stack (number of elements)
};

/*  
 * CAVEAT
 * With this definition of stack data type
 * data are NOT part of the struct !!!
 *     size of struct:
 *         sizeof(top) i.e. sizeof(node *) usually 4B or 8B, independent of capacity!
 *         + sizeof(int)
 * If the struct is copied, the address of the top node is copied
 * but the actual nodes/data are shared between the copies !!!!
*/

// basic operations
int size(const stack &s)
{
    return s.size;
}
int capacity(const stack &s)
{
    return s.size; // can change
}
bool push(stack &s, item i)
{
    // create a new node
    node *inserted = new (nothrow) node;
    // check success
    if (inserted != nullptr)
    {
        // setup of the new node
        inserted->info = i;     // insert data
        inserted->next = s.top; // link to previous top of the stack
        // update stack
        s.top = inserted; // new top node
        s.size++;
        return true;
    }
    return false;
}
bool pop(stack &s, item &i)
{
    node *removed = s.top;
    // if not empty
    if (removed != nullptr)
    {
        // setup info
        i = removed->info; // extract from top node
        // update stack
        s.top = removed->next; // new top node
        s.size--;              // one element less
        // no memory leakage, please
        delete removed; // free memory
        return true;
    }
    return false;
}

// for debug purposes
// almost implementation independent
void print(const stack &s, ostream &out /* = cout */, bool newLine /* = true */)
{
    out << "Stack{ ";
    out << size(s) << "/" << capacity(s) << ", top :";
    node *current = s.top;
    while (current != nullptr)
    {
        // show elements from top to bottom
        out << " " << current->info; // implementation dependent
        current = current->next;
    }
    out << " : bottom}";
    if (newLine)
    {
        out << endl;
    }
}
