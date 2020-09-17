
namespace prog
{

  struct Item
  {
    int col;
    double data;
    Item *next;

    Item() : col(-1), data(0), next(nullptr)
    {}

    Item(int col, double data, Item *next) : col(col), data(data), next(next)
    {}
  };

  struct Line{
    int raw;
    Item *next;
    Line *next_line;

    Line() : raw(0), next(nullptr), next_line(nullptr)
    {}

    Line(int raw, Line *next_line=nullptr) :
    raw(raw), next(new Item()), next_line(next_line) {}
  };

  template <class T>
  int getNum(T &a)
  {
    std::cin >> a;
    if (std::cin.good())
      return 0;
    return 1;
  }

  Item *create_new_item(int col, double d);
  int add_item_in_raw(Line *line, Item *tl);
  Line *find_or_create_Line(Line *line, int raw);
  int input_base(int &tn, int &tm);
  Line *advanced_input(int &tn, int &tm);
  Line *input(int &tn, int &tm);
  int draw(Line *l, int n, int m); ////
  int dispose(Line *ll); ////
  int update(Line *l, int m);
  int updateLine(Line *l, int m);

  int swap(Line *l, Item *fp, Item *lp, int fi, int li, int m);
  int swapLineItems(Item *fp, Item *lp);
  int swapLineItems(Line *line, Item *p, int l, int m);
  int sdraw(Line *l, int n, int m); 
  bool check_col(Item *l, Item *f);

}
