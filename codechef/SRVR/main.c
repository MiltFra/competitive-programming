#include <stdio.h>
#include <stdlib.h>

#define CACHE_STEP 1024

const int MOD = 987654319;
const int OK = 0;
const int NULL_PTR_ERR = 1;
const int PARSE_ERR = 2;

struct Config {
  int N;
  int Q;
  int *D;
  int *C;
  int *P;
} config;

int cache_length;
char **set_cache;
char *suc_cache;

// Parses the config from the input.
int get_config(void);

// Prints the config to the output.
int print_config(void);

// Stores the indices of the elements in the given subset in the given array.
int make_subset(const char *s, int *subset);

// Calculates how many processing slots per second a given subset of customers
// requires.
int required_space(const int *subset, int length);

// Checks whether the given subset can be handled by the given server.
int check_subset(char *s, int srv);

// Compares two ints such to sort in descending order.
int comp(const void *e1, const void *e2);

// Converts the given subset from an array of bools to an array of bytes
// containing each bools as a bit.
void encode(const char *s, char *enc);

void decode(const char *enc, char *s);

void encode(const char *s, char *enc) {
  int k, buf;
  k = buf = 0;
  for (int i = 0; i < config.N; i++) {
    buf += !!s[i];     // "!!" to make sure it's definetly 0 or 1.
    if (++k == 8) {    // Check whether all eight bits have been filled.
      *(enc++) = buf;  // Write buffer into correct slot and move to right;
      k = 0;           // reset bit count
    } else {
      buf = buf << 1;  // Shift to free next bit.
    }
  }
}

void decode(const char *enc, char *s) {
  int k, j, buf;
  k = j = 0;
  buf = enc[j++];
  for (int i = 0; i < config.N; i++) {
    s[i] = !!(buf & 0x80);  // Getting the first bit of a byte.
    if (++k == 8) {
      buf = enc[j++];
    } else {
      buf = buf << 1;
    }
  }
}

int comp(const void *e1, const void *e2) {
  int f = *((int *)e1);
  int s = *((int *)e2);
  return (f < s) - (f > s);
}

int get_config(void) {
  if (!scanf("%d %d", &config.N, &config.Q)) {
    fprintf(stderr, "Could not find expected integers N and Q.\n");
    return PARSE_ERR;
  }
  config.D = (int *)malloc(sizeof(int) * config.N);
  int *d = config.D;
  for (int i = 0; i < config.N; i++) {
    if (!scanf("%d", d++)) {
      fprintf(stderr, "Could not find expected integer D_%d.\n", i);
      return PARSE_ERR;
    }
  }
  qsort(config.D, config.N, sizeof(int), comp);
  config.C = (int *)malloc(sizeof(int) * config.Q);
  config.P = (int *)malloc(sizeof(int) * config.Q);
  int *c = config.C;
  int *p = config.P;
  for (int i = 0; i < config.Q; i++) {
    if (!scanf("%d %d", c++, p++)) {
      fprintf(stderr, "Could not find expected integers C_%d and P_%d.\n", i,
              i);
      return PARSE_ERR;
    }
  }
  return OK;
}

int print_config(void) {
  fprintf(stderr, "N=%d Q=%d\n", config.N, config.Q);
  int *d = config.D;
  for (int i = 0; i < config.N; i++) {
    fprintf(stderr, "D_%d=%d\n", i, *d++);
  }
  int *c = config.C;
  int *p = config.P;
  for (int i = 0; i < config.Q; i++) {
    fprintf(stderr, "C_%d=%d P_%d=%d\n", i, *c++, i, *p++);
  }
  return OK;
}

int make_subset(const char *s, int *t) {
  int count = 0;
  for (int i = 0; i < config.N; i++) {
    if (s[i]) {
      t[count++] = i;
    }
  }
  return count;
}

int required_space(const int *subset, int l) {
  if (l == 0) {
    return 0;
  }
  int space = (config.D[subset[0]] + 1) / 2;
  for (int i = 1; i < l; i++) {
    space += config.D[subset[i]];
  }
  return space;
}

int check_subset(char *s, int srv) {
  int subset[config.N];
  int count = make_subset(s, subset);
  // Check whether this is the empty set.
  if (!count) {
    return 1;
  }
  // Check whether the first (and biggest) task fits the server with exclusive
  // processing.
  if ((config.D[subset[0]] + 1) / 2 > config.P[srv]) {
    return 0;
  } else if (count == 1) {
    // If there is only one task
    return 1;
  }
  // Check whether the second task fits the server without exclusive processing.
  if (config.D[subset[1]] > config.P[srv]) {
    return 1;
  }
  return required_space(subset, count) <= config.P[srv] * config.C[srv];
}

void memorise(const char *s, char suc) {}

int main(void) {
  struct Config config;
  int err;
  if (err = get_config()) {
    fprintf(stderr, "Loading inputs failed.\n");
    return err;
  }
  cache_length = 0;
  set_cache = (char **)malloc(sizeof(char *) * CACHE_STEP);
  suc_cache = (char *)malloc(sizeof(char *) * CACHE_STEP);
  print_config();
}