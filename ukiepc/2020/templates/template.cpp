#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

#define u32 unsigned
#define u64 unsigned long long
#define i32 int
#define i64 long long

#define isize i32
#define usize u32

template <typename T> void next_signed(T &number) {
  register isize c;
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

template <typename T> void next_unsigned(T &number) {
  register usize c;
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

void next_upper_letter(char &c) {
  do {
    c = getchar();
  } while (c < 65 || c > 90);
}

int main(void) {
  u32 T;
  next_unsigned(T);
  while (T--) {
  }
}