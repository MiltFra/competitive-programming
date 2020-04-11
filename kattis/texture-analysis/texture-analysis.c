#include <stdio.h>

#define NOTEVEN 0
#define EVEN 1
#define END 2

int nextLineEven();
int nextLength();
int initLength();
void clearLine();
void output(int);

int no = 0;

int main() {
    int r;
    while ((r = nextLineEven()) != END) {
        output(r);
    }
    return 0;
}

void output(int v) {
    if (v == EVEN) {
        printf("%d EVEN\n", ++no);
    } else {
        printf("%d NOT EVEN\n", ++no);
    }
}

int nextLineEven() {
    int l = initLength();
    if (l == -1) {
        return END;
    }
    int m;
    while ((m = nextLength()) == l);
    if (m == -1) {
        return EVEN;
    }
    clearLine();
    return NOTEVEN;
}

int initLength() {
    int c = getchar();
    if (c != '*') {
        return -1;
    }
    int i = 0;
    while ((c = getchar()) == '.') {
        i++;
    } 
    if (i == 0 && c == '\n') {
        output(EVEN);
        return initLength();
    }
    return i;
}

void clearLine() {
    while (getchar() != '\n');
}

int nextLength() {
    int c, i;
    i = 0;
    while ((c = getchar()) == '.') {
        i++;
    }
    if (c != '*') {
        return -1;
    }
    return i; 
}