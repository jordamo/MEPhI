#include <iostream>
#include <string>
#include <xnum_dynamic.h>

namespace xnum_d
{
  HexNum::HexNum() : digits(nullptr), size(1), sign(0) 
  {
    unsigned short *arr;
    try
    {
      arr = new unsigned short[1];
      arr[0] = 0;
      digits = arr;
    }
    catch (const std::bad_alloc &e)
    {
      std::cerr << e.what() << std::endl;
      throw std::exception("Not enought memory");
    }
  }

  HexNum::HexNum(const int &num)
  {
    size = sizeof(num)*2;
    try
    {
      digits = new unsigned short[size];
    }
    catch(const std::bad_alloc &e)
    {
      std::cerr << e.what() << std::endl;
      throw std::exception("Not enought memory");
    }
    
    sign = num < 0;
    for (int i=0; i < size; i++)
    {
      digits[size-i-1] = (num >> i*4) & fl;
    }
  }

  HexNum::HexNum(const char *sval) //
  {
    int sz = (int)strlen(sval), n=0, index;
    char tmp;

    sign = 0;
    if (sval[0] == '-')
    {
      sign = 1;
      n=1;
    }
    size = check_zeros(sval+n, sz-n);
    if (!size)
    {
      size = 1;
      digits = new unsigned short[size];
      digits[0] = 0;
      sign = 0;
    }
    else
    {
      try
      {
        digits = new unsigned short[size];
      }
      catch(const std::bad_alloc &e)
      {
        std::cerr << e.what() << std::endl;
        throw std::exception("Not enought memory");
      }

      for (int i=1; i<=size; i++)
      {
        tmp = toupper(sval[sz-i]);
        if (check_val(tmp, index))
          throw std::exception("Not a hex digit");
        digits[size-i] = index;
      }
    }
  }

  HexNum::HexNum(const HexNum &a) : 
  digits(nullptr), size(a.size), sign(a.sign)
  {
    unsigned short *arr;
    try
    {
      arr = new unsigned short[size];
    }
    catch (const std::bad_alloc &e)
    {
      std::cerr << e.what() << std::endl;
      throw std::exception("Not enought memory");
    }
    for (int i=0; i < size; i++)
      arr[i] = a.digits[i];
    delete[] this->digits;
    this->digits = arr;
  }

  HexNum::~HexNum()
  {
    if (digits != nullptr)
      delete[] digits;
    // std::cout << "dest" << std::endl;
  }

  const HexNum &HexNum::operator=(const HexNum &a) //
  {
    delete[] this->digits;
    unsigned short *arr;
    try
    {
      arr = new unsigned short[a.size];
    }
    catch (const std::bad_alloc &e)
    {
      std::cerr << e.what() << std::endl;
      throw std::exception("Not enought memory");
    }
    for (int i=0; i < a.size; i++)
      arr[i] = a.digits[i];
    this->digits = arr;
    this->sign = a.sign;
    this->size = a.size;
    return *this;
  }

  std::istream &operator>>(std::istream &inp, HexNum &hn)
  {
    char buf[256];
    inp >> buf;
    HexNum nhn(buf);
    // std::cout << nhn;
    hn = nhn;
    return inp;
  }

  std::ostream &operator<<(std::ostream &out, const HexNum &hn)
  {
    if (hn.sign)
      out << '-';
    for (int i=0; i < hn.size; i++)
    {
      if ((hn.size-i) % 4 == 0 && i != 0)
        out << " ";
      out << vals[hn.digits[i]];
    } 
    return out;
  }

  void add_case(int &v, int &g, const HexNum &aa, const HexNum &bb, const int &i, 
  const int &max_sz, const int &min_sz, const int &sz, const int &szm, const bool &mami)
  { 
    g = (fl + !aa.sign) & fl;
    v = (fl + !bb.sign) & fl;
    if (i < sz)
      g = aa.digits[sz-1-i];
    else  
    {
      if (mami)
      {
        if (i >= sz && i < max_sz)
          g = 0;
      }
      else
      {
        if (i >= sz && i < min_sz)
          g = 0;  
      }
    }
    if (i < szm)
      v = bb.digits[szm-1-i];
    else 
    {
      if (mami)
      {
        if (i >= szm && i < min_sz)
        {
          v = 0;
        }
      }
      else
      {
        if (i >= szm && i < max_sz)
        {
          v = 0;
        }
      }
    }
  }

  bool max_min(const HexNum &a, const HexNum &b, HexNum &aa, HexNum &bb, 
  int &max_sz, int &min_sz, int &sz, int &szm)
  {
    bool sr = true;
    max_sz = a.size, min_sz = b.size;
    aa = a.dop_code();
    bb = b.dop_code();
    if (b.size > a.size)
    {
      max_sz = b.size;
      min_sz = a.size;
      sr = !sr;
    }
    sz = aa.size, szm = bb.size;
    if (bb.size > aa.size)
    {
      sr = !sr; 
      sz = bb.size;
      szm = aa.size;
      swap(aa,bb);
    }
    return sr;
    
  }

  HexNum operator+(const HexNum &a, const HexNum &b)
  {
    HexNum aa, bb;
    int max_sz, min_sz, sz, szm;
    bool mami = max_min(a, b, aa, bb, max_sz, min_sz, sz, szm);
    char *n_str;

    try
    {
      n_str = new char[max_sz+3];
    }
    catch (const std::bad_alloc &e)
    {
      std::cerr << e.what() << std::endl;
      throw std::exception("Not enought memory");
    }
    n_str[max_sz+2] = '\0';
    n_str[0] = '0';
    n_str[1] = '0';
    int tmp, v, g, sg=0, psg=0;
    std::cout << sz << "_" << szm << std::endl;
    std::cout << aa << std::endl << bb <<std::endl;
    std::cout << "msaz: " << max_sz << " min_sz" << min_sz << std::endl;
    std::cout << "s: " << n_str[max_sz+1] << std::endl;
    for (int i=0; i <= max_sz; i++)
    {
      add_case(v,g, aa, bb, i, max_sz, min_sz, sz, szm, mami);
      
      tmp = v + g;
      std::cout << v << " " << g << " " << (tmp+sg)%(fl+1) << std::endl;
      n_str[max_sz+1-i] = vals[(tmp+sg)%(fl+1)];

      psg = sg;
      sg = (tmp + sg) / (fl+1);
    }
    if ((sg + a.sign + b.sign) & 1)
      n_str[0] = '-';
    std::cout << n_str << " " << strlen(n_str) << std::endl;

    HexNum c(n_str);
    
    delete[] n_str;
    return c.dop_code();
    
  }

  HexNum operator-(const HexNum &a, const HexNum &b)
  {
    HexNum c = b;
    return a + c.change_sign();
  }

  HexNum &HexNum::operator<<=(const int &shift)
  {
    if (shift <= 0)
      throw std::exception("Negativ shift");
    unsigned short *arr;
    if (this->size >= 1 && this->digits[0] == 0)
      return *this;
    try
    {
      arr = new unsigned short[size+shift];
    }
    catch (const std::bad_alloc &e)
    {
      std::cerr << e.what() << std::endl;
      throw std::exception("Not enought memory");
    }
    
    for (int i=0; i < size; i++)
    {
      arr[i] = digits[i];
    }
    for (int i=size; i<size+shift; i++)
    {
      arr[i] = 0;
    }

    delete[] digits;
    digits = arr;
    size = size + shift;
    return *this;
  }

  HexNum &HexNum::operator>>=(const int &shift)
  {
    if (shift <= 0)
      throw std::exception("Negativ shift");
    unsigned short *arr;
    if (shift >= size)
    {
      delete[] digits;
      size = 1;
      
      try
      {
        arr = new unsigned short[1];
      }
      catch (const std::bad_alloc &e)
      {
        std::cerr << e.what() << std::endl;
        throw std::exception("Not enought memory");
      }
      *arr = 0;
    }
    else
    {
      try
      {
        arr = new unsigned short[size-shift];
      }
      catch (const std::bad_alloc &e)
      {
        std::cerr << e.what() << std::endl;
        throw std::exception("Not enought memory");
      }

      for (int i=0; i < size-shift; i++)
      {
        arr[i] = digits[i];
      }

      delete[] digits;
      digits = arr;
      size = size - shift;
    }
    return *this;
  }

  bool operator==(const HexNum &a, const HexNum &b)
  {
    if (a.sign != b.sign || a.size != b.size)
      return false;
    for (int i=0; i < a.size; i++)
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
    if (a.size == b.size)
    {
      if (a.sign && b.sign)
      {
        for (int i=0; i < a.size; i++)
        {
          if (a.digits[i] < b.digits[i])
            return true;
        }
        return false;
      }
      else
      {
        for (int i=0; i < a.size; i++)
        {
          if (a.digits[i] > b.digits[i])
            return true;
        }
        return false;
      }
    }
    else
    {
      if (a.size > b.size)
      {
        if (a.sign)
          return false;
        return true;
      }
      else
      {
        if (a.sign)
          return true;
        return false;
      }
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

  void swap(HexNum &a, HexNum &b)
  {
    int t = a.size, s = a.sign;
    unsigned short *p = a.digits;
    a.size = b.size;
    a.sign = b.sign;
    a.digits = b.digits;
    b.size = t;
    b.sign = s;
    b.digits = p;
  }

  bool HexNum::is_odd() const
  {
    return digits[size-1] & 1;
  }

  HexNum HexNum::dop_code() const
  {
    if (!sign)
      return *this;
    char *n_str;
    try
    {
      n_str = new char[size+2];
    }
    catch (const std::bad_alloc &e)
    {
      std::cerr << e.what() << std::endl;
      throw std::exception("Not enought memory");
    }

    n_str[size+1] = '\0';
    *n_str = '-';
    int tmp, sg = 1;
    
    for (int i=size; i >= 1; i--)
    {
      tmp = (fl + sg - digits[i-1]) % (fl+1);
      sg = 0;
      n_str[i] = vals[tmp];
    }
    HexNum ht(n_str);
    delete[] n_str;
    return ht;
  }

  HexNum &HexNum::change_sign()
  {
    this->sign = (this->sign + 1) & 1;
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

  int HexNum::check_zeros(const char *s, const int slen)
  {
    for (int i=0; i<slen; i++)
    {
      if (s[i] != '0')
        return slen-i;
    }
    return 0;
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
    if (get_num(s, "Enter a number to shift --> "))
      return 1;
    a <<= s;
    return 0;
  }

  int dialog_shift_r(HexNum &a)
  {
    int s;
    if (get_num(s, "Enter a number to shift --> "))
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
};