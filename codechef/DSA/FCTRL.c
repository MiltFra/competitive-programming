#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define u32_t unsigned int
#define u64_t unsigned long int
#define i32_t int
#define i64_t long int

#define int i32_t
#define uint u32_t

void next_signed(int *number) {
  register int c;
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

void next_unsigned(uint *number) {
  register int c;
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
  int cmp = (*(int *)a - *(int *)b);
  if (cmp > 0) {
    return 1;
  } else if (cmp < 0) {
    return -1;
  } else {
    return 0;
  }
}

uint min(uint a, uint b) { return a < b ? a : b; }

int main(void) {
  uint T, *arr, *sorted_arr;
  next_unsigned(&T);
  arr = malloc(T * sizeof(uint));
  for (uint i = 0; i < T; i++) {
    next_unsigned(arr + i);
  }
  sorted_arr = malloc(T * sizeof(uint));
  memcpy(sorted_arr, arr, T * sizeof(uint));
  qsort(sorted_arr, T, sizeof(uint), &cmp);
  uint twos, fives, tens;
  twos = fives = tens = 0;
  uint x = 1;
  uint *p = sorted_arr;
  uint *values = malloc(T * sizeof(uint));
  for (uint i = 0; i < T; i++) {
    uint target_factor = *(p++);
    for (; x <= target_factor; x++) {
      uint factor = x;
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
    uint new_tens = min(fives, twos);
    tens += new_tens;
    fives -= new_tens;
    twos -= new_tens;
    values[i] = tens;
  }
  for (uint i = 0; i < T; i++) {
    for (uint j = 0; j < T; j++) {
      if (sorted_arr[j] == arr[i]) {
        printf("%u\n", values[j]);
        break;
      }
    }
  }
  return 0;
}