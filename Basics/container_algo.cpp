/* All material based on the book C++ Programming Language, 4th Edition, by Bjarne Stroustrup */
/* C++ standard library provides the most common fundamental data structures together with the fundamental algorithms used on them */

//~~~~~~~~Strings~~~~~~~~~

#include <string>
std::string s {"C++ is a general−purpose programming language"};
//std indicates string belongs to the standard namespace

// String concantenation
string compose(const string& name, const string& domain)
{
    return name + '@' + domain;
}
auto addr = compose("arun.ravindran","uncc.edu");

// You can concatenate a string , a string literal, a C-style string, or a character to a string 

void m2(string& s1, string& s2)
{
    s1 = s1 + '\n'; // append newline
    s2 += '\n'; // append newline
}

// Note: string is mutable

// substr, replace, toupper
string name = "Niels Stroustrup";
void m3()
{
    string s = name.substr(6,10); // s = Stroustrup; substr(start_pos, len); s is a copy 
    name.replace(0,5,"nicholas"); // name becomes nicholas Stroustrup
    name[0] = toupper(name[0]); // name becomes Nicholas Stroustrup
}

// String comparison
string incantation;
void respond(const string& answer)
{
    if (answer == incantation) {
    // perfor m magic   
    }
    else if (answer == "yes") {
        // ...
    }
        // ...
}



//~~~~~~~~Stream I/O~~~~~~~

// The standard library provides formatted character input and output through the iostream library
// The input operations are typed and extensible to handle user-defined types

// Output

// << operator is used as an insertion operator on objects of type ostream
// cout is the standard output stream and cerr is the standard stream for reporting errors
// By default, values written to cout are converted to a sequence of characters

void f()
{
    cout << 10; //Places 1 followed by 0 on the standard output stream
}

// Result of an output expression can itself be used for further output
void h2(int i)
{
    cout << "the value of i is " << i << '\n';
}

// Input

// >> operator is used as in extraction operator on objects of type istream
// RHS determines the type of the target
void f()
{
    int i;
    cin >> i; // read an integer into i
    double d;
    cin >> d; // read a double-precision floating-point number into d
}

// Whitespace character such as space terminates the read

// To read the whole line including '\n' (discarded)
void hello_line()
{
    cout << "Please enter your name\n";
    string str;
    getline(cin,str);
    cout << "Hello, " << str << "!\n";
}

// I/O of user defined types