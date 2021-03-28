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

#define MAX 360000

void normalise(usize N, usize *arr, usize k) {
  LOG("Normalising with seed %u\n", k);
  usize oldarr[N];
  memcpy(oldarr, arr, N * sizeof(usize));
  for (usize i = 0; i < N; i++) {
    arr[i + k] = (oldarr[i] + MAX - oldarr[k]) % MAX;
  }
}

void read_positions(usize N, usize *arr) {
  LOG("  Loading values\n");
  for (usize i = 0; i < N; i++) {
    next_unsigned(arr + i);
  }
  LOG("  Sorting values\n");
  qsort(arr, N, sizeof(usize), cmp_unsigned);
}

void diffs(usize *arr, usize *darr, usize len) {
  LOG("Calculating differences\n");
  darr[0] = MAX - (arr[len - 1] - arr[0]);
  for (usize i = 1; i < len; i++) {
    darr[i] = arr[i] - arr[i - 1];
  }
}

void log_usigned(usize *arr, usize len) {
  for (usize i = 0; i < len; i++) {
    LOG("%u ", arr[i]);
  }
  LOG("\n");
}

isize main(void) {
  usize N;
  next_unsigned(&N);
  usize *A, *B, *dA, *dB;
  A = malloc(N * sizeof(usize));
  dA = malloc(N * sizeof(usize));
  B = malloc(N * sizeof(usize));
  dB = malloc(N * sizeof(usize));

  LOG("Reading positions A\n");
  read_positions(N, A);
  log_usigned(A, N);
  LOG("Reading positions B\n");
  read_positions(N, B);
  log_usigned(B, N);

  diffs(A, dA, N);
  diffs(B, dB, N);

  usize k = min_arg(N, dA, sizeof(usize), cmp_unsigned);
  normalise(N, A, k);
  log_usigned(A, N);

  usize *p, num_ks, *temp_B, min;
  temp_B = malloc(N * sizeof(usize));
  min = dA[k];
  num_ks = count(dB, N, sizeof(usize), &min);
  LOG("Found min (%u) %u times\n", min, num_ks);
  p = dB;
  log_usigned(dB, N);
  for (usize i = 0; i < num_ks; i++) {
    memcpy(temp_B, B, N);
    while (*p != min) {
      LOG("  Found %u, Required %u\n", *p, min);
      p++;
    }
    LOG("  Checking %lu\n", p - dB);
    normalise(N, temp_B, p - dB);
    log_usigned(A, N);
    log_usigned(temp_B, N);
    char eq = 1;
    for (usize j = 0; j < N; j++) {
      if (A[j] != B[j]) {
        eq = 0;
        break;
      }
    }
    if (eq) {
      printf("possible\n");
      exit(0);
    }
    p++;
  }
  printf("impossible\n");
  return 0;
}