/* Lab 1 - Money class */
// Code up a Money class that represents US dollars (dollar, cent) and implements the operations in test 
#include <iostream>

using namespace std;


const double DOL2EUR = 0.87;

class Money {
private:
    int dollars;
    int cents;
public:
    Money(double m);
    Money(int m) : dollars{m}, cents{0} {}
    Money() : dollars{0}, cents{0} {}

    int getDollars() {return dollars;}
    int getCents() {return cents;}
    friend Money operator+(Money& m1, Money& m2);
    double euros();
};

Money::Money(double m)
{
    int val = static_cast<int>(m*100.0);
    dollars = val/100; 
    cents = val%100;
}

Money operator+(Money& m1, Money& m2)
{
    int total1 = m1.dollars*100 + m1.cents;
    int total2 = m2.dollars*100 + m2.cents;
    int total = total1 + total2;
    return Money(static_cast<double>(total/100.0));
}

double Money::euros()
{
    int total = dollars*100 + cents;
    return DOL2EUR*static_cast<double>(total/100);
}


// Test
int main()
{
    Money m1{1.25}, m2{2}, m3, m4(100.755); // Round down to nearest valid cents
    cout << "m1 is " << m1.getDollars() << " dollars " << " and " << m1.getCents() << " cents" << endl;
    cout << "m2 is " << m2.getDollars() << " dollars " << " and " << m2.getCents() << " cents" << endl;
    cout << "m3 is " << m3.getDollars() << " dollars " << " and " << m3.getCents() << " cents" << endl;
    m3 = m1 + m2;
    cout << "m3 is " << m3.getDollars() << " dollars " << " and " << m3.getCents() << " cents" << endl;
    cout << "m3 in Euros is " << m3.euros() << endl;
    cout << "m4 is " << m4.getDollars() << " dollars " << " and " << m4.getCents() << " cents" << endl;
}