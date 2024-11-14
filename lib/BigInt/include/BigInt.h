#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdint.h>
#include <cmath>

inline int range = 9;

inline int max_digit = 999999999;

class BigInt
{
public:
    uint32_t base;
    uint32_t null_count;
    uint32_t max_digit;
    std::vector<uint64_t> num;


public:
    BigInt();
    void TempPrint()
    {
        for (std::size_t i = num.size() - 1; i != -1; --i)
        {
            if ((num.at(i) == 0) && (num.at(i - 1) == 0))
            {
                num.pop_back();
            }
            if ((num.at(num.size() - 1)) == 0)
            {
                num.pop_back();
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
    BigInt(int input);
    BigInt(std::string str); // бросать исключение std::invalid_argument при ошибке
    BigInt(const BigInt&);
    ~BigInt();
    BigInt& operator=(const BigInt& other);  //возможно присваивание самому себе!

    BigInt operator~() const;

    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int) const;

    BigInt& operator+=(const BigInt& other);
    BigInt& operator*=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    BigInt& operator/=(const BigInt&);
    BigInt& operator^=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator int() const;
   // operator std::string() const;

    size_t size() const;  // size in bytes
private:
};
BigInt operator+(const BigInt& a, const BigInt& b);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
//BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
//BigInt operator&(const BigInt&, const BigInt&);
//BigInt operator|(const BigInt&, const BigInt&);


