#include <iostream>
#include <string>
#include <xnum_dynamic.h>

namespace xnum_d
{
  HexNum::HexNum() : digits(nullptr), size(1), sign(0)
  /* BaseConstructor */
  {
    digits = zero_digits();
  }

  HexNum::HexNum(const int &num)
  /* Constructor via int */
  {
    if (num == 0)
    {
      size = 1;
      sign = 0;
      digits = zero_digits();
    }
    else
    {
      int dsz = num, count = 0;
      unsigned short *tmp_d;
      sign = 0;
      if (dsz < 0)
      {
        dsz = -dsz;
        sign = 1;
      }
      tmp_d = new unsigned short[2*(int)sizeof(dsz)];
      while (dsz > 0)
      {
        tmp_d[count++] = dsz % (fl+1);
        dsz /= (fl+1);
      }
      digits = new unsigned short[count];
      size = count;
      for (int i=0; i < count; i++)
        digits[count-i-1] = tmp_d[i];
      delete []tmp_d;
    }
  }

  HexNum::HexNum(const char *sval)
  /* Constructor via str */
  {
    sign = get_vals_string_sign(sval);
    size = get_vals_string_size(sval);
    digits = get_vals_string_digits(sval, size);
    if (!size || digits[0] == 0)
    {
      size = 1;
      sign = 0;
    }
  }

  HexNum::HexNum(const HexNum &a) : 
  digits(nullptr), size(a.size), sign(a.sign)
  /* Copy constructor */
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
  /* Destructor */
  {
    if (digits != nullptr)
      delete[] digits;
  }

  const HexNum &HexNum::operator=(const HexNum &a)
  /* Assignment operator */
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
  /* creates HexNum from istream */
  {
    char buf[256];
    inp >> buf;
    HexNum nhn(buf);
    hn = nhn;
    return inp;
  }

  std::ostream &operator<<(std::ostream &out, const HexNum &hn)
  /* puts HexNum to ostream */
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

  HexNum operator+(const HexNum &a, const HexNum &b)
  /* returns the sum of a and b */
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
    n_str[0] = '0'; n_str[1] = '0';
    int tmp, v, g, sg=0, psg=0;

    for (int i=0; i <= max_sz; i++)
    {
      add_case(v,g, aa, bb, i, max_sz, min_sz, sz, szm, mami);
      
      tmp = v + g;
      n_str[max_sz+1-i] = vals[(tmp+sg)%(fl+1)];

      psg = sg;
      sg = (tmp + sg) / (fl+1);
    }
    if ((sg + a.sign + b.sign) & 1)
      n_str[0] = '-';

    HexNum c(n_str);
    
    delete[] n_str;
    return c.dop_code();
  }

  HexNum operator-(const HexNum &a, const HexNum &b)
  /* returns the sum of a and -b */
  {
    HexNum c = b;
    return a + c.change_sign();
  }

  HexNum &HexNum::operator<<=(const int &shift)
  /* shifts a HexNum to the left by 'shift' number of hex digits */
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
  /* shifts a HexNum to the right by 'shift' number of hex digits */
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
  /* returns true if a == b, false otherwise */
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
  /* returns true if a > b, false otherwise */
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
  /* returns true if a < b, false otherwise */
  {
    return b > a;
  }

  bool operator>=(const HexNum &a, const HexNum &b)
  /* returns true if a >= b, false otherwise */
  {
    return !(a < b); 
  }

  bool operator<=(const HexNum &a, const HexNum &b)
  /* returns true if a <= b, false otherwise */
  {
    return !(a > b);
  }

  bool operator!=(const HexNum &a, const HexNum &b)
  /* returns true if a != b, false otherwise */
  {
    return !(a==b);
  }

  void swap(HexNum &a, HexNum &b)
  /* Swap HexNums */
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

  void add_case(int &v, int &g, const HexNum &aa, const HexNum &bb, const int &i, 
    const int &max_sz, const int &min_sz, const int &sz, const int &szm, const bool &mami)
  /* support function. Set numbers to calc */
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
  /* support function. Finds max and min sizes of HexNums */
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

  bool HexNum::is_odd() const
  /* returns true if a is odd, false otherwise */
  {
    return digits[size-1] & 1;
  }

  HexNum HexNum::dop_code() const
  /* returns twos-complement of HexNum */
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
      tmp = (fl + sg - digits[i-1]);
      sg = tmp / (fl + 1);
      n_str[i] = vals[tmp % (fl+1)];
    }
    HexNum ht(n_str);
    delete[] n_str;
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
      for (int i=0; i < size; i++)
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

  unsigned short *HexNum::get_vals_string_digits(const char *s, int size)
  /* support function. Generate digits array to the HexNum */
  {
    int sz = (int)strlen(s);
    int index;
    unsigned short *digits;
    char tmp;
    if (!size)
    {
      digits = HexNum::zero_digits();
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
        tmp = toupper(s[sz-i]);
        if (HexNum::check_val(tmp, index))
        {
          delete[] digits;
          digits = HexNum::zero_digits();
          return digits;
        }
        digits[size-i] = index;
      }
    }
    return digits;
  }

  unsigned short *HexNum::zero_digits()
  /* support function. Generates zero digits array to
    the HexNum
   */
  {
    unsigned short *digits = nullptr;
    try
    {
      digits = new unsigned short[1];
      digits[0] = 0;
    }
    catch(const std::bad_alloc& e)
    {
      std::cerr << e.what() << '\n';
    }
    return digits;
  }

  int HexNum::get_vals_string_size(const char *s)
  /* support function. Returns size of new digits array */
  {
    int size, sz = (int)strlen(s);
    int n = HexNum::get_vals_string_sign(s);
    size = HexNum::check_zeros(s+n, sz-n);
    return size;
  }

  short HexNum::get_vals_string_sign(const char *s)
  /* support function. Checks a sign of HexNum string */
  {
    return s[0] == '-';
  }


  int HexNum::check_zeros(const char *s, const int slen)
  /* support function. Checks the length of HexNum string
    without highest zeros and returns real string length
   */
  {
    for (int i=0; i<slen; i++)
    {
      if (s[i] != '0')
        return slen-i;
    }
    return 0;
  }

  int dialog_input(HexNum &a)
  /* dialog function. Inputs HexNum from console */
  {
    std::cout << "Enter a hex number: ";
    std::cin >> a;
    return 0;
  }

  int dialog_add(HexNum &a)
  /* dialog function. Inputs and adds HexNum to a */
  {
    HexNum b;
    std::cout << "Enter a hex number to add: ";
    std::cin >> b;
    std::cout << "a + b = " << a + b << std::endl;
    return 0;
  }

  int dialog_sub(HexNum &a)
  /* dialog function. Input and add -HexNum to a */
  {
    HexNum b;
    std::cout << "Enter a hex number to sub: ";
    std::cin >> b;
    std::cout << "a - b = " << a - b << std::endl;
    return 0;
  }

  int dialog_eq(HexNum &a)
  /* dialog function. Inputs HexNum and checks if it
    equals to a
   */
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    std::cin >> b;
    std::cout << "a == b is " << (a == b) << std::endl;
    return 0;
  }

  int dialog_ne(HexNum &a)
  /* dialog function. Inputs HexNum and checks if it
    not equals to a
   */
  {
    
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    std::cin >> b;
    std::cout << "a != b is " << (a != b) << std::endl;
    return 0;
  }

  int dialog_gt(HexNum &a)
  /* dialog function. Inputs HexNum and checks if it
    greater than  a
   */
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    std::cin >> b;
    std::cout << "a > b is " << (a > b) << std::endl;
    return 0;
  }

  int dialog_lt(HexNum &a)
  /* dialog function. Inputs HexNum and checks if it
    less than a
   */
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    std::cin >> b;
    std::cout << "a < b is " << (a < b) << std::endl;
    return 0;
  }

  int dialog_ng(HexNum &a)
  /* dialog function. Inputs HexNum and checks if it
    no greater than a
   */
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    std::cin >> b;
    std::cout << "a <= b is " << (a <= b) << std::endl;
    return 0;
  }

  int dialog_nl(HexNum &a)
  /* dialog function. Inputs HexNum and checks if it
    no less than a
   */
  {
    HexNum b;
    std::cout << "Enter a hex number to comp: ";
    std::cin >> b;
    std::cout << "a >= b is " << (a >= b) << std::endl;
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
    if (get_num(s, "Enter a number to shift --> "))
      return 1;
    a <<= s;
    return 0;
  }

  int dialog_shift_r(HexNum &a)
  /* dialog function. Shifts HexNum to the right */
  {
    int s;
    if (get_num(s, "Enter a number to shift --> "))
      return 1;
    a >>= s;
    return 0;
  }

  int dialog_show(HexNum &a)
  /* dialog function. Displays HexNum in console */
  {
    std::cout << a << std::endl;
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
};