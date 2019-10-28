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
    std::fill(data.begin(), data.end(), value);
}
Matrix :: Matrix(size_t r, size_t c, int * value):
    columns(c),
    rows(r), 
    data(value, value + columns*rows),
    subClass(*this)
{}
Matrix :: Matrix(const Matrix& m):
    columns(m.columns),
    rows(m.rows),
    data(m.data),
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
Matrix :: SubClassMatrix& Matrix :: operator[](size_t r)
{
    subClass.setRow(r);
    return subClass;
}
const Matrix :: SubClassMatrix& Matrix :: operator[](size_t r) const
{
    subClass.setRow(r);
    return subClass;
}
Matrix :: SubClassMatrix :: SubClassMatrix(Matrix& p):
    r(0),
    parent(p)
{}
int& Matrix :: SubClassMatrix :: operator[](size_t c)
{
    if(c >= parent.columns || r >= parent.rows)
        throw std::out_of_range("out of range");
    return parent.data[r*parent.columns + c];
}
int Matrix :: SubClassMatrix :: operator[](size_t c) const 
{
    if(c >= parent.columns || r >= parent.rows)
        throw std::out_of_range("out of range");
    return parent.data[r*parent.columns + c];
}
void Matrix :: SubClassMatrix :: setRow(size_t row) const
{
       r = row;
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
bool Matrix :: operator==(const Matrix& m)const 
{
    if(m.columns != columns || m.rows != rows)
        return false;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if((*this)[i][j] != m[i][j])
                return false;
        }
    }
    return true;
}
bool Matrix :: operator!=(const Matrix& m) const
{
    return !(*this == m);
}
std::ostream& operator <<(std::ostream& os, const Matrix& m) 
{
    os << "Rows - " << m.rows << " Columns - " << m.columns << std::endl;
    for(int i = 0; i < m.rows; i++)
    {
        for(int j = 0; j < m.columns; j++)
            os << m[i][j] << " ";
        os << std::endl;
    }
    return os;
}