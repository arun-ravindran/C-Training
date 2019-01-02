/* Redesign of the no_decorator.cpp example with decorator pattern */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility> //pair
#include <memory> //shared_ptr

using namespace std;

class ACInterface {
public:
    virtual double getCost() = 0;
    virtual vector<string> getFeatures() = 0;
    virtual unordered_map<string,double> getFeaturesCost() = 0;
};



class BasicAC : public ACInterface {
protected:
    unordered_map<string, double> features_cost; //Hashtable <feature_name, cost>;
public:
    BasicAC();
    double getCost();
    vector<string> getFeatures();
    unordered_map<string, double> getFeaturesCost(){return features_cost;}  
};


BasicAC::BasicAC()
{
    features_cost.insert(make_pair("Single stage scroll compressor", 500.00));
    features_cost.insert(make_pair("Filter drier", 500.00));   
}

double BasicAC::getCost() {
    double total_cost = 0.0;
    for (auto& kv : features_cost)
        total_cost += kv.second;
    return total_cost;
}

vector<string> BasicAC::getFeatures() {
    vector<string> res;
    for(auto& kv : features_cost)
        res.push_back(kv.first);
    return res;
}

void printInfo(shared_ptr<ACInterface> ac);

class ACDecorator : public BasicAC {
protected:
    shared_ptr<ACInterface> innerAC;
public:
    ACDecorator(shared_ptr<ACInterface> ac) : innerAC(ac) {this->features_cost = innerAC->getFeaturesCost();}
    double getCost() {return BasicAC::getCost();}
    vector<string> getFeatures() {return BasicAC::getFeatures();}    
};

// ReliableAC extends BasicAC and ACDecorator(for dependency injection) without modification
class ReliableAC : public ACDecorator {
public:
    ReliableAC(shared_ptr<ACInterface> ac, unordered_map<string, double>& extraf);
};

ReliableAC::ReliableAC(shared_ptr<ACInterface> ac, unordered_map<string, double>& extraf) : ACDecorator{ac}
{
    for (auto& kv : extraf)
        features_cost.insert(make_pair(kv.first, kv.second)); 
}

class QuietAC : public ACDecorator {
public:
    QuietAC(shared_ptr<ACInterface> ac, unordered_map<string, double>& extraf);
};

QuietAC::QuietAC(shared_ptr<ACInterface> ac, unordered_map<string, double>& extraf) : ACDecorator{ac}
{
    for (auto& kv : extraf)
        features_cost.insert(make_pair(kv.first, kv.second));
}

class SmartAC : public ACDecorator {
public:
    SmartAC(shared_ptr<ACInterface> ac, unordered_map<string, double>& extraf);
};

SmartAC::SmartAC(shared_ptr<ACInterface> ac, unordered_map<string, double>& extraf) : ACDecorator{ac}
{
    for (auto& kv : extraf)
        features_cost.insert(make_pair(kv.first, kv.second));
}

class SmartQuietAC : public ACDecorator {
public:
    SmartQuietAC(shared_ptr<ACInterface> ac, unordered_map<string, double>& extraf);
};

SmartQuietAC::SmartQuietAC(shared_ptr<ACInterface> ac, unordered_map<string, double>& extraf) : ACDecorator{ac}
{
    for (auto& kv : extraf)
        features_cost.insert(make_pair(kv.first, kv.second));
}

int main()
{
    shared_ptr<ACInterface> bac{shared_ptr<ACInterface>(new BasicAC)}; // ACInterface* bac
    printInfo(bac);

    unordered_map<string, double> new_feature;

    // Decorate BasicAC to get ReliableAC
    new_feature.insert(make_pair("System protection pressure switches", 300.00));
    shared_ptr<ACInterface> rac{shared_ptr<ACInterface>(new ReliableAC(bac, new_feature))}; // ACInterface* rac{bac, new_feature}
    printInfo(rac);

    // Decorate BasicAC to get QuietAC
    new_feature.clear();
    new_feature.insert(make_pair("Sound reduction", 400.00));
    shared_ptr<ACInterface> qac{shared_ptr<ACInterface>(new QuietAC(bac, new_feature))}; // ACInterface* qac{bac, new_feature}
    printInfo(qac);

    // Decorate BasicAC to get SmartAC
    new_feature.clear();
    new_feature.insert(make_pair("Intelligent diagnostics", 600.00));
    shared_ptr<ACInterface> sac{shared_ptr<ACInterface>(new SmartAC(bac, new_feature))}; // ACInterface* sac{bac, new_feature}
    printInfo(sac);

     // Decorate SmartAC to get Smart and QuietAC
    new_feature.clear();
    new_feature.insert(make_pair("Sound reduction", 400.00));
    shared_ptr<ACInterface> sqac{shared_ptr<ACInterface>(new SmartQuietAC(sac, new_feature))}; // ACInterface* sqac{sac, new_feature}
    printInfo(sqac);

}

void printInfo(shared_ptr<ACInterface> ac) 
{
    vector<string> f{ac->getFeatures()};
    for(auto e: f)
        cout << e << " ; ";
    cout << endl;
    cout << "Total cost " << ac->getCost() << endl;
}
