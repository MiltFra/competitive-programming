#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int STACKSIZE = 1024;

void parseTerrain(char *T, int H, int W);
int neighbours(const char *T, int H, int W, char *visited, int r, int c, int *neighs);
int pathExists(const char *T, int H, int W, int r1, int c1, int r2, int c2);

void stackInit(int size);
void stackReset();
void stackPut(int r, int c);
void stackGet(int *r, int *c);

int setContains(const char *set, int value);
void setInsert(char *set, int value);
void setRemove(char *set, int value);
void setSubstract(char *a, const char *b, int len);
int shareSet(int W, int r1, int c1, int r2, int c2);

char *reachable(const char *T, int H, int W, int r0, int c0);
void init(const char *T, int H, int W);

char *out;
int outPos;
void output(char *str, int length) {
    strcpy(out+outPos, str);
    outPos += length;
}

int* stack;
int stackLen;
char** allSets;
int setCount;

int main() {
   int H, W;
    scanf("%d %d", &H, &W);
    char T[H*W];
    parseTerrain(T, H, W);
    init(T, H, W);
    int n, r1, c1, r2, c2;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &r1, &c1, &r2, &c2); 
        if (!shareSet(W, --r1, --c1, --r2, --c2)) {
            output("neither\n", 8);
            continue;
        }
        if (T[r1*W+c1] == '0') {
            output("binary\n", 7);
        } else {
            output("decimal\n", 8);
        }
    }
    out[outPos] = 0;
    printf("%s", out);
}

int shareSet(int W, int r1, int c1, int r2, int c2) {
    for (int i = 0; i < setCount; i++) {
        if (setContains(allSets[i], r1*W+c1) && setContains(allSets[i], r2*W+c2)) {
            return 1;
        }
    }
    return 0;
}

void init(const char *T, int H, int W) {
    out = (char*) malloc(8001*sizeof(char));
    outPos = 0;
    stackInit(H*W);
    char fullSet[H*W];
    memset(fullSet, 1, H*W);
    allSets = (char**) malloc(H*W*sizeof(char*));
    int n = 0;
    for (int i = 0; i < H*W; i++) {
        if (!setContains(fullSet, i)) {
            continue;
        }
        allSets[n] = reachable(T, H, W, i / W, i % W);
        setSubstract(fullSet, allSets[n], H*W);
        n++;
    }
    setCount = n;
}

char *reachable(const char *T, int H, int W, int r0, int c0) {
    char *res = (char*) malloc(H*W*sizeof(char));
    stackReset();
    stackPut(r0, c0);
    int ns[8];
    int n, r, c, nr, nc;
    while (stackLen > 0) {
        stackGet(&r, &c);
        setInsert(res, r*W+c);
        n = neighbours(T, H, W, res, r, c, ns);
        for (int i = 0; i < n; i++) {
            nr = ns[i*2];
            nc = ns[i*2+1];
            stackPut(nr, nc);
        }
    }
    return res;
}

void stackInit(int size) {
    stack = (int*) malloc(size*2*sizeof(int));
    stackLen = 0;
}

void stackReset() {
    stackLen = 0;
}

void stackPut(int r, int c) {
    stack[stackLen*2] = r;
    stack[(stackLen++)*2+1] = c;
}

void stackGet(int *r, int *c) {
    *r = stack[(--stackLen)*2];
    *c = stack[stackLen*2+1];
}

int neighbours(const char *T, int H, int W, char *visited, int r, int c, int *neighs) {
    int startV = T[r*W+c];
    int count = 0;
    unsigned int newC, newR;
    unsigned int index;
    newC = c;
    newR = r - 1;
    if (r > 0 && !visited[index = newR*W+newC] && T[index] == startV) {
        neighs[2*count] = newR;
        neighs[2*count+1] = newC;
        visited[index] = 1;
        count++;
    }
    newR = r + 1;
    if (newR < H && !visited[index = newR*W+newC] && T[index] == startV) {
        neighs[2*count] = newR;
        neighs[2*count+1] = newC;
        visited[index] = 1;
        count++;
    }
    newR = r;
    newC = c - 1;
    if (c > 0 && !visited[index = newR*W+newC]&& T[index] == startV) {
        neighs[2*count] = newR;
        neighs[2*count+1] = newC;
        visited[index] = 1;
        count++;
    }
    newC = c + 1;
    if (newC < W && !visited[index = newR*W+newC] && T[newR*W+newC] == startV) {
        neighs[2*count] = newR;
        neighs[2*count+1] = newC;
        visited[index] = 1;
        count++;
    }
    for (int i = 0; i < count; i++) {
    }
    return count;
}

void parseTerrain(char* T, int H, int W) {
    // Getting the first NL
    getchar();
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            T[i*W+j] = getchar();
        }
        // reading the NL
        getchar();
    }
}

int setContains(const char *set, int value) {
    return set[value];
}

void setInsert(char *set, int value) {
    set[value] = 1;
}

void setRemove(char *set, int value) {
    set[value] = 0;
}

void setSubstract(char *a, const char *b, int len) {
    for (int i = 0; i < len; i++) {
        if (b[i]) {
            a[i] = 0;
        }
    }
}
