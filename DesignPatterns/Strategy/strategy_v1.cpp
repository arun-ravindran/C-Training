/* Redesign of the naive code in no_stratey.cpp with the strategy pattern. The controller algorithm is abstracted */

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

class FurnaceModelv1 : public HeatingCoolingSystem { // v1 uses a on/off controller
public:
    FurnaceModelv1() : HeatingCoolingSystem{new OnOff} {}// Constructor
    void description() {cout << "Furnace model v1" << endl;}
    void getControl() {cntrl->control();}
};

class FurnaceModelv2 : public HeatingCoolingSystem { // v1 uses a on/off controller
public:
    FurnaceModelv2() : HeatingCoolingSystem{new PI} {}// Constructor
    void description() {cout << "Furnace model v2" << endl;}
    void getControl() {cntrl->control();}
};

int main()
{
    FurnaceModelv1 f1;
    f1.description();
    f1.commonSystemStuff();
    f1.getControl();

    FurnaceModelv2 f2;
    f2.description();
    f2.commonSystemStuff();
    f2.getControl();
}
