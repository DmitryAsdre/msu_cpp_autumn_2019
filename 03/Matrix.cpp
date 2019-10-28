#include "Matrix.hpp"
Matrix :: Matrix(size_t r, size_t c):
    columns(c),
    rows(r),
    subClass(*this)
{
    data.resize(columns*rows);
}
Matrix :: Matrix(size_t r, size_t c, int value):
    columns(c),
    rows(r),
    subClass(*this)
{
    data.resize(columns*rows);
    fill(data.begin(), data.end(), value);
}
Matrix :: Matrix(size_t r, size_t c, int * value):
    columns(c),
    rows(r), 
    data(value, value + columns*rows),
    subClass(*this)
{}
int Matrix :: getRows()const
{
    return rows;
}
int Matrix :: getColumns()const
{
    return columns;
}
Matrix :: SubClassMatrix& Matrix :: operator[](int r)
{
    subClass.r = r;
    return subClass;
}
const Matrix :: SubClassMatrix& Matrix :: operator[](int r) const
{
    subClass.r = r;
    return subClass;
}
Matrix :: SubClassMatrix :: SubClassMatrix(Matrix& p):
    r(0),
    parent(p)
{}
int& Matrix :: SubClassMatrix :: operator[](int c)
{
    if(c >= parent.columns || r >= parent.rows)
        throw std::out_of_range("out of range");
    return parent.data[r*parent.columns + c];
}
int Matrix :: SubClassMatrix :: operator[](int c) const 
{
    if(c >= parent.columns || r >= parent.rows)
        throw std::out_of_range("out of range");
    return parent.data[r*parent.columns + c];
}
Matrix& Matrix :: operator*=(int value)
{
    for(int& x : data)
        x *= value;
    return (*this);
}
Matrix& Matrix :: operator+=(int value)
{
    for(int& x : data)
        x += value;
    return (*this);
}
Matrix& Matrix :: operator-=(int value)
{
    for(int& x : data)
        x -= value;
    return (*this);
}
Matrix& Matrix :: operator/=(int value)
{
    if(value == 0)
        throw std::runtime_error("division by 0");
    for(int& x : data)
        x /= value;
    return (*this);
}
