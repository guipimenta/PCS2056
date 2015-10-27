#include <stdio.h>
#include <stdlib.h>
#include "../headers/bool.h"
#include "../headers/tokenizer.h"
#include "../headers/syntatic.h"

typedef enum {
	SUBMACHINE_PROGRAM_ID,
	SUBMACHINE_2,
	SUBMACHINE_COUNT
} sub_machine;

STRUCTURED_AUTOMATA SUBMACHINE_LIST[] = {
	[SUBMACHINE_PROGRAM_ID] = {
		Q0,
		{
			[Q0] = { { RESERVED_WORD, "program" }, FALSE, Q1 },
			[Q1] = { { RESERVED_WORD, "begin" }, FALSE, Q2 }
		}
	}
};





typedef struct {
  sub_machine sm;
  int state;
} sm_stack_pair;

typedef struct stack {
  sm_stack_pair sm_pair;
  struct stack *next;
} node;

node * Stack_Get_node(sm_stack_pair sm_pair);
void Stack_Init(node **top);
void Stack_Push(sm_stack_pair sm_pair, node **top);
void Stack_Display(node **head);
sm_stack_pair Stack_Pop(node **top);
int Stack_Empty(node *temp);

void Stack_Init(node **top) {
  *top = NULL;
}

void Stack_Push(sm_stack_pair sm_pair, node **top) {
  node *New;
  node * Stack_Get_node(sm_stack_pair);
  New = Stack_Get_node(sm_pair);
  New->next = *top;
  *top = New;
}

node * Stack_Get_node(sm_stack_pair sm_pair) {
  node * temp;
  temp = (node *) malloc(sizeof(node));
  if (temp == NULL)
    printf("\nMemory Cannot be allocated");
  temp->sm_pair = sm_pair;
  temp->next = NULL;
  return (temp);
}

int Stack_Empty(node *temp) {
  if (temp == NULL)
    return 1;
  else
    return 0;
}

sm_stack_pair Stack_Pop(node **top) {
  sm_stack_pair sm_pair;
  node *temp;
  sm_pair = (*top)->sm_pair;
  temp = *top;
  *top = (*top)->next;
  free(temp);
  return sm_pair;
}

void Stack_Display(node **head) {
  node *temp;
  temp = *head;
  if (Stack_Empty(temp))
    printf("\nThe stack is empty!");
  else {
    while (temp != NULL) {
      printf("%d\n", temp->sm_pair.state);
      temp = temp->next;
    }
  }
}

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
	//STRUCTURED_AUTOMATA current = sub_machine_list[SUBMACHINE_PROGRAM];


    while (!endOfProgram) {
        wasTokenFound = get_token(input_file, &token,  &endOfProgram);
        if (wasTokenFound) {
            // printf("%s\n", get_token_value(token.token_class, token.table_index));
          print_token(token);
        }
    }

    fclose(input_file);
}

void run_automata(STRUCTURED_AUTOMATA automata, TOKEN token) {
	
}
