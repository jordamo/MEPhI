#include <iostream>
#include <string>
#include <xnum_full_static.h>

namespace xnum_f
{
  HexNum::HexNum()
  /* BaseConstructor */
  {
    for (int i=0; i < SIZE; i++)
      digits[i] = 0;
    sign = 0;
  }

  HexNum::HexNum(const int &n)
  /* Constructor via int */
  {
    int num = n;
    int sz = sizeof(num)*2;
    if (sz*4 > SIZE*4+1)
      throw std::exception("Too big number");

    sign = 0;
    if (num < 0)
    {
      sign = 1;
      num = -num;
    }
    for (int i=0; i < sz; i++)
    {
      digits[SIZE-i-1] = (num >> i*4) & fl;
    }
    for (int i=sz+1; i <= SIZE; i++)
      digits[SIZE-i] = 0;
  }

  HexNum::HexNum(const char *sval)
  /* Constructor via str */
  {
    int sz = (int)strlen(sval), n=0, index;
    char tmp;
    sign = 0;
    if (sz > SIZE+1)
      throw std::exception("Too big number");
    if (sval[0] == '-')
    {
      sign = 1;
      n=1;
    }
    
    if (sz-n == 1 && sval[n] == '0')
    {
      sign = 0; 
    }
    
    for (int i=1; i<=sz-n; i++)
    {
      tmp = toupper(sval[sz-i]);
      if (check_val(tmp, index))
        throw std::exception("Not a hex digit");
      digits[SIZE-i] = index;
    }
    for (int i=sz+1-n; i <= SIZE; i++)
      digits[SIZE-i] = 0;
    
  }

  std::istream &input(std::istream &inp, HexNum &hn)
  /* creates HexNum from istream */
  {
    char buf[SIZE+2];
    inp >> buf;
    HexNum nhn(buf);
    hn = nhn;
    return inp;
  }

  std::ostream &print(std::ostream &out, const HexNum &hn)
  /* puts HexNum to ostream */
  {
    if (hn.sign)
      out << '-';
    for (int i=0; i < SIZE; i++)
    {
      if ((i) % 4 == 0 && i != 0)
        out << " ";
      out << vals[hn.digits[i]];
    } 
    return out;
  }

  HexNum add(const HexNum &a, const HexNum &b)
  /* returns the sum of a and b */
  {
    HexNum aa = a.dop_code(), bb = b.dop_code();    
    int tmp, sg = 0;
    char n_str[SIZE+2];
    n_str[SIZE+1] = '\0';
    for (int i=SIZE-1; i >= 0; i--)
    {
      tmp = aa.digits[i] + bb.digits[i];
      n_str[i+1] = vals[(tmp+sg)&fl];
      sg = (tmp + sg) / (fl + 1);
    }
    sg = (sg + aa.sign + bb.sign) & 1;

    if ((aa.sign == bb.sign) && (sg != aa.sign))
      throw std::exception("OF");

    if (sg)
      n_str[0] = '-';
    HexNum c(n_str-sg+1);
    return c.dop_code();
  }

  HexNum sub(const HexNum &a, const HexNum &b)
  /* returns the sum of a and -b */
  {
    HexNum c = b;
    return add(a, c.change_sign());
  }

  HexNum &HexNum::shift_l(const int &shift)
  /* shifts a HexNum to the left by 'shift' number of hex digits */
  {
    if (shift < 0)
      throw std::exception("Negativ shift");
    int sh = std::min(shift, SIZE);
    for (int i=sh; i < SIZE; i++)
    {
      digits[i-sh] = digits[i];
    }
    for (int i=SIZE-1; i>SIZE-1-sh; i--)
    {
      digits[i] = 0;
    }
    return *this;
  }

  HexNum &HexNum::shift_r(const int &shift)
  /* shifts a HexNum to the right by 'shift' number of hex digits */
  {
    if (shift < 0)
      throw std::exception("Negativ shift");
    int sh = std::min(shift, SIZE);
    for (int i=SIZE-1; i >= sh; i--)
    {
      digits[i] = digits[i-sh];
    }
    for (int i=0; i < sh; i++)
      digits[i] = 0;
    return *this;
  }

  bool eq(const HexNum &a, const HexNum &b)
  /* returns true if a == b, false otherwise */
  {
    if (a.sign != b.sign)
      return false;
    for (int i=0; i < SIZE; i++)
    {
      if (a.digits[i] != b.digits[i])
        return false;
    }
    return true;
  }

  bool gt(const HexNum &a, const HexNum &b)
  /* returns true if a > b, false otherwise */
  {
    if (!a.sign && b.sign)
      return true;
    if (a.sign && !b.sign)
      return false;
    if (a.sign && b.sign)
    {
      for (int i=0; i < SIZE; i++)
      {
        if (a.digits[i] < b.digits[i])
          return true;
      }
      return false;
    }
    else
    {
      for (int i=0; i < SIZE; i++)
      {
        if (a.digits[i] > b.digits[i])
          return true;
      }
      return false;
    }
  }

  bool lt(const HexNum &a, const HexNum &b)
  /* returns true if a < b, false otherwise */
  {
    return gt(b, a);
  }

  bool nl(const HexNum &a, const HexNum &b)
  /* returns true if a >= b, false otherwise */
  {
    return !lt(a, b); 
  }

  bool ng(const HexNum &a, const HexNum &b)
  /* returns true if a <= b, false otherwise */
  {
    return !gt(a, b);
  }

  bool ne(const HexNum &a, const HexNum &b)
  /* returns true if a != b, false otherwise */
  {
    return !eq(a,b);
  }

  bool HexNum::is_odd() const
  /* returns true if a is odd, false otherwise */
  {
    return digits[SIZE-1] & 1;
  }

  HexNum HexNum::dop_code() const
  /* returns twos-complement of HexNum */
  {
    if (!sign)
      return *this;
    char n_str[SIZE+2];
    n_str[SIZE+1] = '\0';
    int tmp, sg = 1;
    *n_str = '-';
    for (int i=SIZE; i >= 1; i--)
    {
      tmp = (fl + sg - digits[i-1]);
      sg = tmp / (fl+1);
      n_str[i] = vals[tmp % (fl+1)];
    }
    HexNum ht(n_str);
    return ht;
  }

  HexNum &HexNum::change_sign()
  /* changes the sign of a HexNum and returns it */
  {
    if (this->sign)
    {
      this->sign = 0;
    }
    else
    {
      bool nz = false;
      for (int i=0; i < SIZE; i++)
        if (digits[i] != 0) nz = true;
      if (nz)
      {
        sign = 1; 
      }
    }
    return *this;
  }

  bool HexNum::check_val(const char &s, int &index)
  /* checks if char is in '0123456789ABCDEF' and
     returns index of char in '0123456789ABCDEF'
   */
  {
    for (int i=0; i<=fl; i++)
    {
      if (s == vals[i])
      {
        index = i;
        return false;
      }
    }
    index = -1;
    return true;
  }

  int dialog_input(HexNum &a)
  /* dialog function. Inputs HexNum from console */
  {
    std::cout << "Enter a hex number: ";
    input(std::cin, a);
    return 0;
  }

  int dialog_add(HexNum &a)
  /* dialog function. Inputs and adds HexNum to a */
  {
    HexNum b;
    std::cout << "Enter a hex number to add: ";
    input(std::cin, b);
    std::cout << "a + b = ";
    print(std::cout, add(a,b));
    std::cout << std::endl;
    return 0;
  }

  int dialog_sub(HexNum &a)
  /* dialog function. Input and add -HexNum to a */
  {
    HexNum b;
    std::cout << "Enter a hex number to sub: ";
    input(std::cin, b);
    std::cout << "a - b = ";
    print(std::cout, sub(a,b));
    std::cout << std::endl;
    return 0;
  }

  int dialog_eq(HexNum &a)
  /* dialog function. Inputs HexNum and checks if it
    equals to a
   */
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    input(std::cin, b);
    std::cout << "a == b is " << eq(a,b) << std::endl;
    return 0;
  }

  int dialog_ne(HexNum &a)
  /* dialog function. Inputs HexNum and checks if it
    not equals to a
   */
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    input(std::cin, b);
    std::cout << "a != b is " << ne(a,b) << std::endl;
    return 0;
  }

  int dialog_gt(HexNum &a)
  /* dialog function. Inputs HexNum and checks if it
    greater than  a
   */
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    input(std::cin, b);
    std::cout << "a > b is " << gt(a,b) << std::endl;
    return 0;
  }

  int dialog_lt(HexNum &a)
  /* dialog function. Inputs HexNum and checks if it
    less than a
   */
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    input(std::cin, b);
    std::cout << "a < b is " << lt(a,b) << std::endl;
    return 0;
  }

  int dialog_ng(HexNum &a)
  /* dialog function. Inputs HexNum and checks if it
    no greater than a
   */
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    input(std::cin, b);
    std::cout << "a <= b is " << ng(a,b) << std::endl;
    return 0;
  }

  int dialog_nl(HexNum &a)
  /* dialog function. Inputs HexNum and checks if it
    no less than a
   */
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    input(std::cin, b);
    std::cout << "a >= b is " << nl(a,b) << std::endl;
    return 0;
  }

  int dialog_odd(HexNum &a)
  /* dialog function. Checks if HexNum is odd */
  {
    std::cout << a.is_odd() << std::endl;
    return 0;
  }

  int dialog_shift_l(HexNum &a)
  /* dialog function. Shifts HexNum to the left */
  {
    int s;
    if (!get_command(s,SIZE, "Enter a number to shift --> "))
      return 1;
    a.shift_l(s);
    return 0;
  }

  int dialog_shift_r(HexNum &a)
  /* dialog function. Shifts HexNum to the right */
  {
    int s;
    if (!get_command(s,SIZE, "Enter a number to shift --> "))
      return 1;
    a.shift_r(s);
    return 0;
  }

  int dialog_show(HexNum &a)
  /* dialog function. Displays HexNum in console */
  {
    print(std::cout, a);
    return 0;
  }

  void display_menu()
  /* dialog function. Displays a list of commands */
  {
    for (unsigned int i=0; i<menu_size; i++)
    {
      std::cout << i << ". " << dialog_menu[i].info << std::endl;
    }
  }

}