#include <stdio.h>
#include <string.h>
#include <ctype.h>
void identify(char name[]) {
        if (strcmp(name, "int") == 0 || strcmp(name, "float") == 0 || strcmp(name, "else") == 0 ||strcmp(name, "if") == 0 || strcmp(name, "elseif") == 0 || strcmp(name, "char") == 0|| strcmp(name, "long") == 0|| strcmp(name, "break") == 0|| strcmp(name, "continue") == 0|| strcmp(name, "do") == 0|| strcmp(name, "while") == 0|| strcmp(name, "fgets") == 0|| strcmp(name, "double") == 0|| strcmp(name, "printf") == 0|| strcmp(name, "scanf") == 0|| strcmp(name, "sizeof") == 0|| strcmp(name, "getchar") == 0|| strcmp(name, "void") == 0|| strcmp(name, "longint") == 0|| strcmp(name, "switch") == 0|| strcmp(name, "try") == 0|| strcmp(name, "catch") == 0){
                printf("Keyword: %s\n", name);
        }
        else if (((name[0]>='a' && name[1]<='z')||(name[0]>='A' && name[0]<='Z'))&& (name[1]=='+'||name[1]=='-')){
                printf("Invalid : %s\n", name);

        }
        else if (strcmp(name, "name") == 0 || strcmp(name, "a") == 0 || strcmp(name, "b") == 0|| (name[0]>='a' && name[0]<='z')|| (name[0]>='A' && name[0]<='Z')&&(name[1]!='=')&&(name[1]!='+')) {
                printf("Identifier: %s\n", name);
        }
        else if (strcmp(name, "=") == 0||strcmp(name, ">") == 0||strcmp(name, "<") == 0||strcmp(name, "==") == 0||strcmp(name, "!=") == 0) {
                printf("Relational Operator: %s\n", name);
        }
        else if (strcmp(name, "+") == 0||strcmp(name, "-") == 0||strcmp(name, "/") == 0||strcmp(name, "%") == 0||strcmp(name, "*") == 0) {
                printf("Arithematic Operator: %s\n", name);
        }
        else if (isdigit(name[0]) &&  !((name[1]>='a' && name[1]<='z')||(name[1]>='A' && name[1]<='Z'))) {
                printf("Constant value: %s\n", name);
        }
        else if (isdigit(name[0])&&(((name[1]>='a' && name[1]<='z')||(name[1]>='A' && name[1]<='Z')||(name[1]=='+' && name[1]<='-')))) {
                printf("Invalid Identifier: %s\n", name);
        }
        else if (name[0] == ';') {
                printf("Special Character: %s\n", name);
        }
        else{
                printf("Invalid: %s\n",name);
        }
}

int main() {
        int continueFlag = 0;

        do {
                char input[100] = {0};
                char name[20] = {0};
                printf("Enter the string: ");
                fgets(input, sizeof(input), stdin);
                size_t length = strlen(input);
                if (length > 0 && input[length - 1] == '\n') {
                        input[length - 1] = '\0';
                }
                char* word = strtok(input, " ");
                //word = strtok(word, "+");
                //word = strtok(word, "-");
                //word = strtok(word, "=");
                identify(word);
                //while (word != NULL) {
                //      identify(word);
                //      word = strtok(NULL, " ");
                //}
                printf("Enter 1 to continue, else press 0: ");
                if (scanf("%d", &continueFlag) != 1) {
                        printf("Invalid input. Exiting...\n");
                        break;
                }
                while (getchar() != '\n');
        } while (continueFlag == 1);
        return 0;
}