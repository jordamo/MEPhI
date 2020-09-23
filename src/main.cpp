#include <iostream>
#include <prog.h>
using namespace std;
using namespace graphs;

int main()
{
  BytLemniscat line;
  int rc;
  while (display_menu(),get_command(rc))
  {
    if((dialog_menu[rc].func)(line))
    {
      cout << "Error ocured" << endl;
      break;
    }
    cout << endl;
  }

  cout << "Bye!" << endl;
  return 0;
}
