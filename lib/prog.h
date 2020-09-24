#include <iostream>
using namespace std;

namespace graphs
{
  #define INFO "Enter a number --> "
  #define ERMSG "Incorrect input.\n"
  #define N 200
  #define MAX_LONG_DOUBLE 1e060
  #define PI 3.14159265358979323846
  

  enum LemType {elips, giperb};
  
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

  struct Coords
  {
    long double x;
    long double y;

    Coords(long double x, long double y) : x(x), y(y) {}
    Coords() : x(0), y(0) {}

    // friend ostream &operator<<(ostream &os, Coords &cd);
    void print_coords();
  };

  class BytLemniscat
  {
    private:
      long double c;
      long double m;
      long double aa;
      long double bb;
      Coords cords;
      LemType type;

      void update_type();
      void update_koefs();
      void update_type_koefs();
      long double calc_elips_area() const;
      long double calc_giperb_area() const;

    public:
      BytLemniscat() : c(0), m(0), cords(Coords()) {update_type_koefs();}
      BytLemniscat(long double const cc, long double const mm, long double x=0, long double y=0);
      // BytLemniscat(long double const cc, long double const mm);
      BytLemniscat(long double const c, long double const m, Coords const cords);
      ~BytLemniscat() {};

      int change_params(long double const c, long double const m);
      int get_params(long double &cc, long double &mm) const;
      int get_coords(Coords &coords) const;
      int change_coords(Coords const coords);
      int get_polar_koefs(long double &a, long double &b) const;
      long double world_distance() const;
      Coords *distance_to_center(long double const phi) const;
      char *get_equation() const;
      char *get_abs_equation() const;
      LemType get_type() const;
      long double area() const;
      long double get_ksi() const;
  };

  bool is_zero(long double a);
  int dialog_chage_params(BytLemniscat &line);
  int dialog_get_params(BytLemniscat &line);
  int dialog_get_coords(BytLemniscat &line);
  int dialog_change_coords(BytLemniscat &line);
  int dialog_get_polar_koefs(BytLemniscat &line);
  int dialog_distance_to_center(BytLemniscat &line);
  int dialog_get_equation(BytLemniscat &line);
  int dialog_get_type(BytLemniscat &line);
  int dialog_area(BytLemniscat &line);
  int dialog_get_abs_equation(BytLemniscat &line);


  struct DialogFunc
  {
    int (*func) (BytLemniscat &line);
    const char *info;
  };

  DialogFunc dialog_menu[]  = {
    {dialog_chage_params, "Change parameters"},
    {dialog_change_coords, "Change coordinates"},
    {dialog_get_type, "Get type"},
    {dialog_get_params, "Get parameters"},
    {dialog_get_coords, "Get coordinates"},
    {dialog_get_polar_koefs, "Get polar koefs"},
    {dialog_distance_to_center, "Get distance to center"},
    {dialog_get_equation, "Get equation"},
    {dialog_area, "Get area"},
    {dialog_get_abs_equation, "Get Abs Equation"},
  };

  void display_menu();

  int menu_size = sizeof(dialog_menu)/sizeof(DialogFunc);
  
  bool get_command(int &a)
  {
    const char *err = "";
    int n = 0;
    do
    {
      n=0;
      cout << err;
      err = ERMSG;
      if (get_num(n, "Enter command --> "))
      {
        return false;
      }
    } while (n < 0 || n >= menu_size);
    a = n;
    return true;
  }
  

};