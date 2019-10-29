#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstddef>
#include <vector>
#include <stdexcept>
#include <iostream>
class Matrix
{
    public:
        class SubClassMatrix
        {
            private:
                size_t r;
                Matrix& parent;
            public:
                SubClassMatrix(Matrix& p, size_t row);
                int& operator[](size_t c);
        }; 
        
        class SubClassMatrixConst
        {
            private:
                size_t r;
                const Matrix& parent;
            public:
                SubClassMatrixConst(const Matrix& p, size_t row);
                int operator[](size_t c);
        };
    private:
        size_t columns;
        size_t rows;
        std :: vector<int> data;
    public:
        Matrix(size_t r, size_t c);
        Matrix(size_t r, size_t c, int value);
        Matrix(size_t r, size_t c, int * values);
        Matrix(const Matrix& t);

        int getRows()const;
        int getColumns()const;

        SubClassMatrix operator[](size_t r);
        SubClassMatrixConst operator[](size_t r)const;

        Matrix& operator+=(int value);
        Matrix& operator-=(int value);
        Matrix& operator*=(int value);
        Matrix& operator/=(int value);

        bool operator==(const Matrix& m)const;
        bool operator!=(const Matrix& m)const;

        friend std::ostream& operator <<(std::ostream& os, const Matrix& m);
};
#endif