#include "geometry.h"

#include <stdio.h>

double area(double* p) {
  int l;
  if ((l = length(p)) < 3) {
    return 0;
  }
  double result = 0;
  double x1, y1, x2, y2;
  for (int i = 0; i < l - 1; i++) {
    coords(p, i, &x1, &y1);
    coords(p, i + 1, &x2, &y2);
    result += x1 * y2 + x2 * y1;
  }
  return result / 2;
}

int contains(const double* p, double x, double y) {
  if (!boundaryContains(p, x, y)) {
    return 0;
  }
  if (onPerimeter(p, x, y)) {
    return 0;
  }
  int c = 0;
  double* b;
  boundary(p, b);
  double l[5] = {2, x, y, x, b[2] - 1};
  // TODO.
}

int doLSIntersect(const double* l1, const double* l2) {
  return !relOf(l1, l2[1], l2[2]) || !relOf(l1, l2[3], l2[4]) ||
         !relOf(l2, l1[1], l1[2]) || !relOf(l2, l1[3], l1[4]);
}

void toLine(const double* l, double* a, double* b, double* c) {
  *a = l[2] - l[4];
  *b = l[1] - l[3];
  *c = l[3] * l[2] - l[1] * l[4];
}

int relOf(const double* l, double x, double y) {
  double a, b, c;
  toLine(l, &a, &b, &c);
  if (b == 0) {
    if (x > c / a) {
      return 1;
    }
    if (x < c / a) {
      return -1;
    }
    return 0;
  }
  double lY = (c - a * x) / b;
  if (lY > y) {
    return 1;
  }
  if (lY < y) {
    return -1;
  }
  return 0;
}

int onPerimeter(const double* p, double x, double y) {
  int l = length(p);
  double x1, y1;
  for (int i = 0; i < l; i++) {
    coords(p, i, &x1, &y1);
    if (x == x1 && y == y1) {
      return 1;
    }
  }
  // x1, y1 are now the coordinates of the last point in p
  double x2, y2;
  for (int i = 0; i < l; i++) {
    coords(p, i, &x2, &y2);
    if (onLS(x, y, x1, y1, x2, y2)) {
      return 1;
    }
    x1 = x2, y1 = y2;
  }
  return 0;
}

int onLS(double x, double y, double x1, double y1, double x2, double y2) {
  if (!onLine(x, y, x1, y1, x2, y2)) {
    return 0;
  }
  double v;
  if (x1 > x2) {
    v = x1, x1 = x2, x2 = v;
  }
  if (y1 > y2) {
    v = y1, y1 = y2, y2 = v;
  }
  return x >= x1 && x <= x2 && y >= y1 && y <= y2;
}

int onLine(double x1, double y1, double x2, double y2, double x3, double y3) {
  if (x1 == x2 && x1 == x3) {
    return 1;
  }
  if (y1 == y2 && y1 == y3) {
    return 1;
  }
  return (x1 - x2) / (y1 - y2) == (x1 - x3) / (y1 - y2);
}

int boundaryContains(const double* p, double x, double y) {
  double b[5];
  boundary(p, b);
  return x >= b[1] && x <= b[3] && y >= b[2] && y <= b[4];
}

void boundary(const double* p, double* t) {
  t[0] = 2;
  // Initial values for min and max
  coords(p, 0, &t[1], &t[2]);
  coords(p, 0, &t[3], &t[4]);
  int l = length(p);
  double x, y;
  for (int i = 0; i < l; i++) {
    coords(p, i, &x, &y);
    if (x < t[1]) {
      t[1] = x;
    } else if (x > t[3]) {
      t[3] = x;
    }
    if (y < t[2]) {
      t[2] = y;
    } else if (y > t[4]) {
      t[4] = y;
    }
  }
}

int intersection(const double* p1, const double* p2, double** t) {
  // TODO.
}

double sharedArea(const double* p1, const double* p2) {
  double* inss[length(p1) / 2 * length(p2) / 2];
  double total = 0;
  int n = intersection(p1, p2, inss);
  for (int i = 0; i < n; i++) {
    total += area(inss[i]);
  }
  return total;
}

int length(const double* p) {
  return (int)p[0];
}

void coords(const double* p, int i, double* x, double* y) {
  *x = p[1 + 2 * i];
  *y = p[2 + 2 * i];
}
