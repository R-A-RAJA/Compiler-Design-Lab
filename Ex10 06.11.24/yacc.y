%{
#include <stdio.h>
#include <stdlib.h>

int flag = 0;
int yylex(void);              // Declaration of yylex function
void yyerror(const char *s);  // Declaration of yyerror function
%}
%token NUMBER

%left '+' '-'
%left '*' '/' '%'
%right '(' ')'

/* Rule Section */
%%
ArithmeticExpression:
    E {
        printf("\nResult = %d\n", $1);
        return 0;
    }
;

E:
    E '+' E { $$ = $1 + $3; }
    | E '-' E { $$ = $1 - $3; }
    | E '*' E { $$ = $1 * $3; }
    | E '/' E {
        if ($3 == 0) {
            yyerror("Error: Division by zero");
            $$ = 0;
            flag = 1;
        } else {
            $$ = $1 / $3;
        }
    }
    | E '%' E { $$ = $1 % $3; }
    | '(' E ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
;

%%
/* Driver code */
int main() {
    printf("Enter any arithmetic expression:\n");
    yyparse();
    if (flag == 0) {
        printf("Entered arithmetic expression is valid.\n");
    }
    return 0;
}

void yyerror(const char *s) {
    printf("Error: %s\n", s);
    flag = 1;
}
