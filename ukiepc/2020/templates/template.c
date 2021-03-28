#define DEBUG
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
// IO Utils
//------------------------------------------------------------------------------

#ifdef DEBUG
#define LOG(FMT, ...) fprintf(stderr, FMT, ##__VA_ARGS__)
#else
#define LOG(FMT, ...)
#endif

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
// Sorting and comparisons
//------------------------------------------------------------------------------

int cmp_signed(const void *a, const void *b) {
  return (*(isize *)a - *(isize *)b);
}

int cmp_unsigned(const void *a, const void *b) {
  return (*(usize *)a - *(usize *)b);
}

int min_arg(const usize N, const void *arr, const usize size,
            __compar_fn_t cmp) {
  const void *end = arr + (N * size);
  const void *min = arr;
  for (const void *p = arr + size; p != end; p += size) {
    if (cmp(min, p) > 0) {
      min = p;
    }
  }
  return (min - arr) / size;
}

usize count(const void *arr, const usize n, const usize size, const void *ref) {
  usize total = 0;
  const void *end = arr + (n * size);
  for (const void *p = arr; p != end; p += size) {
    if (!memcmp(ref, p, size)) {
      ++total;
    }
  }
  return total;
}

//------------------------------------------------------------------------------
// Solution
//------------------------------------------------------------------------------

isize main(void) {
  usize T;
  next_unsigned(&T);
  while (T--) {
    
  }
}