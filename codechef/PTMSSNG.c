#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define u32_t unsigned int
#define u64_t unsigned long int
#define i32_t int
#define i64_t long int

#define int_t i32_t
#define uint_t u32_t

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

#define MAX_N 200000
#define MAX_NUM_POINTS 4 * MAX_N

int cmp(const void *a, const void *b) {
  int_t cmp = (*(int_t *)a - *(int_t *)b);
  if (cmp > 0) {
    return 1;
  } else if (cmp < 0) {
    return -1;
  } else {
    return 0;
  }
}

int_t main(void) {
  uint_t T, N;
  next_unsigned(&T);
  uint_t *x_buffer = malloc(MAX_NUM_POINTS * sizeof(uint_t));
  uint_t *y_buffer = malloc(MAX_NUM_POINTS * sizeof(uint_t));
  while (T--) {
    next_unsigned(&N);
    uint_t *p = x_buffer;
    uint_t *q = y_buffer;
    register uint_t num_points, points_left;
    num_points = points_left = N * 4 - 1;
    while (points_left--) {
      next_unsigned(p++);
      next_unsigned(q++);
    }
    qsort(x_buffer, num_points, sizeof(uint_t), &cmp);
    qsort(y_buffer, num_points, sizeof(uint_t), &cmp);
    *p = *q = -1;
    p = x_buffer;
    for (p = x_buffer; p != x_buffer + num_points + 1; p += 2) {
      if (*p != *(p + 1)) {
        printf("%u ", *p);
        break;
      }
    }
    for (q = y_buffer; q != y_buffer + num_points + 1; q += 2) {
      if (*q != *(q + 1)) {
        printf("%u\n", *q);
        break;
      }
    }
  }
}