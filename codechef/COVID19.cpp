// https://www.codechef.com/MAY20B/problems/COVID19
// Template begins
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

void fastscan(u32 &number) {
  register int c;
  number = 0;
  do {
    c = getchar();
  } while (c == '\n' || c == '\r' || c == ' ');
  for (; (c > 47 && c < 58); c = getchar())
    number = number * 10 + c - 48;
}
// Template ends

void solve() {
  u32 T, N;
  u32 min, max, cur;
  u32 a, b;
  fastscan(T);
  while (T--) {
    // fprintf(stderr, "Next test case.\n");
    fastscan(N);
    fastscan(a);
    N--;
    // fprintf(stderr, "N=%u\n", N);
    min = -1;
    max = 0;
    cur = 1;
    while (N--) {
      fastscan(b);
      // fprintf(stderr, "Next pair. (%u, %u)\n", a, b);
      if (b - a <= 2) {
        cur++;
      } else {
        if (cur < min) {
          min = cur;
        }
        if (cur > max) {
          max = cur;
        }
        cur = 1;
      }
      a = b;
    }
    if (cur < min) {
      min = cur;
    }
    if (cur > max) {
      max = cur;
    }
    printf("%u %u\n", min, max);
  }
}

int main(void) { solve(); }