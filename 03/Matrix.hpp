#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstddef>
#include <vector>
#include <stdexcept>
using namespace std;

class Matrix
{
    public:
        class SubClassMatrix
        {
            private:
                mutable size_t r;
                Matrix& parent;
            public:
                SubClassMatrix(Matrix& p);
                int& operator[](size_t c);    
                int operator[](size_t c)const;
                void setRow(size_t r)const;
        }; 
    private:
        size_t columns;
        size_t rows;
        vector<int> data;
        SubClassMatrix subClass;
    public:
        Matrix(size_t r, size_t c);
        Matrix(size_t r, size_t c, int value);
        Matrix(size_t r, size_t c, int * values);
        Matrix(const Matrix& t);

        int getRows()const;
        int getColumns()const;

        SubClassMatrix& operator[](size_t r);
        const SubClassMatrix& operator[](size_t r)const;

        Matrix& operator+=(int value);
        Matrix& operator-=(int value);
        Matrix& operator*=(int value);
        Matrix& operator/=(int value);

        bool operator==(const Matrix& m)const;
        bool operator!=(const Matrix& m)const;
};
#endif