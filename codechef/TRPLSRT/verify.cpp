#include <stdio.h>

#include <random>
#include <vector>

#define u32 unsigned int
#define i32 int

template<typename i>
void next_signed(i &number) {
  register int c;
  number = 0;
  do {
    c = getchar();
  } while (c == '\n' || c == '\r' || c == ' ');
  bool negative = false;
  if (c == '-') {
    negative = true;
    c        = getchar();
  }

  for (; (c > 47 && c < 58); c = getchar())
    number = number * 10 + c - 48;
  if (negative) {
    number *= -1;
  }
}

template<typename u>
void next_unsigned(u &number) {
  register int c;
  number = 0;
  do {
    c = getchar();
  } while (c == '\n' || c == '\r' || c == ' ');
  for (; (c > 47 && c < 58); c = getchar())
    number = number * 10 + c - 48;
}

void next_lower_letter(char &c) {
  do {
    c = getchar();
  } while (c < 97 || c > 122);
}

void next_upper_letter(char &c) {
  do {
    c = getchar();
  } while (c < 65 || c > 90);
}

u32 N, K;
std::vector<u32> P;
void swap_unchecked(const u32 a, const u32 b, const u32 c) {
  register u32 t = P.at(a);
  P.at(a)        = P.at(c);
  P.at(c)        = P.at(b);
  P.at(b)        = t;
}

int main(void) {
  u32 T, p, a, b, c;
  i32 S;
  next_unsigned(T);
  while (T--) {
    next_unsigned(N);
    next_unsigned(K);
    P.clear();
    for (int i = 0; i < N; i++) {
      next_unsigned(p);
      P.push_back(p - 1);
    }
    next_signed(S);
    for (i32 i = 0; i < S; i++) {
      next_unsigned(a);
      next_unsigned(b);
      next_unsigned(c);
      swap_unchecked(a - 1, b - 1, c - 1);
    }
    bool sorted = true;
    for (u32 i = 0; i < P.size(); i++) {
      if (P.at(i) != i) {
        sorted = false;
        break;
      }
    }
    if (sorted || S < 0) {
      printf("Verified output.\n");
    } else {
      printf("Output could not be verified.\n");
    }
  }
}