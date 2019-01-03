/* Adapter pattern. Using adapters to reuse test for devices with two different interfaces. 
Note that an a state variable is used to store the intermedidate output from the new device  
Uses the OOP principle of open to extension, close to modification */

#include <iostream>
#include <memory>

using namespace std;

class DeviceInterface { // No change from previous
public:
    virtual void on() = 0;
    virtual void applyInput() = 0;
    virtual string measureOutput() = 0;
    virtual void off() = 0;
};

class Device : public DeviceInterface { // No change from previous
public:
    void on() override {cout << "Turn on device" << endl;} 
    void applyInput() override{cout << "Apply input to device" << endl;}
    string measureOutput() override {return "Output from device";}
    void off() override {cout << "Turn off device" << endl;}
};

class TestDevice { // No change from previous
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

class NewDeviceInterface { // No change from previous
public:
    virtual void on() = 0;
    virtual void applyLoInput() = 0;
    virtual void applyHiInput() = 0;
    virtual string measureOutput() = 0;
    virtual void off() = 0;
};

class NewDevice : public NewDeviceInterface { // No change from previous
public:
    void on() override {cout << "Turn on device" << endl;} 
    void applyLoInput() override {cout << "Apply low input to device" << endl;}
    void applyHiInput() override {cout << "Apply high input to device" << endl;}
    string measureOutput() override {return "Output from device";}
    void off() override {cout << "Turn off device" << endl;}
};


// Goal is to use TestDevice "as is" for devices that support the NewDeviceInterface

class NewDeviceInterfaceAdapter : public DeviceInterface { // The adapter
protected:
    shared_ptr<NewDeviceInterface> ndev;
    string output;
public:
    NewDeviceInterfaceAdapter(shared_ptr<NewDeviceInterface> nd) : ndev(nd) {}
    void on() override {ndev->on();} 
    void applyInput() override;
    string measureOutput() override;
    void off() override {cout << "Turn off device" << endl;}

};

void NewDeviceInterfaceAdapter::applyInput() 
{
    ndev->applyLoInput(); 
    output = ndev->measureOutput();
    ndev->applyHiInput();
    output = output + " " + ndev->measureOutput();
}

string NewDeviceInterfaceAdapter::measureOutput()
{
    return output;
}

int main()
{
    TestDevice test_dev1{shared_ptr<DeviceInterface>(new Device)};
    test_dev1.applyTest();
    cout << endl;
    shared_ptr<NewDevice>new_dev{new NewDevice}; // New device
    shared_ptr<DeviceInterface> newdev_adapter{new NewDeviceInterfaceAdapter{new_dev}}; // Wrap
    TestDevice test_dev2{newdev_adapter}; // Now create a test
    test_dev2.applyTest();
    cout << endl;
    
    return 0;
}
