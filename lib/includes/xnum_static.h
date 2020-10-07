#include <iostream>
using namespace std;
namespace xnum
{
  #define SIZE 32
  #define INFO "Enter a number --> "
  #define ERMSG "Incorrect input.\n"

  // the biggest hex digit
  const short fl = 0xF; 

  // decimal to hex number conversion array
  const char vals[16] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F'
  };

  class HexNum
  {
    private:
      unsigned short digits[SIZE];
      short sign;

    public:
    // constructors
      HexNum();
      HexNum(const int &n);
      HexNum(const char *sval);
    // iostream functions
      friend std::istream &operator>>(std::istream &inp, HexNum &hn);
      friend std::ostream &operator<<(std::ostream &out, const HexNum &hn);
    // arifmetics functions
      friend HexNum operator+(const HexNum &a, const HexNum &b);
      friend HexNum operator-(const HexNum &a, const HexNum &b);
    // shift functions
      HexNum &operator<<=(const int &shift);
      HexNum &operator>>=(const int &shift);
    // boolean functions
      friend bool operator==(const HexNum &a, const HexNum &b);
      friend bool operator>(const HexNum &a, const HexNum &b);
      friend bool operator<(const HexNum &a, const HexNum &b);
      friend bool operator>=(const HexNum &a, const HexNum &b);
      friend bool operator<=(const HexNum &a, const HexNum &b);
      friend bool operator!=(const HexNum &a, const HexNum &b);
      bool is_odd() const;
    // support functions
      HexNum dop_code() const;
      HexNum &change_sign();
      static bool check_val(const char &s, int &index);
  };
  
  // dialog functions
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