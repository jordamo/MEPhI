#include <iostream>
#include "prog.h"

namespace prog
{

	Raw **input(int &rn, int &rm)
	{
		double d;
		int n,m;
		Raw **raw;
		const char *erm = "";

		do {
			std::cout << erm << std::endl;
			std::cout << "Enter number of raws: ";
			erm = "Incorrect input";
			if (getNum(n))
				return nullptr;
		} while(n < 1);

		erm = "";

		try
		{
			raw = new Raw*[n];
			for (int k=0; k<n; k++)
				raw[k] = nullptr;
		}
		catch (std::bad_alloc &ba)
		{
			std::cout << "Too many raws in matrix: " << ba.what() << std::endl;
			return nullptr;
		}

		do
		{
			std::cout << erm << std::endl;
			std::cout << "Enter number of cols: ";
			erm = "Incorrect input";
			if (getNum(m))
			{
				dispose(raw, 0);
				return nullptr;
			}
		} while (m < 1);


		Raw *tr, **h;
		for (int i=0; i<n; i++)
		{
			std::cout << "Enter " << m << " numbers for raw #" << i+1 << std::endl;
			h = &raw[i];
			for (int j=0; j<m; j++)
			{
				if (getNum(d))
				{
					dispose(raw,i);
					return nullptr;
				}
				if (d != 0)
				{
					try
					{
						tr = new Raw;
						tr->col = j;
						tr->data = d;
						tr->next = nullptr;
						if (*h == nullptr)
							(*h) = tr;
						else
							(*h)->next = tr;
						h = &(*h)->next;
					}
					catch (std::bad_alloc &ba)
					{
						std::cout << "Too many items in raw: " << ba.what() << std::endl;
						dispose(raw, i);
						return nullptr;
					}
				}
			}
		}
		rn = n;
		rm = m;
		return raw;
	}

	int drawRaw(Raw *a, int m)
	{
		Raw *tpr = a;
		int l = 0;
		while (tpr != nullptr)
		{
			for (; l<tpr->col; l++)
			{
				std::cout << "0 ";
			}
			l++;
			std::cout << tpr->data << " ";
			tpr = tpr->next;
		}
		for (; l<m;l++)
		{
			std::cout << "0 ";
		}
		return 0;
	}

	int drawMat(Raw **a, int n, int m)
	{
		std::cout << "Drawing matrix " << n << "x" << m << std::endl;
		for (int i=0; i<n; i++)
		{
			drawRaw(a[i], m);
			std::cout << std::endl;
		}
		return 0;
	}

	int dispose(Raw **r, int n)
	{
		Raw *ptr, *tmp;
		for (int i=0; i<n; i++)
		{
			ptr = r[i];
			while (ptr != nullptr)
			{
				tmp = ptr;
				ptr = ptr->next;
				delete tmp;
			}
		}
		delete [] r;
		return 0;
	}

	int updateRaw(Raw *a, int m)
	{
		Raw *ptr = a->next, *prev = a;
		int fg =-1, ll = -1;

		if (prev->col > 0 && prev->data > 0) fg = prev->col;

		while (ptr != nullptr)
		{
			if (ptr->col-1 == prev->col)
			{
				if (fg < 0 && ptr->data > prev->data)
					fg = prev->col;
				else if (ptr->data < prev->data)
					ll = prev->col;
			}
			else
			{
				if (fg < 0)
				{
					if (prev->data < 0)
						fg = prev->col +1;
					else if (ptr->data > 0)
						fg = ptr->col;
				}
				else if (ll < 0)
				{
					if (prev->data > 0 && ptr->data > 0)
						ll = prev->col + 1;
					else if (ptr->data < 0)
						ll = ptr->col;
				}
			}

			prev = prev->next;
			ptr = ptr->next;
		}

		if (prev->col < m-1 && prev->data > 0) ll = prev->col + 1;

		if (fg >-1 && ll > -1)
			swapRaws(a, fg, ll);
		return 0;
	}

	int updateMat(Raw **a, int n, int m)
	{
		for (int i=0; i<n; i++)
		{
			updateRaw(a[i], m);
		}
		return 0;
	}

	int swapRaws(Raw *a, int l, int r)
	{
		Raw *c = a->next, *cp = a;
		Raw *ll = nullptr, *rr = nullptr;
		while (c->next != nullptr)
		{
			if (c->next->col == l)
				ll = c;
			else if (c->next->col == r)
				rr = c;
			if (c->next->col > l && cp->next->col < l)
			{
				if (c->next->data > 0 && cp->next->data>0)
					ll = cp;
			}
			if (c->next->col > r && cp->next->col < r)
			{
				if (cp->next->data < 0)
					rr = cp;
			}

			c = c->next;
			cp = cp->next;
		}

		if (ll == nullptr) ll = cp;
		if (rr == nullptr) rr = cp;

		ll->col = r;
		rr->col = l;

		Raw *tmp, *tmp2;
		tmp = ll->next;
		tmp2 = rr->next->next;
		ll->next = rr->next;
		rr->next = tmp;
		ll->next->next = tmp->next;
		tmp->next = tmp2;

		return 0;
	}

}
