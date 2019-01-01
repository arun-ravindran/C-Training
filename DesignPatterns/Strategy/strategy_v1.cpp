/* Redesign of the naive code in no_stratey.cpp with the strategy pattern. The controller algorithm is abstracted */

#include <iostream>
#include <memory>

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
    shared_ptr<ControlAlgo> cntrl; // Needs to be pointer since ControlAlgo is not a concrete class
public:
    HeatingCoolingSystem(shared_ptr<ControlAlgo> c) : cntrl{c} {}
    virtual void description() {};
    virtual void commonSystemStuff() final {cout << "Implements behavior common to all systems" << endl;}

};

class FurnaceModelv1 : public HeatingCoolingSystem { // v1 uses a on/off controller
public:
    FurnaceModelv1() : HeatingCoolingSystem{shared_ptr<ControlAlgo>(new OnOff)} {}// Constructor
    void description() {cout << "Furnace model v1" << endl;}
    void getControl() {cntrl->control();}
};

class FurnaceModelv2 : public HeatingCoolingSystem { // v2 uses a PI controller
public:
    FurnaceModelv2() : HeatingCoolingSystem{shared_ptr<ControlAlgo>(new PI)} {}// Constructor
    void description() {cout << "Furnace model v2" << endl;}
    void getControl() {cntrl->control();}
};

class FurnaceModelv3 : public HeatingCoolingSystem { // v3 uses a PID controller
public:
    FurnaceModelv3() : HeatingCoolingSystem{shared_ptr<ControlAlgo>(new PID)} {}// Constructor
    void description() {cout << "Furnace model v3" << endl;}
    void getControl() {cntrl->control();}
};

class FurnaceModelv4 : public HeatingCoolingSystem { // v4 uses a MPC controller
public:
    FurnaceModelv4() : HeatingCoolingSystem{shared_ptr<ControlAlgo>(new MPC)} {}// Constructor
    void description() {cout << "Furnace model v4" << endl;}
    void getControl() {cntrl->control();}
};

class ACModelv1 : public HeatingCoolingSystem { // v1 uses a on/off controller
public:
    ACModelv1() : HeatingCoolingSystem{shared_ptr<ControlAlgo>(new OnOff)} {}// Constructor
    void description() {cout << "AC model v1" << endl;}
    void getControl() {cntrl->control();}
};

class ACModelv2 : public HeatingCoolingSystem { // v2 uses a PI controller
public:
    ACModelv2() : HeatingCoolingSystem{shared_ptr<ControlAlgo>(new PI)} {}// Constructor
    void description() {cout << "AC model v2" << endl;}
    void getControl() {cntrl->control();}
};

class ACModelv3 : public HeatingCoolingSystem { // v3 uses a PID controller
public:
    ACModelv3() : HeatingCoolingSystem{shared_ptr<ControlAlgo>(new PID)} {}// Constructor
    void description() {cout << "AC model v3" << endl;}
    void getControl() {cntrl->control();}
};

class ACModelv4 : public HeatingCoolingSystem { // v4 uses an MPC controller
public:
    ACModelv4() : HeatingCoolingSystem{shared_ptr<ControlAlgo>(new MPC)} {}// Constructor
    void description() {cout << "AC model v4" << endl;}
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

    FurnaceModelv3 f3;
    f3.description();
    f3.commonSystemStuff();
    f3.getControl();

    FurnaceModelv4 f4;
    f4.description();
    f4.commonSystemStuff();
    f4.getControl();

    cout << endl;

    ACModelv1 a1;
    a1.description();
    a1.commonSystemStuff();
    a1.getControl();

    ACModelv2 a2;
    a2.description();
    a2.commonSystemStuff();
    a2.getControl();

    ACModelv3 a3;
    a3.description();
    a3.commonSystemStuff();
    a3.getControl();

    ACModelv4 a4;
    a4.description();
    a4.commonSystemStuff();
    a4.getControl();
}
