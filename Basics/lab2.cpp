/* Lab 2 - Matrix class */
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
    Matrix(vector<vector<int>>& m);
    Matrix(const Matrix& rhs);
    friend ostream& operator<<(ostream& os, Matrix& mat);
    Matrix operator=(const Matrix& mat);
    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    int getRows() const {return rows;}
    int getCols() const {return cols;}
    Matrix transpose();
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

Matrix::Matrix(vector<vector<int>>& m)
{
    for (auto& row: m ) {
        vector<int> temp;
        temp.reserve(row.size());
        copy(row.begin(), row.end(), back_inserter(temp));
        this->m.push_back(temp);
    }
    this->rows = m.size();
    this->cols = m[0].size();
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

    auto it1 = m1.m.begin();
    auto it2 = m2.m.begin();
    for (; it1 != m1.m.end(); ++it1, ++it2) {
        vector<int> temp;
        for (int i = 0; i < m1.getCols(); i++)
            temp.push_back( (*it1).at(i) + (*it2).at(i));
        res.push_back(temp);
    }
    return Matrix{res};
}

// Copy assignment
Matrix Matrix::operator=(const Matrix& rhs)
{
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

Matrix Matrix::transpose()
{
    vector<vector<int>> res;

    for (int i = 0; i < cols; i++) {
        vector<int> temp;
        for (auto& row : m)
            temp.push_back(row.at(i));
        res.push_back(temp);
    }
    return res;
}



// Test 

int main()
{
    Matrix m1{{1,2,3}, {4,5,6}, {7,8,9}}; // Test constructor, initializer list
    cout << m1; // Test stream insertion operator. Should print matrix as rows and columns
    cout << "Rows: " << m1.getRows() << " Cols: " << m1.getCols() << endl; 
    cout << endl;

    Matrix m2{m1}; // Test copy constructor
    cout << m2;
    cout << endl;

    Matrix m3 = m1 + m2; // Test copy assignment, constructor with vector<vector> argumemnt, and overloaded + operator
    cout << m3; 
    cout << endl;

    Matrix m4 = m3.transpose(); // Test transpose method
    cout << m4;

}