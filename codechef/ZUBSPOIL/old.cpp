#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <vector>
#define u32 unsigned int
#define u64 unsigned long int
#define i32 int
#define i64 long int
#define MAX 100001

#define TEST1
#define ABS_F(x) std::abs(x);

u32 C = 0;
#ifdef TEST
u32 N;
u32 U;
std::vector<u32> A;
#endif
u64 V;       // Value of the array
u64 test_V;  // Value of the array
u32 L;       // Last input read.
std::array<std::vector<u32>, MAX> D;
std::vector<i32> S;  // S[i] = A[i-1] - A[i] for all 0 < i < MAX



inline void insert(u32 x) {
  D.at(x).push_back(S.size());
  S.push_back((i32)L - x);
  V += (u64)ABS_F((i64)L - x);
  L = x;
}

inline void init_value() {
  V -= (u64)ABS_F(S.at(0));
}

inline void merge(u32 x, u32 y) {
  std::vector<u32> *og = &D.at(x);
  std::vector<u32> *tg = &D.at(y);
  tg->insert(tg->end(), og->begin(), og->end());
  og->clear();
}

inline void update(u32 x, u32 y) {
  if (x == y) {
    return;
  }
  std::for_each(D.at(x).begin(), D.at(x).end(), [=](u32 n) {
    if (n) {
      V -= (u64)ABS_F(S.at(n));
      S.at(n) -= (i32)y - x;
      V += (u64)ABS_F(S.at(n));
    }
    if (n + 1 - S.size()) {
      V -= (u64)ABS_F(S.at(n + 1));
      S.at(n + 1) += (i32)y - x;
      V += (u64)ABS_F(S.at(n + 1));
    }
  });
  merge(x, y);
}

inline void init(u32 len) {
  for (u32 i = 1; i < MAX; i++) {
    D.at(i).clear();
  }
  S.clear();
  V = 0;
}

inline void solve() {
  u32 q, n, k, x, y;
  scanf("%u", &q);
  for (u32 i = 0; i < q; i++) {
    printf("Case %u:\n", i + 1);
    scanf("%u %u", &n, &k);
    init(n);
    for (u32 j = 0; j < n; j++) {
      scanf("%u", &x);
      insert(x);
    }
    init_value();
    for (u32 j = 0; j < k; j++) {
      scanf("%u %u", &x, &y);
      update(x, y);
      printf("%lu\n", V);
    }
    C++;
  }
}

#ifndef TEST

int main(void) {
  solve();
}

#else

void test_update(u32 x, u32 y) {
  update(x, y);
  U++;
  for (u32 i = 0; i < A.size(); i++) {
    if (A.at(i) == x) {
      A.at(i) = y;
    }
  }
  test_V = 0;
  i32 last = (i32)A.at(0);
  for (u32 i = 1; i < A.size(); i++) {
    test_V += (u64)ABS_F(((i32)A.at(i)) - last);
    last = (i32)A.at(i);
  }
  if (V != test_V) {
    fprintf(stderr,
            "An error occurred while updating (%u, %u) (N=%u, U=%u): %lu "
            "(expected: %lu)\n",
            x, y, N, U, V, test_V);
    throw 0;
  }
}

void test_insert(u32 x) {
  insert(x);
  A.push_back(x);
}

void test_init(u32 n) {
  init(n);
  A.clear();
  test_V = 0;
  N++;
  U = 0;
}

void test_solve() {
  N = 0;
  u32 q, n, k, x, y;
  scanf("%u", &q);
  for (u32 i = 0; i < q; i++) {
    printf("Case %u:\n", i + 1);
    scanf("%u %u", &n, &k);
    test_init(n);
    for (u32 j = 0; j < n; j++) {
      scanf("%u", &x);
      test_insert(x);
    }
    init_value();
    u64 bef;
    for (u32 j = 0; j < k; j++) {
      scanf("%u %u", &x, &y);
      test_update(x, y);
      printf("%lu\n", V);
    }
    C++;
  }
}

int main(void) {
  test_solve();
}

#endif