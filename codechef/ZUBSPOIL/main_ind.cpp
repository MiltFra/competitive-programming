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
#define MAX_VAL_SIZE 20000

u32 U;
u32 N;
u32 C = 0;
u64 V;       // Value of the array
u64 test_V;  // Value of the array
u32 L;       // Last input read.
std::array<std::vector<u32> *, MAX>
    VAL;  // Contains the categories that currently have this value.
std::array<std::vector<u32> *, MAX>
    CAT;  // Contains the indices in the array that belong to this categorie.
std::vector<u32> A;
std::vector<i32> S;  // S[i] = A[i-1] - A[i] for all 0 < i < MAX

void insert(u32 x) {
  CAT.at(x)->push_back(S.size());
  S.push_back((i32)L - x);
  V += (u64)std::abs((i64)L - x);
  L = x;
}

void init_value() {
  V -= (u64)std::abs(S.at(0));
}

void merge_val(u32 x) {
  if (VAL.at(x)->empty()) {
    return;
  }
  std::vector<u32> *val = VAL.at(x);
  std::vector<u32> *tg = CAT.at(val->at(0));
  size_t s = tg->size();
  for (u32 i = 1; i < val->size(); i++) {
    s += CAT.at(val->at(i))->size();
  }
  tg->reserve(s);
  std::vector<u32> *og;
  for (u32 i = 1; i < val->size(); i++) {
    og = CAT.at(val->at(i));
    tg->insert(tg->end(), og->begin(), og->end());
    og->clear();
  }
  while (val->size() > 1) {
    val->pop_back();
  }
}

void merge(u32 x, u32 y) {
  std::vector<u32> *og = VAL.at(x);
  std::vector<u32> *tg = VAL.at(y);
  tg->reserve(tg->size() + og->size());
  tg->insert(tg->end(), og->begin(), og->end());
  og->clear();
  if (tg->size() > MAX_VAL_SIZE) {
    merge_val(y);
  }
}

void update(u32 x, u32 y) {
  if (x == y) {
    return;
  }
  i32 inc = (i32)y - x;
  std::for_each(VAL.at(x)->begin(), VAL.at(x)->end(), [=](u32 c) {
    std::for_each(CAT.at(c)->begin(), CAT.at(c)->end(), [=](u32 n) {
      if (n) {
        V -= (u64)abs(S.at(n));
        S.at(n) -= inc;
        V += (u64)abs(S.at(n));
      }
      if (n + 1 - S.size()) {
        V -= (u64)abs(S.at(n + 1));
        S.at(n + 1) += inc;
        V += (u64)abs(S.at(n + 1));
      }
    });
  });
  merge(x, y);
}

void init(u32 len) {
  V = 0;
  for (u32 i = 1; i < MAX; i++) {
    delete CAT.at(i);
    delete VAL.at(i);
    CAT.at(i) = new std::vector<u32>();
    VAL.at(i) = new std::vector<u32>();
    // In the beginning each category has its own value.
    VAL.at(i)->push_back(i);
  }
  S.clear();
}

void print_s() {
  for (const i32 x : S) {
    fprintf(stderr, "%d ", x);
  }
  fprintf(stderr, "\n");
}

void solve() {
  N = 0;
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
    u64 bef;
    for (u32 j = 0; j < k; j++) {
      scanf("%u %u", &x, &y);
      update(x, y);
      printf("%lu\n", V);
    }
    C++;
  }
}

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
    test_V += (u64)std::abs(((i32)A.at(i)) - last);
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
  solve();
}