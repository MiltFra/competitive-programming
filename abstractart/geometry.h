#ifndef H_GEOMETRY
#define H_GEOMETRY

// area: returns the area of a given polygon
double area(double* p);

// intersection: writes the polygons given by the intersections of two polygons
// into a given array; return the number of polygons found
int intersection(const double* p1, const double* p2, double** t);

// sharedArea: returns the sum of the areas of all the intersection of two
// polygons
double sharedArea(const double* p1, const double* p2);

int length(const double* p);

void coords(const double* p, int i, double* x, double* y);

// contains: returns whether a polygon contains a given point. If the point is
// on one of the edges of the polygon, it's not inside.
int contains(const double* p, double x, double y);

// boundary: writes the minimal axis-aligned triangle the polygon p fits into to
// t.
void boundary(const double* p, double* t);

// boundaryContains: returns whether the boundary of a given polygon p contains
// a given point (x,y). If the point is on one of the edges of the boundary,
// it's not inside.
int boundaryContains(const double* p, double x, double y);

int relOf(const double* l, double x, double y);

int onPerimeter(const double* p, double x, double y);

int onLine(double x1, double y1, double x2, double y2, double x3, double y3);

int onLS(double x, double y, double x1, double y1, double x2, double y2);
#endif