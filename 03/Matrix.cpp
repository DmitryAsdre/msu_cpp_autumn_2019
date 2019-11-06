#include "Matrix.hpp"
Matrix :: Matrix(size_t r, size_t c):
    columns(c),
    rows(r)
{
    data.resize(columns*rows);
}
Matrix :: Matrix(size_t r, size_t c, int value):
    columns(c),
    rows(r)
{
    data.resize(columns*rows);
    std::fill(data.begin(), data.end(), value);
}
Matrix :: Matrix(size_t r, size_t c, int * value):
    columns(c),
    rows(r),
    data(value, value + columns*rows)
{}
Matrix :: Matrix(const Matrix& m):
    columns(m.columns),
    rows(m.rows),
    data(m.data)
{}


int Matrix :: getRows()const
{
    return rows;
}
int Matrix :: getColumns()const
{
    return columns;
}


Matrix :: SubClassMatrix Matrix :: operator[](size_t r)
{
    SubClassMatrix tmp(*this, r);
    return tmp;
}
Matrix :: SubClassMatrixConst Matrix :: operator[](size_t r)const
{
    SubClassMatrixConst tmpConst(*this, r);
    return tmpConst;
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


Matrix :: SubClassMatrix :: SubClassMatrix(Matrix& p, size_t row):
    r(row),
    parent(p)
{}
int& Matrix :: SubClassMatrix :: operator[](size_t c)
{
    if(c >= parent.columns || r >= parent.rows)
        throw std::out_of_range("out of range");
    return parent.data[r*parent.columns + c];
}


Matrix :: SubClassMatrixConst :: SubClassMatrixConst(const Matrix& p, size_t row):
    r(row),
    parent(p)
{}
int Matrix :: SubClassMatrixConst :: operator[](size_t c)
{
    if(c >= parent.columns || r >= parent.rows)
        throw std::out_of_range("out of range");
    return parent.data[r*parent.columns + c];
}