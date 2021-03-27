#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define u32 unsigned int
#define u64 unsigned long int
#define i64 long int
#define i32 int
#define MAX 100001
#define MIN_BITS 8
#define MIN_SIZE 1 << MIN_BITS
#define MAX_F(X, Y) (((X) > (Y)) ? (X) : (Y))
#define ABS_F(x) ((X) > 0 ? (X) : -(X))

u64 V;        // Value of the array
u32 T;        // Total number of integers read.
u32 L;        // Last input read.
u32 N[MAX];   // Number of elements per integer after next insertion.
u32 *D[MAX];  // Indices with a given integer.
i32 *S;       // S[i] = A[i-1] - A[i] for all 0 < i < MAX

#define fits(n) ((n) & ((n)-1))
#define LEN(n) ((n)-1)

void insert(u32 x) {
  u32 **d = D + x;
  u32 *n = N + x;
  if (!fits(*n) && *n >= MIN_SIZE) {
    u32 *new_d =
        malloc(sizeof(u32) * (*n << 1));  // Doubeling size for each insertion.
    memcpy(new_d, *d, *n);
    free(*d);
    *d = new_d;
  }
  S[T] = (i32)L - x;
  // fprintf(stderr, "Added summand %u-%x=%d\n", L, x, (i32)L - x);
  L = x;
  (*d)[LEN((*n)++)] = T++;
}

void init_value() {
  V = 0;
  for (u32 i = 1; i < T; i++) {
    // fprintf(stderr, "%ld += %d\n", V, S[i]);
    V += (u64)abs(S[i]);
  }
}

// https://stackoverflow.com/questions/364985/algorithm-for-finding-the-smallest-power-of-two-thats-greater-or-equal-to-a-giv
u32 pow2roundup(u32 x) {
  x--;
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  return x + 1;
}

void reinit(u32 len) {
  u32 *n = N;
  u32 **d = D;
  for (u32 i = 1; i < MAX; i++) {
    if (*n > MIN_SIZE)
      *d = malloc(sizeof(u32) * (MIN_SIZE + 1));
    d++;
    *(n++) = 1;
  }
  free(S);
  S = malloc(sizeof(u32) * len);
  T = 0;
}

void merge(u32 x, u32 y) {
  u32 n0 = N[y];
  u32 pu = pow2roundup(N[y]);
  if (N[x] + N[y] - 2 >= (pu = MAX_F(MIN_SIZE, pu))) {
    do {
      pu <<= 1;
    } while (N[x] + N[y] - 2 >= pu);
    u32 *new_d = malloc(sizeof(u32) * pu);
    memcpy(new_d, D[y], N[y] - 1);
    free(D[y]);
    D[y] = new_d;
  }
  memcpy(D[y] + LEN(N[y]), D[x], LEN(N[y]));
  N[y] += LEN(N[x]);
  // Re-initialising x
  if (N[x] > MIN_SIZE) {
    free(D[x]);
    D[x] = malloc(sizeof(u32) * MIN_SIZE);
  }
  N[x] = 1;
}

void update(u32 x, u32 y) {
  u32 n;
  i32 inc;
  inc = (i32)y - x;
  for (u32 i = 0; i < LEN(N[x]); i++) {
    n = D[x][i];  // index to replace
    if (n != 0) {
      V += (u64)abs(((i32)S[n]) - inc) - abs((i32)S[n]);
      S[n] -= inc;
    }
    if (n != T - 1) {
      V += (u64)abs(((i32)S[n + 1]) + inc) - abs((i32)S[n + 1]);
      S[n + 1] += inc;
    }
  }
  merge(x, y);
}

void init(u32 len) {
  u32 *n = N;
  u32 **d = D;
  for (u32 i = 1; i < MAX; i++) {
    *(d++) = malloc(sizeof(u32) * MIN_SIZE);
    *(n++) = 1;
  }
  S = malloc(sizeof(u32) * len);
  T = 0;
}

void print_s() {
  for (int i = 0; i < T; i++) {
    fprintf(stderr, "%d ", S[i]);
  }
  fprintf(stderr, "\n");
}

int main(void) {
  u32 q, n, k, x, y;
  scanf("%u", &q);
  for (u32 i = 0; i < q; i++) {
    printf("Case %u:\n", i + 1);
    scanf("%u %u", &n, &k);
    if (i == 0) {
      init(n);
    } else {
      reinit(n);
    }
    for (u32 j = 0; j < n; j++) {
      scanf("%u", &x);
      insert(x);
    }
    init_value();
    // fprintf(stderr, "T=%u, V=%ld\n", T, V);
    for (u32 j = 0; j < k; j++) {
      scanf("%d %d", &x, &y);
      update(x, y);
      printf("%ld\n", V);
      // print_s();
    }
  }
}
