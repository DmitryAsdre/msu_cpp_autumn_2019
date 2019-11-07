#ifndef BIGINT
#define BIGINT
#include <cstring>
#include <string>
#include <ostream>
#include <cmath>
#include <iostream>
#include <sstream>
#include <bitset>
#include <stdexcept>
#include <cstdint>
const unsigned int BASE = 1e1;
int sgn(int a);
class BigInt
{
    private:
        unsigned char * data;
        size_t size;
        size_t len;
        int sign;
    private:
        void resize(size_t l);
        void strip();
        static bool amax(const BigInt& b1, const BigInt& b2);
    public:
        BigInt();
        BigInt(const BigInt& copy);
        BigInt(int t);
        BigInt(unsigned int t);
        BigInt(unsigned char* data_, size_t size_, int sign_);
        BigInt(const std::string& str);


        BigInt& operator -();

        BigInt operator +(const BigInt& add)const;
        BigInt operator -(const BigInt& add)const;

        BigInt& operator +=(const BigInt& add);
        BigInt& operator -=(const BigInt& sub);

        BigInt& operator ++();
        BigInt& operator --();

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
        friend std::ostream& operator<<(std::ostream& os, const BigInt& b);
};
#endif