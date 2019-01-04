/* Creating differnt "board test" object types without application of the facotry pattern. The resulting code needs modification when new object types
need to be created and existing ones removed */

#include <iostream>
#include <memory>

using namespace std;


class BoardTest {
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

shared_ptr<BoardTest> testBoard(string type) 
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
    
    bt->applyConfig();
    bt->applyTest1();
    bt->applyTest2();

    return bt;

}

int main() 
{
    testBoard("Intel");
    testBoard("ARM");
    testBoard("Power");
}

