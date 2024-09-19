#include<stdio.h>
#include<string.h>
int main(){
        char n;
        do{
                char s;
                //char n;
                printf("Enter a value: ");
                scanf(" %c",&s);

                if (s>='a' && s<='z'){
                        printf("Entered value %c is Small letter\n",s);
                }
                else if(s>='A' && s<='Z'){
                        printf("Entered value %c is Capital letter\n",s);
                }
                else if(s>='0' && s<='9'){
                        printf("Entered value %c is a Number\n",s);
                }
                else if(s=='+'||s=='-'||s=='/'||s=='%'||s=='*'){
                        printf("Entered value %c is a Arithematic Operator\n",s);
                }
                else if(s=='<'||s=='>'||s=='='){
                        printf("Entered value %c is a Relational Operator\n",s);
                }
                else{
                        printf("Entered value %c is Special Symbols\n",s);
                }


                //printf("Entered value: %c\n",s);

                printf("Enter y to continue: ");
                scanf(" %c",&n);

        }while(n=='y');
        return 0;
}