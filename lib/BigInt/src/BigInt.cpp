#include "BigInt.h"

BigInt::BigInt():base(UINT32_MAX), null_count(0), max_digit(::max_digit), num(){}

BigInt::~BigInt(){}

BigInt::BigInt(int input):base(UINT32_MAX), null_count(0)
{
    num.push_back(input);
}

BigInt::BigInt(std::string str):base(UINT32_MAX), null_count(0), max_digit(::max_digit), num()
{
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

BigInt& BigInt::operator++()
{
    if (num.at(0) != max_digit)
    {
        ++num.at(0);
        return *this;
    }
    if (num.at(0) == max_digit)
    {
        for (size_t i = 0; i != num.size(); ++i)
        {
            ++num.at(i);
            if (num.at(i) == max_digit + 1)
            {
                num.at(i) = 0;
            }
            else
            {
                break;
            }
        }
        if (num.at(num.size() - 1) == 0)
        {
            num.push_back(1);
        }
    }
    return *this;
}


const BigInt BigInt::operator++(int)
{
    BigInt copy_obj = *this;
    for (size_t i = 0; i != num.size(); ++i)
    {
        if (num.at(i) == base)
        {
            num.at(i) = 0;
            ++num.at(i + 1);
        }
        else
        {
            ++num.at(i);
            break;
        }
    }
    if (num.at(num.size() - 1) == 0)
    {
        num.push_back(1);
    }
    return copy_obj;
}



BigInt& BigInt::operator+=(const BigInt& other)
{
    if ((num.at(0) + other.num.at(0)) <= max_digit)
    {
        num.at(0)+=other.num.at(0);
        return *this;
    }
    size_t t_size = num.size();

    for (size_t i = 0; i != t_size; ++i)
    {

        if ((num.at(i) + other.num.at(i)) > max_digit)
        {
            if (i == t_size - 1)
            {
                num.push_back(0);
            }
            ++num.at(i + 1);
            num.at(i) = num.at(i) + other.num.at(i) - max_digit - 1;
        }
        else
        {
            num.at(i)+=other.num.at(i);
            break;
        }


    }
    return *this;
}


BigInt& BigInt::operator-=(const BigInt& other)
{
    if (num.at(0) > other.num.at(0))
    {
        num.at(0)-=other.num.at(0);
        return *this;
    }
    for (size_t i = 0; i != num.size(); ++i)
    {
        if ((num.at(i) < other.num.at(i)))
        {
            num.at(i)+=max_digit + 1;
            num.at(i)-=other.num.at(i);
            --num.at(i + 1);
        }
    }

}

BigInt& BigInt::operator*=(const BigInt&other)
{
    if (num.at(0) * other.num.at(0) <= max_digit)
    {
        num.at(0)*=other.num.at(0);
        return *this;
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


BigInt& BigInt::operator/=(const BigInt&)
{

}


/*
умножение
543-985439090-
843903498-34954390-
459-71214928-131616012-273105100-
*/

/*
1999999999
1999999999
3999999996000000001
---
945398903934904535674464654039391234576547
19999999995543111514457579745675432156789
18907978074484553224297392352255492865472777944962742705205702301775133571326227583
---
9453989039349045356744646540393912345765475434458397854389

1999999999554311151445757974567543215678985974389578378534895789347859348979


189079780744845532242973923522554928654736016148162747073679754059808915827988712305837901057019290507650583410864267290
08127977818831
*/

