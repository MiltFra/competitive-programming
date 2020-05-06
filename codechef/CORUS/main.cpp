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

template <typename i>
void next_signed(i &number) {
  register int c;
  number = 0;
  do {
    c = getchar();
  } while (c == '\n' || c == '\r' || c == ' ');

  bool negative = c == '-';

  for (; (c > 47 && c < 58); c = getchar())
    number = number * 10 + c - 48;
  if (negative) {
    number *= -1;
  }
}

template <typename u>
void next_unsigned(u &number) {
  register int c;
  number = 0;
  do {
    c = getchar();
  } while (c == '\n' || c == '\r' || c == ' ');
  for (; (c > 47 && c < 58); c = getchar())
    number = number * 10 + c - 48;
}

void next_lower_letter(char &c) {
  do {
    c = getchar();
  } while (c < 97 || c > 122);
}
// Template ends

int main(void) {
  u32 T;
  next_unsigned(T);
  while (T--) {
    u32 counts[26];
    for (u32 i = 0; i < 26; i++) {
      counts[i] = 0;
    }
    u32 N, Q;
    next_unsigned(N);
    next_unsigned(Q);
    char c;
    while (N--) {
      next_lower_letter(c);
      counts[c - 97]++;
    }
    u32 C;
    u32 sum;
    while (Q--) {
      next_unsigned(C);
      sum = 0;
      for (u32 i = 0; i < 26; i++) {
        sum += std::max(0, (i32)(counts[i] - C));
      }
      printf("%u\n", sum);
    }
  }
}