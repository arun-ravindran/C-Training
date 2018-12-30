/* Naive example implementation without using the stratgey pattern. The example consists of classes representing two industrial products, 
furnace and air conditioning. Each product could implement different control algorithms - ON/OFF, PI, PID, MPC. The naive implemenentation suffers from lack of code reuse,
violates dependency inversion principle, and violates open to extension/close to modification principle if the control algorithms need to updated */

#include <iostream>

using namespace std;

class HeatingCoolingSystem { // Super class
public:
    virtual void description() = 0;
    virtual void control() = 0;
    virtual void commonSystemStuff() final {cout << "Implements behavior common to all systems" << endl;}
};

class FurnaceModelv1 : public HeatingCoolingSystem { // v1 uses a on/off controller
public:
    void description() {cout << "Furnace model v1" << endl;}
    void control() {cout << "Implements on/off controller with X-onoff parameters" << endl;}
};

class ACModelv1 : public HeatingCoolingSystem { // v1 uses a on/off controller
public:
    void description() {cout << "AC model v1" << endl;}
    void control() {cout << "Implements on/off controller with X-onoff parameters" << endl;}
};

class FurnaceModelv2 : public HeatingCoolingSystem { // v2 uses a PI controller
public:
    void description() {cout << "Furnace model v2" << endl;}
    void control() {cout << "Implements PI controller with X-PI parameters" << endl;}
};

class ACModelv2 : public HeatingCoolingSystem { // v2 uses a PI controller
public:
    void description() {cout << "AC model v2" << endl;}
    void control() {cout << "Implements PI controller with X-PI parameters" << endl;}
};

class FurnaceModelv3 : public HeatingCoolingSystem { // v3 uses a PID controller
public:
    void description() {cout << "Furnace model v3" << endl;}
    void control() {cout << "Implements PID controller with X-PID parameters" << endl;}
};

class ACModelv3 : public HeatingCoolingSystem { // v3 uses a PID controller
public:
    void description() {cout << "AC model v3" << endl;}
    void control() {cout << "Implements PID controller with X-PID parameters" << endl;}
};

class FurnaceModelv4 : public HeatingCoolingSystem { // v4 uses an MPC controller
public:
    void description() {cout << "Furnace model v4" << endl;}
    void control() {cout << "Implements MPC controller X-MPC model" << endl;}
};

class ACModelv4 : public HeatingCoolingSystem { // v4 uses an MPC controller
public:
    void description() {cout << "AC model v4" << endl;}
    void control() {cout << "Implements MPC controller X-MPC model" << endl;}
};

// Test classes

int main()
{
    FurnaceModelv1 f1;
    f1.description();
    f1.commonSystemStuff();
    f1.control();

    FurnaceModelv2 f2;
    f2.description();
    f2.commonSystemStuff();
    f2.control();

    FurnaceModelv3 f3;
    f3.description();
    f3.commonSystemStuff();
    f3.control();

    FurnaceModelv4 f4;
    f4.description();
    f4.commonSystemStuff();
    f4.control();

    cout << endl;

    ACModelv1 a1;
    a1.description();
    a1.commonSystemStuff();
    a1.control();

    ACModelv2 a2;
    a2.description();
    a2.commonSystemStuff();
    a2.control();

    ACModelv3 a3;
    a3.description();
    a3.commonSystemStuff();
    a3.control();

    ACModelv4 a4;
    a4.description();
    a4.commonSystemStuff();
    a4.control();

    return 0;
}