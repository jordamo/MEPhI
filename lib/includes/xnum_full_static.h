#include <iostream>
using namespace std;
namespace xnum_f
{
  #define SIZE 32
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
      unsigned short digits[SIZE];
      short sign;

    public:
      HexNum();
      HexNum(const int &n);
      HexNum(const char *sval);
      friend std::istream &input(std::istream &inp, HexNum &hn);
      friend std::ostream &print(std::ostream &out, const HexNum &hn);
      friend HexNum add(const HexNum &a, const HexNum &b);
      friend HexNum sub(const HexNum &a, const HexNum &b);
      HexNum &shift_l(const int &shift);
      HexNum &shift_r(const int &shift);
      friend bool eq(const HexNum &a, const HexNum &b);
      friend bool gt(const HexNum &a, const HexNum &b);
      friend bool lt(const HexNum &a, const HexNum &b);
      friend bool nl(const HexNum &a, const HexNum &b);
      friend bool ng(const HexNum &a, const HexNum &b);
      friend bool ne(const HexNum &a, const HexNum &b);
      bool is_odd() const;
      HexNum dop_code() const;
      HexNum &change_sign();
      static bool check_val(const char &s, int &index);
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