#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>
#include <utility>

constexpr int range = 9;
constexpr int max_digit = 999999999;

class BigInt
{
public:
    BigInt();
    void TempPrint();
    BigInt(int input);
    BigInt(std::string str);
    ~BigInt();
    BigInt& operator=(const BigInt& other);
    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);
    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    BigInt& operator*=(const BigInt& other);
    BigInt& operator/=(const BigInt& other);
    BigInt& operator%=(const BigInt&other);
    BigInt& operator^=(const BigInt &other);
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    friend std::ostream& operator<<(std::ostream& os, const BigInt& Bg);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt operator+(const BigInt& a, const BigInt& b);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt operator/(const BigInt&, const BigInt&);
    friend BigInt operator^(const BigInt &a, const BigInt &b);
    void destroy_nulls();
    void shift_right();
    bool is_odd();
    friend std::pair<BigInt, BigInt> divmod(BigInt& a, BigInt &b);


private:
    uint32_t base;
    uint32_t max_digit;
    std::vector<uint64_t> num;
};




