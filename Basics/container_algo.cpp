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
struct Entry {
    string name;
    int number;
};

// Output
ostream& operator<<(ostream& os, const Entry& e)
{
    return os << "{\"" << e.name << "\", " << e.number << "}";
}

// Input : More complicated because of formatting and error handling
// Note: is >> c produces a bool indicating success at reading is into c

istream& operator>>(istream& is, Entry& e)
// read { "name" , number } pair. Note: for matted with { " " , and }
{
    char c, c2;
    if (is>>c && c=='{' && is>>c2 && c2=='"') { // star t with a { "
        string name;    // the default value of a string is the empty string: ""
        while (is.get(c) && c!='"') // anything before a " is part of the name
            name+=c;

        if (is>>c && c==',') {
            int number = 0;
            if (is>>number>>c && c=='}') { // read the number and a }
                e = {name ,number};`// assign to the entry
                return is;
            }
        }
    }
    is.setf(ios_base::failbit); // register the failure in the stream
    return is;
}

// Usage
for (Entry ee; cin>>ee; ) // read from cin into ee
    cout << ee << '\n'; // write ee to cout



//~~~~~Containers - vectors~~~~~~~~~~

// Class with the main purpose of holding objects is commonly called a container

// The most useful standard-library container is vector 
// A vector is a sequence of elements of a given type. The elements are stored contiguously in memory

// Example use 
vector<Entry> phone_book = { // Entry defined above
    {"David Hume",123456},
    {"Karl Popper",234567},
    {"Bertrand Ar thur William Russell",345678}
};

// Element access through subscripting
void print_book(const vector<Entry>& book)
{
    for (int i = 0; i!=book.size(); ++i)
        cout << book[i] << '\n';
}

// Range loop
void print_book(const vector<Entry>& book)
{
    for (const auto& x : book)
        cout << x << '\n';
}

// Initialization
vector<int> v1 = {1, 2, 3, 4}; // size is 4
vector<string> v2; // size is 0
vector<Shape∗> v3(23); // size is 23; initial element value: nullptr
vector<double> v4(32,9.9); // size is 32; initial element value: 9.9


// Adding element. Automatic size increase
void input()
{
    for (Entr y e; cin>>e;)
        phone_book.push_back(e);
}

// Copying vectors
vector<Entry> book2 = phone_book; //Note: Use pointers if copying is expensive

// Templating vectors
// vector<T> where T can be built in types, user defined types, pointers 

// Note: subscript operator [] does not do range checking. Use at() operator instead
// at() throws an exception of type out_of_range

int main()
    try {
        // your code
    }
    catch (out_of_rang e) {
        cerr << "range error\n";
    }
    catch (...) { //Default exceptioin handler
        cerr << "unknown exception thrown\n";
    }
}


//~~~~~Containers - lists~~~~~~~~~~