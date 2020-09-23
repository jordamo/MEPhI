#include "prog.h"
#include <cmath>
#include <iostream>
#include <string.h>
#include <stdio.h>

namespace graphs
{
  
  BytLemniscat::BytLemniscat(long double cc, long double mm, long double x, long double y)
  {
    this->c = cc; 
    this->m = mm; 
    this->cords = Coords(x,y);
    update_type_koefs();
  }
  BytLemniscat::BytLemniscat(long double cc, long double mm)
  {
    this->c = cc;
    this->m = mm;
    this->cords = Coords(0,0);
    update_type_koefs();
  }
  BytLemniscat::BytLemniscat(long double c, long double m, Coords coords) 
  {
    this->c = c; 
    this->m = m;
    this->cords = coords;
    update_type_koefs();
  }
      
  
  ostream &operator<<(ostream &os, Coords &cd)
    {
      return os << "(" << cd.x << ", " << cd.y << ")";
    }

  void BytLemniscat::update_type()
  {
    if (c>2*m*m)
      type = elips;
    else
      type = giperb;
  }

  void BytLemniscat::update_koefs()
  {
    aa = 2*m*m+c;
    if (c > 2*m*m)
      bb = c - 2*m*m;
    else
      bb = 2*m*m - c;
    if (is_zero(aa)) aa = 0.0;
    if (is_zero(bb)) bb = 0.0;
  }

  void BytLemniscat::update_type_koefs()
  {
    update_koefs();
    update_type();
  }

  long double BytLemniscat::calc_elips_area()
  {
    long double S = PI*(aa+bb)/2;
    return S;
  }

  long double BytLemniscat::calc_giperb_area()
  {
    long double a = sqrtl(aa);
    long double b = sqrtl(bb);
    long double S = (aa-bb)/2*atanl(a/b) + a*b/2; 
    return S;
  }

  int BytLemniscat::change_params(long double cc, long double mm)
  {
    this->c = cc;
    this->m = mm;
    update_type_koefs();
    return 0;
  }

  int BytLemniscat::get_params(long double &cc, long double &mm)
  {
    cc = c;
    mm = m;
    return 0;
  }

  int BytLemniscat::get_coords(Coords &coords)
  {
    coords = cords;
    return 0;
  }

  int BytLemniscat::change_coords(Coords coords)
  {
    cords = coords;
    return 0;
  }

  int BytLemniscat::get_polar_koefs(long double &a, long double &b)
  {
    a = is_zero(aa) ? 0 : aa;
    b = is_zero(bb) ? 0 : bb;
    if (type == giperb)
      b *= -1;
    
    return 0;
  }

  long double BytLemniscat::world_distance()
  {
    return cords.x*cords.x + cords.y*cords.y;
  }

  Coords BytLemniscat::distance_to_center(long double phi)
  {
    long double b = bb;
    if (type == giperb)
      b *= -1;
    long double p = sqrtl(aa*powl(cosl(phi), 2) + b*powl(sinl(phi), 2));

    return Coords(p*cosl(phi)+cords.x, p*sinl(phi)+cords.y);
  }

  char *BytLemniscat::get_equation()
  {
    long double a, b;
    get_polar_koefs(a,b);
    int l;
    char buf[200];

    if (is_zero(a) && is_zero(b))
    {
      l = sprintf_s(buf, "p^2 = 0");
    }
    else if (is_zero(a))
    {
      l = sprintf_s(buf, "p^2 = %.2f*cos^2(phi)", b);
    }
    else if (is_zero(b))
    {
      l = sprintf_s(buf, "p^2 = %.2f*sin^2(phi)", a);
    }
    else
    {
      l = sprintf_s(buf, "p^2 = %.2f*cos^2(phi) %+.2f*sin^2(phi)", a, b);
    }
    buf[++l] = '\0';
    char *end = new char[l];
    end[0] = '\0';
    strcat_s(end, l, buf);
    
    return end;
  }

  LemType BytLemniscat::get_type()
  {
    return type;
  }

  long double BytLemniscat::area()
  {
    if (type == elips)
      return calc_elips_area();
    return calc_giperb_area();
  }

  int dialog_chage_params(BytLemniscat &line)
  {
    std::cout << "Enter c and m:" << std::endl;
    long double c,m;
    if (get_num(c, "Enter c --> "))
      return 1;
    if (get_num(m, "Enter m --> "))
      return 1;
    line.change_params(c,m);
    return 0;
  }

  int dialog_get_params(BytLemniscat &line)
  {
    long double c,m;
    line.get_params(c,m);
    std::cout << "c: " << c << "; m: "<< m << std::endl;
    return 0;
  }

  int dialog_get_coords(BytLemniscat &line)
  {
    Coords cd;
    line.get_coords(cd);
    std::cout << "coords: " << cd << std::endl;
    return 0;
  }

  int dialog_change_coords(BytLemniscat &line)
  {
    long double x,y;
    get_num(x,"Enter x coord --> ");
    get_num(y,"Enter y coord --> ");
    
    Coords cd(x,y);
    line.change_coords(cd);
    return 0;
  }

  int dialog_get_polar_koefs(BytLemniscat &line)
  {
    long double a,b;
    line.get_polar_koefs(a,b);
    std::cout << "a*a = " << a << "; b*b = " << b << std::endl;
    return 0;
  }

  int dialog_distance_to_center(BytLemniscat &line)
  {
    long double phi;
    get_num(phi,"Enter phi angle --> ");
    Coords cd = line.distance_to_center(phi);
    std::cout << "Distant to polar center is: " << cd << std::endl;
    return 0;
  }

  int dialog_get_equation(BytLemniscat &line)
  {
    char *t = line.get_equation();
    std::cout << "Equation: " << t << std::endl;
    delete t;
    return 0;
  }

  int dialog_get_type(BytLemniscat &line)
  {
    std::cout << "Line type: ";
    if (line.get_type() == elips)
      std::cout << "elips" << std::endl;
    else 
      std::cout << "giperb" << std::endl;
    return 0;
  }

  int dialog_area(BytLemniscat &line)
  {
    std::cout << "Area: " << line.area() << std::endl;
    return 0;
  }
  
  void display_menu()
  {
    for (int i=0; i<menu_size; i++)
    {
      std::cout << i << ". " << dialog_menu[i].info << std::endl;
    }
  }

  bool is_zero(long double a)
  {
    return fabsl(a) < DBL_EPSILON || fabsl(a) > MAX_LONG_DOUBLE;
  }

};