typedef struct {
    char *data;
    int top;
} CharStack;

// Initializes top of stack to -1
// which signals that the stack is empty
CharStack char_stk_init(char *arr) {
    CharStack s = { arr, -1 };
    return s;
}

// Pushes char onto stack
void char_stk_push(CharStack *stack, char ch) {
    stack->top++;
    stack->data[stack->top] = ch;
}

// Pops topmost value from the stack
// Returns '\0' if empty
char char_stk_pop(CharStack *stack) {
    if (stack->top == -1) 
        return '\0';
    
    char val = stack->data[stack->top];
    stack->top--;
    return val;
}

// Returns topmost value from the stack
// without popping it
// Returns '\0' if empty
char char_stk_peek(CharStack *stack) {
    if (stack->top == -1)
        return '\0';
    return stack->data[stack->top];
}



