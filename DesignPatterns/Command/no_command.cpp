/* Control panel for AC - Components - Fan, Compressor, Humidifier, Temp Display (on/off commands) 
In naive implementation all commands are hardcoded into control panel.
*/

#include <iostream>
#include <memory>

using namespace std;

class Fan {
public:
    void on() {cout << "Fan turned on" << endl;}
    void off() {cout << "Fan turned off" << endl;}
};

class Compressor {
public:
    void on() {cout << "Compressor turned on" << endl;}
    void off() {cout << "Compressor turned off" << endl;}
};

class Humidifier {
public:
    void on() {cout << "Humidifer turned on" << endl;}
    void off() {cout << "Humidifier turned off" << endl;}
};

class TempDisplay {
public:
    void on() {cout << "Temp Display turned on" << endl;}
    void off() {cout << "Temp Display turned off" << endl;}
};

class ControlPanel{
protected:
    Fan fan;
    Compressor comp;
    Humidifier hum;
    TempDisplay temp;
public:
    ControlPanel(Fan f, Compressor c, Humidifier h, TempDisplay t) : fan{f}, comp{c}, hum{h}, temp{t} {}
    void FanOn() {fan.on();}
    void FanOff() {fan.off();}
    void CompressorOn() {comp.on();}
    void CompressorOff() {comp.off();}
    void HumidifierOn() {hum.on();}
    void HumidifierOff() {hum.off();}
    void TempDisplayOn() {temp.on();}
    void TempDisplayOff() {temp.off();}
};

int main() 
{
    Fan fan;
    Compressor compressor;
    Humidifier humidifier;
    TempDisplay tempdisplay;

    ControlPanel controlpanel{fan, compressor, humidifier, tempdisplay};
    // Give the commands from the controlpanel
    cout << "Turning AC on" << endl;
    controlpanel.FanOn();
    controlpanel.CompressorOn();
    controlpanel.HumidifierOn();
    controlpanel.TempDisplayOn();
    cout << endl;
    cout << "Turning AC off" << endl;
    controlpanel.FanOff();
    controlpanel.CompressorOff();
    controlpanel.HumidifierOff();
    controlpanel.TempDisplayOff();

    return 0;
}   