/* All about consts in C++! */
/* From https://isocpp.org/wiki/faq/const-correctness#overview-const */

// Const correctness - Use of keyword const to prevent const objects from getting mutated
// Part of C++ type safety

// Const violations are found at compile time - no run time costs! 


// Maintain constness of a reference
void g1(std::string& s);
void f1(const std::string& s)
{
  g1(s);          // Compile-time Error since s is const
  std::string localCopy = s;
  g1(localCopy);  // Okay since localCopy is not const
}

// Conceptually const std::string is different from std::string sine the const version doesn't have 
// mutative operaitons. For example += operator

//ADD CONST EARLY AND OFTEN! 

// What does const X* p mean?
// It means p points to an object of class X, but p can’t be used to change that X object
// Read it right-to-left: “p is a pointer to an X that is constant.”
// Importantly if X has a const member function inspect(), okay to call p->inspect()
// However, if X has non-const member function, mutate(), error to call p->mutate()
// Same semnatics for const X& x

// const X*p vs. X* const p vs. const X* const p
// Hint: Read from right to left
// const X* p means “p points to an X that is const”: the X object can’t be changed via p.
// X* const p means “p is a const pointer to an X that is non-const”: 
// you can’t change the pointer p itself, but you can change the X object via p.
// const X* const p means “p is a const pointer to an X that is const”:
// you can’t change the pointer p itself, nor can you change the X object via p.


// Const member function
// Member function that inspects not mutates
class Fred {
public:
  void inspect() const;   // This member promises NOT to change *this
  void mutate();          // This member function might change *this
};
void userCode(Fred& changeable, const Fred& unchangeable)
{
  changeable.inspect();   // Okay: doesn't change a changeable object
  changeable.mutate();    // Okay: changes a changeable object
  unchangeable.inspect(); // Okay: doesn't change an unchangeable object
  unchangeable.mutate();  // ERROR: attempt to change unchangeable object
}

// Relationship between return-by-reference and a const member function

class Person {
public:
  const std::string& name_good() const;  // Right: the caller can't change the Person's name
  std::string& name_evil() const;        // Wrong: the caller can change the Person's name
  int age() const;                       // Also right: the caller can't change the Person's age
  // ...
};
void myCode(const Person& p)  // myCode() promises not to change the Person object...
{
  p.name_evil() = "Igor";     // But myCode() changed it anyway!!
}
// Try this out! g++ 5.4.0 catches this error, even if one of the const is missing



// Const overloading 
// const overloading is having an inspector and mutuator method with identical name and type and number of parameters
class Fred { /*...*/ };
class MyFredList {
public:
  const Fred& operator[] (unsigned index) const;  // Subscript operators often come in pairs
  Fred&       operator[] (unsigned index);        // Subscript operators often come in pairs
  // ...
};
// Use case of non-const
void f(MyFredList& a)  // The MyFredList is non-const
{
  // Okay to call methods that inspect (look but not mutate/change) the Fred at a[3]:
  Fred x = a[3];       // Doesn't change to the Fred at a[3]: merely makes a copy of that Fred
  a[3].inspect();      // Doesn't change to the Fred at a[3]: inspect() const is an inspector-method
  // Okay to call methods that DO change the Fred at a[3]:
  Fred y;
  a[3] = y;            // Changes the Fred at a[3]
  a[3].mutate();       // Changes the Fred at a[3]: mutate() is a mutator-method
}

// Use case of const
void f(const MyFredList& a)  // The MyFredList is const
{
  // Okay to call methods that DON'T change the Fred at a[3]:
  Fred x = a[3];
  a[3].inspect();
  // Compile-time error (fortunately!) if you try to mutate/change the Fred at a[3]:
  Fred y;
  a[3] = y;       // Fortunately(!) the compiler catches this error at compile-time
  a[3].mutate();  // Fortunately(!) the compiler catches this error at compile-time
}

// Logical state vs. physical state - mutable keyword
// Logical states what the user of the class sees - from the outside
// const is to protect logical state
// Physical state is the hidden state of the class, not visible to to user
// For example, an internal cache or lock
// If physical state has to be mutated internally for logical consts, use mutable keyword