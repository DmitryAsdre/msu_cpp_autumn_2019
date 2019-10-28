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
                int& operator[](int c);    
                int operator[](int c)const;
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

        int getRows()const;
        int getColumns()const;

        SubClassMatrix& operator[](int r);
        const SubClassMatrix& operator[](int r)const;

        Matrix& operator+=(int value);
        Matrix& operator-=(int value);
        Matrix& operator*=(int value);
        Matrix& operator/=(int value);
};
#endif