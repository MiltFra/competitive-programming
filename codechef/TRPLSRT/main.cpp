#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <deque>
#include <tuple>
#include <vector>
#define u32 unsigned int
#define u64 unsigned long int
#define i32 int
#define i64 long int

template<typename i>
inline void next_signed(i &number) {
  register int c;
  number = 0;
  do {
    c = getchar();
  } while (c == '\n' || c == '\r' || c == ' ');

  bool negative = c == '-';

  for (; (c > 47 && c < 58); c = getchar())
    number = number * 10 + c - 48;
  if (negative) {
    number *= -1;
  }
}

template<typename u>
inline void next_unsigned(u &number) {
  register int c;
  number = 0;
  do {
    c = getchar();
  } while (c == '\n' || c == '\r' || c == ' ');
  for (; (c > 47 && c < 58); c = getchar())
    number = number * 10 + c - 48;
}

inline void next_lower_letter(char &c) {
  do {
    c = getchar();
  } while (c < 97 || c > 122);
}

inline void next_upper_letter(char &c) {
  do {
    c = getchar();
  } while (c < 65 || c > 90);
}

u32 N, K, unsorted_count;
std::vector<bool> sorted;
std::vector<u32> P;
std::deque<u32> unsorted;
std::vector<std::tuple<u32, u32, u32>> swaps;

inline void swap(u32 a, u32 b, u32 c) {
  // if (a == b || a == c || b == c) {
  //  throw 0;
  //}
  // if (sorted.at(a) || sorted.at(b) || sorted.at(c)) {
  //  throw false;
  //}
  register u32 t = P.at(a);
  P.at(a)        = P.at(c);
  P.at(c)        = P.at(b);
  P.at(b)        = t;
}

inline void next_unsorted() {
  while (sorted.at(unsorted.front())) {
    unsorted.pop_front();
  }
}

inline void set_sorted(u32 x) {
  unsorted_count--;
  sorted.at(x) = true;
}

inline void solve(void) {
  register u32 a, b, c;
  for (u32 i = 0; i < K; i++) {
    if (unsorted_count < 3) {
      break;
    }
    while (sorted.at(unsorted.back())) {
      unsorted.pop_back();
    }
    a = unsorted.back();
    b = P.at(a);
    c = P.at(b);
    set_sorted(b);
    if (c == a) {
      next_unsorted();
      if (unsorted.front() == b) {
        unsorted.push_back(unsorted.front());
        unsorted.pop_front();
        next_unsorted();
      }
      c = unsorted.front();
    } else {
      set_sorted(c);
    }
    // fprintf(stderr, "unsorted: %u\n", unsorted);
    // fprintf(stderr, "a=%u, b=%u, c=%u\n", a + 1, b + 1, c + 1);
    // fprintf(
    //    stderr,
    //    "P(a)=%u, P(b)=%u, P(c)=%u\n",
    //    P.at(a) + 1,
    //    P.at(b) + 1,
    //    P.at(c) + 1);
    swap(a, b, c);
    if (P.at(a) == a) {
      set_sorted(a);
    }
    // fprintf(
    //    stderr,
    //    "P(a)=%u, P(b)=%u, P(c)=%u\n",
    //    P.at(a) + 1,
    //    P.at(b) + 1,
    //    P.at(c) + 1);
    swaps.push_back(std::make_tuple(a + 1, b + 1, c + 1));
  }
  if (unsorted_count == 0) {
    printf("%lu\n", swaps.size());
    std::for_each(
        swaps.begin(), swaps.end(), [](std::tuple<u32, u32, u32> swap) {
          printf(
              "%u %u %u\n",
              std::get<0>(swap),
              std::get<1>(swap),
              std::get<2>(swap));
        });
  } else {
    printf("-1\n");
  }
}

int main(void) {
  u32 T, p;
  next_unsigned(T);
  while (T--) {
    next_unsigned(N);
    next_unsigned(K);
    sorted.clear();
    P.clear();
    unsorted_count = 0;
    unsorted.clear();
    swaps.clear();
    for (int i = 0; i < N; i++) {
      next_unsigned(p);
      P.push_back(p - 1);
      sorted.push_back(P.back() == i);
      if (!sorted.back()) {
        unsorted_count++;
        unsorted.push_back(i);
      }
    }
    solve();
  }
}