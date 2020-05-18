#include <stdio.h>

#include <random>
#include <vector>

#define u32 unsigned int
#define T   1
#define N   200000
#define K   N / 2

std::vector<u32> P;

void swap_back(u32 a, u32 b, u32 c) {
  register u32 t;
  t       = P.at(a);
  P.at(a) = P.at(b);
  P.at(b) = P.at(c);
  P.at(c) = t;
}

u32 r() {
  return rand() % N;
}

void rand_triple(u32 &a, u32 &b, u32 &c) {
  a = r();
  do {
    b = r();
  } while (b == a);
  do {
    c = r();
  } while (c == a || c == b);
}

int main(void) {
  srand(time(NULL));
  printf("%u\n", T);
  for (u32 t = 0; t < T; t++) {
    printf("%u %u\n", N, K);
    P.clear();
    for (u32 i = 0; i < N; i++) {
      P.push_back(i);
    }
    u32 a, b, c;
    for (u32 i = 0; i < K; i++) {
      rand_triple(a, b, c);
      swap_back(a, b, c);
    }
    for (u32 i = 0; i < N; i++) {
      printf("%u ", P.at(i) + 1);
    }
    printf("\n");
  }
}