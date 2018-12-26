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



//~~~~~Containers - vectors (dynamic array)~~~~~~~~~~

// Class with the main purpose of holding objects is commonly called a container

// The most useful standard-library container is vector 
// A vector is a sequence of elements of a given type. The elements are stored contiguously in memory

// Example use 
vector<Entry> phone_book = { // Entry defined above
    {"David Hume",123456},
    {"Karl Popper",234567},
    {"Bertrand Arthur William Russell",345678}
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


//~~~~~Containers - lists (doubly linked list)~~~~~~~~~~

// The standard library offers a doubly-linked list called list

// Initialization 
list<Entry> phone_book = {
    {"David Hume",123456},
    {"Karl Popper",234567},
    {"Bertrand Arthur William Russell",345678}
};

// Accessing list elements using range loop
int get_number(const string& s)
{
    for (const auto& x : phone_book)
        if (x.name==s)
            return x.number;
    return 0; // use 0 to represent "number not found"
}

// Accesssing list elements using an iterator
int get_number(const string& s)
{
    for (auto p = phone_book.begin(); p!=phone_book.end(); ++p)
        if (p−>name==s)
    return p−>number;
    return 0; // use 0 to represent "number not found"
}

// Iterator is an object that allows access to an element
// all containers have a begin() and end() methods that an iterator pointing to the first and beyond last element
// Depending on the container, the iterator can be moved forward (++) and backward (--)
// Here, p is of type list<Entry>::iterator


// Inserting and removing elements
void f(const Entry& ee, list<Entry>::iterator p, list<Entry>::iterator q)
{
    phone_book.insert(p,ee);    // add ee before the element referred to by p
    phone_book.erase(q);    // remove the element referred to by q
}



//~~~~~Containers - map (binary search tree)~~~~~~~~~~

// Maps store elements as (key, value) pairs
// Elemeents are stored in order
// Specific implementation is a red-black tree

// Initialization
map<string,int> phone_book {
    {"David Hume",123456},
    {"Karl Popper",234567},
    {"Bertrand Arthur William Russell",345678}
};

// Insert a key, value pair
void put_number(const string& s, int& i)
{
    phone_book.insert(std::pair<string,int>(s,i))
}

// Find value for key - find method returns an iterator or map::end otherwise
int get_number(const string& s)
{
    return phone_book.find(s)->second; 
}


//~~~~~Containers - unordered_map (hashtable)~~~~~~~~~~

// unordered_maps store elements as (key, value) pairs
// Elemeents are not stored in order
// Default hash functions provided for strings. Possible to supply custom hash functions


// Initialization
unordered_map<string,int> phone_book {
    {"David Hume",123456},
    {"Karl Popper",234567},
    {"Bertrand Arthur William Russell",345678}
};

// Insert and find - identical code to map

// Use custom hashes with function objects
int main() 
{
    using name = pair<string, string>;
    struct hash_name { //custom hash function object
        size_t operator()(const name &n ) const
        {
            return hash<string>()(n.first) ^ hash<string>()(n.second);
        }
    };

    unordered_map<name,int, hash_name> phone_book {
        {name("David", "Hume"),123456},
        {name("Karl", "Popper"),234567},
        {name("Bertrand", "Russell"),345678}
    };
    for (auto entry: phone_book){
        cout << entry.first.first << " " << entry.first.second << " " << entry.second << endl;
    }
}


// Useful standard containers

vector<T> // A dynamic array
list<T>  // A doubly-linked list
forward_list<T> // A singly-linked list
deque<T> // A double-ended queue
set<T> // A set - only keys with no repitions
multiset<T> // A set in which a key can occur many times
map<K,V> // Binary search tree
multimap<K,V> // A map in which a key can occur many times 
unordered_map<K,V> // Hash table
unordered_multimap<K,V> // Hash table in which a key can occur many times
unordered_set<T> // Hash table of only keys 
unordered_multiset<T> // Hash table where a key can occur many times

// Methods supported by the containers are semnatically uniform

// begin() and end() give iterators to the first and one-beyond-the-last elements, respectively.
// push_back() can be used (efficiently) to add elements to the end of a vector, forward_list, list etc. 
// size() returns the number of elements



//~~~~~~~Algorithms~~~~~~~~~~~~~

// Sort and copy 

struct less_than { //function object
    bool operator<(const Entry& x, const Entry& y) 
    {
        return x.name < y.name; // order Entrys by their names
    }    
};

list<Entry> f(vector<Entry>& vec) // Sort vector and copy to newlist
{
    list<Entry> lst;
    sort(vec.begin(),vec.end(), less_than());
    unique_copy(vec.begin(),vec.end(),back_inerter(lst)); // append to list - no explicit realloc!
    return lst; // move constructor 
}

// Find
bool has_c(const string& s, char c) // does s contain the character c?
{
    return find(s.begin(),s.end(),c)!=s.end(); // find returns an iterator
}

vector<string::iterator> find_all(string& s, char c) // find all occurences of c in s
{
    vector<string::iterator> res;
    for (auto p = s.begin(); p!=s.end(); ++p)
        if (∗p==c)
            res.push_back(p);
    return res; //vector iterators
}

void test() // test find_all
{
    string m {"Mary had a little lamb"};
    for (auto p : find_all(m,'a'))
        if (∗p!='a')
    cerr << "a bug!\n";
}

// Generalize find_all to any container type C, and search type V 
template<typename C, typename V>
vector<typename C::iterator> find_all(C& c, V v)
{
    vector<typename C::iterator> res;
    for (auto p = c.begin(); p!=c.end(); ++p)
        if (∗p==v)
            res.push_back(p);
    return res;
}

// Simplify code  - using Iterator<T> = typename T::iterator;

// Test generic find_all

void test()
{
    string m {"Mary had a little lamb"};
    for (auto p : find_all(m,'a')) // p is a string::iterator
        if (∗p!='a')
            cerr << "string bug!\n";

    list<double> ld {1.1, 2.2, 3.3, 1.1};
    for (auto p : find_all(ld,1.1))
        if (∗p!=1.1)
            cerr << "list bug!\n";

    vector<string> vs { "red", "blue", "green", "green", "orange", "green" };
    for (auto p : find_all(vs,"green"))
        if (∗p!="green")
            cerr << "vector bug!\n";

    for (auto p : find_all(vs,"green"))
        ∗p = "ver t";
}

// File I/O with I/O streams
/* File I/O with I/O streams */

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std; 

vector<string> arguments(int argc, char* argv[]);

int main(int argc, char* argv[])
{

    vector<string> args{arguments(argc, argv)};
    assert(args.size() == 3)
    
    ifstream is {args[1]}; // input stream for file "from"
    istream_iterator<string> ii {is}; // input iterator for stream
    istream_iterator<string> eos {}; // input sentinel

    ofstream os{args[2]}; // output stream for file "to"
    ostream_iterator<string> oo {os,"\n"};  // output iterator for stream
    // \n is delimiter. Each word is printed to a new line

    vector<string> b {ii,eos}; // b is a vector initialized from input [ii:eos)
    sort(b.begin(),b.end()); // sort the buffer
    unique_copy(b.begin(),b.end(),oo); // copy buffer to output, discard replicated values

    return !is.eof() || !os; // return error state 
}


vector<string> arguments(int argc, char* argv[])
{
    vector<string> res;
    for (int i = 0; i!=argc; ++i)
        res.push_back(argv[i]);
    return res;

}

// A succint version with set
set<string> b {istream_iterator<string>{is},istream_iterator<string>{}}; // read input
copy(b.begin(),b.end(),ostream_iterator<string>{os,"\n"}); // copy to output

// Use of predicates in modifying algoriithm behavior

// Find if element in a map > 42
struct Greater_than { // Predicate with function object
    int val;
    Greater_than(int v) : val{v} { }
    bool operator()(const pair<string,int>& r) { return r.second>val; }
};

void f(map<string,int>& m)
{
    auto p = find_if(m.begin(),m.end(),Greater_than{42});
    // ...
}
// Count number of elements > 42 using a lambda expression
int cxx = count_if(m.begin(), m.end(), [](const pair<string,int>& r) { return r.second>42; });



// Selected Standard Algorithms

p=find(b,e,x) // is the first p in [ b : e ) so that ∗p==x
p=find_if(b,e,f) // is the first p in [ b : e ) so that f(∗p)==true
n=count(b,e,x) // is the number of elements ∗q in [ b : e ) so that ∗q==x
n=count_if(b,e,f) // is the number of elements ∗q in [ b : e ) so that f(∗q,x)
replace(b,e,v,v2) // Replace elements ∗q in [ b : e ) so that ∗q==v by v2
replace_if(b,e,f,v2) // Replace elements ∗q in [ b : e ) so that f(∗q) by v2
p=copy(b,e ,out) // Copy [ b : e ) to [ out : p )
p=copy_if(b,e ,out,f) // Copy elements ∗q from [ b : e ) so that f(∗q) to [ out : p )
p=unique_copy(b,e ,out) // Copy [ b : e ) to [ out : p ); don’t copy adjacent duplicates
sort(b,e) // Sort elements of [ b : e ) using < as the sorting criterion
sort(b,e,f) // Sort elements of [ b : e ) using f as the sorting criterion
(p1,p2)=equal_range(b,e,v) // [ p1 : p2 ) is the subsequence of the sorted sequence [ b : e ) with the value v ; basically a binary search for v
p=merge(b,e ,b2,e2,out) // Merge two sorted sequences [ b : e ) and [ b2 : e2 ) into [ out : p )













