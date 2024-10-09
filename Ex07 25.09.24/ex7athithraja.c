#include <stdio.h>
#include <stdbool.h>
#define MAX_STATES 10
#define MAX_ALPHABET 2
typedef struct {
    int transition[MAX_STATES][MAX_ALPHABET];
    bool final[MAX_STATES];
    int num_states;
} DFA;
void print_minimized_dfa(DFA *dfa, int new_states[], int num_new_states) {
    printf("\nAfter Minimization- DFA looks like: \n");
    printf("No.of States: %d\n", num_new_states);
    for (int i = 0; i < dfa->num_states; i++) {
        if (new_states[i] == i) {
            printf("STATE -%d: ", i);
            printf("Transitions => ");
            for (int j = 0; j < MAX_ALPHABET; j++) {
                printf("on '%d' => %d ", j, new_states[dfa->transition[i][j]]);
            }
            if (dfa->final[i])
                printf("(END STATE)");
            printf("\n");
        }
    }
}
bool distinguishable(int state1, int state2, bool distinguish[MAX_STATES][MAX_STATES], DFA *dfa) {
    for (int i = 0; i < MAX_ALPHABET; i++) {
        int next_state1 = dfa->transition[state1][i];
        int next_state2 = dfa->transition[state2][i];
        if (distinguish[next_state1][next_state2] || distinguish[next_state2][next_state1])
            return true;
    }
    return false;
}
void minimize_dfa(DFA *dfa) {
    bool distinguish[MAX_STATES][MAX_STATES] = {false};
    for (int i = 0; i < dfa->num_states; i++) {
        for (int j = 0; j < i; j++) {
            if ((dfa->final[i] && !dfa->final[j]) || (!dfa->final[i] && dfa->final[j])) {
                distinguish[i][j] = true;
            }
        }
    }
    bool changed;
    do {
        changed = false;
        for (int i = 0; i < dfa->num_states; i++) {
            for (int j = 0; j < i; j++) {
                if (!distinguish[i][j] && distinguishable(i, j, distinguish, dfa)) {
                    distinguish[i][j] = true;
                    changed = true;
                }
            }
        }
    } while (changed);
    int new_states[MAX_STATES];
    for (int i = 0; i < dfa->num_states; i++) {
        new_states[i] = i;
    }
    for (int i = 0; i < dfa->num_states; i++) {
        for (int j = 0; j < i; j++) {
            if (!distinguish[i][j]) {
                new_states[i] = new_states[j];
            }
        }
    }
    int num_new_states = 0;
    for (int i = 0; i < dfa->num_states; i++) {
        if (new_states[i] == i) {
            num_new_states++;
        }
    }
    print_minimized_dfa(dfa, new_states, num_new_states);
}
int main() {
    int cf=0;
    do{
    DFA dfa;
    printf("Enter the no.of States: ");
    scanf("%d", &dfa.num_states);
    printf("Enter the Table:\n");
    for (int i = 0; i < dfa.num_states; i++) {
        for (int j = 0; j < MAX_ALPHABET; j++) {
            printf("Transition from state-%d on '%d': ", i, j);
            scanf("%d", &dfa.transition[i][j]);
        }
    }
    printf("Enter the Final States (hint:Press 1 for Final else 0):\n");
    for (int i = 0; i < dfa.num_states; i++) {
        printf("Is STATE-%d a Final State? ", i);
        scanf("%d", (int*)&dfa.final[i]);
    }
    minimize_dfa(&dfa);
    printf("\nENTER 1 TO CONTINUE ELSE PRESS 0: ");
    if(scanf(" %d",&cf)!=1){
        printf("Invalid input Exiting...");
        break;
    }
    while(getchar()!='\n');
    }while(cf==1);
    return 0;
}