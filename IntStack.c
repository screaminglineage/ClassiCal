typedef struct {
    int *data;
    size_t top;
} IntStack;

// Initializes top of stack to -1
// which signals that the stack is empty
IntStack int_stk_init(int *arr) {
    IntStack s = { arr, -1 };
    return s;
}

// Pushes char onto stack
void int_stk_push(IntStack *stack, int num) {
    stack->top++;
    stack->data[stack->top] = num;
}

// Pops topmost value from the stack
// Returns '\0' if empty
int int_stk_pop(IntStack *stack) {
    if (stack->top == -1) 
        return 0;
    
    int val = stack->data[stack->top];
    stack->top--;
    return val;
}

// Returns topmost value from the stack
// without popping it
// Returns '\0' if empty
int int_stk_peek(IntStack *stack) {
    if (stack->top == -1)
        return 0;
    return stack->data[stack->top];
}

