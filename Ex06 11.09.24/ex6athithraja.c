#include<stdio.h>
#include<string.h>
void gettable(int tt[][3],int statesCount)
{
        int i= 0;
        printf("\nEnter the transition \n                0 1\n");
        for(i = 0 ;i < statesCount ; i++)
        {
                printf("State %d: \t",tt[i][0]);
                scanf(" %d%d",&tt[i][1],&tt[i][2]);
        }
}
void check(int tt[][3] ,int start, int final, char input[])
{
        int state = start ;
        for(int i = 0; i < strlen(input) ; i++)
        {
                int in = input[i]-'0';
                if(in == 0 || in == 1)
                        state = tt[state][in+1];
        }
        if(state == final)
                printf("String Accepted.\n");
        else
                printf("String Rejected.\n");
}
void main()
{
        int stateCount = 0;
        int finalState = 0;
        int startState = 0;
        printf("Enter the no.of States: ");
        scanf("%d",&stateCount);
        int TT[stateCount][3];
        int states[stateCount];
        int i = 0;
        for(i = 0 ;i < stateCount ; i++)

        {
                printf("Enter the State-%d: ",i);
                scanf("%d",&states[i]);
                TT[i][0] = states[i];
        }
        printf("Enter START STATE and FINAL STATE: ");
        scanf("%d%d",&startState,&finalState);
        gettable(TT,stateCount);
        int continueFlag = 0;
        do
        {
                char input[1024];
                printf("Enter the string: ");
                scanf("%s",input);
                check(TT,startState,finalState,input);
                printf("\nENTER 1 TO CONTINUE, ELSE PRESS 0: ");
                if (scanf(" %d",&continueFlag)!=1){
                        printf("Invalid input Exitintg...");
                        break;
                }
                while(getchar()!='\n');
        }while(continueFlag == 1);
}