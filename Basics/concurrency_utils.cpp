/* All material based on the book C++ Programming Language, 4th Edition, by Bjarne Stroustrup */
/* Resource management, Concurrency, Small Utilities, Regex, Math */

//~~~~~~~~~~Smart Pointers~~~~~~~~~~`

// Raw pointers do not indicate ownership - not clear who is supposed to delete the object
// unique_ptr to represent unique ownership
// shared_ptr to represent shared ownership

// unique_ptr

// unique_ptr ensures that its object is properly destroyed when it goes out of scope
// Either through return, or by throwing an exception
// It cannot be copied, only moved

// X* vs. unique_ptr<X>
void f(int i, int j)    
{
    X∗ p = new X; // allocate a new X
    unique_ptr<X> sp {new X};  // allocate a new X and give its pointer to unique_ptr
    // ...
    if (i<99) throw Z{}; // may throw an exception
    if (j<77) return;   // may retur n "early"
    p−>do_something(); // may throw an exception
    sp−>do_something(); // may throw an exception
    // ...
    delete p; // destroy *p

}
// Forgot to delete p when throwing exception or returning early

// unique_ptr is a very lightweightmechanism with no space or time overhead compared to correct use of a built-in pointer.

// Passing unique_pt out of functions
unique_ptr<X> make_X(int i) // make an X and immediately give it to a unique_ptr
{
// ... check i, etc. ...
    return unique_ptr<X>{new X{i}}; // move semantics
}

// Passing into functions
unique_ptr<int> f(unique_ptr<int> p)
{
    ++∗p;
    return p;
}
void f2(const unique_ptr<int>& p)
{
    ++∗p;
}

void use()
{   
    unique_ptr<int> p {new int{7}};
    p=f(p); // error: no copy constructor
    p=f(move(p)); // transfer ownership there and back
    f2(p); // pass a reference
}   


// Ownership transfer
unique_ptr<string> p1(new string("Alice"))
unique_ptr<string> p2(p1.release()) //Transfers ownership to p2, resets p1
unique_ptr<string> p3(new string("Bob"))
p3.reset(p2.release()) // reset deletes the memory to which p2 has pointed



// shared_ptr

//A shared_ptr represents shared ownership
// It is used where two pieces of code need access to some data but neither has exclusive ownership 
// (in the sense of being responsible for destroying the object).
// A shared_ptr is a kind of counted pointer where the object pointed to is deleted when the
// use count goes to zero.

// Use case
// Consider a node in a general graph used by an algorithm that adds and removes vertices and edges
// Need to delete vertices if an only if no other vertex refer to it

struct Vertex {
    vector<Vertex*> adj_list;
    //.... 
}
// Hard to figure out when the vertex pointed to by Vertex* can be deleted. Soln - use shared_ptr

struct Vertex {
    vector<shared_ptr<Vertex>> adj_list;
    // ...
};
// The destructor for adj_list[i] is invoked, and the Vertex pointed to is deleted if adj_list[i] is the lat pointer to it


// Smart pointers and dumb classes

// Dumb classes are those without destructors (C-style)

// Example-  (from C++ Primer, 5th Ed. Lippman, Lajoie, and Moo)
struct destination; // represents what we are connecting to
struct connectoin;  // information needed to use the connection

connection connect(destination *); // open connection
void disconnect(connection); // close the given connection
void f(destionation &d, /* other parameters */)
{
    // get a connection; must remember to close when it is done
    connection c = connect(&d);
    // use connection
    // if we forget to call diconnect before exiting f or if there is an exception, there will be no way to close c

}

// Solution - use a deleter function with a shared_ptr
void end_connection(connection *p) 
{
    disconnect(*p);
}

void f(destionation &d, /* other parameters */)
{
    // get a connection; must remember to close when it is done
    connection c = connect(&d);
    shared_ptr<connection> p(&c, end_connection);
    // use connection
    // if we forget to call diconnect before exiting f or if there is an exception, there will be no way to close c

}



// Stroustrup's advise on when to use pointers
//1. When we share an object, we need pointers (or references) to refer to the shared object, so a
// shared_ptr becomes the obvious choice (unless there is an obvious single owner).
//2. When we refer to a polymorphic object, we need a pointer (or a reference) because we don’t
//know the exact type of the object referred to or even its size), so a unique_ptr becomes the obvious choice.
//3. A shared polymorphic object typically requires shared_ptrs

// Note: do not need to use a pointer to return a collection of objects from a function
// A container that is a resource handle will do that simply and efficiently

