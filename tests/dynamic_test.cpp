#include <xnum_dynamic.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
using namespace xnum_d;
using namespace std;

TEST(GoogleTest, FirstTest)
{
  EXPECT_EQ(1,1);  
}

TEST(StaticTest, CopyConstructorTest)
{
  int av = 0xaa12bb;
  HexNum *a = new HexNum(av);
  HexNum b = *a;
  ostringstream out, sss;
  out << *a;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  delete a;
  sss << b;
  string sss_string = sss.str();
  const char *sss_s = sss_string.c_str();
  for (int i=0; i < (int)strlen(sss_s); i++)
    EXPECT_EQ(sss_s[i], out_s[i]);
}

TEST(StaticTest, BaseConstructorTest)
{
  HexNum a;
  ostringstream out;
  out << a;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  int mSIZE = (int)strlen(out_s);
  const char *s = "0";
  
  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]);
}

TEST(StaticTest, NumConstructorTest)
{
  int av = 0xaa12bb;
  HexNum a(av);
  ostringstream out;
  out << a;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  int mSIZE = (int)strlen(out_s)+2;
  const char *s = "AA 12BB";
  
  for (int i=0; i < mSIZE-1; i++)
    EXPECT_EQ(out_s[i], s[i]);
}

TEST(StaticTest, StrConstructorTest)
{
  const char *av = "cc12ff";
  HexNum a(av);
  ostringstream out;
  out << a;
  string out_string = out.str();
  const char *out_s = out_string.c_str();

  int mSIZE = (int)strlen(out_s);
  const char *s = "CC 12FF";

  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorAssignTest, AssignTest)
{
  int av = 0xaa12bb;
  HexNum *a = new HexNum(av);
  HexNum b(12);
  b = *a;
  ostringstream out, sss;
  out << *a;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  delete a;
  sss << b;
  string sss_string = sss.str();
  const char *sss_s = sss_string.c_str();
  for (int i=0; i < (int)strlen(sss_s); i++)
    EXPECT_EQ(sss_s[i], out_s[i]);
}

TEST(OperatorSubTest, SubTest)
{
  const char *av = "cc12f0";
  int ag = 0x2;
  HexNum a(av), b(ag);
  ostringstream out;
  out << a-b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  int mSIZE = (int)strlen(out_s);
  const char *s = "CC 12EE";

  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorSubTest, PosToNegTest)
{
  const char *av = "cc12f0";
  int ag = 0xcc12f4;
  HexNum a(av), b(ag);
  ostringstream out;
  out << a-b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  int mSIZE = (int)strlen(out_s);
  const char *s = "4";

  EXPECT_EQ(out_s[0],'-');
  for (int i=0; i < mSIZE-1; i++)
    EXPECT_EQ(out_s[i+1], s[i]); 
}

TEST(OperatorAddTest, PositiveAddTest)
{
  const char *av = "cc12ff";
  int ag = 0x2;
  HexNum a(av), b(ag);
  ostringstream out;
  out << a+b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  int mSIZE = (int)strlen(out_s);
  const char *s = "CC 1301";

  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorAddTest, OverFlowTest)
{
  const char *av = "fff";
  int ag = 0xf1;
  HexNum a(av), b(ag);
  ostringstream out;
  out << a+b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  int mSIZE = (int)strlen(out_s);
  const char *s = "10F0";

  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorAddTest, ToZeroTest)
{
  const char *av = "fff";
  int ag = 0xfff;
  HexNum a(av), b(ag);
  ostringstream out;
  out << a-b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  int mSIZE = (int)strlen(out_s);
  const char *s = "0";

  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorAddTest, ZeroTest)
{
  const char *av = "fff";
  HexNum a(av), b("0");
  ostringstream out;
  out << a+b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  int mSIZE = (int)strlen(out_s);
  const char *s = "FFF";

  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorAddTest, MinusZeroTest)
{
  const char *av = "fff";
  HexNum a(av), b("0");
  ostringstream out;
  out << a-b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  int mSIZE = (int)strlen(out_s);
  const char *s = "FFF";

  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
  
}

TEST(OperatorAddTest, MinusNumTest)
{
  const char *av = "fff";
  int ag = 0xfffF;
  HexNum a(av), b(ag);
  ostringstream out;
  out << a-b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  int mSIZE = (int)strlen(out_s);
  const char *s = "F000";

  EXPECT_EQ(out_s[0], '-');
  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i+1], s[i]); 
  
}

TEST(OperatorShiftTest, ShiftLeftTest)
{
  const char *av = "fAf";
  HexNum a(av);
  ostringstream out;
  a <<= 1;
  out << a;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  int mSIZE = (int)strlen(out_s);
  const char *s = "FAF0";

  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
  
}

TEST(OperatorShiftTest, ShiftRightTest)
{
  const char *av = "fAf";
  HexNum a(av);
  ostringstream out;
  a >>= 1;
  out << a;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  int mSIZE = (int)strlen(out_s);
  const char *s = "FA";

  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
  
}

TEST(BoolOperatorsTest, EqTest)
{
  const char *av = "fAf", *cav = "fac", *nav = "-faf";
  HexNum a(av), b(av), c(cav), d(nav);
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);
  EXPECT_FALSE(d == c);
  EXPECT_FALSE(a == d);
  
}

TEST(BoolOperatorsTest, NeTest)
{
  const char *av = "fAf", *cav = "fac", *nav = "-faf";
  HexNum a(av), b(av), c(cav), d(nav);
  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
  EXPECT_TRUE(d != c);
  EXPECT_TRUE(a != d);
}

TEST(BoolOperatorsTest, GtTest)
{
  const char *av = "fAf", *cav = "fac", *nav = "-faf";
  HexNum a(av), b(av), c(cav), d(nav);
  EXPECT_FALSE(a > b);
  EXPECT_TRUE(a > c);
  EXPECT_FALSE(d > c);
  EXPECT_TRUE(a > d);
}

TEST(BoolOperatorsTest, LtTest)
{
  const char *av = "fAf", *cav = "fac", *nav = "-faf";
  HexNum a(av), b(av), c(cav), d(nav);
  EXPECT_FALSE(a < b);
  EXPECT_FALSE(a < c);
  EXPECT_TRUE(d < c);
  EXPECT_FALSE(a < d);
}

TEST(BoolOperatorsTest, NgTest)
{
  const char *av = "fAf", *cav = "fac", *nav = "-faf";
  HexNum a(av), b(av), c(cav), d(nav);
  EXPECT_TRUE(a <= b);
  EXPECT_FALSE(a <= c);
  EXPECT_TRUE(d <= c);
  EXPECT_FALSE(a <= d);
}

TEST(BoolOperatorsTest, NlTest)
{
  const char *av = "fAf", *cav = "fac", *nav = "-faf";
  HexNum a(av), b(av), c(cav), d(nav);
  EXPECT_TRUE(a >= b);
  EXPECT_TRUE(a >= c);
  EXPECT_FALSE(d >= c);
  EXPECT_TRUE(a >= d);
}

TEST(OddTest, OddTest)
{
  const char *av = "fAf", *cav = "fac", *nav = "-faf";
  HexNum a(av), c(cav), d(nav);
  EXPECT_TRUE(a.is_odd());
  EXPECT_FALSE(c.is_odd());
  EXPECT_TRUE(d.is_odd());
}


int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}