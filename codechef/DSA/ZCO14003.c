#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define u32_t unsigned int
#define u64_t unsigned long long
#define i32_t int
#define i64_t long long

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

int main(void) {
  uint_t T;
  next_unsigned(&T);
  uint_t arr[T];
  uint_t num;
  for (uint_t i = 0; i < T; i++) {
    next_unsigned(&num);
    arr[i] = num;
  }
  qsort(arr, T, sizeof(uint_t), &cmp);
  uint_t max_value, current_value, last_budget;
  max_value = current_value = last_budget = 0;
  for (uint_t i = 0; i < T; i++) {
    // Removing last customer from buyers list
    current_value -= last_budget;
    // Adding price increase (arr[i]-last_budget) for remaining (T-i) customers
    current_value += (T - i) * (arr[i] - last_budget);
    last_budget = arr[i];
    if (current_value > max_value) {
      max_value = current_value;
    }
    // fprintf(stderr, "%llu,%llu\n", current_value, max_value);
  }
  printf("%llu\n", max_value);
}