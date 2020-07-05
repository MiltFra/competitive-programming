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

uint_t min(uint_t a, uint_t b) { return a < b ? a : b; }

int main(void) {
  uint_t T, *arr, *sorted_arr;
  next_unsigned(&T);
  arr = malloc(T * sizeof(uint_t));
  for (uint_t i = 0; i < T; i++) {
    next_unsigned(arr + i);
  }
  sorted_arr = malloc(T * sizeof(uint_t));
  memcpy(sorted_arr, arr, T * sizeof(uint_t));
  qsort(sorted_arr, T, sizeof(uint_t), &cmp);
  uint_t twos, fives, tens;
  twos = fives = tens = 0;
  uint_t x = 1;
  uint_t *p = sorted_arr;
  uint_t *values = malloc(T * sizeof(uint_t));
  for (uint_t i = 0; i < T; i++) {
    uint_t target_factor = *(p++);
    for (; x <= target_factor; x++) {
      uint_t factor = x;
      while (factor && (factor % 10 == 0)) {
        tens++;
        factor /= 10;
      }
      while (factor && (factor % 5 == 0)) {
        fives++;
        factor /= 5;
      }
      while (factor && (factor % 2 == 0)) {
        twos++;
        factor /= 2;
      }
    }
    uint_t new_tens = min(fives, twos);
    tens += new_tens;
    fives -= new_tens;
    twos -= new_tens;
    values[i] = tens;
  }
  for (uint_t i = 0; i < T; i++) {
    for (uint_t j = 0; j < T; j++) {
      if (sorted_arr[j] == arr[i]) {
        printf("%u\n", values[j]);
        break;
      }
    }
  }
  return 0;
}