#include <iostream>
using namespace std;

namespace xnum_d
{
  #define INFO "Enter a number --> "
  #define ERMSG "Incorrect input.\n"

  const short fl = 0xF; 

  const char vals[16] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F'
  };

  class HexNum
  {
    private:
      unsigned short *digits;
      int size;
      short sign;

    public:
      HexNum();
      HexNum(const int &num);
      HexNum(const char *sval);
      HexNum(const HexNum &a);
      ~HexNum();
      const HexNum &operator=(const HexNum &a);
      friend std::istream &operator>>(std::istream &inp, HexNum &hn);
      friend std::ostream &operator<<(std::ostream &out, const HexNum &hn);
      friend HexNum operator+(const HexNum &a, const HexNum &b);
      friend HexNum operator-(const HexNum &a, const HexNum &b);
      HexNum &operator<<=(const int &shift);
      HexNum &operator>>=(const int &shift);
      friend bool operator==(const HexNum &a, const HexNum &b);
      friend bool operator>(const HexNum &a, const HexNum &b);
      friend bool operator<(const HexNum &a, const HexNum &b);
      friend bool operator>=(const HexNum &a, const HexNum &b);
      friend bool operator<=(const HexNum &a, const HexNum &b);
      friend bool operator!=(const HexNum &a, const HexNum &b);
      friend void swap(HexNum &a, HexNum &b);
      friend void add_case(int &v, int &g, const HexNum &aa, const HexNum &bb, 
        const int &i, const int &max_sz, const int &min_sz, const int &sz, const int &szm, const bool &mami);
      friend bool max_min(const HexNum &a, const HexNum &b, HexNum &aa, HexNum &bb, int &max_sz, int &min_sz, int &sz, int &szm);
      bool is_odd() const;
      HexNum dop_code() const;
      HexNum &change_sign();

      static bool check_val(const char &s, int &index);
      static unsigned short *get_vals_string_digits(const char *s, int size);
      static unsigned short *zero_digits();
      static int get_vals_string_size(const char *s);
      static short get_vals_string_sign(const char *s);
      static int check_zeros(const char *s, const int slen);
  };

  int dialog_input(HexNum &);
  int dialog_add(HexNum &);
  int dialog_sub(HexNum &);
  int dialog_eq(HexNum &);
  int dialog_ne(HexNum &);
  int dialog_gt(HexNum &);
  int dialog_lt(HexNum &);
  int dialog_ng(HexNum &);
  int dialog_nl(HexNum &);
  
  int dialog_odd(HexNum &);
  int dialog_shift_l(HexNum &);
  int dialog_shift_r(HexNum &);

  int dialog_show(HexNum &);

  void display_menu();

  struct DialogFunc
  {
    int (*func) (HexNum &);
    const char *info;
  };

  DialogFunc dialog_menu[] = {
    {dialog_input, "Input num"},
    {dialog_show, "Show num"},
    {dialog_add, "Add"},
    {dialog_sub, "Sub"},
    {dialog_eq, "=="},
    {dialog_ne, "!="},
    {dialog_gt, ">"},
    {dialog_lt, "<"},
    {dialog_ng, "<="},
    {dialog_nl, ">="},
    {dialog_odd, "Is odd?"},
    {dialog_shift_l, "Shift left"},
    {dialog_shift_r, "Shift right"},
  };

  unsigned int menu_size = sizeof(dialog_menu)/sizeof(DialogFunc);

  template <class T>
  int get_num(T &a, const char *info=INFO, const char *ermsg=ERMSG)
  {
    cout << info;
    
    while (!(cin >> a))
    {
      if (cin.eof())
        return 1;
      cout << ermsg;
      cout << info;
      cin.clear();
      cin.ignore(10000, '\n');
    }
    
    return 0;
  }

  bool get_command(int &a,const int size, const char *inf="Enter command --> ")
  {
    const char *err = "";
    int n = 0;
    do
    {
      n=0;
      std::cout << err;
      err = ERMSG;
      if (get_num(n, inf))
      {
        return false;
      }
    } while (n < 0 || n >= size);
    a = n;
    return true;
  }

  bool get_menu_command(int &a)
  {
    return get_command(a, menu_size);
  }

};