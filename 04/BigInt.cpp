#include "BigInt.hpp"
int sgn(int a)
{
    return a >= 0 ? 1 : -1;
}
BigInt :: BigInt():
    data(new unsigned char[1]),
    size(1),
    len(1),
    sign(1)
{
    if(data == NULL)
        throw std::runtime_error("cannot alloc memory");
    data[0] = 0;
}
BigInt :: BigInt(const BigInt& copy):
    size(copy.size),
    len(copy.len),
    sign(copy.sign)
{
    data = new unsigned char[len];
    if(data == NULL)
        throw std::runtime_error("cannot alloc memory");
    std::memcpy(data, copy.data, len*sizeof(char));
}
BigInt :: BigInt(int t):
    data(new unsigned char[30]),
    size(0),
    len(30),
    sign(sgn(t))
{
    if(data == NULL)
        throw std::runtime_error("cannot alloc memory");
    t = abs(t);
    while(t != 0)
    {
        data[size] = t%BASE;
        t /= BASE;
        size++;
    }
}
BigInt :: BigInt(unsigned int t):
    data(new unsigned char[30]),
    size(0),
    len(30),
    sign(1)
{
    if(data == NULL)
        throw std::runtime_error("cannot alloc memory");
    while(t != 0)
    {
        data[size] = t%BASE;
        t /= BASE;
        size++;
    }
}
BigInt :: BigInt(const std::string& str):
    data(new unsigned char[str.size()]),
    size(0),
    len(str.size()),
    sign(1)
{
    std::string buf;
    for(size_t i = str.size(); i >= 1; i--)
    {
        if(!(isdigit(str[i - 1]) || (i - 1 == 0 && str[i - 1] == '-')))
            throw std::runtime_error("unexpected input");
        if(isdigit(str[i - 1]))
        {
            buf = str[i - 1];
            data[size] = std::stoi(buf);
            size++;
        }
        else 
            sign *= -1;
    }
}
void BigInt::resize(size_t l)
{
    if(l < size)
        throw std::runtime_error("memory corruption");
    unsigned char* newData = new unsigned char[l];
    if(newData == NULL)
        throw std::runtime_error("cannot alloc memory");
    std::memcpy(newData, data, size*sizeof(char));
    delete[] data;
    data = newData;
    len = l;
}
void BigInt::strip()
{
    for(size_t i = size; i >= 1; i--)
    {
        if(data[i - 1] == 0)
            size--;
        else 
            break;
    }
    if(size == 0)
    {
        sign = 1;
        size = 1;
    }
    if(size*4 < len && len > 4)
        resize(size*2);
}
BigInt& BigInt :: operator += (const BigInt& add)
{
    if(sign != add.sign)
    {
        sign *= -1;
        *this -= add;
        sign *= -1;
        return *this;
    }
    if(len < add.size)
        resize(add.size + 2);
    unsigned int buf = 0;
    for(size_t i = 0; i < std::max(size, add.size); i++)
    {
        buf += i < size ? data[i] : 0;
        buf += i < add.size ? add.data[i] : 0;
        data[i] = buf%BASE;
        buf /= BASE; 
    }
    if(buf)
    {
        if(len == size)
            resize(2*len);
        data[size] = buf;
        size++;
    }
    strip();
    return *this;
}
bool BigInt :: amax(const BigInt& b1, const BigInt& b2)
{
    if(b1.size > b2.size)
        return true;
    else if(b1.size < b2.size)
        return false;
    for(size_t i = b1.size; i >= 1; i--)
    {
        if(b1.data[i - 1] > b2.data[i - 1])
            return true;
        else if(b1.data[i - 1] < b2.data[i - 1])
            return false;
    }
    return true;
}
BigInt& BigInt::operator-=(const BigInt& sub)
{
    if(sign != sub.sign)
    {
        sign *= -1;
        *this += sub;
        sign *= -1;
        return *this;
    }
    bool amax = BigInt::amax(*this, sub);
    unsigned int buf1 = 0;
    unsigned int buf2 = 0;
    unsigned int  shift = 0;
    if(!amax)
        sign *= -1;
    if(len < sub.len)
        resize(sub.len + 2);
    for(size_t i = 0; i < std::max(size, sub.size);i++)
    {
        buf1 = i < size ? data[i] : 0;
        buf2 = i < sub.size ? sub.data[i] : 0;
        if(amax)
        {
            buf2 += shift;
            shift = 0;
            if(buf1 < buf2)
            {
                buf1 += BASE;
                shift = 1;
            }
            data[i] = buf1 - buf2;
        }
        else
        {
            buf1 += shift;
            shift = 0;
            if(buf2 < buf1)
            {
                buf2 += BASE;
                shift = 1;
            }
            data[i] = buf2 - buf1;
        }
    }
    strip();
    return *this;
}
BigInt& BigInt::operator -()
{
    sign *= -1;
    return *this;
}
BigInt BigInt::operator+(const BigInt& add)const
{
    BigInt res(*this);
    res += add;
    return res;
}
BigInt BigInt::operator-(const BigInt& sub)const
{
    BigInt res(*this);
    res -= sub;
    return res;
}
BigInt& BigInt::operator++()
{
    (*this) += 1;
    return *this;
}
BigInt& BigInt::operator--()
{
    (*this) -= 1;
    return *this;
}
BigInt& BigInt::operator+=(int add)
{
    return (*this)+=BigInt(add);
}
BigInt& BigInt::operator-=(int sub)
{
    return (*this)-=BigInt(sub);
}
BigInt BigInt::operator+(int add)const
{
    BigInt res(*this);
    return res += add;
}
BigInt BigInt::operator-(int sub)const
{
    BigInt res(*this);
    return res -= sub;
}


bool BigInt::operator>(const BigInt& cmp)const
{
    if(sign > cmp.sign)
        return true;
    else if(sign < cmp.sign)
        return false;
    if(size > cmp.size)
        return (sign == 1) ? true : false;
    else if(size < cmp.size)
        return (sign == 1) ? false : true;
    for(size_t i = size; i >= 1; i--)
    {
        if(data[i - 1] > cmp.data[i - 1])
            return (sign == 1) ? true : false;
        else if(data[i - 1] < cmp.data[i - 1])
            return (sign == 1) ? false : true;
    }
    return false;
}
bool BigInt::operator ==(const BigInt& cmp)const 
{
    if(sign != cmp.sign || size != cmp.size)
        return false;
    for(size_t i = 0; i < size; i++)
    {
        if(cmp.data[i] != data[i])
            return false;
    }
    return true;
}
bool BigInt::operator<(const BigInt& cmp)const 
{
    return !(*this > cmp || *this == cmp);
}
bool BigInt::operator!=(const BigInt& cmp)const
{
    return !(*this == cmp);
}
bool BigInt::operator>=(const BigInt& cmp)const 
{
    return (*this > cmp || *this == cmp);
}
bool BigInt::operator<=(const BigInt& cmp)const
{
    return (*this < cmp || *this == cmp);
}


bool BigInt::operator<(int cmp)const
{
    return *this < BigInt(cmp);
}
bool BigInt::operator>(int cmp)const
{
    return *this > BigInt(cmp);
}
bool BigInt::operator==(int cmp)const
{
    return *this == BigInt(cmp);
}
bool BigInt::operator!=(int cmp)const
{
    return *this != BigInt(cmp);
}
bool BigInt::operator<=(int cmp)const
{
    return *this <= BigInt(cmp);
}
bool BigInt::operator>=(int cmp)const
{
    return *this >= BigInt(cmp);
}


BigInt& BigInt::operator=(const BigInt& tmp)
{
    if(len == tmp.len)
    {
        std::memset(data, 0, len);
        std::memcpy(data, tmp.data, len);
        size = tmp.size;
    }
    else
    {
        delete[] data;
        data = new unsigned char[tmp.len];
        if(data == NULL)
            throw std::runtime_error("cannot alloc memory");
        std::memcpy(data, tmp.data, tmp.size*sizeof(unsigned char));
        size = tmp.size;
        len = tmp.len;
    }
    return *this;
}
BigInt& BigInt::operator=(int tmp)
{
    *this = BigInt(tmp);
    return *this;
}
BigInt& BigInt::operator=(const std::string& str)
{
    *this = BigInt(str);
    return *this;
}

std::string BigInt::toString()const
{
    std::string res;
    if(sign < 0)
        res += '-';
    for(size_t i = size ; i >= 1; i--)
        res += std::to_string(data[i - 1]);
    return res;
}
std::ostream& operator<<(std::ostream& os, const BigInt& b)
{
    os << b.toString();
    return os;
}