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
    BigInt();
    void TempPrint();
    BigInt(int input);
    BigInt(std::string str); // бросать исключение std::invalid_argument при ошибке
    BigInt(const BigInt&);
    ~BigInt();
    BigInt& operator=(const BigInt& other);  //возможно присваивание самому себе!

    BigInt operator~() const;

    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);

    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    BigInt& operator/=(const BigInt&);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt&other) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    void BaseMult();
    operator int() const;
   // operator std::string() const;
    friend std::ostream& operator<<(std::ostream& os, const BigInt& Bg);
    friend BigInt operator*(const BigInt&, const BigInt&);
    size_t size() const;  // size in bytes
private:
    uint32_t base;
    uint32_t null_count;
    uint32_t max_digit;
    std::vector<uint64_t> num;
};
BigInt operator+(const BigInt& a, const BigInt& b);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);



