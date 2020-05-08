#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int top;
    unsigned int length;
    int *array;
} Stack;

/**/
Stack *newStack(unsigned int length);
/**/
void freeStack(Stack *stack);
/* Returns 1 if empty else 0 */
int isStackEmpty(Stack *stack);
/* Pushes an element to the top if there is space. Returns 1 if the element was pushed else 0 */
int pushToStack(Stack *stack, int item);
/* Pops and returns the item on the top of the stack */
int popFromStack(Stack *stack);

int main(int amount, char** input) {
    const int length = 10;
    Stack *stack;
    /* Create items used for tests */
    int *items = (int*)calloc(length, sizeof(int));
    int i;
    for(i = 0; i < length; ++i) {
        items[i] = i;
    }

    /* Create the stack used for tests */
    stack = newStack(length);
    printf("Is the initial stack empty? %s\n", isStackEmpty(stack) ? "Yes" : "No");
    printf("Stack top is %i\n", stack->top);
    pushToStack(stack, items[0]);
    printf("Stack top is %i\n", stack->top);
    i = popFromStack(stack); /* Has to be on this line because parameters are calculated from "first <- last" and isStackEmpty is the last paramter */
    printf("Is the 0'th element from items pushed/popped? %i -> %s\n", i, isStackEmpty(stack) ? "Yes" : "No");
    printf("Stack top is %i\n", stack->top);

    for(i = 0; i < length; ++i) {
        pushToStack(stack, items[i]);
    }

    printf("Stack top is %i\n", stack->top);
    printf("Can an item be pushed to the supersaturated stack? %s\n", pushToStack(stack, -1) ? "Yes" : "No");
    printf("Stack top is %i\n", stack->top);

    return 0;
}

Stack *newStack(unsigned int length) {
    Stack *stack = malloc(sizeof(Stack));
    stack->top = -1;
    stack->length = length;
    stack->array = (int*)calloc(stack->length, sizeof(int));
    return stack;
}

void freeStack(Stack *stack) {
    free(stack->array);
    stack->array = NULL;
    free(stack);
    stack = NULL;
}

int isStackEmpty(Stack *stack) {
    return stack->top < 0;
}

int pushToStack(Stack *stack, int item) {
    /* Check overflow */
    if(stack->top == stack->length - 1) {
        return 0;
    }
    stack->top++;
    stack->array[stack->top] = item;
    return 1;
}

int popFromStack(Stack *stack) {
    /* Check underflow */
    if(isStackEmpty(stack) == 1) {
        return -1;
    }
    return stack->array[stack->top--];
}