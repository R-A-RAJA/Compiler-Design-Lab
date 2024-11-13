#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 100
#define MAX_TEMP_VARS 100

typedef struct {
        char result[MAX_INPUT_LEN];
        char arg1[MAX_INPUT_LEN];
        char op[MAX_INPUT_LEN];
        char arg2[MAX_INPUT_LEN];
} TAC;

TAC tac[MAX_TEMP_VARS];
int tempVarCount = 0;

void generateTAC(char *expr);
void printTAC();

int main() {
        char expr[MAX_INPUT_LEN];
        printf("Enter an arithmetic expression (e.g., a = b + c * d): ");
        fgets(expr, MAX_INPUT_LEN, stdin);
        expr[strcspn(expr, "\n")] = 0;

        generateTAC(expr);
        printTAC();

        return 0;
}

void generateTAC(char *expr) {
        char *token;
        char tempVar[MAX_INPUT_LEN];
        char stack[MAX_TEMP_VARS][MAX_INPUT_LEN];
        int top = -1;

        token = strtok(expr, " ");
        while (token != NULL) {
                if (strcmp(token, "=") == 0 || strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
                                strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
                        strcpy(tac[tempVarCount].op, token);
                        strcpy(tac[tempVarCount].arg1, stack[top--]);
                        token = strtok(NULL, " ");
                        strcpy(tac[tempVarCount].arg2, token);
                        sprintf(tempVar, "t%d", tempVarCount);
                        strcpy(tac[tempVarCount].result, tempVar);
                        strcpy(stack[++top], tempVar);
                        tempVarCount++;
                } else {
                        strcpy(stack[++top], token);
                }
                token = strtok(NULL, " ");
        }

        strcpy(tac[tempVarCount].op, "=");
        strcpy(tac[tempVarCount].arg1, stack[top--]);
        strcpy(tac[tempVarCount].arg2, "");
        strcpy(tac[tempVarCount].result, stack[top--]);
        tempVarCount++;
}

void printTAC() {
        for (int i = 0; i < tempVarCount; i++) {
                if (strcmp(tac[i].op, "=") == 0) {
                        printf("%s = %s\n", tac[i].result, tac[i].arg1);
                } else {
                        printf("%s = %s %s %s\n", tac[i].result, tac[i].arg1, tac[i].op, tac[i].arg2);
                }
        }
}