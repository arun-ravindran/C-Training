/* Naive example implementation without using the decorator pattern. Examples of various additions to a basic AC product. 
In the naive implementation, the super AC class has all possible features. The basicAC sub class is derived from the superclass 
with two of the basic features marked true. The other AC classes are feature additions to the basicAC subclass and are derived
from it. The subclasses compute the cost according to the features they have.  The drawback of this design is that it violates
the closed to modification/open to extension OOP principle, since adding new features requies modifications to the super class */


#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility> //pair

using namespace std;



// AC class with all features and costs, initialized to false
class AC {
protected:
    unordered_map<string, pair<bool, double>> features; //(ac_feature, (is_present,feature_cost))
public:
    AC();
    virtual double getCost();
    virtual vector<string> getFeatures();
};

void printInfo(AC& a);

AC::AC()
{
    features.insert(make_pair("Single stage scroll compressor", make_pair(false, 500.00)));
    features.insert(make_pair("Filter drier", make_pair(false, 500.00)));
    features.insert(make_pair("System protection pressure switches", make_pair(false, 300.00)));
    features.insert(make_pair("Sound reduction", make_pair(false, 400.00)));
    features.insert(make_pair("Intelligent diagnostics", make_pair(false, 600.00)));

}
// Get relevant features
vector<string> AC::getFeatures() 
{
    vector<string> res;
    for (auto& kv: features)
        if ((kv.second).first == true)
            res.push_back(kv.first);
    return res;
}

// Calculate relevant cost
double AC::getCost()
{
    double total_cost = 0.0;
    for (auto& kv: features)
        if ((kv.second).first == true)
            total_cost += (kv.second).second; 
    return total_cost;
} 

// Different AC types

//Basic AC
class BasicAC : public AC {
public:
    BasicAC();
    
};

// Set characteristic features to true
BasicAC::BasicAC() 
{
    features["Single stage scroll compressor"].first = true;
    features["Filter drier"].first = true;
}


// Reliable AC : Basic AC + safety switch
class ReliableAC : public BasicAC {
public:
    ReliableAC();
};

ReliableAC::ReliableAC() : BasicAC()
{
    features["System protection pressure switches"].first = true;
}

// Quiet AC: Basic AC + sound reduction
class QuietAC : public BasicAC {
public:
    QuietAC();
};

QuietAC::QuietAC() : BasicAC()
{
    features["Sound reduction"].first = true;
}

// SmartAC: Basic AC + Intelligent diagnostics
class SmartAC : public BasicAC {
public:
    SmartAC();
};

SmartAC::SmartAC() : BasicAC()
{
    features["Intelligent diagnostics"].first = true;
}

//SmartQuietAC : SmartAC + QuietAC
// Note: Multiple inheritance is tricky due to both classes being derived from the same base class
class SmartQuietAC : public SmartAC {
public:
    SmartQuietAC();
};

SmartQuietAC::SmartQuietAC() : SmartAC()
{
    features["Sound reduction"].first = true;
}



int main()
{
    BasicAC a1;
    printInfo(a1);
    ReliableAC a2;
    printInfo(a2);
    QuietAC a3;
    printInfo(a3);
    SmartAC a4;
    printInfo(a4);
    SmartQuietAC a5;
    printInfo(a5);


    return 0;    

}

void printInfo(AC& ac) 
{
    vector<string> features = ac.getFeatures();
    for(auto e: features)
        cout << e << " ; ";
    cout << endl;
    cout << "Total cost " << ac.getCost() << endl;

}