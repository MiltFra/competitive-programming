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

#define OCCURRENCES_LEN 256

void is_lapindrome(char *buffer) {
  uint_t occurences_left[OCCURRENCES_LEN], occurences_right[OCCURRENCES_LEN];
  char *left, *right;
  uint_t len = strlen(buffer);
  uint_t part_len = len / 2;
  for (uint_t i = 0; i < OCCURRENCES_LEN; i++) {
    occurences_left[i] = 0;
    occurences_right[i] = 0;
  }
  left = buffer;
  right = left + (len + 1) / 2;
  for (uint_t i = 0; i < part_len; i++) {
    occurences_left[*(left++)]++;
    occurences_right[*(right++)]++;
  }
  for (uint_t i = 0; i < OCCURRENCES_LEN; i++) {
    if (occurences_left[i] != occurences_right[i]) {
      printf("NO\n");
      return;
    }
  }
  printf("YES\n");
}


int main(void) {
  uint_t T;
  next_unsigned(&T);
  char buffer[1001];
  while (T--) {
    scanf("%s", &buffer);
    is_lapindrome(buffer);
  }
  return 0;
}