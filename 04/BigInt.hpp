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

        std::string toString()const;

};
#endif