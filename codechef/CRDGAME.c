#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define u32_t unsigned int
#define u64_t unsigned long int
#define i32_t int
#define i64_t long int

#define int_t i64_t
#define uint_t u64_t


void next_signed(int_t *number) {
  register int_t c;
  *number = 0;
  do {
    c = getchar();
  } while (c == '\n' || c == '\r' || c == ' ');

  char negative = c == '-';

  for (; (c > 47 && c < 58); c = getchar())
    *number = *number * 10 + c - 48;
  if (negative) {
    *number *= -1;
  }
}

void next_unsigned(uint_t *number) {
  register int_t c;
  *number = 0;
  do {
    c = getchar();
  } while (c == '\n' || c == '\r' || c == ' ');
  for (; (c > 47 && c < 58); c = getchar())
    *number = *number * 10 + c - 48;
}

void next_lower_letter(char *c) {
  do {
    *c = getchar();
  } while (*c < 97 || *c > 122);
}

void next_upper_letter(char *c) {
  do {
    *c = getchar();
  } while (*c < 65 || *c > 90);
}

uint_t sum_of_digits(uint_t x) {
  register uint_t sum = 0;
  while (x) {
    sum += x % 10;
    x /= 10;
  }
  return sum;
}

int main(void) {
  uint_t T, N, A, B;
  register uint_t points_A, points_B, sum_A, sum_B;
  next_unsigned(&T);
  while (T--) {
    next_unsigned(&N);
    points_A = points_B = 0;
    while (N--) {
      next_unsigned(&A);
      next_unsigned(&B);
      sum_A = sum_of_digits(A);
      sum_B = sum_of_digits(B);
      points_A += sum_A >= sum_B;
      points_B += sum_B >= sum_A;
    }
    if (points_A > points_B) {
      printf("0 %lu\n", points_A);
    } else if (points_A < points_B) {
      printf("1 %lu\n", points_B);
    } else {
      printf("2 %lu\n", points_A);
    }
  }
  return 0;
}