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

//~~~~~~~Class Hiearchies~~~~~~~~`

// A class hierarchy is a set of classes ordered in a lattice created by derivation 
// We use class hierarchies to represent concepts that have an "is a" relationship
// A fire engine is a kind of a truck or A smiley face is a kind of a circle which is a kind of a shape

// Abstract class shape
class Shape {
public:
    virtual Point center() const =0;
    virtual void move(Point to) =0; // pure virtual
    virtual void draw() const = 0;
    virtual void rotate(int angle) = 0; // draw on current "Canvas"
    virtual  ~Shape() {} // destructor
};

// Using shapes in a Canvas application
void rotate_all(vector<Shape∗>& v, int angle) // rotate v’s elements by angle degrees
{
    for (auto p : v)
        p−>rotate(angle);
}

// Define a concrete shape Circle
class Circle : public Shape { //Subclass Circle from Shape
private:
    Point x; // center
    int r; // radius
public:
    Circle(Point p, int rr); // constructor
    Point center() const { return x; }
    void move(Point to) { x=to; }
    void draw() const;
    void rotate(int) {}

};

// Define a concerte shape Smiley derived from Circle
class Smiley : public Circle { // use the circle as the base for a face
private:
    vector<Shape∗> eyes;
    Shape∗ mouth;
public:
    Smiley(Point p, int r) : Circle{p,r}, mouth{nullptr} { } //Initialize super class constructor
    ~Smiley()
    {
        delete mouth;
        for (auto p : eyes) delete p;
    }
    void move(Point to);
    void draw() const;
    void rotate(int);
    void add_eye(Shape∗ s) { eyes.push_back(s); }
    void set_mouth(Shape∗ s);
    virtual void wink(int i);   // wink eye number i
    // ...
};

void Smiley::draw()
{
    Circle::draw();
    for (auto p : eyes)
        p−>draw();
    mouth−>draw();
}

// Note that subclasses maybe used as type superclasses (Smiley is a Shape)
// So superclass destructors have to be virtual to call the appropriaate subclass destructor

// Two kinds of inhertiances - Interface inheritance. For example, inheriting from Shape
// Immplmentation inheritance. For example, inheriting constructor from Circle

// More examples of how class hiearchies are used
// Read Shapes
enum class Kind { circle, triangle , smiley };
Shape∗ read_shape(istream& is) // read shape descriptions from input stream is
{
    // ... read shape header from is and find its Kind k ...
    switch (k) {
    case Kind::circle:
        // read     circle data {Point,int} into p and r
        return new Circle{p,r};
    case Kind::triangle:
        // read triangle data {Point,Point,Point} into p1, p2, and p3
    return new Triangle{p1,p2,p3};
    case Kind::smiley:
        // read smiley data {Point,int,Shape,Shape,Shape} into p, r, e1 ,e2, and m
        Smiley∗ ps = new Smiley{p,r};
        ps−>add_eye(e1);
        ps−>add_eye(e2);
        ps−>set_mouth(m);
    return ps;
    }
}

// More Shape operations
void user()
{
    std::vector<Shape∗> v;
    while (cin)
        v.push_back(read_shape(cin));
    draw_all(v);    // call draw() for each element
    rotate_all(v,45); // call rotate(45) for each element
    for (auto p : v) delete p;  // remember to delete elements
}

// User must delete all pointers 
// Use unique pointers instead from the standard library
// Rewrite of read_shape() with unique_ptr
unique_ptr<Shape> read_shape(istream& is) // read shape descriptions from input stream is
{
    // read shape header from is and find its Kind k
    switch (k) {
        case Kind::circle:
    // read circle data {Point,int} into p and r
        return unique_ptr<Shape>{new Circle{p,r}};
    // ...

    }
void user()
{
    vector<unique_ptr<Shape>> v;
    while (cin)
        v.push_back(read_shape(cin));
    draw_all(v);    // call draw() for each element
    rotate_all(v,45);   // call rotate(45) for each element
} // all Shapes implicitly destroyed when unique_ptr goes out of scope

// Note: all functions (for example rotate_all()) has to use unique_ptr as well


//~~~~~~~~Copy and Move~~~~

// By default, objects can be copied
// This is true for objects of user-defined types as well as for built-in types.
// The default meaning of copy is memberwise copy: copy each member
// May not be appropriate for all object - for example, vector class define earlier

// Eexample - for the complex class defined earlier

void test(complex z1)
{
    complex z2 {z1}; // copy initialization
    complex z3; // copy assignment
    z3 = z2;
    // ...
}

// z1 , z2 , and z3 have the same value because both the assignment and the initialization copied both members.


// Copying containers

// Effect of shallow copy when resources are accessed  through a pointer
void bad_copy(Vector v1)
{
    Vector v2 = v1; // copy v1’s representation into v2
    v1[0] = 2;  // v2[0] is now also 2!
    v2[1] = 3;  // v1[1] is now also 3!
}

// Copy constructor and copy assignment
class Vector {
private:
    double∗ elem; // elem points to an array of sz doubles
    int sz;
public:
    Vector(int s);  // constructor: establish invariant, acquire resources
    ~Vector() { delete[] elem; }    // destructor: release resources
    Vector(const Vector& a); // copy constructor
    Vector& operator=(const Vector& a); //copy assignment
    double& operator[](int i);
    int size() const;
};

// Deep copy by allocating space and then copying
Vector::Vector(const Vector& a) : elem{new double[sz]}, sz{a.sz}
{
    for (int i=0; i!=sz; ++i)
        elem[i] = a.elem[i];
}

// Deep copy. Also needs to delete existing elements of LHS
Vector& Vector::operator=(const Vector& a)
{
    double∗ p = new double[a.sz];
    for (int i=0; i!=a.sz; ++i)
        p[i] = a.elem[i];
    delete[] elem;  // delete old elements
    elem = p;
    sz = a.sz;
    return ∗this;
}

// Move constructor and move assignment
Vector operator+(const Vector& a, const Vector& b)
{
    if (a.size()!=b.siz e())
        throw Vector_siz e_mismatch{};
    Vector res(a.size());
    for (int i=0; i!=a.size(); ++i)
        res[i]=a[i]+b[i];
    return res;
}
// res needs to be copied to some place where caller can access
// Caller
void f(const Vector& x, const Vector& y, const Vector& z)
{
    Vector r;
    // ...
    r = x+y+z; // Needs to be copied twice! Bad for large vectors
    // ...
}
// Need a move instead of a copy
class Vector {
    // ...
    Vector(const Vector& a);    // copy constructor
    Vector& operator=(const Vector& a); // copy assignment
    Vector(Vector&& a);  // move constructor
    Vector& operator=(Vector&& a); // move assignment
};
Vector::Vector(Vector&& a)
    :elem{a.elem},  // "grab the elements" from a
    sz{a.sz}
{
    a.elem = nullptr;   // now a has no elements
    a.sz = 0;
}

// && means r-value reference - something that cannot be assigned to
// Use case
Vector f()
{
    Vector x(1000);
    Vector y(1000);
    Vector z(1000);
    // ...
    z = x; // copy 
    y = std::move(x); // momve
    // ...
    return z; // move
};

// Supressing operations
// Move or copy should not be done by superclass, since it may not be appropriate for sub classes
// delete keyword to supress defailt operations
class Shape {
public:
    Shape(const Shape&) =delete; // no copy
    Shape& operator=(const Shape&) =delete;
    Shape(Shape&&) =delete; // no move
    Shape& operator=(Shape&&) =delete; 

    ~Shape();
// ...
};



//~~~~~~~~Templates~~~~~~~~~~~
// A template is a class or a function that we parameterize with a set of types or values.
// We use templates to represent concepts that are best understood as something very general 
// from which we can generate specific types and functions by specifying arguments
// Example, vector<double> or vector<int>

// Vector of any type T

template<typename T>
class Vector {
private:
    T∗ elem; // elem points to an array of sz elements of type T
    int sz;
public:
    Vector(int s); // constructor: establish invariant, acquire resources
    ~Vector() { delete[] elem; } // destructor: release resources

    // ... copy and move operations ...

    T& operator[](int i);
    int size() const { return sz; }
};

template<typename T>
Vector<T>::Vector(int s)
{
    if (s<0) throw Negative_siz e{};
    elem = new T[s];
    sz = s;
}

template<typename T>
const T& Vector<T>::operator[](int i) const
{
    if (i<0 || size()<=i)
        throw out_of_rang e{"Vector::operator[]"};
    return elem[i];
}

// Usage examples
Vector<char> vc(200); // vector of 200 characters
Vector<string> vs(17); // vector of 17 strings
Vector<list<int>> vli(45); // vector of 45 lists of integers

void write(const Vector<string>& vs)
{
    for (int i = 0; i!=vs.size(); ++i)
        cout << vs[i] << '\n';
}

// Function Templates

// Allows writing generic algorithms
// Function that calculates the sum of the element values of any container type
template<typename Container, typename Value>
Value sum(const Container& c, Value v)
{
    for (auto x : c)
        v+=x;
    return v;
}

void user(Vector<int>& vi, std::list<double>& ld, std::vector<complex<double>>& vc)
{
    int x = sum(vi,0);  // the sum of a vector of ints (add ints)
    double d = sum(vi,0.0); // the sum of a vector of ints (add doubles to allow for large numbers)
    double dd = sum(ld,0.0);    // the sum of a list of doubles
    auto z = sum(vc,complex<double>{}); // the sum of a vector of complex<double>
                                        // the initial value is {0.0,0.0}
}



// Function objects (Also knowns as functors)


// Used to define objects that can be called like functions

template<typename T>
class Less_than {
    const T val;    // value to compare against
public:
    Less_than(const T& v) :val(v) { }
    bool operator()(const T& x) const { return x<val; } // call operator
};

// The function called operator() implements the function call

// Create function objects
Less_than<int> lti {42};    // lti(i) will compare i to 42 using < (i<42)
Less_than<string> lts {"Backus"}; // lts(s) will compare s to "Backus" using < (s<"Backus")

void fct(int n, const string & s)
{
    bool b1 = lti(n);   // true if n<42
    bool b2 = lts(s);   // true if s<"Backus"
    // ...
}

// Functors are used to implement predicates (returns true or false) to control behavior  of algorithms
// Example count elements in a container if condition is true
template<typename C, typename P>
int count(const C& c, P pred)
{
    int cnt = 0;
    for (const auto& x : c)
        if (pred(x))
            ++cnt;
    return cnt;
}

void f(const Vector<int>& vec, const list<string>& lst, int x, const string& s)
{
    cout << "number of values less than " << x << ": " << count(vec,Less_than<int>{x})  << '\n';
    cout << "number of values less than " << s  << ": " << count(lst,Less_than<string>{s})  << '\n';
}

// Less_than<int>{x} constructs an object for which the call operator compares to the int called x
// Function objects carry the value with them. Saves on writing separate functions for each value and type

// Lambda expressions - implicitly generate function objects

void f(const Vector<int>& vec, const list<string>& lst, int x, const string& s)
{
    cout << "number of values less than " << x  << ": " << count(vec,[&x](int a){ return a<x; }) << '\n';
    cout << "number of values less than " << s << ": " << count(lst,[&x](const string& a){ return a<s; }) << '\n';
}

// [&x](int a){ return a<x; } is called a lambda expression and generates a function object
// [&x] is a capture list specifying that local names used (such as x ) will be passed by reference
// x is the state, and a is the input to the function object
// Use lamba expressions only to generate simple function objects

// Use of lambdas and templates to make the drawing code seen earlier generic

// Apply operation to all elements of a container
// class indicates that C and oper have to be classes. Interchangable in C++17
template<class C, class Oper>
void for_all(C& c, Oper op) // assume that C is a container of pointers
{
    for (auto& x : c)
        op(∗x); // pass op() a reference to each element pointed to
}

void user()
{
    vector<unique_ptr<Shape>> v;
    while (cin)
        v.push_back(read_shape(cin));
    for_all(v,[](Shape& s){ s.draw(); }); // draw_all()
    for_all(v,[](Shape& s){ s.rotate(45); }); // rotate_all(45)
}

// Aliases - using keyword

// using size_t = unsigned int; 
// Similar to typedef
// Defining new temmplate by binding some or all template arguments
template<typename Key, typename Value>
class Map {
// ...
};
template<typename Value>
using String_map = Map<string,Value>;
String_map<int> m; // m is a Map<str ing,int>
