#include <stdio.h>

const int N = 1000;

void snake(int i, int j);

int main() {
    srand(time(NULL));
    int r;
    printf("%d %d\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            snake(i, j);
        }
        putchar('\n');
    }
    printf("%d\n", N);
    for (int i = 0; i < N; i++)
        printf("%d %d %d %d\n", 1, 1, 1, N);

}

void snake(int i, int j) {
    if (j % 2 == 0) {
            putchar('0');
    } else if (i == N-1 && j % 4 == 1) {
        putchar('0');
    } else if (i == 0 && j % 4 == 3) {
        putchar('0');
    } else {
        putchar('1');
    }
}