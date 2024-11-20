#include "gtest/gtest.h"
#include "BigInt.h"
#include <sstream>
#include <iomanip>




TEST(BigIntIncrementDecrementTest, IncrementOperators)
{
    BigInt a("999");
    ++a;
    EXPECT_EQ(a, BigInt("1000"));

    BigInt b("0");
    ++b;
    EXPECT_EQ(b, BigInt("1"));
    BigInt f("99999999999999999999999999");
    ++f;
    EXPECT_EQ(f, BigInt("100000000000000000000000000"));
    BigInt q( BigInt("99999999999998999999999999"));
    ++q;
    EXPECT_EQ(q, BigInt("99999999999999000000000000"));


    BigInt c("999");
    BigInt d = c++;
    EXPECT_EQ(d, BigInt("999"));
    EXPECT_EQ(c, BigInt("1000"));


}




TEST(BigIntComprasionTest, Equal_PositiveCases)
{
    BigInt a("12345678901234567890");
    BigInt b("12345678901234567890");
    EXPECT_TRUE(a == b);

    BigInt c("37459375389795836895478450909029084237891");
    BigInt d("37459375389795836895478450909029084237891");
    EXPECT_TRUE(c == d);
}

TEST(BigIntComparisonTest, GreaterThanOrEqual_PositiveCases)
{
    BigInt a("12345678901234567890");
    BigInt b("12345678901234567890");
    EXPECT_TRUE(a >= b);

    BigInt c("12345678901234567891");
    EXPECT_TRUE(c >= a);

    BigInt d("12345678901234567889");
    EXPECT_TRUE(a >= d);
}

TEST(BigIntComparisonTest, GreaterThanOrEqual_NegativeCases)
{
    BigInt a("12345678901234567890");
    BigInt b("12345678901234567891");
    EXPECT_FALSE(a >= b);
}

TEST(BigIntComparisonTest, GreaterThanOrEqual_DifferentLengths)
{
    BigInt a("1000000000000000000000000000000");
    BigInt b("999999999999999999999");
    EXPECT_TRUE(a >= b);

    BigInt c("1000000000000000000000000000001");
    EXPECT_FALSE(a >= c);
}


TEST(BigIntComparisonTest, LessThanOrEqual_PositiveCases)
{
    BigInt a("12345678901234567890");
    BigInt b("12345678901234567890");

    EXPECT_TRUE(a <= b);

    BigInt c("12345678901234567891");
    EXPECT_FALSE(c <= a);

    BigInt d("12345678901234567889");
    EXPECT_FALSE(a <= d);
}

TEST(BigIntComparisonTest, LessThanOrEqual_NegativeCases)
{
    BigInt a("12345678901234567890");
    BigInt b("12345678901234567891");
    EXPECT_TRUE(a <= b);
}

TEST(BigIntComparisonTest, LessThanOrEqual_DifferentLengths)
{
    BigInt a("1000000000000000000000000000000");
    BigInt b("999999999999999999999");

    EXPECT_FALSE(a <= b);

    BigInt c("1000000000000000000000000000001");
    EXPECT_TRUE(a <= c);
}


TEST(BigIntArithmeticTest, SubtractionAssignment)
{
    BigInt a(BigInt("98765432109876543210"));
    BigInt b(BigInt("12345678901234567890"));
    a -= b;
    EXPECT_EQ(a, BigInt("86419753208641975320"));

    BigInt c("12345678901234567890");
    BigInt zero("0");
    c -= zero;
    EXPECT_EQ(c, BigInt("12345678901234567890"));
    BigInt t1(BigInt("1234567890123456789058344908538"));
    BigInt t2(BigInt("213558934897589348"));
    t1-=t2;
    EXPECT_EQ(t1, BigInt("1234567890123243230123447319190"));
    BigInt t3(BigInt("100000000000000000000000000000"));
    BigInt t4(BigInt("11111111111111111111111111111"));
    t3-=t4;
    EXPECT_EQ(t3, BigInt("88888888888888888888888888889"));
    BigInt t5(BigInt("100000000000000000000000000000"));
    BigInt t6(BigInt("11111111111111111111"));
    t5-=t6;
    EXPECT_EQ(t5, BigInt("99999999988888888888888888889"));
    BigInt t7(BigInt("100000000000000000000000000000000000"));
    BigInt t8(BigInt("1"));
    t7-=t8;
    EXPECT_EQ(t7, BigInt("99999999999999999999999999999999999"));
    BigInt e("1001");
    BigInt f("2");
    e -= f;
    EXPECT_EQ(e, BigInt("999"));

}

TEST(BigIntArithmeticTest, MulAssignment)
{
    BigInt a("945398903934904535674464654039391234576547");
    BigInt b("19999999995543111514457579745675432156789");
    BigInt c = a * b;
    EXPECT_EQ(c, BigInt("18907978074484553224297392352255492865472777944962742705205702301775133571326227583"));
    /*
    BigInt t1("1999999999");
    BigInt t2("1999999999");
    BigInt t3 = t1 * t2;
    EXPECT_EQ(t3, BigInt("3999999996000000001"));
    */
    BigInt t4("945398903934904535674464654039391234576547");
    BigInt t5("19999999995543111514457579745675432156789");
    BigInt t6 = t4 * t5;
    EXPECT_EQ(t6, BigInt("18907978074484553224297392352255492865472777944962742705205702301775133571326227583"));









}



TEST(BigIntIncrementDecrementTest, DecrementOperators) {
    BigInt a("1000");
    --a;
    EXPECT_EQ(a, BigInt("999"));

    BigInt b("1");
    --b;
    EXPECT_EQ(b, BigInt("0"));
    BigInt f = BigInt("9893543000000000000000");
    --f;
    EXPECT_EQ(f, BigInt("9893542999999999999999"));
}

/*
TEST(BigIntTest, AdditionAssignment)
{
    BigInt a("12345678901234567890");
    BigInt b("98765432109876543210");

    // Простое сложение
    a += b;
    EXPECT_EQ(a, BigInt("111111111011111111100"));

    // Сложение с нулем
    BigInt c("0");
    b += c;
    EXPECT_EQ(b, BigInt("98765432109876543210"));
    BigInt e("99999999999999999999");
    BigInt f("1");
    e += f;
    EXPECT_EQ(e, BigInt("100000000000000000000"));
}
*/

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}