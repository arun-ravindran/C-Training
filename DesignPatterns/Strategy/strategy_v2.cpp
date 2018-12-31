/* Redesign of strategy_v1 code to reduce the number of classes through dependency injection */

#include <iostream>

using namespace std;

class ControlAlgo {
public:
    virtual void control() {};
};

class OnOff : public ControlAlgo {
public:
    void control() {cout << "Implements on/off controller with X-onoff parameters" << endl;}
};

class PI : public ControlAlgo {
public:
     void control() {cout << "Implements PI controller with X-PI parameters" << endl;}
};

class PID : public ControlAlgo {
public:
    void control() {cout << "Implements PID controller with X-PID parameters" << endl;}
};

class MPC : public ControlAlgo {
public:
    void control() {cout << "Implements MPC controller X-MPC model" << endl;}
};

class HeatingCoolingSystem { // Super class
protected:
    ControlAlgo* cntrl; // Needs to be pointer since ControlAlgo is not a concrete class
public:
    HeatingCoolingSystem(ControlAlgo* c) : cntrl{c} {}
    virtual void description() {};
    virtual void commonSystemStuff() final {cout << "Implements behavior common to all systems" << endl;}

};

class FurnaceModel : public HeatingCoolingSystem { 
private:
    string desc;
public:
    FurnaceModel(string d, ControlAlgo* c) : HeatingCoolingSystem{c}, desc{d} {}    // Constructor
    void description() {cout << desc << endl;}
    void getControl() {cntrl->control();}
    // Other furnace related meethods...
};

class ACModel : public HeatingCoolingSystem { 
private:
    string desc;
public:
    ACModel(string d, ControlAlgo* c) : HeatingCoolingSystem{c}, desc{d} {}    // Constructor
    void description() {cout << desc << endl;}
    void getControl() {cntrl->control();}
    // Other AC related methods...
};

int main()
{
    FurnaceModel f1("Furnace model v1", new OnOff);
    f1.description();
    f1.getControl();
    FurnaceModel f2("Furnace model v2", new PI);
    f2.description();
    f2.getControl();
    FurnaceModel f3("Furnace model v3", new PID);
    f3.description();
    f3.getControl();
    FurnaceModel f4("Furnace model v4", new MPC);
    f4.description();
    f4.getControl();

    cout << endl;

    ACModel a1("AC model a1", new OnOff);
    a1.description();
    a1.getControl();
    ACModel a2("AC model a2", new PI);
    a2.description();
    a2.getControl();
    ACModel a3("AC model a3", new PID);
    a3.description();
    a3.getControl();
    ACModel a4("AC model a4", new MPC);
    a4.description();
    a4.getControl();

}


