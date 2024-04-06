#define FORWARD_ITERATION  1
#define BACWARD_ITERATION 0


typedef struct s_ListIterator ListIterator;
typedef struct _List List;
typedef struct _Maillon Maillon;
struct s_ListIterator ;


List  *list();
List *push_back(List *l, int v);
bool list_empty (const List *l);
List *pop_front(List *l);
int print_i(int i);

ListIterator *listIterator_create(List *collection, int direction);

Maillon *goto_next(Maillon *e);

Maillon *goto_previous(Maillon *e);