#include <iostream>
#include "prog.h"
using namespace std;
using namespace prog;

int main()
{
	int n, m;
	Raw **raws = input(n,m);
	if (raws == nullptr)
	{
		cout << "Incorrect input" << endl;
		return EXIT_FAILURE;
	}
	drawMat(raws, n, m);

	if (m > 2)
		updateMat(raws, n, m);

	drawMat(raws,n,m);

	dispose(raws, n);
	return EXIT_SUCCESS;
}
