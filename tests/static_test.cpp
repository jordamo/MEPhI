#include <xnum_static.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
using namespace xnum;
using namespace std;

TEST(GoogleTest, FirstTest)
{
  EXPECT_EQ(1,1);  
}

const int mSIZE = SIZE+SIZE/4;
TEST(StaticTest, BaseConstructorTest)
{
  HexNum a;
  ostringstream out, sss;
  out << a;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';
  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }
  
  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]);
}

TEST(StaticTest, NumConstructorTest)
{
  int av = 0xaa12bb;
  HexNum a(av);
  ostringstream out, sss;
  out << a;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';
  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }

  s[mSIZE-2] = 'B';
  s[mSIZE-3] = 'B';
  
  s[mSIZE-4] = '2';
  s[mSIZE-5] = '1';
  
  s[mSIZE-7] = 'A';
  s[mSIZE-8] = 'A';
  
  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(StaticTest, StrConstructorTest)
{
  const char *av = "cc12ff";
  HexNum a(av);
  ostringstream out, sss;
  out << a;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';
  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }

  s[mSIZE-2] = 'F';
  s[mSIZE-3] = 'F';
  
  s[mSIZE-4] = '2';
  s[mSIZE-5] = '1';
  
  s[mSIZE-7] = 'C';
  s[mSIZE-8] = 'C';
  
  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorSubTest, SubTest)
{
  const char *av = "cc12f0";
  int ag = 0x2;
  HexNum a(av), b(ag);
  ostringstream out, sss;
  out << a-b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';

  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }

  s[mSIZE-2] = 'E';
  s[mSIZE-3] = 'E';
  
  s[mSIZE-4] = '2';
  s[mSIZE-5] = '1';
  
  s[mSIZE-7] = 'C';
  s[mSIZE-8] = 'C';
  
  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorSubTest, PosToNegTest)
{
  const char *av = "cc12f0";
  int ag = 0xcc12f4;
  HexNum a(av), b(ag);
  ostringstream out, sss;
  out << a-b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';

  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }
  s[mSIZE-2] = '4';
  EXPECT_EQ(out_s[0],'-');
  for (int i=0; i < mSIZE-1; i++)
    EXPECT_EQ(out_s[i+1], s[i]); 
}

TEST(OperatorAddTest, PositiveAddTest)
{
  const char *av = "cc12ff";
  int ag = 0x2;
  HexNum a(av), b(ag);
  ostringstream out, sss;
  out << a+b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';

  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }

  s[mSIZE-2] = '1';
  s[mSIZE-3] = '0';
  
  s[mSIZE-4] = '3';
  s[mSIZE-5] = '1';
  
  s[mSIZE-7] = 'C';
  s[mSIZE-8] = 'C';
  
  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorAddTest, OverFlowTest)
{
  const char *av = "fff";
  int ag = 0xf1;
  HexNum a(av), b(ag);
  ostringstream out, sss;
  out << a+b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';

  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }

  s[mSIZE-2] = '0';
  s[mSIZE-3] = 'F';
  
  s[mSIZE-4] = '0';
  s[mSIZE-5] = '1';
  
  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorAddTest, ToZeroTest)
{
  const char *av = "fff";
  int ag = 0xfff;
  HexNum a(av), b(ag);
  ostringstream out, sss;
  out << a-b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';

  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }

  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorAddTest, ZeroTest)
{
  const char *av = "fff";
  HexNum a(av), b("0");
  ostringstream out, sss;
  out << a+b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';

  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }

  s[mSIZE-2] = 'F';
  s[mSIZE-3] = 'F';
  s[mSIZE-4] = 'F';  

  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorAddTest, MinusZeroTest)
{
  const char *av = "fff";
  HexNum a(av), b("0");
  ostringstream out, sss;
  out << a-b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';

  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }

  s[mSIZE-2] = 'F';
  s[mSIZE-3] = 'F';
  s[mSIZE-4] = 'F';  

  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorAddTest, MinusNumTest)
{
  const char *av = "fff";
  int ag = 0xfffF;
  HexNum a(av), b(ag);
  ostringstream out, sss;
  out << a-b;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';

  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }

  s[mSIZE-2] = '0';
  s[mSIZE-3] = '0';
  
  s[mSIZE-4] = '0';
  s[mSIZE-5] = 'F';
  EXPECT_EQ(out_s[0], '-');
  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i+1], s[i]); 
}

TEST(OperatorShiftTest, ShiftLeftTest)
{
  const char *av = "fAf";
  HexNum a(av);
  ostringstream out, sss;
  a <<= SIZE-2;
  out << a;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';
  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }

  s[0] = 'A';
  s[1] = 'F';
  
  for (int i=0; i < mSIZE; i++)
    EXPECT_EQ(out_s[i], s[i]); 
}

TEST(OperatorShiftTest, ShiftRightTest)
{
  const char *av = "fAf";
  HexNum a(av);
  ostringstream out, sss;
  a >>= 1;
  out << a;
  string out_string = out.str();
  const char *out_s = out_string.c_str();
  char s[mSIZE];
  s[mSIZE-1] = '\0';
  for (int i=0; i<mSIZE-1; i++)
  {
    if ((i+1) % 5 == 0 && i != 0)
      s[i] = ' ';
    else
      s[i] = '0';
  }

  s[mSIZE-2] = 'A';
  s[mSIZE-3] = 'F';
  
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