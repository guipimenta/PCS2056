#include <stdio.h>
#include "../headers/bool.h"
#include "../headers/tokenizer.h"

#define STACK_MAX 100

typedef enum {
    SUBMACHINE_1,
    SUBMACHINE_2,
    SUBMACHINE_COUNT
} sub_machine;

typedef struct sm_stack {
    sub_machine sm;
    int state;
    struct sm_stack *next;
} SubMachine_Stack;

void read_file(char* file_name) {

    FILE *input_file;
    input_file = fopen(file_name, "r");
    if (input_file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    TOKEN token;
    BOOL wasTokenFound = FALSE;
    BOOL endOfProgram = FALSE;

    while (!endOfProgram) {
        wasTokenFound = get_token(input_file, &token,  &endOfProgram);
        if (wasTokenFound) {
            print_token(token);
        }
    }

    fclose(input_file);
}
