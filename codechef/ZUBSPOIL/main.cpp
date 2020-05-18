#include <stdint.h>
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

#define ONLINE_JUDGE

#define ABS_F(x) std::abs(x);

u32 C = 0;
#ifndef ONLINE_JUDGE
u32 N;
u32 U;
std::vector<u32> A;
u64 test_V;   // Value of the array
#endif
u64 V;   // Value of the array
u32 L;   // Last input read.
std::array<std::vector<u32>, MAX> D;
std::vector<i32> S;   // S[i] = A[i-1] - A[i] for all 0 < i < MAX

inline void fastscan(u32 &number) {
  register int c;
  number = 0;
  do {
    c = getchar();
  } while (c == '\n' || c == '\r' || c == ' ');
  for (; (c > 47 && c < 58); c = getchar())
    number = number * 10 + c - 48;
}

inline void insert(u32 x) {
  D.at(x).push_back(S.size());
  S.push_back(L - x);
  V += ABS_F(S.back());
  L = x;
}

inline void init_value() {
  V -= ABS_F(S.front());
}

inline void update(u32 x, u32 y) {
  if (x == y) {
    return;
  }
  std::for_each(D.at(x).begin(), D.at(x).end(), [=](u32 n) {
    if (n) {
      V -= (u64)abs(S.at(n));
      S.at(n) -= (i32)y - x;
      V += (u64)abs(S.at(n));
    }
    if (n + 1 - S.size()) {
      V -= (u64)abs(S.at(n + 1));
      S.at(n + 1) += (i32)y - x;
      V += (u64)abs(S.at(n + 1));
    }
  });
  std::vector<u32> *og = &D.at(x);
  std::vector<u32> *tg = &D.at(y);
  // if (og->size() > tg->size()) {
  //  std::vector<u32> temp = *og;
  //  *og = *tg;
  //  *tg = temp;
  //}
  tg->insert(tg->end(), og->begin(), og->end());
  og->clear();
  og->shrink_to_fit();
}

inline void init(u32 len) {
  for (u32 i = 1; i < MAX; i++) {
    D.at(i).clear();
  }
  S.clear();
  V = 0;
}

#ifdef ONLINE_JUDGE

inline void solve() {
  u32 q, n, k, x, y;
  fastscan(q);
  for (u32 i = 0; i < q; i++) {
    printf("Case %u:\n", i + 1);
    fastscan(n);
    fastscan(k);
    init(n);
    for (u32 j = 0; j < n; j++) {
      fastscan(x);
      insert(x);
    }
    init_value();
    for (u32 j = 0; j < k; j++) {
      fastscan(x);
      fastscan(y);
      update(x, y);
      printf("%lu\n", V);
    }
    C++;
  }
}

int main(void) {
  solve();
}

#else

void print_s() {
  for (const i32 x : S) {
    fprintf(stderr, "%d ", x);
  }
  fprintf(stderr, "\n");
}

void test_update(u32 x, u32 y) {
  update(x, y);
  U++;
  for (u32 i = 0; i < A.size(); i++) {
    if (A.at(i) == x) {
      A.at(i) = y;
    }
  }
  test_V   = 0;
  i32 last = (i32)A.at(0);
  for (u32 i = 1; i < A.size(); i++) {
    test_V += (u64)ABS_F(((i32)A.at(i)) - last);
    last = (i32)A.at(i);
  }
  if (V != test_V) {
    print_s();
    fprintf(
        stderr,
        "An error occurred while updating (%u, %u) (N=%u, U=%u): %lu "
        "(expected: %lu)\n",
        x,
        y,
        N,
        U,
        V,
        test_V);
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
  fastscan(q);
  for (u32 i = 0; i < q; i++) {
    printf("Case %u:\n", i + 1);
    fastscan(n);
    fastscan(k);
    test_init(n);
    for (u32 j = 0; j < n; j++) {
      fastscan(x);
      test_insert(x);
    }
    init_value();
    u64 bef;
    for (u32 j = 0; j < k; j++) {
      fastscan(x);
      fastscan(y);
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