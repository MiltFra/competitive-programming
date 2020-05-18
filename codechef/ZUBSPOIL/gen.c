#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define u32 unsigned int
#define N 100000
u32 r() {
  return 1 + rand() % N;
}
int random_cases(void) {
  srand(time(NULL));
  u32 t = 10;
  printf("%u\n", t);
  for (u32 j = 0; j < t; j++) {
    u32 n, q;
    n = N;
    q = N;
    printf("%u %u\n", n, q);
    for (u32 i = 0; i < n; i++) {
      printf("%u ", r());
    }
    printf("\n");
    for (u32 i = 0; i < q; i++) {
      printf("%u %u\n", r(), r());
    }
  }
}

int worst_cases(void) {
  srand(time(NULL));
  u32 t = 10;
  printf("%u\n", t);
  for (u32 j = 0; j < t; j++) {
    u32 n, q;
    n = N;
    q = N;
    printf("%u %u\n", n, q);
    for (u32 i = 0; i < n; i++) {
      printf("%u ", i);
    }
    printf("\n");
    for (u32 i = 0; i < q; i++) {
      printf("%u %u\n", i, i + 1);
    }
  }
}

int main(void) {
  worst_cases();
}