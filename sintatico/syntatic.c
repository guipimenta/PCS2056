#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/bool.h"
#include "../headers/tokenizer.h"
#include "../headers/syntatic.h"

STRUCTURED_AUTOMATA SUBMACHINE_LIST[MAXAUTOMATA] = {
	[SUBMACHINE_PROGRAM] = {
		SUBMACHINE_PROGRAM,
		Q0,
		{
			[Q0] = { { { RESERVED_WORD, "program"   }, FALSE, Q1, SUBMACHINE_NULL }, EOR_TRANSITION },
			[Q1] = { { { RESERVED_WORD, "begin"		}, FALSE, Q2, SUBMACHINE_NULL }, EOR_TRANSITION },
			[Q2] = { { { RESERVED_WORD, "def"		}, TRUE,  Q3, SUBMACHINE_DEF_FUNCTION }, EOR_TRANSITION },
			[Q3] = { { { RESERVED_WORD, "end"		}, FALSE,  Q0, SUBMACHINE_NULL}, EOR_TRANSITION },
		}
	},
	[SUBMACHINE_DEF_FUNCTION] = {
		SUBMACHINE_DEF_FUNCTION,
		Q0,
		{
			[Q0] = { { { RESERVED_WORD, "def" }, FALSE, Q1, SUBMACHINE_NULL }, EOR_TRANSITION },
			[Q1] = { { { IDENTIFIER, EMPTY_VALUE}, FALSE, Q2, SUBMACHINE_NULL }, EOR_TRANSITION }
		}
	}
};

char submachine_debug_names[256][256] = {
	[SUBMACHINE_PROGRAM] = "Automata Program",
	[SUBMACHINE_DEF_FUNCTION] = "Automata Definition Function"
};

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
	STRUCTURED_AUTOMATA *automata = &SUBMACHINE_LIST[SUBMACHINE_PROGRAM];

	Stack *stack;
	Stack_Init(&stack);

    while (!endOfProgram) {
        wasTokenFound = get_token(input_file, &token,  &endOfProgram);
        if (wasTokenFound) {
            // printf("%s\n", get_token_value(token.token_class, token.table_index));
          print_token(token);
		  run_automata(automata, token, &stack);
        }
    }

    fclose(input_file);
}

// Receaves a automata and a token
// Calculate next state
BOOL run_automata(STRUCTURED_AUTOMATA *automata, TOKEN token, Stack **stack) {
	int state = automata->current_state;
	for (int i = 0; automata->transitions[state][i].next_state != EOR; i++) {
		STRUCTURED_AUTOMATA_TRANSITION transition = automata->transitions[state][i];
		if (compare_token_values(transition.trigger, token)) {
			if (transition.is_submachine_transition == FALSE) {
				// this is a non-submachine transition
				#ifdef DEBUG
				printf("[DEBUG] Make transition from state: %d to %d \n\n\n", automata->current_state, transition.next_state);
				#endif
				automata->current_state = transition.next_state;
				return TRUE;
			} else {
				// this is a submachine transition
				sm_stack_pair pair;
				pair.sm = automata->automata_id;
				pair.state = transition.next_state;

				#ifdef DEBUG
				printf("[DEBUG] Pushed to stack: ");
				print_stack_pair(pair);
				printf("[DEBUG] Chaging to automata: %s\n\n\n", submachine_debug_names[transition.next_submachime]);
				#endif

				Stack_Push(pair, stack);

				automata = &SUBMACHINE_LIST[transition.next_submachime];
				run_automata(automata, token, stack);
				
				return TRUE;
			}
		}
	}
	// here, no transition was found
	// lets take a look at the stack
	if (Stack_Empty(*stack) == 0) {
		// Lets get back to the stacked automata
		sm_stack_pair pair = Stack_Pop(stack);
		automata = &SUBMACHINE_LIST[pair.sm];
		automata->current_state = pair.state;

		#ifdef DEBUG
		printf("[DEBUG] Pop from stack: ");
		print_stack_pair(pair);
		printf("[DEBUG] Changing to automata: %s\n", submachine_debug_names[pair.sm]);
		printf("[DEBUG] Going into state: %d\n\n", pair.state);
		#endif
	}
	// case it hits here
	// unespected token was found
	return FALSE;
}

// Used to compare two tokens
BOOL compare_token_values(STRUCTURED_AUTOMATA_TOKEN t1, TOKEN t2) {
	// some tokens can be compared only by class
	// others must be compared with class and value
	char *t2value = get_token_value(t2.token_class, t2.table_index);
	switch (t2.token_class)
	{
		case RESERVED_WORD:
			if (t2.token_class == t1.class 
					&& strcmp(t1.value, t2value) == 0)
				return TRUE;
			break;
		default:
			if (t2.token_class == t1.class)
				return TRUE;
			break;
	}
	return FALSE;
}

void print_stack_pair(sm_stack_pair pair) {
	printf("(%d,%d)\n", pair.sm, pair.state);
}