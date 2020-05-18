#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
char *pop_set(SetStack *s);
void push_uint(UIntStack *s, uint v);
void push_set(SetStack *s, char *v);

int comp(const void *e1, const void *e2) {
  int f = *((uint *)e1);
  int s = *((uint *)e2);
  return (f > s) - (f < s);
}

int check_graph(Graph *G) {
  if (G == NULL) {
    // fprintf(stderr, "Received null pointer as graph.\n");
    return ARG_ERR;
  }
  if (G->N == NULL || G->E == NULL || G->P == NULL) {
    // fprintf(stderr,
    //"Not all of the given graphs fields have been initialised.\n");
    return ARG_ERR;
  }
  return OK;
}

int check_node(Graph *G, uint a) {
  if (a >= G->n) {
    // fprintf(stderr, "Found node %d which exceeds index space for n=%d
    // nodes.\n",
    // a, G->n);
    return ARG_ERR;
  }
  return OK;
}

int are_connected(Graph *G, uint a, uint b) {
  if (check_graph(G) || check_node(G, a) || check_node(G, b)) {
    // fprintf(stderr, "Tried to check invalid node-graph-combination.\n");
    return 0;  // Can't return error here.
  }
  if (a > b) {
    uint t = a;
    a = b;
    b = t;
  }
  for (uint *p = G->E[a]; p != G->P[a]; p++) {
    if (*p > b) {
      break;
    }
    if (*p == b) {
      return 1;
    }
  }
  return 0;
}

int fit(Graph *G, uint a) {
  if (check_graph(G) || check_node(G, a)) {
    return ARG_ERR;
  }
  if (G->E[a] == NULL) {
    initialise_list(G, a);
  } else if (G->P[a] - G->E[a] >= 1 << G->N[a]) {
    extend_list(G, a);
  }
  return OK;
}

int finalise_graph(Graph *G) {
  if (check_graph(G)) {
    return ARG_ERR;
  }
  for (int i = 0; i < G->n; i++) {
    uint n = G->P[i] - G->E[i];
    G->N[i] = n;
    if (n == 0) {
      continue;
    }
    qsort(G->E[i], n, sizeof(uint), comp);
  }
}

// Insert an edge between a and b into the graph G and extend the lists if
// necessary.
int insert_edge(Graph *G, uint a, uint b) {
  if (check_graph(G) || check_node(G, a) || check_node(G, b)) {
    return ARG_ERR;
  }
  if (a > b) {
    uint t = a;
    a = b;
    b = t;
  }
  for (uint *p = G->E[a]; p != G->P[a]; p++) {
    if (*p == b) {
      // fprintf(stderr, "Tried to insert edge that's already present.\n");
      return OK;
    }
  }
  int err;
  if (err = fit(G, a)) {
    return err;
  }
  if (err = fit(G, b)) {
    return err;
  }
  *(G->P[a]++) = b;
  return OK;
}

// Double the size of the current array G->E[a] and
// change N and P accordingly.
int extend_list(Graph *G, uint a) {
  if (check_graph(G) || check_node(G, a)) {
    return ARG_ERR;
  }
  if (G->N[a] == 0) {
    return initialise_list(G, a);
  }
  uint *p = G->P[a];
  uint *e = G->E[a];
  uint n = G->N[a];
  uint l = 1 << n;
  uint *arr = malloc(sizeof(uint) * (l << 1));
  memcpy(arr, e, sizeof(uint) * l);
  G->P[a] = arr + (p - e);
  free(e);
  G->E[a] = arr;
  return OK;
}

// Fill N, E and P properly fora given a in a given G.
int initialise_list(Graph *G, uint a) {
  if (check_graph(G) || check_node(G, a)) {
    return ARG_ERR;
  }
  G->N[a] = MIN_SIZE;
  int l = 1 << MIN_SIZE;
  uint *arr = malloc(sizeof(uint) * l);
  G->E[a] = arr;
  G->P[a] = arr;
  return OK;
}

int parse_config() {
  scanf("%d", &config.Q);
  config.Gs = malloc(sizeof(Graph) * config.Q);
  for (int i = 0; i < config.Q; i++) {
    Graph *g = malloc(sizeof(Graph));
    scanf("%d %d", &g->n, &g->m);
    g->N = malloc(sizeof(uint) * g->n);
    g->E = malloc(sizeof(uint *) * g->n);
    g->P = malloc(sizeof(uint *) * g->n);
    uint a, b;
    for (int j = 0; j < g->m; j++) {
      scanf("%d %d", &a, &b);
      if (insert_edge(g, a - 1, b - 1)) {
        // fprintf(
        //    stderr,
        //    "An error occurred inserting edge no. %d of node %d (%d->%d).\n",
        //    j + 1, i + 1, a, b);
        return 1;
      }
    }
    config.Gs[i] = g;
  }
  return 0;
}
void init_set_stack(SetStack *s) {
  uint size = 1 << MIN_SIZE;
  s->data = malloc(sizeof(uint) * size);
  s->next = s->data;
  s->end = s->data + size;
}

int is_empty_set(SetStack *s) {
  return s->data == s->next;
}

int is_full_set(SetStack *s) {
  return s->data == s->end;
}

void grow_stack_set(SetStack *s) {
  size_t cap = s->end - s->data;
  size_t len = s->next - s->data;
  char **arr = malloc(sizeof(char *) * cap << 1);
  memcpy(arr, s->data, cap);
  free(s->data);
  s->data = arr;
  s->end = arr + cap;
  s->next = arr + len;
}

char *pop_set(SetStack *s) {
  if (is_empty_set(s)) {
    // fprintf(stderr, "Tried to pop from empty stack.\n");
    return NULL;
  }
  return *(--s->next);
}

void push_set(SetStack *s, char *v) {
  if (is_full_set(s)) {
    grow_stack_set(s);
  }
  *(s->next++) = v;
}

void init_uint_stack(UIntStack *s) {
  uint size = 1 << MIN_SIZE;
  s->data = malloc(sizeof(uint) * size);
  s->next = s->data;
  s->end = s->data + size;
}

int is_empty_uint(UIntStack *s) {
  return s->data == s->next;
}

int is_full_uint(UIntStack *s) {
  return s->data == s->end;
}

void grow_stack_uint(UIntStack *s) {
  size_t cap = s->end - s->data;
  size_t len = s->next - s->data;
  uint *arr = malloc(sizeof(uint) * cap << 1);
  memcpy(arr, s->data, cap);
  free(s->data);
  s->data = arr;
  s->end = arr + cap;
  s->next = arr + len;
}

uint pop_uint(UIntStack *s) {
  if (is_empty_uint(s)) {
    // fprintf(stderr, "Tried to pop from empty stack.\n");
    return -1;
  }
  return *(--s->next);
}

void push_uint(UIntStack *s, uint v) {
  if (is_full_uint(s)) {
    grow_stack_uint(s);
  }
  *(s->next++) = v;
}

void free_stack_uint(UIntStack *s) {
  free(s->data);
}
void free_stack_set(SetStack *s) {
  free(s->data);
}

void free_graph(Graph *g) {
  free(g->N);
  if (g->E != NULL) {
    for (int i = 0; i < g->n; i++) {
      if (g->E[i] != NULL) {
        free(g->E[i]);
      }
    }
    free(g->E);
  }
  if (g->P != NULL) {
    free(g->P);
  }
}

void print_no() {
  printf("NO\n");
}

uint to_index_array(Graph *g, char *subset, uint *arr) {
  uint size = 0;
  for (int i = 0; i < g->n; i++) {
    if (subset[i]) {
      arr[size++] = i;
    }
  }
  return size;
}

uint find_root(Graph *g, char *subset) {
  uint nodes[g->n];
  uint size = to_index_array(g, subset, nodes);
  uint edge_count[g->n];
  for (int i = 0; i < g->n; i++) {
    edge_count[i] = 0;
  }
  for (uint i = 0; i < size; i++) {
    for (uint j = i; j < size; j++) {
      if (are_connected(g, nodes[i], nodes[j])) {
        edge_count[nodes[i]]++;
        edge_count[nodes[j]]++;
      }
    }
  }
  uint count = 0;
  uint last;
  for (int i = 0; i < size; i++) {
    if (edge_count[nodes[i]] == size - 1) {
      count++;
      last = nodes[i];
    }
  }
  if (count == 1 || count == size) {
    return last;
  }
  return -1;
}

uint clusters(Graph *g, char *subset, char **clusters) {
  char new_sub[g->n];
  memcpy(new_sub, subset, sizeof(char) * g->n);
  uint nodes[g->n];
  uint size = to_index_array(g, subset, nodes);
  uint next_root = 0;
  for (; next_root < g->n; next_root++) {
    if (new_sub[next_root]) {
      break;
    }
  }
  new_sub[next_root] = 0;
  uint count = 0;
  while (next_root < g->n) {
    // fprintf(stderr, "Allocating %d bytes of memory in clusters...", g->n);
    char *cluster = malloc(sizeof(char) * g->n);
    for (uint i = 0; i < g->n; i++) {
      cluster[i] = 0;
    }
    // fprintf(stderr, "Done.\n");
    UIntStack stack;
    init_uint_stack(&stack);
    push_uint(&stack, next_root);
    while (!is_empty_uint(&stack)) {
      // fprintf(stderr, "Stack size: %d\n", stack.next - stack.data);
      uint node = pop_uint(&stack);
      // fprintf(stderr, "Processing node #%d\n", node + 1);
      cluster[node] = 1;
      // Since new_sub doesn't grow, it will always fit into nodes.
      size = to_index_array(g, new_sub, nodes);
      for (uint i = 0; i < size; i++) {
        // fprintf(stderr, "Checking %d and %d.\n", node, nodes[i]);
        if (are_connected(g, node, nodes[i])) {
          new_sub[nodes[i]] = 0;
          push_uint(&stack, nodes[i]);
        }
      }
    }
    clusters[count++] = cluster;
    // fprintf(stderr, "Found cluster #%d\n", count);
    for (; next_root < g->n; next_root++) {
      if (new_sub[next_root]) {
        break;
      }
    }
    new_sub[next_root] = 0;
  }
  // fprintf(stderr, "Returning from clusters\n");
  return count;
}

void fill_subset(char *subset, uint length) {
  for (int i = 0; i < length; i++) {
    subset[i] = 1;
  }
}

int print_tree(Graph *g) {
  // fprintf(stderr, "Printing tree...\n");
  char *full = malloc(sizeof(char) * g->n);
  uint tree[g->n];
  for (uint i = 0; i < g->n; i++) {
    tree[i] = -1;
  }
  fill_subset(full, g->n);
  SetStack s;
  init_set_stack(&s);
  push_set(&s, full);
  // fprintf(stderr, "Initialized stack.\n");
  while (!is_empty_set(&s)) {
    char *sub = pop_set(&s);
    for (uint i = 0; i < g->n; i++) {
      // fprintf(stderr, "%d ", sub[i]);
    }
    // fprintf(stderr, "\n");
    uint root = find_root(g, sub);
    // fprintf(stderr, "Got root: #%d\n", root + 1);
    if (root == -1) {
      printf("NO\n");
      return 0;
    }
    sub[root] = 0;
    for (uint i = 0; i < g->n; i++) {
      if (sub[i]) {
        tree[i] = root;
      }
    }
    // fprintf(stderr, "Changed roots in tree array.\n");
    // fprintf(stderr, "Allocating %d bytes of memory in print_tree...", g->n);
    char **cs = malloc(sizeof(char *) * g->n);
    for (uint i = 0; i < g->n; i++) {
      cs[i] = NULL;
    }
    // fprintf(stderr, "Done\n");
    uint cs_count = clusters(g, sub, cs);
    // fprintf(stderr, "Got %d clusters.\n", cs_count);
    for (uint i = 0; i < cs_count; i++) {
      // fprintf(stderr, "Pushing to set.\n");
      push_set(&s, cs[i]);
    }
    // fprintf(stderr, "Freeing 0x%x and 0x%x\n", cs, sub);
    free(sub);
    free(cs);
  }
  free_stack_set(&s);
  printf("YES\n");
  for (uint i = 0; i < g->n; i++) {
    printf("%d ", tree[i] + 1);
  }
  printf("\n");
  return 0;
}

void tree_to_graph(const uint *tree, Graph *g) {
  UIntStack s;
  init_uint_stack(&s);
  
}

int main(void) {
  if (parse_config()) {
    // fprintf(stderr, "An error occurred parsing the config.\n");
  }
  for (int i = 0; i < config.Q; i++) {
    if (print_tree(config.Gs[i])) {
      fprintf(stderr,
              "An error occurred trying to print the tree for graph #%d.\n",
              i + 1);
    }
  }
}