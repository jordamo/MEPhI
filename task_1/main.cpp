#include <iostream>
#include "prog.h"
using namespace std;
using namespace prog;

int main()
{
  Line **mat;
  int n, m;

  if ((mat = input(n,m)) == nullptr)
  {
    return EXIT_FAILURE;
  }

  Line l;

  draw(mat, n,m);
  update(mat, n,m);

  draw(mat, n,m);

  dispose(mat,n);
  cout << "Bye!" << endl;
  return EXIT_SUCCESS;
}
