#include "BigInt.h"

BigInt::BigInt():base(UINT32_MAX), null_count(0), max_digit(::max_digit), num(){}

BigInt::~BigInt(){}

BigInt::BigInt(int input):base(UINT32_MAX), null_count(0)
{
    num.push_back(input);
}

BigInt::BigInt(std::string str):base(UINT32_MAX), null_count(0), max_digit(::max_digit), num()
{
    if (str.empty() || (str[0] == '-' && str.size() == 1))
    {
        throw std::invalid_argument("Invalid input string for BigInt");
    }
    if (str[0] == '-')
    {
        throw std::invalid_argument("BigInt only supports non-negative numbers");
    }
    size_t index = str.size() - 1;
    while(true)
    {
        if (((str.size() - index - 1)% range) == 0)
        {
            if (str.substr(index + 1, range) != "")
            {
                num.push_back( stoi(str.substr(index + 1, range)));
            }
        }
        if (index + 1 >= range)
        {
            index -= range;
        }
        else
        {
            break;
        }
    }
    if (str.substr(0 , index + 1) != "")
    {
        num.push_back(std::stoi(str.substr(0, index + 1), nullptr, 10));
    }
}

BigInt::BigInt(const BigInt &other):base(other.base), null_count(0), num(other.num){}

BigInt& BigInt::operator=(const BigInt& other)
{
    if (this == &other)
    {
        return *this;
    }
    base = other.base;
    null_count = other.null_count;
    num = other.num;
    return *this;
}

void BigInt::TempPrint()
{
    if ((num.at(0) == 0) && ((num.size() == 1)))
    {
        std::cout << 0 << std::endl;
        return;
    }
    for (std::size_t i = num.size() - 1; i != 0; --i)
    {

        if (num.at(i) == 0)
        {
            num.pop_back();
        }
        else
        {
            break;
        }
    }
    for (std::size_t i = num.size() - 1; i != -1; --i)
    {
        if (((num.at(i) / 100000000) == 0) && (i != num.size() - 1))
        {

            std::string nulls(9, '0');
            std::string num_str(std::to_string(num.at(i)));
            nulls.replace(nulls.size() - num_str.size(), num_str.size(), num_str);
            std::cout << nulls;
        }
        else
        {
            std::cout << num.at(i);
        }
    }
}


BigInt& BigInt::operator++()
{
    return *this += 1;
}

const BigInt BigInt::operator++(int)
{
    BigInt copy_this = *this;
    *this+=1;
    return copy_this;
}

BigInt& BigInt::operator--()
{
    return *this -= 1;
}

const BigInt BigInt::operator--(int)
{
    BigInt copy_this = *this;
    *this-=1;
    return copy_this;
}

BigInt& BigInt::operator+=(const BigInt& other)
{
    if (other.num.empty())
    {
        throw std::invalid_argument("Cannot add an uninitialized BigInt");
    }
    size_t t_size = num.size();
    for (size_t i = 0; i != other.num.size(); ++i)
    {
        if ((num.at(i) + other.num.at(i)) > max_digit)
        {
            num.at(i)+=other.num.at(i);
            for (size_t j = i; j != t_size; ++j)
            {
                if (num.at(j) > max_digit)
                {
                    num.at(j)-=max_digit + 1;
                    if (j == t_size)
                    {
                        num.push_back(1);
                        return *this;
                    }
                    ++num.at(j + 1);
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            num.at(i)+=other.num.at(i);
        }
    }
    return *this;
}

BigInt operator+(const BigInt& a, const BigInt& b)
{
    BigInt res = a;
    return res+=a;
}


BigInt& BigInt::operator-=(const BigInt& other)
{
    if (other.num.empty())
    {
        throw std::invalid_argument("Cannot subtract an uninitialized BigInt");
    }

    for (size_t i = 0; i != other.num.size();++i)
    {
        if ((num.at(i) < other.num.at(i)))
        {
            num.at(i)+=max_digit + 1;
            for (size_t j = i + 1; j < num.size(); ++j)
            {
                if (num.at(j) == 0)
                {
                    num.at(j)+=max_digit;
                }
                else
                {
                    --num.at(j);
                    break;
                }
            }
            num.at(i)-=other.num.at(i);
        }
        else
        {
            num.at(i)-=other.num.at(i);
        }
    }
    return *this;
}


BigInt operator*(const BigInt&a, const BigInt&b)
{
    if ((a.num.empty()) || (b.num.empty()))
    {
        throw std::invalid_argument("Cannot multiply by an uninitialized BigInt");
    }

    BigInt mul;
    if (a.num.at(0) * b.num.at(0) <= max_digit)
    {
        mul = a.num.at(0) * b.num.at(0);
        return mul;
    }
    mul.num.resize(a.num.size() + b.num.size(), 0);
    BigInt buff;
    for (size_t i = 0; i != b.num.size(); ++i)
    {
        for (size_t j = 0; j != a.num.size(); ++j)
        {
            if ((a.num.at(j) * b.num.at(i) + mul.num.at(i + j)) > max_digit)
            {
                mul.num.at(i + j) += (a.num.at(j) * b.num.at(i));
                mul.num.at(i + j + 1) += mul.num.at(i + j) / (max_digit + 1);
                mul.num.at(i + j) = mul.num.at(i + j) % (max_digit + 1);
            }
            else
            {
                mul.num.at(i + j) += (a.num.at(j) * b.num.at(i));
            }
        }
    }
    return mul;
}



bool BigInt::operator>=(const BigInt& other) const
{
    if (num.empty() || other.num.empty())
    {
        throw std::invalid_argument("Cannot compare uninitialized BigInt objects");
    }
    if (num.size() == other.num.size())
    {
        for (size_t i = num.size() - 1; i != -1; --i)
        {
            if (num.at(i) < other.num.at(i))
            {
                return false;
            }
        }
        return true;
    }
    if (num.size() > other.num.size())
    {
        return true;
    }
    if (num.size() < other.num.size())
    {
        return false;
    }
}


bool BigInt::operator<=(const BigInt& other) const
{
    if (num.empty() || other.num.empty())
    {
        throw std::invalid_argument("Cannot compare uninitialized BigInt objects");
    }
    if (num.size() == other.num.size())
    {
        for (size_t i = num.size() - 1; i != -1; --i)
        {
            if (num.at(i) > other.num.at(i))
            {
                return false;
            }
        }
        return true;
    }
    if (num.size() < other.num.size())
    {
        return true;
    }
    if (num.size() > other.num.size())
    {
        return false;
    }
}

bool BigInt::operator==(const BigInt&other) const
{
    if (num.empty() || other.num.empty())
    {
        throw std::invalid_argument("Cannot compare uninitialized BigInt objects");
    }
    if (num.size() != other.num.size())
    {
        return false;
    }
    else
    {
        for (size_t i = 0; i != num.size(); ++i)
        {
            if (other.num.at(i) != num.at(i))
            {
                return false;
            }
        }
    }
    return true;
}


std::ostream& operator<<(std::ostream& os, const BigInt& Bg)
{

    if ((Bg.num.at(0) == 0) && ((Bg.num.size() == 1)))
    {
        os << 0 << std::endl;
        return os;
    }
    size_t t_size = Bg.num.size();
    for (std::size_t i = Bg.num.size() - 1; i != 0; --i)
    {
        if (Bg.num.at(i) == 0)
        {
           --t_size;
        }
        else
        {
            break;
        }
    }
    for (std::size_t i = t_size - 1; i != -1; --i)
    {
        if (((Bg.num.at(i) / 100000000) == 0) && (i != t_size - 1))
        {

            std::string nulls(9, '0');
            std::string num_str(std::to_string(Bg.num.at(i)));
            nulls.replace(nulls.size() - num_str.size(), num_str.size(), num_str);
            os << nulls;
        }
        else
        {
            os << Bg.num.at(i);
        }
    }
    return os;
}