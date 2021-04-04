//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------
// Types
//------------------------------------------------------------------------------

#define u32 unsigned
#define u64 unsigned long long
#define i32 int
#define i64 long long

#define isize i32
#define usize u32

//------------------------------------------------------------------------------
// Utils
//------------------------------------------------------------------------------

void next_signed(isize *number) {
  register isize c;
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

void next_unsigned(usize *number) {
  register isize c;
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

//------------------------------------------------------------------------------
// Solution
//------------------------------------------------------------------------------

isize main(void) {
  usize x = 0;
  while (getchar() == 'a') {
    x++;
  }
  while (getchar() != '\n')
    ;
  usize y = 0;
  while (getchar() == 'a') {
    y++;
  }
  if (x >= y) {
    printf("go\n");
  } else {
    printf("no\n");
  }
}