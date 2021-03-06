#include <iostream>
#include "prog.h"
using namespace std;

namespace prog
{
#define ERMSG "INCORRECT INPUT. TRY AGAIN!"


  Line **input(int &tn, int &tm)
  /* creates matrix via console */
  {
    int n,m;
    const char *ermsg = "";
    do
    {
      cout << ermsg << endl;
      cout << "Enter number of raws: ";
      ermsg = ERMSG;
      if (getNum(n))
        return nullptr;
    } while (n < 1);

    ermsg = "";

    Line **line;
    try
    {
      line = new Line*[n];
      for (int i=0; i<n;i++)
        line[i] = nullptr;
    }
    catch (bad_alloc &ba)
    {
      cout << "Too many raws in mat: " << ba.what() << endl;
    }

    do
    {
      cout << ermsg << endl;
      cout << "Enter number of cols: ";
      ermsg = ERMSG;
      if (getNum(m))
      {
        dispose(line, 0);
        return nullptr;
      }
    } while (m < 1);

    double d;
    Line *tl, **h;
    for (int i=0;i<n;i++)
    {
      cout << "Enter " << m << " numbers for raw #" << i+1 << ":" << endl;
      ermsg = "";
      h = &(line[i]);
      for (int j=0; j<m; j++)
      {
        if (getNum(d))
        {
          dispose(line, i);
          return nullptr;
        }
        if (d != 0)
        {
          tl = new Line(j,d,nullptr);
          if ((*h) == nullptr)
            *h = tl;
          else
            (*h)->next = tl;
          h = &((*h)->next);
        }
      }
    }

    tn = n; tm = m;
    return line;
  }

  int draw(Line **l, int n, int m)
  {
    /* draw matrix on the screen */
    Line *t;
    cout << "Drawing mat " << n << "x" << m << endl;
    for (int i=0;i<n;i++)
    {
      t = l[i];
      int k = 0;
      while (t != nullptr)
      {
        for (;k<t->col; k++)
        {
          cout << "0 ";
        }
        k++;
        cout << t->data << " ";
        t = t->next;
      }
      for (;k<m;k++)
        cout << "0 ";
      cout << endl;
    }
    return 0;
  }

  int dispose(Line **ll, int n)
  /* free memory */
  {
    for (int i=0;i<n;i++)
    {
      Line *t = ll[i], *tmp;
      while (t != nullptr)
      {
        tmp = t;
        t = t->next;
        delete tmp;
      }
    }

    delete [] ll;
    return 0;
  }

  int update(Line **l, int n, int m)
  /* updates all lines in matrix */
  {
    for (int i=0; i<n;i++)
    {
      if (l[i] != nullptr)
        updateLine(l[i], m);
    }
    return 0;
  }

  int updateLine(Line *l, int m)
  /* updates a line */
  {
    Line *ptr = l->next, *pptr = l;
    Line *ll = nullptr, *fg=nullptr;
    int fi = -1, li = -1;
    while (ptr != nullptr)
    {
      if (ptr->col - 1 == pptr->col)
      {
        if (fg == nullptr && ptr->data > pptr->data)
          fg = pptr;
        if (ptr->data < pptr->data)
          ll = pptr;
      }
      else
      {
        if (fi < 0 && pptr->data < 0)
          fi = pptr->col + 1;
        if (pptr->data > 0 && ptr->data > 0)
          li = pptr->col + 1;
      }

      if (ptr->col + 1 == m)
      {
        if (pptr->col + 1 != ptr->col)
        {
          if (ptr->data < 0)
            ll = pptr;
          else if (ptr->data > 0 && fg == nullptr)
            fg = pptr;
        }
      }

      pptr = pptr->next;
      ptr = ptr->next;
    }

    if (fi < 0 && pptr->data < 0 && pptr->col + 1< m)
      fi = pptr->col + 1;

    if (pptr->data > 0 && pptr->col + 1 < m)
      li = pptr->col + 1;


    if (ll != nullptr && ll->next->col < li && li >= 0) ll = nullptr;
    if (fg != nullptr && fg->next->col > fi && fi >= 0) fg = nullptr;

    swap(l, fg, ll, fi, li, m);

    return 0;
  }

  int swap(Line *l, Line *fp, Line *lp, int fi, int li, int m)
  /* swaps line items
     *l - Line start
     *fp - one line item root
     *lp - other line item root
     fi - one index
     li - other index
     m - number of cols in matrix*/
  {
    if (fp != nullptr && lp != nullptr)
    {
      // std::cout << "fp: " << fp->col << "; lp: " << lp->col << std::endl;
      swapLineItems(fp, lp);
    }
    else if (fp == nullptr && lp != nullptr && fi >= 0)
    {

      // std::cout << "fi: " << fi << "; lp: " << lp->col << std::endl;
      swapLineItems(l, lp, fi, m);
    }
    else if (fp != nullptr && lp == nullptr&& li >= 0)
    {

      // std::cout << "fp: " << fp->col << "; li: " << li << std::endl;
      swapLineItems(l, fp, li, m);
    }

    return 0;
  }

  int swapLineItems(Line *fp, Line *lp)
  /* swaps line items that are in line */
  {
    int t = fp->next->col; fp->next->col = lp->next->col; lp->next->col = t;
    Line *tmp, *tmp2;
    if (lp->next != fp && fp->next != lp)
    {
      tmp = lp->next;
      tmp2 = fp->next->next;
      lp->next = fp->next;
      fp->next = tmp;
      lp->next->next = tmp->next;
      tmp->next = tmp2;
    }
    else
    {
      if (lp->next != fp)
      {
        tmp = lp;
        lp = fp;
        fp = tmp;
      }
      tmp = fp->next->next;
      tmp2 = fp->next;
      fp->next->next = fp;
      fp->next = tmp;
      lp->next = tmp2;
    }
    return 0;
  }

  int swapLineItems(Line *line, Line *p, int l, int m)
  /* swaps line item with zero*/
  {
    Line *pptr=line, *ptr=line->next, *sptr=nullptr;
    while (ptr != nullptr)
    {
      if (pptr->col < l && l < ptr->col)
      {
        sptr = pptr;
        break;
      }

      ptr = ptr->next;
      pptr = pptr->next;
    }

    if (sptr == nullptr && pptr->col < l && l < m)
      sptr = pptr;


    Line *tptr = p->next;
    tptr->col = l;
    if (tptr != sptr)
    {
      p->next = tptr->next;
      tptr->next = sptr->next;
      sptr->next = tptr;
    }
    return 0;
  }

  int sdraw(Line **l, int n, int m)
  /* draw matrix like a list */
  {
    for (int i=0; i<n; i++)
    {
      Line *ptr = l[i];
      while (ptr != nullptr)
      {
        std::cout << "(" << ptr->col << ", " << ptr->data << "), ";
        ptr = ptr->next;
      }
      std::cout << std::endl;
    }
    return 0;
  }

}
