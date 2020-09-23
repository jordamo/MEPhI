#include <gtest/gtest.h>
#include <prog.h>
using namespace graphs;

TEST(FIRST_TEST, FIRST)
{
  BytLemniscat line;
  long double c,m;
  line.change_params(10.0,12.0);
  line.get_params(c,m);
  EXPECT_EQ(c, 10.0);
  EXPECT_EQ(m, 12.0);
}

int main(int argc, char *argv[])
{

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
