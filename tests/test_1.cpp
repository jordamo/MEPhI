#include <gtest/gtest.h>
#include <prog.h>
#include <string.h>
#include <cmath>
using namespace graphs;

TEST(BytLemniscatTest, ParamsTest)
{
  BytLemniscat line;
  long double c,m;
  line.change_params(10.0,12.0);
  line.get_params(c,m);
  EXPECT_EQ(c, 10.0);
  EXPECT_EQ(m, 12.0);

  line.change_params(0.0,0.0);
  line.get_params(c,m);
  EXPECT_EQ(c, 0.0);
  EXPECT_EQ(m, 0.0);

  line.change_params(-10.0,12.0);
  line.get_params(c,m);
  EXPECT_EQ(c, -10.0);
  EXPECT_EQ(m, 12.0);  
}

TEST(BytLemniscatTest, TypeTest)
{
  BytLemniscat line;
  line.change_params(10.0,12.0);
  EXPECT_EQ(line.get_type(), giperb);
  line.change_params(10.0,2);
  EXPECT_EQ(line.get_type(), elips);
  line.change_params(-1.0,-2.0);
  EXPECT_EQ(line.get_type(), giperb);
  line.change_params(-10010.0,12.0);
  EXPECT_EQ(line.get_type(), giperb);
}

TEST(BytLemniscatTest, ConstructorTest)
{
  long double c,m;
  Coords cd;
  BytLemniscat line1;
  line1.get_coords(cd);
  line1.get_params(c,m);
  EXPECT_EQ(c, 0);
  EXPECT_EQ(m, 0);
  EXPECT_EQ(cd.x, 0);
  EXPECT_EQ(cd.y, 0);
  
  BytLemniscat line2(1,3);
  line2.get_coords(cd);
  line2.get_params(c,m);
  EXPECT_EQ(c, 1);
  EXPECT_EQ(m, 3);
  EXPECT_EQ(cd.x, 0);
  EXPECT_EQ(cd.y, 0);
  
  BytLemniscat line5(-2,4.0, 6, 12);
  line5.get_coords(cd);
  line5.get_params(c,m);
  EXPECT_EQ(c, -2);
  EXPECT_EQ(m, 4.0);
  EXPECT_EQ(cd.x, 6);
  EXPECT_EQ(cd.y, 12);

  BytLemniscat line6((long double)-2.0, (long double)4.0, Coords(4,4));
  line6.get_coords(cd);
  line6.get_params(c,m);
  EXPECT_EQ(c, -2);
  EXPECT_EQ(m, 4.0);
  EXPECT_EQ(cd.x, 4);
  EXPECT_EQ(cd.y, 4);
}

TEST(BytLemniscatTest, CoordsTest)
{
  Coords cd;
  BytLemniscat line;
  line.get_coords(cd);
  EXPECT_EQ(cd.x, 0);
  EXPECT_EQ(cd.y, 0);

  line.change_coords(Coords(5,6));
  line.get_coords(cd);
  EXPECT_EQ(cd.x, 5);
  EXPECT_EQ(cd.y, 6);  
}

TEST(BytLemniscatTest, PolarKoefsTest)
{
  long double a,b;
  BytLemniscat line;
  line.get_polar_koefs(a,b);
  EXPECT_EQ(a, 0);
  EXPECT_EQ(b, 0);

  line.change_params(5,6);
  line.get_polar_koefs(a,b);
  EXPECT_EQ(a, 77);
  EXPECT_EQ(b, -67);
}

TEST(BytLemniscatTest, DistantToCenterTest)
{
  const long double eps = 1e-12;
  long double a,b,x,y, phi, r;
  Coords *cd, cd2;
  BytLemniscat line;

  cd2 = Coords(2,-2);
  line.change_params(10.0,12.0);
  line.change_coords(cd2);
  
  line.get_polar_koefs(a,b);
  for (int i=0; i<10;i++)
  {
    phi = i*PI/4;
    cd = line.distance_to_center(phi);
    r = sqrtl(a*cosl(phi)*cosl(phi) + b*sin(phi)*sin(phi));
    x = r*cosl(phi) + cd2.x;
    y = r*sinl(phi) + cd2.y;

    if (!isnan(cd[0].x))
      EXPECT_NEAR(cd[0].x, x, eps);
    
    if (!isnan(cd[0].y))
      EXPECT_NEAR(cd[0].y, y, eps);
    
    x = -r*cosl(phi) + cd2.x;
    y = -r*sinl(phi) + cd2.y;
    
    if (!isnan(cd[1].x))
      EXPECT_NEAR(cd[1].x, x, eps);
  
    if (!isnan(cd[1].y))
      EXPECT_NEAR(cd[1].y, y, eps);
    delete[] cd;
  }

  // cd2 = Coords(6,-3);
  // line.change_params(10.0,2.0);
  // line.change_coords(cd2);
  
  // line.get_polar_koefs(a,b);
  // for (int i=0; i<10;i++)
  // {
  //   phi = i*PI/4;
  //   cd = line.distance_to_center(phi);
  //   r = a*cosl(phi)*cosl(phi) + b*sin(phi)*sin(phi);
  //   x = r*cosl(phi) + cd2.x;
  //   y = r*sinl(phi) + cd2.y; 
  //   EXPECT_EQ(cd.x, x);
  //   EXPECT_EQ(cd.y, y);
  // } 
}

TEST(BytLemniscatTest, AreaTest)
{
  long double a,b,s;
  Coords cd;
  BytLemniscat line;

  line.change_params(10.0,12.0);
  line.change_coords(Coords(2,-2));
  
  line.get_polar_koefs(a,b);
  b *= -1;
  
  long double aa = sqrtl(a);
  long double bb = sqrtl(b);
  s = (a-b)/2*atanl(aa/bb) + aa*bb/2; 
  EXPECT_EQ(s, line.area());
  
  line.change_params(10.0,2.0);
  line.get_polar_koefs(a,b);
  s = PI/2*(a+b);
  EXPECT_EQ(s, line.area());
}

TEST(BytLemniscatTest, EquationTest)
{
  BytLemniscat line;
  long double a,b;
  const char *t;
  char tmp[200] = "p^2 = 0";
  line.change_params(0.0,0.0);
  t = line.get_equation();
  EXPECT_STRCASEEQ(t, tmp);
  delete t;
  
  line.change_params(-8,2);
  line.get_polar_koefs(a,b);
  sprintf_s(tmp, "p^2 = %.2f*sin^2(phi)", b);
  
  t = line.get_equation();
  EXPECT_STRCASEEQ(t, tmp);
  delete t;
  
  line.change_params(8,2.0);
  line.get_polar_koefs(a,b);
  sprintf_s(tmp, "p^2 = %.2f*cos^2(phi)", a);
  
  t = line.get_equation();
  EXPECT_STRCASEEQ(t, tmp);
  delete t;

  line.change_params(10.0,12.0);
  
  line.get_polar_koefs(a,b);
  sprintf_s(tmp, "p^2 = %.2f*cos^2(phi) %+.2f*sin^2(phi)", a, b);
  t = line.get_equation();
  EXPECT_STRCASEEQ(t, tmp);
  delete t;

}



int main(int argc, char *argv[])
{

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
