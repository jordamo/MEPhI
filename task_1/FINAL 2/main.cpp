#include <iostream>
#include "prog.h"
using namespace std;
using namespace prog;

int main()
{
  Line *mat;
  int n, m;

  cout << "0 - input; 1 - advanced_input" << endl;
  int rc;
  if (getNum(rc))
  return EXIT_FAILURE;

  if (rc == 0)
  {
    if ((mat = input(n,m)) == nullptr)
    {
      return EXIT_FAILURE;
    }
  }
  else
  {
    if ((mat = advanced_input(n,m)) == nullptr)
    {
      return EXIT_FAILURE;
    }
  }

  draw(mat, n, m);
  update(mat, m);

  draw(mat, n, m);

  dispose(mat);
  cout << "Bye!" << endl;
  return EXIT_SUCCESS;
}
