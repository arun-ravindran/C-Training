/* Testing devices with two different interfaces without applying the Adapter pattern. No code reuse */

#include <iostream>
#include <memory>

using namespace std;

class DeviceInterface {
public:
    virtual void on() = 0;
    virtual void applyInput() = 0;
    virtual string measureOutput() = 0;
    virtual void off() = 0;
};

class Device : public DeviceInterface {
public:
    void on() override {cout << "Turn on device" << endl;} 
    void applyInput() override{cout << "Apply input to device" << endl;}
    string measureOutput() override {return "Output from devie";}
    void off() override {cout << "Turn off device" << endl;}
};

class TestDevice {
protected:
    shared_ptr<DeviceInterface> dev;
public:
    TestDevice(shared_ptr<DeviceInterface> d) : dev(d) {} 
    void applyTest();
};

void TestDevice::applyTest()
{
    dev->on();
    dev->applyInput();
    cout << dev->measureOutput() << endl;
    dev->off();
}

class NewDeviceInterface {
public:
    virtual void on() = 0;
    virtual void applyLoInput() = 0;
    virtual void applyHiInput() = 0;
    virtual string measureOutput() = 0;
    virtual void off() = 0;
};

class NewDevice : public NewDeviceInterface {
public:
    void on() override {cout << "Turn on device" << endl;} 
    void applyLoInput() override {cout << "Apply low input to device" << endl;}
    void applyHiInput() override {cout << "Apply high input to device" << endl;}
    string measureOutput() override {return "Output from device";}
    void off() override {cout << "Turn off device" << endl;}
};


class TestNewDevice {
protected:
    shared_ptr<NewDeviceInterface> dev;
public:
    TestNewDevice(shared_ptr<NewDeviceInterface> d) : dev(d) {} 
    void applyTest();
};

void TestNewDevice::applyTest()
{
    dev->on();
    dev->applyLoInput();
    dev->measureOutput();
    dev->applyHiInput();
    cout << dev->measureOutput() << endl;
    dev->off();

}

int main()
{
    TestDevice test_dev1{shared_ptr<DeviceInterface>(new Device)};
    test_dev1.applyTest();
    cout << endl;
    TestNewDevice test_dev2{shared_ptr<NewDeviceInterface>(new NewDevice)};
    test_dev2.applyTest();
    cout << endl;
    
    return 0;
}


