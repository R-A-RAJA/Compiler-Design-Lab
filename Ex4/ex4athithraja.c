#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

const char *keywords[] = {"int", "float", "if", "else", "while", "return", "for", "void", "break", "continue","char",
                          "get","getchar","sizeof","do","long","double","longint","not","is","null","and","or","getch",
                          "printf","scanf","fgets"};
const char *arithmetic_ops[] = {"+", "-", "*", "/", "%", "++", "--"};
const char *relational_ops[]={">","<","<=",">=","==","===","!=","="};

int is_keyword(const char *word) {
        for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
                if (strcmp(word, keywords[i]) == 0) {
                        return 1;
                }
        }
        return 0;
}
int is_arithmetic_operation(const char *word) {
        for (int i = 0; i < sizeof(arithmetic_ops) / sizeof(arithmetic_ops[0]); i++) {
                if (strcmp(word, arithmetic_ops[i]) == 0) {
                        return 1;
                }
        }
        return 0;
}
int is_relational_operator(const char *word){
        for(int i=0; i < sizeof(relational_ops)/sizeof(relational_ops[0]); i++){
                if(strcmp(word, relational_ops[i]) ==0){
                        return 1;
                }
        }
        return 0;
}
int is_number(const char *word) {
        for (int i = 0; word[i] != '\0'; i++) {
                if (!isdigit(word[i])) {
                        return 0;
                }
        }
        return 1;
}
int is_identifier(const char *word) {
        if (!isalpha(word[0]) && word[0] != '_') {
                return 0;
        }
        for (int i = 1; word[i] != '\0'; i++) {
                if (!isalnum(word[i]) && word[i] != '_') {
                        return 0;
                }
        }
        return 1;
}
void classify_words(const char *input) {
        char words[MAX_WORDS][MAX_WORD_LENGTH];
                 int word_count = 0;
        char temp[MAX_WORD_LENGTH];
        int temp_index = 0;
        for (int i = 0; input[i] != '\0'; i++) {
                if (isspace(input[i]) || strchr("+-*/%=();,", input[i]) != NULL) {
                        if (temp_index > 0) {
                                temp[temp_index] = '\0';
                                strncpy(words[word_count++], temp, MAX_WORD_LENGTH);
                                temp_index = 0;
                        }
                        if (strchr("+-*/%=();,", input[i]) != NULL) {
                                temp[0] = input[i];
                                temp[1] = '\0';
                                strncpy(words[word_count++], temp, MAX_WORD_LENGTH);
                        }
                } else {
                        temp[temp_index++] = input[i];
                }
        }
        if (temp_index > 0) {
                temp[temp_index] = '\0';
                strncpy(words[word_count++], temp, MAX_WORD_LENGTH);
        }
        void l(){
                printf("--------------------------------------------------------------\n");
        }
        l();
        printf("|                         Symbol Table:                      |\n");
        l();
        printf("|        SYMBOL      |     TYPE     |           NAME         |\n");
        l();
        for (int i = 0; i < word_count; i++) {

                if (is_keyword(words[i])) {
                        printf("|         %s        |       0      |         Keyword        |\n", words[i]);
                } else if (is_number(words[i])) {
                        printf("|          %s         |       2      |         Constant       |\n", words[i]);
                } else if (is_arithmetic_operation(words[i])) {
                        printf("|          %s         |       3      |   Arithmatic Operator  |\n", words[i]);
                } else if (is_relational_operator(words[i])){
                        printf("|          %s         |       4      |   Relational Operator  |\n", words[i]);
                }else if ((strcmp(words[i], ";") == 0)||(strcmp(words[i], ",") == 0)) {
                        printf("|          %s         |       5      |      Special symbol    |\n", words[i]);
                } else if (isdigit(words[i][0]) && ((words[i][1] >= 'a' && words[i][1] <= 'z') || (words[i][1] >= 'A' && words[i][1] <= 'Z'))) {
                        printf("|          %s         |       -      |         Invalid       |\n", words[i]);
                } else if (is_identifier(words[i])) {
                        printf("|          %s         |       1      |        Identifier      |\n", words[i]);
                } else {
                        printf("|          %s         |       6      |          Others        |\n", words[i]);
                }
                l();
        }
}

int main() {
        int continueFlag=0;
                do{
                        char input[256];
                        printf("Enter a string: ");
                        fgets(input, sizeof(input), stdin);
                        input[strcspn(input, "\n")] = 0;
                        classify_words(input);
                        printf("Enter 1 to continue, else press 0: ");
                        if(scanf("%d",&continueFlag)!=1){
                                printf("Invalid input Exiting...\n");
                                break;
                        }
                        while(getchar()!='\n');
                }while(continueFlag==1);
        return 0;
}