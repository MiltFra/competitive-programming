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

char encode(char c, char s) {
  switch (c) {
  case 'n':
    return 0x10 + s;
  case 'e':
    return 0x20 + s;
  case 'w':
    return 0x30 + s;
  case 's':
    return 0x40 + s;
  default:
    exit(1);
  }
}

void read_map(char *map, usize len) {
  char d;
  usize s;
  for (usize i = 0; i < len; i++) {
    d = getchar();
    if (d == '?') {
      map[i] = 0;
      getchar();
    } else {
      next_unsigned(&s);
      map[i] = encode(d, (char)s);
    }
  }
}

isize main(void) {
  usize m, n;
  next_unsigned(&m);
  next_unsigned(&n);
  char *map1 = malloc(m * sizeof(char));
  char *map2 = malloc(n * sizeof(char));
  read_map(map1, m);
  read_map(map2, n);
  register char matching, x, y;
  register usize total;
  total = 0;
  for (usize i = 0; i <= m - n; i++) {
    matching = 1;
    for (usize j = 0; j < n; j++) {
      x = map1[i + j];
      y = map2[j];
      if (x && y && x != y) {
        matching = 0;
        break;
      }
    }
    total += matching;
  }
  printf("%u\n", total);
}