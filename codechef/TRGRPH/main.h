#define MIN_SIZE 5;
#define OK 0;
#define ARG_ERR 1;

typedef unsigned int uint;

typedef struct Graph {
  uint n;    // Number of vertices
  uint m;    // Number of edges
  uint *N;   // length of each array in E as log_2(c); length n
  uint **E;  // Array of lists containing neighbours; length n
  uint **P;  // Array of pointers to the next free element in E
} Graph;

typedef struct UIntStack {
  uint *data;
  uint *next;
  uint *end;
} UIntStack;

typedef struct SetStack {
  char **data;
  char **next;
  char **end;
} SetStack;

struct {
  uint Q;
  Graph **Gs;
} config;

// Instructions
int parse_config();
int print_tree(Graph *G);
uint clusters(Graph *g, char *subset, char **clusters);
uint find_root(Graph *g, char *subset);

int comp(const void *e1, const void *e2);

// Graph methods
int check_graph(Graph *G);
int check_node(Graph *G, uint a);
int are_connected(Graph *G, uint a, uint b);
int fit(Graph *G, uint a);
int finalise_graph(Graph *G);
int insert_edge(Graph *G, uint a, uint b);
int extend_list(Graph *G, uint a);
int initialise_list(Graph *G, uint a);

// Stack methods
void init_uint_stack(UIntStack *s);
void init_set_stack(SetStack *s);
int is_empty_uint(UIntStack *s);
int is_empty_set(SetStack *s);
int is_full_uint(UIntStack *s);
int is_full_set(SetStack *s);
void grow_stack_uint(UIntStack *s);
void grow_stack_set(SetStack *s);
uint pop_uint(UIntStack *s);
char* pop_set(SetStack *s);
void push_uint(UIntStack *s, uint v);
void push_set(SetStack *s, char* v);