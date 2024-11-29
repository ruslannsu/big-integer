#include "BigInt.h"


BigInt::BigInt():base(UINT32_MAX), max_digit(::max_digit), num(){}

BigInt::~BigInt(){}

BigInt::BigInt(int input):base(UINT32_MAX), max_digit(::max_digit), num()
{
    num.push_back(input);
}

BigInt::BigInt(std::string str):base(UINT32_MAX), max_digit(::max_digit), num()
{
    if (str.empty() || (str.at(0) == '-' && str.size() == 1))
    {
        throw std::invalid_argument("Invalid input string for BigInt");
    }
    if (str.at(0) == '-')
    {
        throw std::invalid_argument("BigInt only supports non-negative numbers");
    }
    size_t index = str.size() - 1;
    while(true)
    {
        if (((str.size() - index - 1) % range) == 0)
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


BigInt& BigInt::operator=(const BigInt& other)
{
    if (this == &other)
    {
        return *this;
    }
    base = other.base;
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
    if (num.size() < other.num.size())
    {
        num.resize(other.num.size());
    }
    size_t t_size = num.size();
    for (size_t i = 0; i != other.num.size(); ++i)
    {
        if ((num.at(i) + other.num.at(i)) > max_digit)
        {
            num.at(i) += other.num.at(i);
            for (size_t j = i; j != t_size - 1; ++j)
            {
                if (num.at(j) > max_digit)
                {
                    num.at(j)-=max_digit + 1;
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
    return res+=b;;
}


BigInt& BigInt::operator-=(const BigInt& other)
{
    if (other.num.empty())
    {
        throw std::invalid_argument("Cannot subtract an uninitialized BigInt");
    }
    if (*this < other)
    {
        throw std::invalid_argument("Only +nums");
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

BigInt operator-(const BigInt& a, const BigInt&b)
{
    BigInt res = a;
    res-=b;
    return res;
}



BigInt& BigInt::operator*=(const BigInt& other)
{
    if ((num.empty()) || (other.num.empty()))
    {
        throw std::invalid_argument("Cannot multiply by an uninitialized BigInt");
    }
    BigInt mul;
    mul.num.resize(num.size() + other.num.size(), 0);
    BigInt buff;
    for (size_t i = 0; i != other.num.size(); ++i)
    {
        for (size_t j = 0; j != num.size(); ++j)
        {
            if ((num.at(j) * other.num.at(i) + mul.num.at(i + j)) > max_digit)
            {
                mul.num.at(i + j) += (num.at(j) * other.num.at(i));
                mul.num.at(i + j + 1) += mul.num.at(i + j) / (max_digit + 1);
                mul.num.at(i + j) = mul.num.at(i + j) % (max_digit + 1);
            }
            else
            {
                mul.num.at(i + j) += (num.at(j) * other.num.at(i));
            }
        }
    }
    *this = mul;
    return *this;
}

BigInt operator*(const BigInt&a, const BigInt&b)
{
    BigInt res = a;
    res*=b;
    return res;
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
            if (num.at(i) > other.num.at(i))
            {
                return true;
            }
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
            if (num.at(i) < other.num.at(i))
            {
                return true;
            }
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

bool BigInt::operator<(const BigInt& other) const
{
    return !(*this >= other);
}

bool BigInt::operator>(const BigInt& other) const
{
    return !(*this <= other);
}

bool BigInt::operator!=(const BigInt& other) const
{
    return !(*this == other);
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

void BigInt::destroy_nulls()
{
    for (size_t i = num.size() - 1; i != 0; --i)
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

void BigInt::shift_right()
{
    if (num.size() == 0)
    {
        num.push_back(0);
        return;
    }
    num.push_back(num.at(num.size() - 1));
    for (size_t i = num.size() - 2; i != 0; i--)
    {
        num.at(i) = num.at(i - 1);
    }
    num.at(0) = 0;
}

BigInt& BigInt::operator/=(const BigInt& other)
{
    BigInt current, res;
    res.num.resize(this->num.size(), 0);
    for (size_t i = num.size() - 1; i != -1; --i)
    {
        current.shift_right();
        current.num.at(0) = num.at(i);
        destroy_nulls();
        int x = 0, l = 0, r = max_digit + 1;
        while(l <= r)
        {
            size_t mid = (r + l) / 2;
            BigInt temp;
            temp = BigInt(std::to_string(mid)) * other;
            temp.destroy_nulls();
            current.destroy_nulls();
            if (current >= temp)
            {
                x = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        res.num.at(i) = x;
        BigInt del = other * BigInt(std::to_string(x));
        del.destroy_nulls();
        current-=del;
    }
    *this = res;
    return *this;
}

std::pair<BigInt, BigInt> divmod(BigInt& a, BigInt& b)
{
    BigInt current;
    BigInt res;
    res.num.resize(a.num.size(), 0);
    for (size_t i = a.num.size() - 1; i != -1; --i)
    {
        current.shift_right();
        current.num.at(0) = a.num.at(i);
        a.destroy_nulls();
        int x = 0, l = 0, r = max_digit + 1;
        while(l <= r)
        {
            size_t mid = (r + l) / 2;
            BigInt temp;
            temp = BigInt(std::to_string(mid)) * b;
            temp.destroy_nulls();
            current.destroy_nulls();
            if (current >= temp)
            {
                x = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        res.num.at(i) = x;
        BigInt del = b * BigInt(std::to_string(x));
        del.destroy_nulls();
        current-=del;
    }
    return std::make_pair(res, current);
}


BigInt operator/(const BigInt&a, const BigInt&b)
{
    BigInt res = a;
    return res/=b;
}

BigInt& BigInt::operator%=(const BigInt&other)
{
    BigInt temp = (*this / other) * other;
    temp.destroy_nulls();
    *this -= temp;
    return *this;
}

BigInt operator%(const BigInt&a, const BigInt&b)
{
    BigInt res = a;
    res %= b;
    return res;
}


bool BigInt::is_odd()
{
    return num.at(0) & 1;
}



BigInt& BigInt::operator^=(const BigInt& other)
{
    BigInt temp_other = other;
    BigInt res(1);
    while (temp_other != BigInt(0))
    {
        if (temp_other.is_odd())
        {
            res *= *this;
            res.destroy_nulls();
        }
        *this *= *this;
        this->destroy_nulls();
        temp_other /= 2;
    }
    *this = res;
    return *this;
}

BigInt operator^(const BigInt &a, const BigInt &b)
{
    BigInt res = a;
    res^=b;
    return res;
}


