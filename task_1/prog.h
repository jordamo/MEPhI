
namespace prog
{

  struct Line
  {
    int col;
    double data;
    Line *next;

    Line() : col(0), data(-1), next(nullptr)
    {}

    Line(int col, double data, Line *next) : col(col), data(data), next(next)
    {}

  };

  template <class T>
  int getNum(T &a)
  {
    std::cin >> a;
    if (std::cin.good())
      return 0;
    return 1;
  }

  Line **input(int &tn, int &tm);
  int draw(Line **l, int n, int m);
  int dispose(Line **ll, int n);
  int update(Line **l, int n, int m);
  int updateLine(Line *l, int m);

  int swap(Line *l, Line *fp, Line *lp, int fi, int li, int m);
  int swapLineItems(Line *fp, Line *lp);
  int swapLineItems(Line *line, Line *p, int l, int m);
  int sdraw(Line **l, int n, int m);

}
