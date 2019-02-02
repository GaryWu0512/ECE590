#include "fraction.h"
#include "imaginary.h"
#include "gtest/gtest.h"

TEST(HW1_GRADING, ReduceBasic1)
{
Fraction a = (Fraction) {2, 4};
EXPECT_EQ(reduce(a).num, 1);
EXPECT_EQ(reduce(a).den, 2);
SUCCEED();
}

TEST(HW1_GRADING, ReduceBasic2)
{
Fraction a = (Fraction) {3, 39};
EXPECT_EQ(reduce(a).num, 1);
EXPECT_EQ(reduce(a).den, 13);
}

TEST(HW1_GRADING, ReduceBasic3)
{
Fraction a = (Fraction) {3, 13};
EXPECT_EQ(reduce(a).num, 3);
EXPECT_EQ(reduce(a).den, 13);
}

TEST(HW1_GRADING, ReduceBasic4)
{
Fraction a = (Fraction) {4, 34};
EXPECT_EQ(reduce(a).num, 2);
EXPECT_EQ(reduce(a).den, 17);
}

TEST(HW1_GRADING, ReduceBasic5)
{
Fraction a = (Fraction) {306, 867};
EXPECT_EQ(reduce(a).num, 6);
EXPECT_EQ(reduce(a).den, 17);
}

TEST(HW1_GRADING, ReduceImproper1)
{
Fraction a = (Fraction) {817, 731};
EXPECT_EQ(reduce(a).num, 19);
EXPECT_EQ(reduce(a).den, 17);
}

TEST(HW1_GRADING, ReduceImproper2)
{
Fraction a = (Fraction) {2537, 645};
EXPECT_EQ(reduce(a).num, 59);
EXPECT_EQ(reduce(a).den, 15);
}

TEST(HW1_GRADING, ReduceImproper3)
{
Fraction a = (Fraction) {561, 528};
EXPECT_EQ(reduce(a).num, 17);
EXPECT_EQ(reduce(a).den, 16);
}

TEST(HW1_GRADING, ReduceImproper4)
{
Fraction a = (Fraction) {5874, 495};
EXPECT_EQ(reduce(a).num, 178);
EXPECT_EQ(reduce(a).den, 15);
}

TEST(HW1_GRADING, ReduceImproper5)
{
Fraction a = (Fraction) {2838, 693};
EXPECT_EQ(reduce(a).num, 86);
EXPECT_EQ(reduce(a).den, 21);
}

TEST(HW1_GRADING, ReduceNegative1)
{
Fraction a = reduce((Fraction) { 2, -4 });
EXPECT_TRUE((a.num == 1 && a.den == -2) || (a.num == -1 && a.den == 2));
}

TEST(HW1_GRADING, ReduceNegative2)
{
Fraction a = reduce((Fraction) { -2, 4 });
EXPECT_TRUE((a.num == 1 && a.den == -2) || (a.num == -1 && a.den == 2));
}

TEST(HW1_GRADING, ReduceNegative3)
{
Fraction a = reduce((Fraction) { -10, -15 });
EXPECT_TRUE((a.num == 2 && a.den == 3));
}

TEST(HW1_GRADING, ReduceNegative4)
{
Fraction a = reduce((Fraction) {-190, 330});
EXPECT_TRUE((a.num == 19 && a.den == -33) || (a.num == -19 && a.den == 33));
}

TEST(HW1_GRADING, ReduceNegative5)
{
Fraction a = reduce((Fraction) {140, -12});
EXPECT_TRUE((a.num == 35 && a.den == -3) || (a.num == -35 && a.den == 3));
}

TEST(HW1_GRADING, ReduceZero1)
{
Fraction a = (Fraction) { 0, 4 };
ASSERT_NO_THROW(reduce(a));
EXPECT_EQ(reduce(a).num, 0);
EXPECT_EQ(reduce(a).den, 1);
}

TEST(HW1_GRADING, ReduceZero2)
{
Fraction a = (Fraction) { 0, -6 };
ASSERT_NO_THROW(reduce(a));
EXPECT_EQ(reduce(a).num, 0);
EXPECT_EQ(reduce(a).den, 1);
}

TEST(HW1_GRADING, ReduceZero3)
{
Fraction a = (Fraction) { 3, 0 };
ASSERT_NO_THROW(reduce(a));
EXPECT_EQ(reduce(a).num, 1);
EXPECT_EQ(reduce(a).den, 0);
}

TEST(HW1_GRADING, ReduceZero4)
{
Fraction a = (Fraction) { -15, 0 };
ASSERT_NO_THROW(reduce(a));
EXPECT_EQ(reduce(a).num, 1);
EXPECT_EQ(reduce(a).den, 0);
}

TEST(HW1_GRADING, ReduceZero5) {
Fraction a = (Fraction) { 0, 0 };
ASSERT_NO_THROW(reduce(a));
EXPECT_EQ(reduce(a).num, 0);
EXPECT_EQ(reduce(a).den, 0);
}

TEST(HW1_GRADING, ImaginaryAdd1)
{
Imaginary a = (Imaginary) { 4, 3 },
        b = (Imaginary) { 7, 3 };

EXPECT_EQ(add(a, b).real,11);
EXPECT_EQ(add(a, b).im,6);
EXPECT_EQ(add(b, a).real,11);
EXPECT_EQ(add(b, a).im,6);
}

TEST(HW1_GRADING, ImaginaryAdd2)
{
Imaginary a = (Imaginary) { -1, 41 },
        b = (Imaginary) { 44, 39 };

EXPECT_EQ(add(a, b).real,43);
EXPECT_EQ(add(a, b).im,80);
EXPECT_EQ(add(b, a).real,43);
EXPECT_EQ(add(b, a).im,80);
}

TEST(HW1_GRADING, ImaginaryAdd3)
{
Imaginary a = (Imaginary) { 45, 61 },
        b = (Imaginary) { -2, 6 };

EXPECT_EQ(add(a, b).real,43);
EXPECT_EQ(add(a, b).im,67);
EXPECT_EQ(add(b, a).real,43);
EXPECT_EQ(add(b, a).im,67);
}

TEST(HW1_GRADING, ImaginaryAdd4)
{
Imaginary a = (Imaginary) { 78, -27 },
        b = (Imaginary) { -73, -31 };

EXPECT_EQ(add(a, b).real,5);
EXPECT_EQ(add(a, b).im,-58);
EXPECT_EQ(add(b, a).real,5);
EXPECT_EQ(add(b, a).im,-58);
}

TEST(HW1_GRADING, ImaginaryAdd5)
{
Imaginary a = (Imaginary) { 85, 43 },
        b = (Imaginary) { 70, 87 };

EXPECT_EQ(add(a, b).real,155);
EXPECT_EQ(add(a, b).im,130);
EXPECT_EQ(add(b, a).real,155);
EXPECT_EQ(add(b, a).im,130);
}

TEST(HW1_GRADING, ImaginaryMult1)
{
Imaginary a = (Imaginary) { 1, 10 },
        b = (Imaginary) { 2, 3 };

EXPECT_EQ(multiply(a, b).real,-28);
EXPECT_EQ(multiply(a, b).im,23);
EXPECT_EQ(multiply(b, a).real,-28);
EXPECT_EQ(multiply(b, a).im,23);
}

TEST(HW1_GRADING, ImaginaryMult2)
{
Imaginary a = (Imaginary) { -90, 96 },
        b = (Imaginary) { 41, 48 };

EXPECT_EQ(multiply(a, b).real,-8298);
EXPECT_EQ(multiply(a, b).im,-384);
EXPECT_EQ(multiply(b, a).real,-8298);
EXPECT_EQ(multiply(b, a).im,-384);
}

TEST(HW1_GRADING, ImaginaryMult3)
{
Imaginary a = (Imaginary) { 82, 37 },
        b = (Imaginary) { -64, 39 };

EXPECT_EQ(multiply(a, b).real,-6691);
EXPECT_EQ(multiply(a, b).im,830);
EXPECT_EQ(multiply(b, a).real,-6691);
EXPECT_EQ(multiply(b, a).im,830);
}

TEST(HW1_GRADING, ImaginaryMult4)
{
Imaginary a = (Imaginary) { 93, -2 },
        b = (Imaginary) { -64, -44 };

EXPECT_EQ(multiply(a, b).real,-6040);
EXPECT_EQ(multiply(a, b).im,-3964);
EXPECT_EQ(multiply(b, a).real,-6040);
EXPECT_EQ(multiply(b, a).im,-3964);
}

TEST(HW1_GRADING, ImaginaryMult5)
{
Imaginary a = (Imaginary) { 39, 60 },
        b = (Imaginary) { 94, 79 };

EXPECT_EQ(multiply(a, b).real,-1074);
EXPECT_EQ(multiply(a, b).im,8721);
EXPECT_EQ(multiply(b, a).real,-1074);
EXPECT_EQ(multiply(b, a).im,8721);
}

TEST(HW1_GRADING, ImaginaryNegate1)
{
Imaginary a = (Imaginary) { 8, 4 };

EXPECT_EQ(negate(a).real,-8);
EXPECT_EQ(negate(a).im,-4);
}

TEST(HW1_GRADING, ImaginaryNegate2)
{
Imaginary a = (Imaginary) { -97, 97 };

EXPECT_EQ(negate(a).real,97);
EXPECT_EQ(negate(a).im,-97);
}

TEST(HW1_GRADING, ImaginaryNegate3)
{
Imaginary a = (Imaginary) { 0, 83 };

EXPECT_EQ(negate(a).real,0);
EXPECT_EQ(negate(a).im,-83);
}

TEST(HW1_GRADING, ImaginaryNegate4)
{
Imaginary a = (Imaginary) { 35, -43 };

EXPECT_EQ(negate(a).real,-35);
EXPECT_EQ(negate(a).im,43);
}

TEST(HW1_GRADING, ImaginaryNegate5)
{
Imaginary a = (Imaginary) { -19, -68 };

EXPECT_EQ(negate(a).real,19);
EXPECT_EQ(negate(a).im,68);
}

TEST(HW1_GRADING, ImaginaryConjugate1)
{
Imaginary a = (Imaginary) { 2, 7 };

EXPECT_EQ(conjugate(a).real,2);
EXPECT_EQ(conjugate(a).im,-7);
}

TEST(HW1_GRADING, ImaginaryConjugate2)
{
Imaginary a = (Imaginary) { -90, 67 };

EXPECT_EQ(conjugate(a).real,-90);
EXPECT_EQ(conjugate(a).im,-67);
}

TEST(HW1_GRADING, ImaginaryConjugate3)
{
Imaginary a = (Imaginary) { 1, 11 };

EXPECT_EQ(conjugate(a).real,1);
EXPECT_EQ(conjugate(a).im,-11);
}

TEST(HW1_GRADING, ImaginaryConjugate4)
{
Imaginary a = (Imaginary) { 51, -74 };

EXPECT_EQ(conjugate(a).real,51);
EXPECT_EQ(conjugate(a).im,74);
}

TEST(HW1_GRADING, ImaginaryConjugate5)
{
Imaginary a = (Imaginary) { -72, -100 };

EXPECT_EQ(conjugate(a).real,-72);
EXPECT_EQ(conjugate(a).im,100);
}

TEST(HW1_GRADING, ImaginaryMag1)
{
Imaginary a = (Imaginary) { 7, 1 };
EXPECT_NEAR(magnitude(a), 7.07106781, 0.0001);
}

TEST(HW1_GRADING, ImaginaryMag2)
{
Imaginary a = (Imaginary) { -64, 89 };

EXPECT_NEAR(magnitude(a), 109.62207807, 0.0001);
}

TEST(HW1_GRADING, ImaginaryMag3)
{
Imaginary a = (Imaginary) { 0, 89 };

EXPECT_NEAR(magnitude(a), 89.00000000, 0.0001);
}

TEST(HW1_GRADING, ImaginaryMag4)
{
Imaginary a = (Imaginary) { 97, -47 };

EXPECT_NEAR(magnitude(a), 107.78682665, 0.0001);
}

TEST(HW1_GRADING, ImaginaryMag5)
{
Imaginary a = (Imaginary) { -58, -51 };

EXPECT_NEAR(magnitude(a), 77.23341246, 0.0001);
}
