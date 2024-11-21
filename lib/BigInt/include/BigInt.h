#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>

inline int range = 9;
inline int max_digit = 999999999;

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
    BigInt operator+() const;
    BigInt operator-() const;
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    operator int() const;
    friend std::ostream& operator<<(std::ostream& os, const BigInt& Bg);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt operator+(const BigInt& a, const BigInt& b);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt operator/(const BigInt&, const BigInt&);
    size_t size() const;
    void destroy_nulls();
    void shift_right();
private:
    uint32_t base;
    uint32_t max_digit;
    std::vector<uint64_t> num;
};



