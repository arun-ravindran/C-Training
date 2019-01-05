/* In naive implementation all commands are hardcoded into control panel. 
If we want to change the functionality - say, remove Temp Display, and add SmartMonoitoring, code needs to be modified.
Use command pattern to decouple Control Panel, and Individual Units. Clients can now flexibly and remove commands.
OOP principles of closed to modification, open to extension & Dependence Inversion.
*/

#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

// Command interface
class Command {
public:
    virtual void execute() = 0; 
};

// Different Units
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

// Concrete command classes for the units
class FanOnCommand : public Command {
protected:
    shared_ptr<Fan> fan;
public:
    FanOnCommand(shared_ptr<Fan> f) : fan{f} {}
    void execute() {
        fan->on();
    }

};

class FanOffCommand : public Command {
protected:
    shared_ptr<Fan> fan;
public:
    FanOffCommand(shared_ptr<Fan> f) : fan{f} {}
    void execute() {
        fan->off();
    }

};

class CompressorOnCommand : public Command {
protected:
    shared_ptr<Compressor> compressor;
public:
    CompressorOnCommand(shared_ptr<Compressor> c) : compressor{c} {}
    void execute() {
        compressor->on();
    }
};

class CompressorOffCommand : public Command {
protected:
    shared_ptr<Compressor> compressor;
public:
    CompressorOffCommand(shared_ptr<Compressor> c) : compressor{c} {}
    void execute() {
        compressor->off();
    }
};

class HumidifierOnCommand : public Command {
protected:
    shared_ptr<Humidifier> humidifier;
public:
    HumidifierOnCommand(shared_ptr<Humidifier> h) : humidifier{h} {}
    void execute() {
        humidifier->on();
    }
};

class HumidifierOffCommand : public Command {
protected:
    shared_ptr<Humidifier> humidifier;
public:
    HumidifierOffCommand(shared_ptr<Humidifier> h) : humidifier{h} {}
    void execute() {
        humidifier->off();
    }
};

class TempDisplayOnCommand : public Command {
protected:
    shared_ptr<TempDisplay> tempdisplay;
public:
    TempDisplayOnCommand(shared_ptr<TempDisplay> t) : tempdisplay{t} {}
    void execute() {
        tempdisplay->on();
    }
};

class TempDisplayOffCommand : public Command {
protected:
    shared_ptr<TempDisplay>tempdisplay;
public:
    TempDisplayOffCommand(shared_ptr<TempDisplay> t) : tempdisplay{t} {}
    void execute() {
        tempdisplay->off();
    }
};

// Control panel with a hashtable of Command*   
class ControlPanel {
protected:
    unordered_map<string, shared_ptr<Command>> command_table; //Hashtable(command name, pointer) 
public:
    
    void setCommand(string cname, shared_ptr<Command> c) {command_table.insert(make_pair(cname, c));} 
    void executeCommand(string cname) {command_table[cname]->execute();}

};

// Client
int main()
{
    ControlPanel cp;
    shared_ptr<Fan> fan{shared_ptr<Fan>(new Fan)};
    cp.setCommand("fanOn", shared_ptr<Command>(new FanOnCommand(fan)));
    cp.executeCommand("fanOn");
    cp.setCommand("fanOff", shared_ptr<Command>(new FanOffCommand(fan)));
    cp.executeCommand("fanOff");
    cout << endl;

    shared_ptr<Compressor> comp{shared_ptr<Compressor>(new Compressor)};
    cp.setCommand("compressorOn", shared_ptr<Command>(new CompressorOnCommand(comp)));
    cp.executeCommand("compressorOn");
    cp.setCommand("compressorOff", shared_ptr<Command>(new CompressorOffCommand(comp)));
    cp.executeCommand("compressorOff");

}