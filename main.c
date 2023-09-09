#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "CharStack.c"
#include "IntStack.c"

#define MAX_SIZE 1024
#define MAX_NUM_LEN 10

bool is_operator(char ch) {
  switch (ch) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '^':
      return true;
    default:
      return false;
  }
}

// Returns precedence of an operator
// as an int. Higher value means greater
// precedence. 
int precedence(char op) {
  switch (op) {
    case '+':
    case '-':
      return 1;

    case '*':
    case '/':
    case '%':
      return 2;

    case '^':
      return 3;

    case '(':
    default:
      return 0;
  }
}


// Converts an infix expression to a postfix one for easier evaluation
// Assumes that the input expression isnt malformed
// len is the size of the infix string
// The length of the postfix string should be double that of len of the infix string
// A space is added after each token in the resulting infix string
void infix_to_postfix(char *infix_str, char *postfix_str, size_t len) {
  char buffer[len];
  CharStack stack = char_stk_init(buffer);

  size_t i = 0;
  size_t j = 0;
  while (i < len) {
    char ch = infix_str[i];
    // check if it is an operand char (digit)
    if (ch >= 48 && ch <= 57) {
      // keeps looping to capture multiple digits
      while (infix_str[i] >= 48 && infix_str[i] <= 57) {
        postfix_str[j++] = infix_str[i++];
      }
      postfix_str[j++] = ' ';
      continue;
    }

    // check if it is an operator char
    // pop until it can placed in the correct precedence order
    else if (is_operator(ch)) {
      while (precedence(char_stk_peek(&stack)) >= precedence(ch)) {
        postfix_str[j++] = char_stk_pop(&stack);
        postfix_str[j++] = ' ';
      }
      char_stk_push(&stack, ch);
    }

    // check if it is an opening parentheses
    else if (ch == '(') {
      char_stk_push(&stack, ch);
    }

    // check if it is a closing parentheses
    // pop until a matching opening parentheses
    // is found and then discard them both
    else if (ch == ')') {
      while (char_stk_peek(&stack) != '(') {
        postfix_str[j++] = char_stk_pop(&stack);
        postfix_str[j++] = ' ';
      }
      char_stk_pop(&stack);
    }
    i++;
  }

  // empty out the stack
  while (char_stk_peek(&stack) != '\0') {
    postfix_str[j++] = char_stk_pop(&stack);
    postfix_str[j++] = ' ';
  }
  postfix_str[j] = '\0';
}

int eval(int a, int b, char op) {
  switch (op) {
    case '+':
      return a + b;
    case '-':
    return a - b;
    case '*':
      return a * b;
    case '/':
      return a / b;
    case '%':
      return a % b;
    case '^':
      return pow(a, b);
    default:
      return 0;
  }
}

// Evaluates a postfix expression and returns the result
int evaluate_expression(char *str, size_t len) {
  int result = 0;
  int buffer[len];
  IntStack stack = int_stk_init(buffer);
  size_t i = 0;
  while (i < len) {
    // converting the char digit to int
    if (str[i] >= 48 && str[i] <= 57) {
      char num[MAX_NUM_LEN];
      size_t j = 0;
      while (str[i] != ' ') {
        num[j++] = str[i++];
      }
      num[j] = '\0';
      int_stk_push(&stack, atoi(num));
    }
    else if (is_operator(str[i])) {
      // popping top two operands and 
      // performing the required operations
      int b = int_stk_pop(&stack);
      int a = int_stk_pop(&stack);
      result = eval(a, b, str[i]);
      int_stk_push(&stack, result);
    }
    i++;
  }
  return int_stk_pop(&stack);
}



int main(int argc, char** argv) {
  char *program = argv[0];
  char *expression = argv[1];
  
  printf("%s\n", expression);

  size_t size = strlen(expression);
  size_t postfix_size = 2 * size;
  char postfix_str[postfix_size];
  infix_to_postfix(expression, postfix_str, size);
  printf("%s\n", postfix_str);
  int x = evaluate_expression(postfix_str, strlen(postfix_str));
  printf("x = %i\n", x);

  return 0;
}
