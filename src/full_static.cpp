#include <xnum_full_static.h>
#include <iostream>
using namespace std;
using namespace xnum_f;

int main()
{
  int rc;
  HexNum a;
  while (display_menu(),get_menu_command(rc))
  {
    if((dialog_menu[rc].func)(a))
    {
      cout << "Error ocured" << endl;
      break;
    }
    cout << endl;
  }

  cout << "Bye!" << endl;
  return 0;
}