/* Redesign of the no_decorator.cpp example with decorator pattern */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility> //pair
#include <memory> //shared_ptr

using namespace std;

class ACInterface {
public:
    double getCost() {}
    vector<string> getFeatures() {}
};



class BasicAC : public ACInterface {
protected:
    unordered_map<string, double> features; //Hashtable <feature_name, cost>;
public:
    BasicAC();
    double getCost();
    vector<string> getFeatures();
};


BasicAC::BasicAC()
{
    features.insert(make_pair("Single stage scroll compressor", 500.00));
    features.insert(make_pair("Filter drier", 500.00));   
}

double BasicAC::getCost() {
    double total_cost = 0.0;
    for (auto& kv : features)
        total_cost += kv.second;
    return total_cost;
}

vector<string> BasicAC::getFeatures() {
    vector<string> res;
    for(auto& kv : features)
        res.push_back(kv.first);
    return res;
}

void printInfo(shared_ptr<BasicAC> ac);

int main()
{
    shared_ptr<BasicAC> a1{shared_ptr<BasicAC>(new BasicAC)};
    printInfo(a1);

}

void printInfo(shared_ptr<BasicAC> ac) 
{
    vector<string> f{ac->getFeatures()};
    for(auto e: f)
        cout << e << " ; ";
    cout << endl;
    cout << "Total cost " << ac->getCost() << endl;
}
