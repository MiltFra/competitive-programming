#include <stdio.h>
#include <math.h>

#define BUFLENGTH 1000

int getLength(char* str);
void processDataSet(int W, int N);
int getP(int cw, int cmax);
int getWidth(int t, int P);

int processed = 0;

int main() {
    int w, n;
    while (1) {
        scanf("%d %d", &w, &n);
        if (w == 0) {
            break;
        }
        processDataSet(w, n);
    }
    return 0;
}

void processDataSet(int W, int N) {
    int inputs[2*N];
    char buf[BUFLENGTH];
    int occ;
    int cmax = 0;
    for (int i = 0; i < N; i++) {
        scanf("%s %d", buf, &occ);
        inputs[2*i] = getLength(buf);
        inputs[2*i+1] = occ;
        if (occ > cmax) {
            cmax = occ;
        }
    }
    int totalh = 0;
    int linew = W;
    int maxh = 0;
    int wordw, P;
    for (int i = 0; i < N; i++) {
        P = getP(inputs[2*i+1], cmax);
        wordw = getWidth(inputs[2*i], P);
        if (linew + wordw + 10> W) {
            totalh += maxh;
            maxh = P;
            linew = wordw;
        } else {
            linew += wordw + 10;
            if (P > maxh) {
                maxh = P;
            } 
        }
    }
    totalh += maxh;
    printf("CLOUD %d: %d\n", ++processed, totalh); 
}

int getLength(char* str) {
    for (int i = 0; i < BUFLENGTH; i++) {
        if (str[i] == '\0') {
            return i;
        }
    }
    return BUFLENGTH;
}

int getP(int cw, int cmax) {
  return (int) 8 + ceil((double) 40*(cw - 4) / (double) (cmax - 4));
}

int getWidth(int t, int P) {
    return (int) ceil(9.0/16.0 * (double) (t * P));
}