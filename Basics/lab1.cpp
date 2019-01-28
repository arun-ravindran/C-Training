/* Lab 1 - Matrix class */
/* Code up a Matrix class for a 2D matrix of ints that supports the operations implemented in test */

#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>

using namespace std;

class Matrix {
private:
    vector<vector<int>> m;
    int rows, cols;
public:
    Matrix(initializer_list<initializer_list<int>> l);
    Matrix(const Matrix& rhs);
    friend ostream& operator<<(ostream& os, Matrix& mat);
    Matrix operator=(const Matrix& mat);
    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    int getRows() {return rows;}
    int getCols() {return cols;}
};

// Constructor
Matrix::Matrix(initializer_list<initializer_list<int>> l)
{
    for (auto& row: l) {
        vector<int> temp;
        temp.reserve(row.size());
        copy(row.begin(), row.end(), back_inserter(temp));
        m.push_back(temp);
        cols = temp.size();
    }
    rows = m.size();
}

// Stream insertion operator overloading
ostream& operator<<(ostream& os, Matrix& mat)
{
    for (auto& row:mat.m) {
        for (auto& ele:row)
            os << ele << " ";
        os << endl;
    }
    return os;
}

// Copy constructor
Matrix::Matrix(const Matrix& rhs)
{
    for (auto& row: rhs.m ) {
        vector<int> temp;
        temp.reserve(row.size());
        copy(row.begin(), row.end(), back_inserter(temp));
        m.push_back(temp);
    }
    rows = rhs.rows;
    cols = rhs.cols;
}

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    if ( (m1.getRows() != m2.getRows()) || (m1.getCols() != m2.getCols()) )
        throw out_of_range{"Matrix dimensions mismatch"};
    vector<vector<int>> res;
    auto itm1 = m1.m.begin();
    auto itm2 = m2.m.begin();
    for (; itm1 != m1.m.end(); ++itm1, ++itm2) {
        vector<int> temp;
        temp.reserve(*itm1.size());
        temp = *itm1 + *itm2; //To Do : Fix this
        res.push_back(temp);
    }
    return res;
}

// Copy assignment
Matrix Matrix::operator=(const Matrix& rhs)

    if (this == &rhs)
        return rhs;
    this->m.clear(); 
    for (auto& row: rhs.m ) {
        vector<int> temp;
        temp.reserve(row.size());
        copy(row.begin(), row.end(), back_inserter(temp));
        m.push_back(temp);
    }

}





// Test 

int main()
{
    Matrix m1{{1,2,3}, {4,5,6}, {7,8,9}}; // Test constructor, initializer list
    cout << m1; // Test stream insertion operator. Should print matrix as rows and columns
    cout << "Rows: " << m1.getRows() << "Cols: " << m1.getCols() << endl; 
    cout << endl;

    Matrix m2{m1}; // Test copy constructor
    cout << m2;
/*
    Matrix m3 = m1 + m2; // Test copy assignment and overloaded + operator
    cout << m3; 
    Matrix m4 = m3.transpose(); // Test transpose method
    if (isTransposeCorrect(m3, m4)  
        cout << "m3 is transpose of m4";
    else 
        cout << "m3 is not transpose of m4";
*/
}