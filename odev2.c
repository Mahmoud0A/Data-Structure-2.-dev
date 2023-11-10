#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;
//initialize the stack
void initialize(Stack* stack) {
    stack->top = -1;
}
//push an item onto the stack
void push(Stack* stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack->data[++stack->top] = item;
}
//pop an item from the stack
char pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return stack->data[stack->top--];
}
//check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}
// Function to check parentheses errors in the file
int checkParentheses(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 0;
    }

    Stack stack;
    initialize(&stack);

    char ch;
    int line = 1;
    // Read the file character by character
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line++;
        } else if (ch == '(') {
        	// Push an opening parenthesis onto the stack
            push(&stack, ch);
        } else if (ch == ')') {
        	// Check for a matching opening parenthesis on the stack and pop it
            if (isEmpty(&stack)) {
                printf("Error: Unmatched closing parenthesis at line %d\n", line);
                fclose(file);
                return 0;
            }
            pop(&stack);
        }
    }

    fclose(file);
    
	// Check for unmatched opening parentheses
    if (!isEmpty(&stack)) {
        printf("Error: Unmatched opening parenthesis\n");
        return 0;
    }

    return 1;
}

int main() {
    const char* filename = "odev2.txt";
    if (checkParentheses(filename)) {
        printf("No parentheses errors found.\n");
    }

    return 0;
}

