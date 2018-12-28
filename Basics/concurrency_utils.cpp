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




//~~~~~~~~Concurrerncy~~~~~~~~~~

// Thread level concurrency to improve throughgput and/or responsiveness

// Spawning thread

void f(); // function
struct F { // function object
    void operator()();
}; 

void user()
{
    thread t1 {f}; // f() executes in separate thread
    thread t2 {F()}; // // F()() executes in separate thread
    t1.join(); // wait for t1
    t2.join(); // wait for t2
}

// Passing arguments

void f(vector<double>& v);  // function do something with v

struct F {  // function object: do something with v
    vector<double>& v;
    F(vector<double>& vv) :v{vv} { }
    void operator()();  // application operator 
};

int main()
{
    vector<double> some_vec {1,2,3,4,5,6,7,8,9};
    vector<double> vec2 {10,11,12,13,14};
    thread t1 {f,some_vec}; // f(some_vec) executes in a separate thread
    thread t2 {F{vec2}};    // F(vec2)() executes in a separate thread
    t1.join();
    t2.join();
}

// Sharing data - mutexes
mutex m; // controlling mutex
int sh; // shared data
void f()
{
    unique_lock<mutex> lck {m}; // acquire mutex
    sh += 7;    // manipulate shared data
    // unique_lock releases the mutex implicitly with a call to m.unlock()
}

// Dealing with deadlocks

void f()
{
// ...
    unique_lock<mutex> lck1 {m1,defer_lock};
    unique_lock<mutex> lck2 {m2,defer_lock};
    unique_lock<mutex> lck3 {m3,defer_lock};
    // ...
    lock(lck1,lck2,lck3);
    // ... manipulate shared data ...
} // implicitly release all mutexes

 // lock() will only proceed after acquiring all its mutex arguments 
 // Will never block ("go to sleep") while holding a mutex 



// Condition variables
// Example shared queue with consumer waiting for producer to insert message

class Message { // object to be communicated
// ...
};

queue<Message> mqueue; // the queue of messages
condition_variable mcond; // the variable communicating events
mutex mmutex; // the locking mechanism

void consumer()
{
    while(true) {
        unique_lock<mutex> lck{mmutex}; // acquire mmutex
        while (mcond.wait(lck)) /* do nothing */; // release lck and wait;
                                // re-acquire lck upon wakeup
        auto m = mqueue.front(); // get the message
        mqueue.pop();
        lck.unlock(); // release lck
        // ... process m ...

    }
}

void producer()
{
    while(true) {
        Message m;
        // ... fill the message ...
        unique_lock<mutex> lck {mmutex}; // protect operations
        mqueue.push(m);
        mcond.notify_one(); // notify
    } // release lock (at end of scope)
}


//~~~~~~ Futures and Promises~~~~~~~~~
// Future and promise enable a transfer of a value between two tasks without explicit use of a lock
// "the system" implements the transfer efficiently
// When a task wants to pass a value to another, it puts the value into a promise
//  The implementation makes that value appear in the corresponding future, from which it can be read


// The packaged_task type enables setting up tasks connected with futures and promises to be run on threads.

// To do: Finish up basic example



//~~~~~~~~Small Utililty Components~~~~~~~~~~

 // Time

#include <chrono>
auto t0 = high_resolution_clock::now();
this_thread::sleep_for(milliseconds{20});
auto t1 = high_resolution_clock::now();
cout << duration_cast<nanoseconds>(t1−t0).count() << " nanoseconds passed\n";



// Type Predicates

// Answers questions about types
bool b1 = Is_arithmetic<int>(); // yes, int is an arithmetic type
bool b2 = Is_arithmetic<string>(); // no, std::str ing is not an arithmetic type

template<typename Scalar>
class complex {
    Scalar re, im;
public:
    static_assert(is_arithmetic<Scalar>::value, "Sorry, I only support complex of arithmetic types");
    // ...
};

// Some others
is_void<X>  // Is X void ?
is_integral<X> // Is X an integral type?
is_floating_point<X> // Is X a floating-point type?
is_pointer<X> // Is X a pointer (not including pointers to members)?
is_lvalue_reference<X> // Is X an lvalue reference?
is_rvalue_reference<X> // Is X an rvalue reference?
is_member_object_pointer<X> // Is X a pointer to a non- static data member?
is_member_function_pointer<X> // Is X a pointer to a non- static member function?
is_enum<X> // Is X an enum (either plain of class enum )?
is_class<X> // Is X a class (including struct s, but not enum s)?
is_function<X> // Is X a function?
is_signed<X> // Is X an arithmetic type and signed?
is_unsigned<X> // Is X an arithmetic type and unsigned?
is_constructible<X,args> // Can an X be constructed from args ?
is_default_constructible<X> // Can an X be constructed from {} ?
is_copy_constructible<X> // Can an X be constructed from an X& ?
is_move_constructible<X> // Can an X be constructed from an X&& ?
is_assignable<X,Y> // Can a Y be assigned to an X ?
is_copy_assignable<X> // Can a X& be assigned to an X ?
is_move_assignable<X> // Can a X&& be assigned to an X ?
is_destructible<X> // Can an X be destroyed (i.e.,  ̃X() has not been deleted)?



//  Pair and Tuple

// Hold heterogeneous objects

// Pair - to hold pair of values
// Example usage of pairs with map
map<int, pair<string, double>> emp_list; // (ID, (name, salary))
pair<string, double> employee = make_pair("Alice", 80000.00); // Name and Salary
emp_list.emplace(200, employee);
    
for (auto& ele: emp_list)
    cout << "ID " << ele.first << " name " << ele.second.first << " salary " << ele.second.second << endl;

// Another use of pair is to return a result, and an error value


// Tuple - For more than two elements, you can use tuple 

// Example 
tuple<string,int,double> t2("Sild",123, 3.14); // the type is explicitly specified
auto t = make_tuple(string("Herring"),10, 1.23); // the type is deduced, t is a tuple<str ing,int,double>
string s = get<0>(t); // get first element of tuple
int x = get<1>(t);
double d = get<2>(t);


// Regex

//Regular expressions are a powerful tool for describing patterns in text

// Example
regex pat (R"(\w{2}\s∗\d{5}(−\d{4})?)"); // ZIP code pattern: XXddddd-dddd and var iants
// It specifies a pattern starting with two letters \w{2} optionally followed by some space \s∗
//  followed by five digits \d{5} and optionally followed by a dash and four digits −\d{4} 
// R is a raw string literal that allows backslashes and quotes to be used directly in string

// Example usage with stream processing
int lineno = 0;
for (string line; getline(cin,line);) { // read into line buffer
    ++lineno;
    smatch matches; // matched strings go here
    if (regex_search(line,matches,pat))    // search for pat in line
    cout << lineno << ": " << matches[0] << '\n';
}





// Math functions and Algorithms

// Standard math function <cmath>

// Commplex numbers <complex>

// Random Numbers <random>
//A random number generator consists of two parts:
// An engine that produces a sequence of random or pseudo-random values
// A distribution that maps those values into a mathematical distribution in a range

using my_engine = default_random_engine; // type of engine
using my_distribution = uniform_int_distribution<>; // type of distribution
my_engine re {}; // the default engine
my_distribution one_to_six {1,6}; // distribution that maps to the ints 1..6
auto die = bind(one_to_six,re); // make a generator
int x = die(); // roll the die: x becomes a value in [1:6]

// Rand_int class
class Rand_int {
public:
    Rand_int(int low, int high) :dist{low,high} {re.seed(chrono::system_clock::now().time_since_epoch().count());} //seed
    int operator()() { return dist(re); } // draw an int
private:
    default_random_engine re;
    uniform_int_distribution<> dist;
};  

int main()
{
    Rand_int rnd {0,4}; // make a unifor m random number generator
    vector<int> hist(5); // make a vector of size 5
    for (int i=0; i!=200; ++i)
        ++hist[rnd()]; // fill histogram with the frequencies of numbers [0:4]


    for (int i = 0; i!=hist.size(); ++i) {    // write out a bar graph
        cout << i << '\t';
        for (int j=0; j!=hist[i]; ++j) cout << "*";
    cout << endl;
    }
}


// Vector Arithmetic

// valarrray for mathematical vector operations - for numerical computation
void f(valarray<double>& a1, valarray<double>& a2)
{
    valarray<double> a = a1∗3.14+a2/a1; // numer ic array operators *, +, /, and =
    a2 += a1∗3.14;
    a = abs(a);
    double d = a2[7];
    // ...
}

// Numeric Limit
// In <limits>,the standard library provides classes that describe the properties of built-in types 
// For example, the maximum exponent of a float or the number of bytes in an int ;

numeric_limits<short>::min(); // smallest short
numeric_limits<short>::max(); // largest short
numeric_limits<double>::epsilon();  // smallest double such that 1+epsilon != 1

