#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100
#define MAX_PRODUCTIONS 100
#define MAX_INPUT_LEN 100

char **terminals;
int numTerminals = 0;

char **nonTerminals;
int numNonTerminals = 0;

char ***productions;
int numProductions = 0;

char ***ACTION;
int **GOTO;

void getGrammar();
void getInputString(char *input);
void printTableHeader();
void printParsingTable();
int getTerminalIndex(char *symbol);
int getNonTerminalIndex(char *symbol);
void constructParsingTable();
void parse(char *input);

void getGrammar() {
        printf("Enter the number of terminal symbols: ");
        scanf("%d", &numTerminals);
        getchar();

        terminals = (char **)malloc(numTerminals * sizeof(char *));
        if (terminals == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
        }

        printf("Enter terminal symbols (space-separated, e.g., id + * ( ) $):\n");
        for (int i = 0; i < numTerminals; i++) {
                terminals[i] = (char *)malloc(MAX_INPUT_LEN);
                if (terminals[i] == NULL) {
                        fprintf(stderr, "Memory allocation error\n");
                        exit(EXIT_FAILURE);
                }
                scanf("%s", terminals[i]);
        }

        printf("Enter the number of non-terminal symbols: ");
        scanf("%d", &numNonTerminals);
        getchar();

        nonTerminals = (char **)malloc(numNonTerminals * sizeof(char *));
        if (nonTerminals == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
        }

        printf("Enter non-terminal symbols (space-separated, e.g., E T F A B):\n");
        for (int i = 0; i < numNonTerminals; i++) {
                nonTerminals[i] = (char *)malloc(MAX_INPUT_LEN);
                if (nonTerminals[i] == NULL) {
                        fprintf(stderr, "Memory allocation error\n");
                        exit(EXIT_FAILURE);
                }
                scanf("%s", nonTerminals[i]);
        }

        printf("Enter the number of production rules: ");
        scanf("%d", &numProductions);
        getchar();

        productions = (char ***)malloc(numProductions * sizeof(char **));
        if (productions == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
        }

        for (int i = 0; i < numProductions; i++) {
                productions[i] = (char **)malloc(MAX_SYMBOLS * sizeof(char *));
                if (productions[i] == NULL) {
                        fprintf(stderr, "Memory allocation error\n");
                        exit(EXIT_FAILURE);
                }

                printf("Enter production %d (LHS -> RHS, space-separated):\n", i + 1);
                char line[MAX_INPUT_LEN];
                fgets(line, MAX_INPUT_LEN, stdin);
                line[strcspn(line, "\n")] = 0;

                char *lhs = strtok(line, " ");
                int lhsIndex = getNonTerminalIndex(lhs);
                if (lhsIndex == -1) {
                        nonTerminals[numNonTerminals++] = strdup(lhs);
                        lhsIndex = numNonTerminals - 1;
                }

                int j = 0;
                char *rhs = strtok(NULL, " ");
                while (rhs != NULL) {
                        productions[i][j] = strdup(rhs);
                        rhs = strtok(NULL, " ");
                        j++;
                }
                productions[i][j] = NULL;
        }
}

void getInputString(char *input) {
        printf("Enter the input string (use terminal symbols like 'id' for identifiers, and '$' to terminate):\n");
        fgets(input, MAX_INPUT_LEN, stdin);
        input[strcspn(input, "\n")] = 0;
}

void printTableHeader() {
        printf("\n+--------+");
        for (int i = 0; i < numTerminals; i++) {
                printf("--------+");
        }
        for (int i = 0; i < numNonTerminals; i++) {
                printf("--------+");
        }
        printf("\n| State  |");
        for (int i = 0; i < numTerminals; i++) {
                printf(" %-6s |", terminals[i]);
        }
        for (int i = 0; i < numNonTerminals; i++) {
                printf(" %-6s |", nonTerminals[i]);
        }
        printf("\n+--------+");
        for (int i = 0; i < numTerminals; i++) {
                printf("--------+");
        }
        for (int i = 0; i < numNonTerminals; i++) {
                printf("--------+");
        }
        printf("\n");
}

void printParsingTable() {
        printTableHeader();
        for (int i = 0; i < MAX_STATES; i++) {
                printf("| %-6d |", i);
                for (int j = 0; j < numTerminals + numNonTerminals; j++) {
                        if (ACTION[i][j] != NULL) {
                                printf(" %-6s |", ACTION[i][j]);
                        } else {
                                printf("        |");
                        }
                }
                printf("\n");
        }
        printf("+--------+");
        for (int i = 0; i < numTerminals; i++) {
                printf("--------+");
        }
        for (int i = 0; i < numNonTerminals; i++) {
                printf("--------+");
        }
        printf("\n");
}

int getTerminalIndex(char *symbol) {
        for (int i = 0; i < numTerminals; i++) {
                if (strcmp(symbol, terminals[i]) == 0) {
                        return i;
                }
        }
        return -1;
}

int getNonTerminalIndex(char *symbol) {
        for (int i = 0; i < numNonTerminals; i++) {
                if (strcmp(symbol, nonTerminals[i]) == 0) {
                        return i;
                }
        }
        return -1;
}

void constructParsingTable() {
        ACTION = (char ***)malloc(MAX_STATES * sizeof(char **));
        GOTO = (int **)malloc(MAX_STATES * sizeof(int *));
        for (int i = 0; i < MAX_STATES; i++) {
                ACTION[i] = (char **)malloc(MAX_SYMBOLS * sizeof(char *));
                GOTO[i] = (int *)malloc(MAX_SYMBOLS * sizeof(int));
                for (int j = 0; j < MAX_SYMBOLS; j++) {
                        ACTION[i][j] = NULL;
                        GOTO[i][j] = -1;
                }
        }

        ACTION[0][getTerminalIndex("id")] = "shift 1";
        ACTION[0][getTerminalIndex("(")] = "shift 2";
        ACTION[1][getTerminalIndex("$")] = "accept";

        ACTION[2][getTerminalIndex("id")] = "shift 1";
        ACTION[2][getTerminalIndex("(")] = "shift 2";
        ACTION[3][getTerminalIndex("+")] = "reduce E->T";
        ACTION[4][getTerminalIndex("+")] = "reduce E->E+T";

        GOTO[0][getNonTerminalIndex("E")] = 3;
        GOTO[3][getNonTerminalIndex("T")] = 4;
}

void parse(char *input) {
        int inputIndex = 0;
        int state = 0;
        int stack[MAX_INPUT_LEN];
        int top = -1;

        stack[++top] = 0;

        strcat(input, "$");

        while (input[inputIndex] != '$') {
                char symbol[10];
                snprintf(symbol, sizeof(symbol), "%c", input[inputIndex]);

                int terminalIndex = getTerminalIndex(&input[inputIndex]);
                if (terminalIndex == -1) {
                        printf("Error: Invalid symbol in input string\n");
                        return;
                }

                char *action = ACTION[state][terminalIndex];
                if (action == NULL) {
                        printf("Error: Invalid action at state %d for symbol %s\n", state, symbol);
                        return;
                }

                printf("Action: %s on symbol '%s'\n", action, symbol);
                if (strncmp(action, "shift", 5) == 0) {
                        state = action[6] - '0';
                        stack[++top] = state;
                        inputIndex++;
                } else if (strncmp(action, "reduce", 6) == 0) {
                        printf("Reduce: %s\n", action);
                        top -= 2;
                        state = stack[top];
                } else if (strncmp(action, "accept", 6) == 0) {
                        printf("Input accepted!\n");
                        return;
                }
        }
}

int main() {
        getGrammar();
        constructParsingTable();

        char input[MAX_INPUT_LEN];
        getInputString(input);

        printParsingTable();
        parse(input);

        for (int i = 0; i < numTerminals; i++) {
                free(terminals[i]);
        }
        free(terminals);

        for (int i = 0; i < numNonTerminals; i++) {
                free(nonTerminals[i]);
        }
        free(nonTerminals);

        for (int i = 0; i < numProductions; i++) {
                for (int j = 0; productions[i][j] != NULL; j++) {
                        free(productions[i][j]);
                }
                free(productions[i]);
        }
        free(productions);

        for (int i = 0; i < MAX_STATES; i++) {
                free(ACTION[i]);
                free(GOTO[i]);
        }
        free(ACTION);
        free(GOTO);

        return 0;
}




