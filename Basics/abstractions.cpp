/* All material based on the book C++ Programming Language, 4th Edition, by Bjarne Stroustrup */
/* Abstraction Mechanisms - C++ support for abstraction and resource management. Implementation techniques, and
language facilities used for concrete classes, abstract classes, and class hierarchies. Templates introduced as a mechanism 
for parameterizing types and algorithms with (other) types and algorithms. Computations on user-defined and built-in types are 
represented as functions, generalized to template functions and function objects. These are the language facilities supporting
the programming styles known as object-oriented programming and generic programming.*/


// Support for basic OOP concepts - abstraction, encapsulation, inheritance, and polymorphism

// Concrete classes
// Abstract Classes
// Class hiearchiess

//~~~~~~Concrete classes~~~~~~~~
// Behaves just like built-in types
// Representation is part of definition
// Can  place objects of concrete types on the stack, in statically allocated memory, and in other objects
// Refer to objects directly (and not just through pointers or references)
// Initialize objects immediately and completely (e.g., using constructors)
// Copy objects 

// Example - Arithmetic Type
class complex {
    double re, im; // representation: two doubles
public:
    complex(double r, double i) :re{r}, im{i} {} // construct complex from two scalars
    complex(double r) :re{r}, im{0} {} // construct complex from one scalar
    complex() :re{0}, im{0} {} // default constructor complex: {0,0}
    
    double real() const { return re; } // const indicates that method does not modify the object
    void real(double d) { re=d; }
    double imag() const { return im; }
    void imag(double d) { im=d; }
    complex& operator+=(complex z) { re+=z.re , im+=z.im; return ∗this; } // add to re and im and return result
    complex& operator−=(complex z) { re−=z.re , im−=z.im; return ∗this; }
    complex& operator∗=(complex);
};

// Additional operations do not require direct access to representation. Written separately
complex operator+(complex a, complex b) { return a+=b; } //Argument passed by value. Modified without affecting caller's copy
complex operator−(complex a, complex b) { return a−=b; }
complex operator−(complex a) { return {−a.real(), −a.imag()}; }
complex operator∗(complex a, complex b) { return a∗=b; }
complex operator/(complex a, complex b) { return a/=b; }

bool operator==(complex a, complex b)   // equal
{
    return a.real()==b.real() && a.imag()==b.imag();
}
bool operator!=(complex a, complex b) // not equal
{
    return !(a==b);
}

// Use of complex
void f(complex z)
{
    complex a {2.3}; // construct {2.3,0.0} from 2.3
    complex b {1/a};
    complex c {a+z∗complex{1,2.3}};
    // ...
    if (c != b) // operator!=(c,b)
        c = −(b/a)+2∗b;
}
// Overloaded operators must make intutive sense to user
// Can only overload existing operators
// Cannot redefine operators for basic types

// Example - Container

// Container is an object holding a collection of elements
// Incorporate destructor to vector - to deallocate memory when object goes out of scope
class Vector {
private:
    double∗ elem; // elem points to an array of sz doubles
    int sz;
public:
    Vector(int s) :elem{new double[s]}, sz{s} // constructor: acquire resources
    {
        for (int i=0; i!=s; ++i) elem[i]=0; // initialize elements
    }
    ~Vector() { delete[] elem; } // destructor: release resources
    double& operator[](int i);
    int size() const;
};

void fct(int n)
{
    Vector v(n);     // ... use v ...
    {
        Vector v2(2∗n); // ... use v and v2 ...

    } // v2 is destroyed here

// ... use v ..

} // v is destroyed here