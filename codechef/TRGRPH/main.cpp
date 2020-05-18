#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <numeric>
#include <vector>

#define MIN_SIZE 5;
#define ARG_ERR 1;

typedef unsigned long int myUint;

template <typename N>
struct Tree {
  N n;
  N *data;

  Tree(std::vector<N> *v) {
    n = v->size();
    data = new N[n];
    std::copy(v->begin(), v->end(), data);
  }

  ~Tree() { delete data; }

  static Tree *random(N size) {
    std::vector<N> *v = new std::vector<N>();
    v->reserve(size);
    v->push_back(-1);
    for (N i = 1; i < size; i++) {
      v->push_back(rand() % i);
    }
    return new Tree(v);
  }

  void print(FILE *f) {
    fprintf(f, "%lu", data[0] + 1);
    for (N i = 1; i < n; i++) {
      fprintf(f, " %lu", data[i] + 1);
    }
    fprintf(f, "\n");
  }
};

template <typename N>
struct Set {
  N len;
  bool *data;
  Set(N len, bool init) {
    this->len = len;
    this->data = new bool[len];
    for (N i = 0; i < len; i++) {
      data[i] = init;
    }
  }

  ~Set() { delete this->data; }

  void check(N node) {
    if (node > len) {
      fprintf(stderr, "Node #%lu exceeded index space for length %lu in set.",
              node + 1, len);
      throw ARG_ERR;
    }
  }

  bool contains(N node) {
    check(node);
    return data[node];
  }

  void insert(N node) {
    check(node);
    data[node] = true;
  }

  void remove(N node) {
    check(node);
    data[node] = false;
  }

  Set<N> *clone() {
    Set<N> *set = new Set<N>(len, false);
    std::copy(data, data + len, set->data);
    return set;
  }

  std::vector<N> *to_index_array() {
    std::vector<N> *arr = new std::vector<N>();
    for (N i = 0; i < len; i++) {
      if (data[i]) {
        arr->push_back(i);
      }
    }
    return arr;
  }

  void print() {
    // fprintf(stderr, "%d", data[0]);
    // for (N i = 1; i < len; i++) {
    //  fprintf(stderr, " %d", data[i]);
    //}
    // fprintf(stderr, "\n");
  }
};

template <typename N>
struct Graph {
  N n;  // Number of vertices
  N m;  // Number of edges
  std::vector<N> *edges;

  Graph(N n, N m) {
    this->n = n;
    this->m = m;
    this->edges = new std::vector<N>[n];
  }

  ~Graph() { delete[] this->edges; }

  void check(N a) {
    if (a > this->n) {
      fprintf(stderr,
              "Node %lu exceeded index space for length %lu in graph.\n ",
              a + 1, n);
      throw ARG_ERR;
    }
  }

  bool are_connected(N a, N b) {
    try {
      check(a);
      check(b);
    } catch (int e) {
      fprintf(stderr,
              "Error in are_connected(%lu, %lu) for graph of length %lu.\n",
              a + 1, b + 1, n);
      throw e;
    }
    normalise(&a, &b);
    std::vector<N> e = edges[a];
    for (N i = 0; i < e.size(); i++) {
      if (e[i] == b) {
        return true;
      } else if (e[i] > b) {
        break;
      }
    }
    return false;
  }

  void sort_edges() {
    for (N i = 0; i < n; i++) {
      std::sort(edges[i].begin(), edges[i].end());
    }
  }

  void insert_edge(N a, N b) {
    try {
      check(a);
      check(b);
    } catch (int e) {
      fprintf(stderr,
              "Error in insert_edge(%lu, %lu) for graph of length %lu.\n",
              a + 1, b + 1, n);
      throw e;
    }
    normalise(&a, &b);
    edges[a].push_back(b);
  }

  void normalise(N *a, N *b) {
    if (*a > *b) {
      N t = *a;
      *a = *b;
      *b = t;
    }
  }

  static Graph<N> *next() {
    N n, m;
    scanf("%lu %lu", &n, &m);
    // fprintf(stderr, "Found n=%lu and m=%lu\n", n, m);
    Graph *g = new Graph(n, m);
    N a, b;
    for (N i = 0; i < m; i++) {
      // fprintf(stderr, "Scanning edge %lu/%lu\n", i + 1, m);
      scanf("%lu %lu", &a, &b);
      g->insert_edge(a - 1, b - 1);
    }
    return g;
  }

  std::vector<N> *find_roots(Set<N> *sub) {
    // fprintf(stderr, "Finding root for subset: ");
    // sub->print();
    std::vector<N> *nodes = sub->to_index_array();
    std::vector<N> edge_count;
    for (N i = 0; i < nodes->size(); i++) {
      edge_count.push_back(0);
    }
    for (N i = 0; i < nodes->size(); i++) {
      for (N j = i + 1; j < nodes->size(); j++) {
        if (are_connected(nodes->at(i), nodes->at(j))) {
          // fprintf(stderr, "Found edge #%lu -> #%lu\n", i + 1, j + 1);
          edge_count[i]++;
          edge_count[j]++;
        }
      }
    }
    std::vector<N> *roots = new std::vector<N>();
    for (N i = 0; i < edge_count.size(); i++) {
      if (edge_count.at(i) == nodes->size() - 1) {
        roots->push_back(nodes->at(i));
      }
    }
    return roots;
  }

  std::vector<Set<N> *> *clusters(Set<N> *sub) {
    std::vector<N> *nodes = sub->to_index_array();
    std::vector<N> roots(*nodes);
    delete nodes;
    std::vector<Set<N> *> *clusters = new std::vector<Set<N> *>();
    Set<N> *new_sub = sub->clone();
    while (!roots.empty()) {
      N next = roots.back();
      roots.pop_back();
      if (!new_sub->contains(next)) {
        continue;
      }
      Set<N> *cluster = new Set<N>(sub->len, false);
      std::vector<uint> stack;
      stack.push_back(next);
      while (!stack.empty()) {
        N node = stack.back();
        stack.pop_back();
        cluster->insert(node);
        std::vector<N> *nodes = new_sub->to_index_array();
        for (N i = 0; i < nodes->size(); i++) {
          if (are_connected(node, nodes->at(i))) {
            new_sub->remove(nodes->at(i));
            stack.push_back(nodes->at(i));
          }
        }
        delete nodes;
      }
      clusters->push_back(cluster);
    }
    return clusters;
  }

  Tree<N> *find_tree() {
    sort_edges();
    std::vector<N> *tree = new std::vector<N>(n);
    for (N i = 0; i < n; i++) {
      (*tree)[i] = -1;
    }
    Set<N> *full = new Set<N>(n, true);
    std::vector<Set<N> *> stack;
    stack.push_back(full);
    while (!stack.empty()) {
      Set<N> *sub = stack.back();
      // fprintf(stderr, "New subset: ");
      // sub->print();
      stack.pop_back();
      std::vector<N> *roots = find_roots(sub);
      if (roots->empty()) {
        // Since the stack is not yet empty, we need to clean up its contents.
        // fprintf(stderr, "Failed to find root for subset.\n");
        std::for_each(stack.begin(), stack.end(),
                      [](Set<N> *sub) { delete sub; });
        delete roots;
        delete sub;
        return NULL;
      }
      N last = roots->front();
      for (N i = 1; i < roots->size(); i++) {
        sub->remove(last);
        (*tree)[i] = last;
        last = (*roots)[i];
      }
      sub->remove(last);
      for (N i = 0; i < n; i++) {
        if (sub->contains(i)) {
          // fprintf(stderr, "%lu now ancestor of %lu\n", root, i);
          (*tree)[i] = last;
        }
      }
      // fprintf(stderr, "New Tree:");
      // for (N i = 0; i < n; i++) {
      //  fprintf(stderr, " %lu", tree[i]);
      //}
      // fprintf(stderr, "\n");
      // fprintf(stderr, "Finding clusters.\n");
      std::vector<Set<N> *> *cs = clusters(sub);
      // fprintf(stderr, "Inserting clusters to stack...");
      stack.insert(stack.end(), cs->begin(), cs->end());
      // fprintf(stderr, "Done. (size: %lu)\n", stack.size());
      delete sub;
      delete cs;
    }
    return new Tree<N>(tree);
  }

  void print_tree() {
    Tree<N> *tree = find_tree();
    if (tree == NULL) {
      printf("NO\n");
    } else {
      printf("YES\n");
      tree->print(stdout);
    }
  }

  static Graph<N> *from_tree(Tree<N> *t) {
    Graph<N> *g = new Graph<N>(t->n, 0);
    N edge_count = 0;
    for (N i = 0; i < t->n; i++) {
      N parent = t->data[i];
      while (parent != (N)-1) {
        g->insert_edge(i, parent);
        edge_count++;
        parent = t->data[parent];
      }
    }
    g->m = edge_count;
    return g;
  }

  static void test(N size) {
    // fprintf(stderr, "Testing with length %lu.\n", size);
    // fprintf(stderr, "Building tree.\n");
    Tree<N> *t = Tree<N>::random(size);
    // fprintf(stderr, "Building graph from tree of size %lu.\n", t->n);
    Graph<N> *g = Graph::from_tree(t);
    // fprintf(stderr, "Searching tree.\n");
    Tree<N> *new_tree = g->find_tree();
    if (new_tree == NULL) {
      t->print(stdout);
    }
  }
};

myUint parse_q() {
  myUint Q;
  scanf("%lu", &Q);
  return Q;
}

#define MAX_N 10000

int main(void) {
  // srand(time(0));

  for (int i = 0; i < 10; i++) {
    // myUint size = 1 + (rand() % (MAX_N - 1));
    myUint size = MAX_N - 1;
    fprintf(stderr, "Test #%d, size: %d\n", i + 1, size);
    Graph<myUint>::test(size);
  }
}

void task(void) {
  myUint Q = parse_q();
  for (myUint i = 0; i < Q; i++) {
    // fprintf(stderr, "Reading graph.\n");
    Graph<myUint> *g = Graph<myUint>::next();
    Set<myUint> full(g->n, true);
    // fprintf(stderr, "Printing tree.\n");
    g->print_tree();
    delete g;
  }
}