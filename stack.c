#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* CREDITS: From lab documentation on GitLab */
/* stack structure */
struct Stack {
    uint32_t top; // index of next empty slot
    uint32_t capacity; // max pushes
    uint32_t *items;
};

/* creates a stack and returns pointer to it */
Stack *stack_create(uint32_t capacity) {

    Stack *s = (Stack *) malloc(sizeof(Stack));

    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t)); // change to calloc??

        /* cant allocate memory. free stack */
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

/* deletes a stack (frees the memory) */
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL; // update pointer to stack (items unsusable since s null)
    }
    return;
}

/* returns size of the stack */
uint32_t stack_size(Stack *s) {
    if (!s)
        return 0;
    return s->top;
}

/* returns true if stack empty, else false */
bool stack_empty(Stack *s) {
    if (!s)
        return true; // no stack
    return s->top == 0; // if top is 0 then no elements
}

/* returns true if stack full, else false */
bool stack_full(Stack *s) {
    if (!s)
        return true;
    return s->top == s->capacity; // all indexes filled or not
}

/* pushes x on top of stack. returns true if push successful, else false */
bool stack_push(Stack *s, uint32_t x) {
    if (!s || stack_full(s))
        return false;
    s->items[s->top] = x; // make top element = x
    s->top++; // increment counter
    return true;
}

/* pops x off of stack. returns true if pop successful, else false. pops value in var pointed by x */
bool stack_pop(Stack *s, uint32_t *x) {
    if (!x || !s || stack_empty(s))
        return false;
    s->top--;
    *x = s->items[s->top]; // assign x top value.
    return true;
}

/* peeks top of stack. returns true if peek successful, else false. peeks value in var pointed by x */
bool stack_peek(Stack *s, uint32_t *x) {
    if (!x || !s || stack_empty(s))
        return false;
    *x = s->items[s->top - 1]; // assign x top value.
    return true;
}

/* copies stack at src to dst */
void stack_copy(Stack *dst, Stack *src) {
    if (!dst || !src)
        return;
    dst->top = src->top; // copy top
    for (uint32_t i = 0; i < stack_size(src); i++) {
        dst->items[i] = src->items[i]; // copy every item in stack
    }
    return;
}

/* CREDITS: from the lab document in the resources folder */
/* prints a stack to a file */
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    if (!s)
        return;

    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
