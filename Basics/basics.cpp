/* All materail based on the book C++ Programming Language, 4th Edition, by Bjarne Stroustrup */
/* Basics - Presents the notation of C++, C++’s model of memory and computation, and the basic mechanisms for organizing code into a program. */



//~~~~~Hello World~~~~~~
#include <iostream> // Headers for standard stream I/O facilites
int main() 
{
    // The operator << (‘‘put to’’) writes its second argument onto its first
    // String literal "Hello, World!\n" is written onto the standard output stream std::cout 
    // A string literal is a sequence of characters surrounded by double quotes.
    // The std:: specifies that the name cout is to be found in the standard-library namespace
    std::cout << "Hello World\n"; 
    
}

// All executable code placed in functions and called indirectly or directly from main() 
#include <iostream>
using namespace std;
double square(double x)
{
    return x∗x;
}

void print_square(double x)
{
    cout << "the square of " << x << " is " << square(x) << "\n";
}

int main()
{
    print_square(1.234);
}






//~~~~Types, Variables and Arithmetic~~~~~

// A declaration is a statement that introduces a name into the program. It specifies a type for the named entity
// A type defines a set of possible values and a set of operations (for an object).
// An object is some memory that holds a value of some type.
// A value is a set of bits interpreted according to a type.
// A variable is a named object.


// bool - Boolean, possible values are true and false
// char - character, for example, 'a', ' z', and '9'
// int - integer, for example, 1, 42, and 1066
// double - double-precision floating-point number, for example, 3.14 and 299793.0
// sizeof() operator used to obtain size in bytes. size is machine dependent

// Arithmetic operators between types

x+y // plus
+x // unary plus
x-y // minus
-x // unary minus
x*y // multiply
x/y // divide
x%y // remainder (modulus) for integers

// Comparison operators between types:

x==y // equal
x!=y // not equal
x<y // less than
x>y // greater than
x<=y // less than or equal
x>=y // greater than or equal


// Initialiation

double d1 = 2.3; // C-style
double d2 {2.3};
complex<double> z = 1;
complex<double> z2 {d1,d2};
complex<double> z3 = {1,2}; // a complex number with double-precision floating-point scalars
vector<int> v {1,2,3,4,5,6}; // a vector of ints

int i1 = 7.2; // i1 becomes 7
int i2 {7.2};  // error : floating-point to integer conversion
int i3 = {7.2}; // error : floating-point to integer conversion (the = is redundant)

// Automatic type deduction from initialization
auto b = true; // bool
auto ch = 'x'; // char
auto i = 123; // int
auto d = 1.2; // double
auto z = sqrt(y); // z has the type of whatever sqr t(y) returns

// Don't use auto in a large scope so as to make type clear to readers
// Want to explicit about range of precision (float rather than double)

// Concise:w operations for modifying a variable
x+=y
++x
x−=y
−−x
x∗=y
x/=y
x%=y




//~~~~~Constants~~~~~~
// C++ supports two notions of immutability 
// const : meaning roughly ‘‘I promise not to change this value
// constexpr : meaning roughly ‘‘to be evaluated at compile time



const int dmv = 17; // dmv is a named constant
int var = 17; // var is not a constant
constexpr double max1 = 1.4∗square(dmv); // OK if square(17) is a constant expression
constexpr double max2 = 1.4∗square(var); // error : var is not a constant expression
const double max3 = 1.4∗square(var); // OK, may be evaluated at run time
double sum(const vector<double>&); // sum will not modify its argument
vector<double> v {1.2, 3.4, 4.5}; // v is not a constant
const double s1 = sum(v); // OK: evaluated at run time
constexpr double s2 = sum(v); // error : sum(v) not constant expression
constexpr double square(double x) { return x∗x; } // square() can be used in a constant expressison



//~~~~~Tests and Loops~~~~~
// use of while, switch, and >> operator

bool accept3()
{
    int tries = 1;
    while (tries<4) {
        cout << "Do you want to proceed (y or n)?\n";
        char answer = 0;
        cin >> answer; //Read answer
        switch (answer) {
        case 'y':
            return true;
        case 'n':
            return false;
        default:
        cout << "Sorry, I don't understand that.\n";
        ++tries; // increment
    }
}
cout << "I'll take that for a no.\n";
return false;
}




// ~~~~~~~Pointers, Arrays, and Loops
char v[6]; // array of 6 characters
char *p; // Pointer to character
char∗ p = &v[3]; // p points to v’s four th element
char x = ∗p; // *p is the object that p points to
// In an expression, prefix unary ∗ means ‘‘contents of’’ and prefix unary & means ‘‘address of.’’

// Use of for-statement for copying array 
void copy_fct()
{
    int v1[10] = {0,1,2,3,4,5,6,7,8,9};
    int v2[10];
    // to become a copy of v1
    for (auto i=0; i!=10; ++i) // copy elements
        v2[i]=v1[i];
// ...
}

// Use of range for-statement for copying array
// Each element is copied to x
void print()
{
    int v[] = {0,1,2,3,4,5,6,7,8,9};
    for (auto x : v) // for each x in v
        cout << x << '\n';

    for (auto x : {10,21,32,43,54,65})
        cout << x << '\n';
    // ...
}

// Use of range for-statement for copying array
// x refers to each element
void increment()
{
    int v[] = {0,1,2,3,4,5,6,7,8,9};
    for (auto& x : v)
        ++x;
    // ...
}
// A reference is similar to a pointer, except that you don’t need to use a prefix ∗ to access the value referred to by the reference.
// Also, a reference cannot be made to refer to a different object after its initialization.

// Declaratotr operators  &, *, []
T a[n]; // T[n]: array of n Ts
T∗ p; // T*: pointer to T
T& r; // T&: reference to T
T f(A); // T(A): function taking an argument of type A returning a result of type T

//nullptr
double∗ pd = nullptr;
Link<Record>∗ lst = nullptr; // pointer to a Link to a Record
int x = nullptr; // error : nullptr is a pointer not an integer

// Check that pointer is valid - that is it pointing to something
// count the number of occurrences of x in p[]
// p is assumed to point to a zero-ter minated array of char (or to nothing)
int count_x(char∗ p, char x) // p is a C style string
{
    if (p==nullptr) return 0;
    int count = 0;
    for (; ∗p!=0; ++p)
        if (∗p==x)
            ++count;
    return count;
}



//~~~~User Defined Types - Structures~~~~~~~~~~~

struct Vector {
    int sz; // number of elements
    double∗ elem; // pointer to elements
};

// Declare a variable of type Vector
Vector v;

// Constructing a Vector
void vector_init(Vector& v, int s)
{
    v.elem = new double[s]; // allocate an array of s doubles
    v.sz = s;
}
// v is passed by non-const reference allowing modification of v
// new operator allocated memory from the free store (dynamic memory allocation)

// Simple use of Vector
// read s integers from cin and return their sum; s is assumed to be positive
double read_and_sum(int s)
{
    Vector v;
    vector_init(v,s); // allocate s elements for v   
    for (int i=0; i!=s; ++i)
        cin>>v.elem[i]; // read into elements
    double sum = 0;
    for (int i=0; i!=s; ++i)
        sum+=v.elem[i]; // take the sum of the elements
    return sum;

}

// Access of struct elements through . operator and -> operator
void f(Vector v, Vector& rv, Vector∗ pv)
{
    int i1 = v.sz; // access through name
    int i2 = rv.sz; // access through reference
    int i4 = pv−>sz; // access through pointer
}


//~~~~~~User Defined Types - Claasses~~~~~

// Goal - to separate interface to a type, and its implementation
// Interface defined by public membes of a class
// Private members are only acceessible through the interface

class Vector {
public:
    Vector(int s) :elem{new double[s]}, sz{s} { } // Constructor
    double& operator[](int i) { return elem[i]; } // Operator overloading
    int size() { return sz; }
private:
    double∗ elem; // pointer to the elements
    int sz; // the number of elements
};

// Define a variable of type Vector
Vector v(6);

// members elem, and sz are only accessbile through public interface
double read_and_sum(int s)
{
    Vector v(s); // make a vector of s elements
    for (int i=0; i!=v.siz e(); ++i)
        cin>>v[i]; // read into elements
    double sum = 0;
    for (int i=0; i!=v.siz e(); ++i)
        sum+=v[i]; // take the sum of the elements
    return sum;
}

// A ‘‘function’’ with the same name as its class is called a constructor
// Constructor is guaranteed to initialize the objects of its class

//~~~~~~User Defined Types - Enumberations~~~~~~

// User defined type used to enumberate values
enum class Color { red, blue , green };
enum class Traffic_light { green, yellow, red };

Color col = Color::red;
Traffic_light light = Traffic_light::red;

// The class after the enum specifies that an enumeration is strongly typed and that its enumerators are scoped

Color x = red; // error : which red?
Color y = Traffic_light::red; // error : that red is not a Color
Color z = Color::red; // OK
int i = Color::red; // error : Color ::red is not an int
Color c = 2; // error : 2 is not a Color

// Defining operators for enums
Traffic_light& operator++(Traffic_light& t)
// prefix increment: ++
{
    switch (t) {
    case Traffic_light::green:  return t=Traffic_light::yellow;
    case Traffic_light::yellow: return t=Traffic_light::red;
    case Traffic_light::red:    return t=Traffic_light::green;  
    }
}
Traffic_light next = ++light;   // next becomes Traffic_light::green

//~~~~~~~Modularity~~~~~~~~~~~~
// Declaration and definitions in separate files 

// Namespaces - as a mechanism for expressing that some declarations belong together 
// Their names shouldn’t clash with other names
namespace My_code {
    class complex { /* ... */ };
    complex sqrt(complex);
    // ...
    int main();
}

int My_code::main()
{
    complex z {1,2};
    auto z2 = sqrt(z);
    std::cout << '{' << z2.real() << ',' << z2.imag() << "}\n";
    // ...
};

int main()
{
    return My_code::main();
}

// Standard library in namespace std

//~~~~~Exceptions~~~~~~~~

// Exception handling is used wheen one part of a program detects a problem that it cannot resolve
// Detecting raises an exception which is handled by another part
// throw - deteting part uses to raise an exceptoin
// try - exception thrown from try blocks are passed to exception handlers
// catch - exception handler. Stack is unwound
// exception classes are used to pass informattion from throw to associated catch

try {
        // program statements
} catch (exception_declaration) {
    // handler statements
} catch (exception declaration) {
    // handler statements
}

// If no handler exists execution is transfered to a library function named terminate that stops the program
// terminate unwinds the stack 
// stdexcept header defines several general-purpose exception classes
// Examples are out_of_range, invalid_argument, logic_error, runtime_error, length_error, bad_alloc 

double& Vector::operator[](int i)
{
    if (i<0 || size()<=i) throw out_of_rang e{"Vector::operator[]"};
        return elem[i];
}

void f(Vector& v)
{
    // ...
    try { // exceptions here are handled by the handler defined below
        v[v.siz e()] = 7; // tr y to access beyond the end of v
    }
    catch (out_of_rang e) { // oops: out_of_range error
        // ... handle range error ...
    }
    // ...
}

// Another example
Vector::Vector(int s)
{
    if (s<0) throw length_error{};
    elem = new double[s];
    sz = s;
}

void test()
{
    try {
        Vector v(−27);
    }
    catch (std::length_error) {
    // handle negative size
    }
    catch (std::bad_alloc) {
    // handle memory exhaustion
    }
}

