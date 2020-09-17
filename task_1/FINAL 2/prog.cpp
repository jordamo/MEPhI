#include <iostream>
#include "prog.h"
using namespace std;

namespace prog
{
#define ERMSG "INCORRECT INPUT. TRY AGAIN!"

  Item *create_new_item(int col, double d)
  {
    try
    {
      Item *tl = new Item(col, d, nullptr);
      return tl;
    }
    catch (bad_alloc &ba)
    {
      std::cout << "Too many Items in mat: " << ba.what() << std::endl;
      return nullptr;
    }
  }

  int add_item_in_raw(Line *line, Item *tl)
  // add item in right position in list
  {
    Item *ttmp=line->next, *tmp=line->next->next;

    while (tmp != nullptr)
    {
      if (tmp->col == tl->col) return 1;
      if (ttmp->col < tl->col && tl->col < tmp->col)
      {
        ttmp->next = tl;
        tl->next = tmp;
        return 0;
      }
      tmp = tmp->next;
      ttmp = ttmp->next;
    }
    ttmp->next = tl;
    return 0;
  }

  Line *find_or_create_Line(Line *line, int raw)
  // finds line of raw index, other wise creates and return new Line
  {
    try
    {
      if (line == nullptr)
      {
        return new Line(raw);
      }
      else if (line->raw > raw)
      {
        return new Line(raw, line);
      }
      else
      {
        Line *lptr = line->next_line, *lpptr = line;
        while (lptr != nullptr)
        {
          if (lpptr->raw == raw)
            return lpptr;
          else if (lpptr->raw < raw && raw < lptr->raw)
          {
            lpptr->next_line = new Line(raw, lptr);
            return lpptr->next_line;
          }

          lptr = lptr->next_line;
          lpptr = lpptr->next_line;
        }
        if (lpptr->raw == raw)
          return lpptr;
        lpptr->next_line = new Line(raw);
        return lpptr->next_line;
      }
    }
    catch (bad_alloc &ba)
    {
      cout << "Not enougth memory: " << ba.what() << endl;
      return nullptr;
    }
  }

  int input_base(int &tn, int &tm)
  // reads number of cols and raws of the matrix
  {
    int n,m;
    const char *ermsg = "";
    do
    {
      cout << ermsg << endl;
      cout << "Enter number of raws: ";
      ermsg = ERMSG;
      if (getNum(n))
        return 1;
    } while (n < 1);

    ermsg = "";
    do
    {
      cout << ermsg << endl;
      cout << "Enter number of cols: ";
      ermsg = ERMSG;
      if (getNum(m))
      {
        return 1;
      }
    } while (m < 1);
    tn = n; tm = m;
    return 0;
  }

  Line *advanced_input(int &tn, int &tm)
  /* read only non-zero items of a matrix */
  {
    int n, m;
    if (input_base(n, m))
      return nullptr;

    double d;
    int col, raw;
    bool finished = false;
    Line *line = nullptr, *lptr = nullptr;
    Item *tl;

    cout << "Input format: data raw col. Last number must be 0." << endl;
    while (!finished)
    {
      if (getNum(d) || getNum(raw) || getNum(col))
      {
        dispose(line);
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
        if ((tl = create_new_item(col, d)) == nullptr)
        {
          dispose(line);
          return nullptr;
        }

        if ((lptr = find_or_create_Line(line, raw)) == nullptr)
        {
          dispose(line);
          return nullptr;
        }

        if (line == nullptr || lptr->raw < line->raw)
          line = lptr;

        if (add_item_in_raw(lptr, tl))
        {
          dispose(line);
          return nullptr;
        }
      }
    }

    tn = n; tm = m;
    return line;
  }

  Line *input(int &tn, int &tm)
  /* reads all items of a matrix */
  {
    int n, m;
    if (input_base(n, m))
      return nullptr;

    Line *line = nullptr, *lptr = nullptr;
    Item *tl;
    const char *ermsg = "";

    double d;
    for (int i=0;i<n;i++)
    {
      cout << "Enter " << m << " numbers for raw #" << i+1 << ":" << endl;
      ermsg = "";

      lptr = find_or_create_Line(line, i);
      if (line == nullptr)
        line = lptr;

      for (int j=0;j<m;j++)
      {
        if (getNum(d))
        {
          dispose(line);
          return nullptr;
        }

        if (d != 0)
        {
          if ((tl = create_new_item(j, d)) == nullptr)
          {
            dispose(line);
            return nullptr;
          }

          if (add_item_in_raw(lptr, tl))
          {
            dispose(line);
            return nullptr;
          }
        }
      }
    }

    tn = n; tm = m;
    return line;
  }

  int draw(Line *l, int n, int m)
  {
    /* draw matrix on the screen */
    if (l == nullptr) return 1;
    Line *lptr = l;
    Item *iptr = nullptr;
    int k = 0;
    cout << "Drawing mat " << n << "x" << m << endl;

    for (int ni=0; ni<n; ni++)
    {
      if (lptr != nullptr && lptr->raw == ni)
      {
        iptr = lptr->next->next;
        k = 0;
        for (;k<m;k++)
        {
          if (iptr != nullptr && k == iptr->col)
          {
            std::cout << iptr->data << " ";
            iptr = iptr->next;
          }
          else
            std::cout << "0 ";
        }
        lptr = lptr->next_line;
      }
      else
      {
        k = 0;
        for (;k<m;k++)
          std::cout << "0 ";
      }
      std::cout << std::endl;
    }

    return 0;
  }

  int dispose(Line *ll)
  /* free memory */
  {
    if (ll == nullptr) return 1;
    Line *lptr = ll, *lpptr = nullptr;
    Item *iptr = nullptr, *ipptr = nullptr;

    do
    {
      lpptr = lptr;
      lptr = lptr->next_line;
      iptr = lpptr->next;

      do
      {
        ipptr = iptr;
        iptr = iptr->next;
        delete ipptr;
      } while (iptr != nullptr);

      delete lpptr;
    } while (lptr != nullptr);

    return 0;
  }

  int update(Line *l, int m)
  /* updates all lines in matrix */
  {
    Line *ptr = l;
    while (ptr != nullptr)
    {
      // std::cout << i << "| ";
      updateLine(ptr, m);
      ptr = ptr->next_line;
    }
    return 0;
  }

  int updateLine(Line *l, int m)
  /* updates a line */
  {
    Item *ptr = l->next->next, *pptr = l->next;
    Item *ll = nullptr, *fg=nullptr;
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

  int swap(Line *l, Item *fp, Item *lp, int fi, int li, int m)
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

  int swapLineItems(Item *fp, Item *lp)
  /* swaps line items that are in line */
  {
    if (fp->next == lp || lp->next == fp)
    {
      Item *tmp;
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
      Item *tmp, *tmp2;
      tmp = lp->next;
      tmp2 = fp->next->next;
      lp->next = fp->next;
      fp->next = tmp;
      lp->next->next = tmp->next;
      tmp->next = tmp2;
    }
    return 0;
  }

  int swapLineItems(Line *line, Item *p, int l, int m)
  /* swaps line item with zero*/
  {
    Item *pptr=line->next, *ptr=line->next->next, *sptr=nullptr;
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

    Item *tptr = p->next;
    tptr->col = l;
    if (tptr != sptr)
    {
      p->next = tptr->next;
      tptr->next = sptr->next;
      sptr->next = tptr;
    }
    return 0;
  }

  int sdraw(Line *l, int n, int m)
  /* draw matrix like a list */
  {
    std::cout << "sdraw " << n << "x" << m << ":" << std::endl;
    Line *lptr = l;
    Item *iptr = nullptr;

    while (lptr != nullptr)
    {
      iptr = lptr->next->next;
      while (iptr != nullptr)
      {
        std::cout << iptr->data << " " << lptr->raw << " " << iptr->col << "\t";
        iptr = iptr->next;
      }
      std::cout << std::endl;
      lptr = lptr->next_line;
    }
    return 0;
  }


  bool check_col(Item *l, Item *f)
  {
    if (l->col == f->col)
    {
      std::cout << "Redefined matrix's item" << std::endl;
      delete f;
      return true;
    }
    return false;
  }

}
