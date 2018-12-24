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

// RAII -  Resource Allocation is Initialization. Client code avoid allocating and deallocatin resources

// Additional ways to initialize container

class Vector {
public:
    Vector(std::initializer_list<double>); // initialize with a list
    // ...

};

Vector::Vector(std::initializer_list<double> lst) // initialize with a list
    :elem{new double[lst.size()]}, sz{lst.size()}
{
    copy(lst.begin(),lst.end(),elem); // copy from lst into elem

}

//Usage
Vector v1 = {1,2,3,4,5}; // v1 has 5 elements
Vector v2 = {1.23, 3.45, 6.7, 8}; // v2 has 4 elements


//~~~~~Abstract types~~~~~~~
// Abstract types insulates the user from immplementation details
// Objects have to be allocated on the free store, and accessed through pointers or references

// Define an interface for an abstract class Container
class Container {
public:
    virtual double& operator[](int) = 0; // pure virtual function
    virtual int size() const = 0; // const member function
    virtual  ~Container() {} // destructor
};

// virtual means may be redefined later in a class derived from this one - inhertiance and polymorphism
// pure virutal (=0) means that the derived class must define the function
// no constructor since nothing to initialize
// destructor is virtual - will call derived class destructors

// Use of Container abstract class. No idea what the actual container will be! 
void use(Container& c)
{
    const int sz = c.size();
    for (int i=0; i!=sz; ++i)
        cout << c[i] << '\n';
}

// Derive a concrete Vector_container subclass from the superclass (also called base class) Container
class Vector_container : public Container { // Vector_container implements Container
    Vector v;
public:
    Vector_container(initializer_list<double> il) : v{il} { }
    ~Vector_container() {} // Call Vectors destructor
    double& operator[](int i) { return v[i]; } // Overrides superclass implementation - polymorphism
    int size() const { return v.size(); } // Overrides superclass implementation
};

// Use case
void g()
{
    Vector_container vc {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; 
    use(vc);
}

// Yet another subclass from Vector_container super class
class List_container : public Container { // List_container implements Container
    std::list<double> ld; // (standard-library) linked list of doubles 

public:
    List_container() { } // empty List
    List_container(initializer_list<double> il) : ld{il} { }
    ~List_container() {}
    double& operator[](int i);
    int size() const { return ld.size();
};
double& List_container::operator[](int i)
{
    for (auto& x : ld) {
        if (i==0) return x;
    −−i;
    }
    throw out_of_rang e("List container");
}

//Use case
void h()
{
    List_container lc = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    use(lc);
}

// Important: use(Container& ) has on idea if the argument is Vector_container or List_container
// It only knows the inteface defined by Container
// Use_container need not be recompiled if derived classes change.
// Caveat: objects now must be maipulated through references or pointers.
// Compiler converts name of virtual function into an index into a table of functions
// This table is called virtual function table (vtbl). Each class maintains its vtbl