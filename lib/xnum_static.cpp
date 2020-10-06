#include <iostream>
#include <string>
#include <xnum_static.h>

namespace xnum
{
  HexNum::HexNum()
  {
    for (int i=0; i < SIZE; i++)
      digits[i] = 0;
    sign = 0;
  }

  HexNum::HexNum(const int &num)
  {
    int sz = sizeof(num)*2;
    if (sz*4 > SIZE*4+1)
      throw std::exception("Too big number");

    sign = num < 0;
    for (int i=0; i < sz-1; i++)
    {
      digits[SIZE-i-1] = (num >> i*4) & fl;
    }
    digits[SIZE-sz] = (num >> (((sz-1)*4)-1)) & fl;
    for (int i=sz+1; i <= SIZE; i++)
      digits[SIZE-i] = 0;
  }

  HexNum::HexNum(const char *sval)
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

  std::istream &operator>>(std::istream &inp, HexNum &hn)
  {
    char buf[SIZE+2];
    inp >> buf;
    HexNum nhn(buf);
    hn = nhn;
    return inp;
  }

  std::ostream &operator<<(std::ostream &out, const HexNum &hn)
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

  HexNum operator+(const HexNum &a, const HexNum &b) //
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

  HexNum operator-(const HexNum &a, const HexNum &b)
  {
    HexNum c = b;
    return a + c.change_sign();
  }

  HexNum &HexNum::operator<<=(const int &shift)
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

  HexNum &HexNum::operator>>=(const int &shift)
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

  bool operator==(const HexNum &a, const HexNum &b)
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

  bool operator>(const HexNum &a, const HexNum &b)
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

  bool operator<(const HexNum &a, const HexNum &b)
  {
    return b > a;
  }

  bool operator>=(const HexNum &a, const HexNum &b)
  {
    return !(a < b); 
  }

  bool operator<=(const HexNum &a, const HexNum &b)
  {
    return !(a > b);
  }

  bool operator!=(const HexNum &a, const HexNum &b)
  {
    return !(a==b);
  }

  bool HexNum::is_odd() const
  {
    return digits[SIZE-1] & 1;
  }

  HexNum HexNum::dop_code() const
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
  {
    std::cout << "Enter a hex number: ";
    std::cin >> a;
    return 0;
  }

  int dialog_add(HexNum &a)
  {
    HexNum b;
    std::cout << "Enter a hex number to add: ";
    std::cin >> b;
    std::cout << "a + b = " << a + b << std::endl;
    return 0;
  }

  int dialog_sub(HexNum &a)
  {
    HexNum b;
    std::cout << "Enter a hex number to sub: ";
    std::cin >> b;
    std::cout << "a - b = " << a - b << std::endl;
    return 0;
  }

  int dialog_eq(HexNum &a)
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    std::cin >> b;
    std::cout << "a == b is " << (a == b) << std::endl;
    return 0;
  }

  int dialog_ne(HexNum &a)
  {
    
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    std::cin >> b;
    std::cout << "a != b is " << (a != b) << std::endl;
    return 0;
  }

  int dialog_gt(HexNum &a)
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    std::cin >> b;
    std::cout << "a > b is " << (a > b) << std::endl;
    return 0;
  }

  int dialog_lt(HexNum &a)
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    std::cin >> b;
    std::cout << "a < b is " << (a < b) << std::endl;
    return 0;
  }

  int dialog_ng(HexNum &a)
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    std::cin >> b;
    std::cout << "a <= b is " << (a <= b) << std::endl;
    return 0;
  }

  int dialog_nl(HexNum &a)
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    std::cin >> b;
    std::cout << "a >= b is " << (a >= b) << std::endl;
    return 0;
  }

  int dialog_odd(HexNum &a)
  {
    std::cout << a.is_odd() << std::endl;
    return 0;
  }

  int dialog_shift_l(HexNum &a)
  {
    int s;
    if (!get_command(s,SIZE, "Enter a number to shift --> "))
      return 1;
    a <<= s;
    return 0;
  }

  int dialog_shift_r(HexNum &a)
  {
    int s;
    if (!get_command(s,SIZE, "Enter a number to shift --> "))
      return 1;
    a >>= s;
    return 0;
  }

  int dialog_show(HexNum &a)
  {
    std::cout << a << std::endl;
    return 0;
  }

  void display_menu()
  {
    for (unsigned int i=0; i<menu_size; i++)
    {
      std::cout << i << ". " << dialog_menu[i].info << std::endl;
    }
  }

}