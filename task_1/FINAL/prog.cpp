#include <iostream>
#include "prog.h"
using namespace std;

namespace prog
{
#define ERMSG "INCORRECT INPUT. TRY AGAIN!"


  Line **advanced_input(int &tn, int &tm)
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


    Line **line = nullptr;
    try
    {
      line = new Line*[n];
      for (int i=0; i<n;i++)
        line[i] = new Line();
    }
    catch (bad_alloc &ba)
    {
      cout << "Too many raws in mat: " << ba.what() << endl;
    }


    ermsg = "";

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
    int col, raw;
    bool finished = false;
    Line *tl, *h, *tmp, *tmp2;

    cout << "Input format: data raw col. Last number must be 0." << endl;
    while (!finished)
    {
      ermsg = "";
      if (getNum(d) || getNum(raw) || getNum(col))
      {
        dispose(line, n);
        return nullptr;
      }

      if (col >= m || raw >= n || col < 0 || raw < 0)
      {
        std::cout << "Item's indexes don't mutch the size of the matrix" << std::endl;
      }
      else if (d == 0)
      {
        finished = true;
      }
      else
      {
        try
        {
          tl = new Line(col, d, nullptr);
        }
        catch (bad_alloc &ba)
        {
          cout << "Too many Items in mat: " << ba.what() << endl;
        }

        tmp = line[raw];
        tmp2 = tmp->next;
        while (tmp2 != nullptr)
        {
          if (tmp->col < tl->col && tmp2->col > tl->col)
          {
            tl->next = tmp2;
            break;
          }
          tmp = tmp->next;
          tmp2 = tmp2->next;
        }
          tmp->next = tl;
      }
    }

    tn = n; tm = m;
    return line;
  }

  bool check_col(Line *l, Line *f)
  {
    if (l->col == f->col)
    {
      std::cout << "Redefined matrix's item" << std::endl;
      delete f;
      return true;
    }
    return false;
  }

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
        line[i] = new Line();
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
        dispose(line, n);
        return nullptr;
      }
    } while (m < 1);

    double d;
    Line *tl, *h;
    for (int i=0;i<n;i++)
    {
      cout << "Enter " << m << " numbers for raw #" << i+1 << ":" << endl;
      ermsg = "";
      h = line[i];
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
          h->next = tl;
          h = h->next;
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
      t = l[i]->next;
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
      {
        // std::cout << i << "| ";
        updateLine(l[i], m);
      }
    }
    return 0;
  }

  int updateLine(Line *l, int m)
  /* updates a line */
  {
    Line *ptr = l->next, *pptr = l;
    Line *ll = nullptr, *fg=nullptr;
    int fi = -1, li = -1;
    if (ptr == nullptr)
      return 0;
    while (ptr != nullptr)
    {
      //fg case
      if (fg == nullptr && ptr->col > 0)
      {
        if (pptr->col < 0 || ptr->col - pptr->col > 1)
        {
          if (ptr->data > 0)
            fg = pptr;
        }
        else
        {
          if (ptr->col - pptr->col == 1 && ptr->data > pptr->data)
            fg = pptr;
        }
      }
      if (pptr->col >= 0 && fi < 0 &&
        pptr->data < 0 && ptr->col - pptr->col > 1)
        fi = pptr->col + 1;

      // ll case
      if (pptr->col < 0 && ptr->col > 0 && ptr->data < 0)
        ll = pptr;
      else
      {
        if (pptr->data > ptr->data && ptr->col - pptr->col == 1 && pptr->col >= 0)
          ll = pptr;
        if (pptr->col >= 0 && ptr->col - pptr->col > 1)
        {
          if (pptr->data > 0 && ptr->data > 0)
            li = pptr->col + 1;
          else if (ptr->data < 0)
            ll = pptr;
        }
      }

      ptr = ptr->next;
      pptr = pptr->next;
    }

    if (fg == nullptr && fi < 0 && pptr->col >= 0 && pptr->col + 1 < m && pptr->data < 0)
      fi = pptr->col + 1;
    if (pptr->col >= 0 && pptr->col + 1 < m && pptr->data > 0)
      li = pptr->col + 1;

    if (fg != nullptr && fi >= 0 && fg->next->col > fi) fg = nullptr;
    if (ll != nullptr && li >= 0 && ll->next->col < li) ll = nullptr;

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
    else if (fp != nullptr && lp == nullptr && li >= 0)
    {
      // std::cout << "fp: " << fp->col << "; li: " << li << std::endl;
      swapLineItems(l, fp, li, m);
    }
    else if (fp == nullptr && lp == nullptr)
    {
      // std::cout << "NOOB" << std::endl;
    }

    return 0;
  }

  int swapLineItems(Line *fp, Line *lp)
  /* swaps line items that are in line */
  {
    if (fp->next == lp || lp->next == fp)
    {
      Line *tmp;
      if (fp == lp->next)
      {
        tmp = lp; lp = fp; fp = tmp;
      }
      int t = lp->next->col; lp->next->col = lp->col; lp->col = t;
      tmp = lp->next->next;
      fp->next = lp->next;
      lp->next->next = lp;
      lp->next = tmp;
    }
    else
    {
      int t = fp->next->col; fp->next->col = lp->next->col; lp->next->col = t;
      Line *tmp, *tmp2;
      tmp = lp->next;
      tmp2 = fp->next->next;
      lp->next = fp->next;
      fp->next = tmp;
      lp->next->next = tmp->next;
      tmp->next = tmp2;
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
    std::cout << "sdraw" << std::endl;
    for (int i=0; i<n; i++)
    {
      Line *ptr = l[i];
      while (ptr != nullptr)
      {
        std::cout << ptr->data << " " << i << " "<< ptr->col << "\t";
        ptr = ptr->next;
      }
      std::cout << std::endl;
    }
    return 0;
  }

}
