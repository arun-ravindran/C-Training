/* Lab 3 - An inventory class */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Item {
public:
    virtual string getId() = 0;
    virtual int getCount() const = 0;
    virtual string getDescription() = 0;
};

class Inventory {
private:
    vector<Item*> stock;
public:
    Inventory() {}
    void insertItem(Item* i) {stock.push_back(i);}
    void sortItemsByCount();
    vector<string> itemDescription();
};


struct less_than { //function object
    bool operator()(const Item* x, const Item* y) 
    {
        return x->getCount() < y->getCount(); // order Items by count
    }    
};

void Inventory::sortItemsByCount()
{
    sort(stock.begin(), stock.end(), less_than());
}

vector<string> Inventory::itemDescription()
{
    vector<string> res;
    for (auto& ele:stock)
        res.push_back(ele->getDescription());
    return res;
}

class Furnace : public Item {
private:
    string id;
    int count;
public:
    Furnace(string i, int c) : id{i}, count{c} {}
    virtual string getId() {return id;}
    virtual int getCount() const {return count;}
    virtual string getDescription();
};

string Furnace::getDescription()
{
    ostringstream out;
    out << "Item id " << id << " ; " << "Item count " << count << endl;
    return out.str();
}

class AC : public Item {
private:
    string id;
    string year;
    int count;
    
public:
    AC(string i, string y, int c) : id{i}, year{y}, count{c} {}
    virtual string getId() {return id;}
    virtual string getYear() {return year;}
    virtual int getCount() const {return count;}
    virtual string getDescription();
};

string AC::getDescription()
{
    ostringstream out;
    out << "Item id " << id << " ; " << "Item Year " << year << " ; " << "Item count " << count << endl;
    return out.str();
}

int main()
{
    Furnace* f1 = new Furnace("HotFurnace1", 10);
    Furnace* f2 = new Furnace("HotFurnace2", 5);
    AC *ac1 = new AC("CoolAC1", "2019", 7);
    
    Inventory current_inv;

    current_inv.insertItem(f1);
    current_inv.insertItem(f2);
    current_inv.insertItem(ac1);

    current_inv.sortItemsByCount();

    vector<string> desc = current_inv.itemDescription();
    for (auto& e: desc)
        cout << e << endl;
}
