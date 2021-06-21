#ifndef _tstackh_
#define _tstackh_

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4
#define STACK_EMPTY -5
#define STACK_FULL -6

struct PontoStack
{
    int x;
    int y;
};

typedef struct PontoStack Ponto;
typedef struct Stack Stack;

Stack *stack_create(int size);
int stack_free(Stack *str);

int stack_push(Stack *str, Ponto p);
int stack_pop(Stack *str);
int stack_top(Stack *str, Ponto *p);

int stack_empty(Stack *str);
int stack_full(Stack *str);

int stack_print(Stack *str);
#endif