namespace prog
{
	struct Raw
	{
		int col;
		double data;
		Raw *next;
	};

	template <class T>
	int getNum(T &a)
	{
		std::cin >> a;
		if (std::cin.good())
			return 0;
		return 1;
	}

	Raw **input(int &rn, int &rm);
	int drawRaw(Raw *a, int m);
	int drawMat(Raw **a, int n, int m);
	int dispose(Raw **r, int n);
	int updateRaw(Raw *a, int m);
	int updateMat(Raw **a, int n, int m);
	int swapRaws(Raw *a, int l, int r);

}
