#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAX 10
#define MAX_PROD_LENGTH 100
void followfirst(char, int, int);
void follow(char c);
void findfirst(char, int, int);
int count, n = 0;
char calc_first[MAX][MAX_PROD_LENGTH];
char calc_follow[MAX][MAX_PROD_LENGTH];
int m = 0;
char production[MAX][MAX_PROD_LENGTH];
char f[MAX], first[MAX];
int k;
char ck;
int e;
int main() {
    int i, j;
    char c;
    printf("Enter the number of production rules: ");
    scanf("%d", &count);
    for (i = 0; i < count; i++) {
        printf("Enter Production %d: ", i + 1);
        scanf("%s", production[i]);
    }
    char done[MAX] = {0};
    int ptr = -1;
    for (k = 0; k < count; k++) {
        for (j = 0; j < MAX_PROD_LENGTH; j++) {
            calc_first[k][j] = '!';
        }
    }
    for (k = 0; k < count; k++) {
        c = production[k][0];
        int exists = 0;
        for (j = 0; j <= ptr; j++)
            if (c == done[j])
                exists = 1;
        if (exists)
            continue;
        findfirst(c, 0, 0);
        ptr += 1;
        done[ptr] = c;
        printf("\nFIRST(%c): { ", c);
        for (i = 0; i < n; i++) {
            printf("%c ,", first[i]);
            calc_first[ptr][i + 1] = first[i];
        }
        calc_first[ptr][n + 1] = '!';
        printf("}\n");
        n = 0;
    }
    char donee[MAX] = {0};
    ptr = -1;
    for (k = 0; k < count; k++) {
        for (j = 0; j < MAX_PROD_LENGTH; j++) {
            calc_follow[k][j] = '!';
        }
    }
    for (e = 0; e < count; e++) {
        ck = production[e][0];
        int exists = 0;
        for (j = 0; j <= ptr; j++)
            if (ck == donee[j])
                exists = 1;
        if (exists)
            continue;
        follow(ck);
        ptr += 1;
        donee[ptr] = ck;
        printf("FOLLOW(%c): { ", ck);
        for (i = 0; i < m; i++) {
            printf("%c ,", f[i]);
            calc_follow[ptr][i + 1] = f[i];
        }
        calc_follow[ptr][m + 1] = '!';
        printf("}\n\n");
        m = 0;
    }
    printf("\nPredictive Parse Table:\n");
    for (i = 0; i < count; i++) {
        char lhs = production[i][0];
        char rhs[MAX_PROD_LENGTH];
        strcpy(rhs, &production[i][2]);
        for (j = 1; calc_first[i][j] != '!'; j++) {
            char terminal = calc_first[i][j];
            if (terminal != '#') {
                printf("M[%c, %c] = %s\n", lhs, terminal, production[i]);
            } else {
                for (int k = 1; calc_follow[i][k] != '!'; k++) {
                    printf("M[%c, %c] = %s\n", lhs, calc_follow[i][k], production[i]);
                }
            }
        }
    }
    return 0;
}
void follow(char c) {
    if (production[0][0] == c)
        f[m++] = '$';
    for (int i = 0; i < count; i++) {
        for (int j = 2; production[i][j] != '\0'; j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0') {
                    followfirst(production[i][j + 1], i, j + 2);
                }
                if (production[i][j + 1] == '\0' && c != production[i][0]) {
                    follow(production[i][0]);
                }
            }
        }
    }
}
void findfirst(char c, int q1, int q2) {
    if (!isupper(c)) {
        first[n++] = c;
        return;
    }
    for (int j = 0; j < count; j++) {
        if (production[j][0] == c) {
            if (production[j][2] == '#') {
                if (production[q1][q2] == '\0')
                    first[n++] = '#';
                else
                    findfirst(production[q1][q2], q1, q2 + 1);
            } else if (!isupper(production[j][2])) {
                first[n++] = production[j][2];
            } else {
                findfirst(production[j][2], j, 3);
            }
        }
    }
}
void followfirst(char c, int c1, int c2) {
    if (!isupper(c)) {
        f[m++] = c;
    } else {
        int i = 0;
        while (calc_first[i][0] != '\0' && calc_first[i][0] != c)
            i++;
        if (calc_first[i][0] == c) {
            for (int j = 1; calc_first[i][j] != '!'; j++) {
                if (calc_first[i][j] != '#')
                    f[m++] = calc_first[i][j];
                else if (production[c1][c2] == '\0')
                    follow(production[c1][0]);
                else
                    followfirst(production[c1][c2], c1, c2 + 1);
            }
        }
    }
}
