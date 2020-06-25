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

void skip_line() {
  int_t c;
  do {
    c = getchar();
  } while (c != '\n' && c != EOF);
}

char is_indian() {
  char c;
  next_upper_letter(&c);
  skip_line();
  return c == 'I';
}

#define CONTEST_WIN 0
#define TOP_CONTRIBUTOR 1
#define BUG_FOUND 2
#define CONTEST_HOSTED 3

int_t parse_activity(char *str) {
  switch (str[0]) {
  case 'C':
    if (str[8] == 'W') {
      return CONTEST_WIN;
    }
    return CONTEST_HOSTED;
  case 'T':
    return TOP_CONTRIBUTOR;
  case 'B':
    return BUG_FOUND;
  default:
    return -1;
  }
}

int main(void) {
  uint_t T, A, X, L;
  char O, str[1024];
  next_unsigned(&T);
  while (T--) {
    next_unsigned(&A);
    O = is_indian();
    L = 0;
    while (A--) {
      scanf("%s", &str);
      switch (parse_activity(str)) {
      case CONTEST_WIN:
        next_unsigned(&X);
        L += 300 + (X > 20 ? 0 : 20 - X);
        break;
      case TOP_CONTRIBUTOR:
        L += 300;
        break;
      case BUG_FOUND:
        next_unsigned(&X);
        L += X;
        break;
      case CONTEST_HOSTED:
        L += 50;
        break;
      default:
        break;
      }
    }
    if (O) {
      printf("%u\n", L / 200);
    } else {
      printf("%u\n", L / 400);
    }
  }
}