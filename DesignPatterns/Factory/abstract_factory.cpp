/* The factory is required to produce testBoard objects depending on the OS platform - Alpine Linux and Angstrom Linux
 We build a factory of factories to do this. Applying OOP principle closed to modfication, open to extension  */

#include <iostream>
#include <memory>

using namespace std;

class BoardTest { // No change
public:
    virtual void applyConfig() = 0;
    virtual void applyTest1() final {cout << "Test1 applied" << endl;}
    virtual void applyTest2() final {cout << "Test2 applied" << endl;}
};

class IntelBoardTest: public BoardTest {
    void applyConfig() {cout << "Intel specific configurations" << endl;}
};

class ARMBoardTest : public BoardTest {
    void applyConfig() {cout << "ARM specific configurations" << endl;}
};

class PowerBoardTest : public BoardTest {
    void applyConfig() {cout << "Power specific configurations" << endl;}

};

class AlpineIntelBoardTest: public BoardTest { // Define Alpine Intel board
    void applyConfig() {cout << "Alpine Linux Intel specific configurations" << endl;}
};

class AlpineARMBoardTest : public BoardTest { // Define Alpine ARM board
    void applyConfig() {cout << "Alpine Linux ARM specific configurations" << endl;}
};

class AlpinePowerBoardTest : public BoardTest { // Define Alpine Power board
    void applyConfig() {cout << "Alpine Linux Power specific configurations" << endl;}

};

class AngstromIntelBoardTest: public BoardTest { // Define Angstrom Intel board
    void applyConfig() {cout << "Angstrom Linux Intel specific configurations" << endl;}
};

class AngstromARMBoardTest : public BoardTest { // Define Angstrom ARM board
    void applyConfig() {cout << "Angstrom Linux ARM specific configurations" << endl;}
};

class AngstromPowerBoardTest : public BoardTest { // Define Angstrom Power board
    void applyConfig() {cout << "Angstrom Linux Power specific configurations" << endl;}

};

class BoardTestFactory { // No change
public:
    virtual shared_ptr<BoardTest> createBoardTest(string type);
};

shared_ptr<BoardTest> BoardTestFactory::createBoardTest(string type) 
{
    shared_ptr<BoardTest> bt;
    if (type == "Intel") 
        bt = shared_ptr<BoardTest>(new IntelBoardTest);
    else if (type == "ARM")
        bt = shared_ptr<BoardTest>(new ARMBoardTest);
    else if (type == "Power")
        bt = shared_ptr<BoardTest>(new PowerBoardTest);
    else    
        return shared_ptr<BoardTest>(nullptr);
    return bt;

}

class AlpineBoardTestFactory : public BoardTestFactory { // Sublcass Alpine factory
    shared_ptr<BoardTest> createBoardTest(string type) override;
};


shared_ptr<BoardTest> AlpineBoardTestFactory::createBoardTest(string type) 
{
    shared_ptr<BoardTest> bt;
    if (type == "Intel") 
        bt = shared_ptr<BoardTest>(new AlpineIntelBoardTest);
    else if (type == "ARM")
        bt = shared_ptr<BoardTest>(new AlpineARMBoardTest);
    else if (type == "Power")
        bt = shared_ptr<BoardTest>(new AlpinePowerBoardTest);
    else    
        return shared_ptr<BoardTest>(nullptr);
    return bt;
}

class AngstromBoardTestFactory : public BoardTestFactory { // Sublcass Angstrom factory
    shared_ptr<BoardTest> createBoardTest(string type) override;
};


shared_ptr<BoardTest> AngstromBoardTestFactory::createBoardTest(string type) 
{
    shared_ptr<BoardTest> bt;
    if (type == "Intel") 
        bt = shared_ptr<BoardTest>(new AngstromIntelBoardTest);
    else if (type == "ARM")
        bt = shared_ptr<BoardTest>(new AngstromARMBoardTest);
    else if (type == "Power")
        bt = shared_ptr<BoardTest>(new AngstromPowerBoardTest);
    else    
        return shared_ptr<BoardTest>(nullptr);
    return bt;
}

class TestBoard { // No change
protected:
    shared_ptr<BoardTestFactory> factory;
public:
    TestBoard(shared_ptr<BoardTestFactory> bf) : factory(bf) {}
    void test(string t);
};

void TestBoard::test(string type) 
{ 
    shared_ptr<BoardTest> bt{factory->createBoardTest(type)};  
    bt->applyConfig();
    bt->applyTest1();
    bt->applyTest2();
}

int main() 
{
    shared_ptr<BoardTestFactory> falp = shared_ptr<BoardTestFactory>(new AlpineBoardTestFactory); 
    TestBoard t1{falp}, t2{falp}, t3{falp};
    t1.test("Intel");
    t2.test("ARM");
    t3.test("Power");

    shared_ptr<BoardTestFactory> fang = shared_ptr<BoardTestFactory>(new AngstromBoardTestFactory); 
    TestBoard t4{fang}, t5{fang}, t6{fang};
    t4.test("Intel");
    t5.test("ARM");
    t6.test("Power");

}