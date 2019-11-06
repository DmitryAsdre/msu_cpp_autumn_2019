#ifndef BIGINT
#define BIGINT
#include "Vector.hpp"
#include <string>
class BigInt
{
    private:
        Vector data;
        int sign;
    public:
        BigInt();
        BigInt(const Vector& v, int sign);
        BigInt(const std::string& str);

        BigInt& operator -();

        BigInt operator +(const BigInt& add)const;
        BigInt operator -(const BigInt& minus)const;

        BigInt& operator +=(const BigInt& add);
        BigInt& operator -=(const BigInt& add);

        BigInt operator +(int add)const;
        BigInt operator -(int add)const;

        BigInt& operator +=(int add);
        BigInt& operator -=(int add);

        
        bool operator <(const BigInt& cmp)const;
        bool operator >(const BigInt& cmp)const;
        bool operator ==(const BigInt& cmp)const;
        bool operator !=(const BigInt& cmp)const;
        bool operator <=(const BigInt& cmp)const;
        bool operator >=(const BigInt& cmp)const;

        bool operator <(int cmp)const;
        bool operator >(int cmp)const;
        bool operator ==(int cmp)const;
        bool operator !=(int cmp)const;
        bool operator <=(int cmp)const;
        bool operator >=(int cmp)const;

        BigInt& operator =(const BigInt& tmp);
        BigInt& operator =(int tmp);
        BigInt& operator =(const std::string& str);

        std::string toString()const;

};
#endif