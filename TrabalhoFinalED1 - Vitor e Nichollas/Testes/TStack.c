#include <stdio.h>
#include <stdlib.h>
#include "TStack.h"

// é possível criar a lista
struct Stack
{
    Ponto *p;
    int size;
    int MAX;
};


Stack *stack_create(int size)
{
    Stack *str;
    str = malloc(sizeof(str));
    str->p = malloc(sizeof(Ponto) * size);

    if(str != NULL || str->p != NULL){
        str->size=0;
        str->MAX = size;
    }

    return str;
}

int stack_free(Stack *str)
{
    if (str == NULL)
        return INVALID_NULL_POINTER;

    //free(str->str);
    free(str);
    
    return SUCCESS;
}

int stack_push(Stack *str, Ponto p)
{
    if (str == NULL)
        return INVALID_NULL_POINTER;
    
    if(stack_full(str))
        return STACK_FULL;

    str->p[str->size] = p;
    str->size++;

    return SUCCESS;
}

int stack_pop(Stack *str)
{
    if (str == NULL)
        return INVALID_NULL_POINTER;
    
    if(stack_empty(str))
        return STACK_EMPTY;

    str->size--;

    return SUCCESS;
}

int stack_top(Stack *str, Ponto *p)
{
    if (str == NULL)
        return INVALID_NULL_POINTER;

    *p = str->p[str->size-1];

    return SUCCESS;
}

int stack_empty(Stack *str)
{
    if (str == NULL)
        return INVALID_NULL_POINTER;

    if(str->size==0) return 1;
    else return 0;
}

int stack_full(Stack *str)
{
    if (str == NULL)
        return INVALID_NULL_POINTER;
    
    if(str->size==str->MAX) return 1;
    else return 0;
}

/*int stack_print(Stack *str)
{
    if (str == NULL)
        return INVALID_NULL_POINTER;
    
    for (int i = 0; i < str->size; i++)
    {
        printf("%c",str->str[i]);
    }

    return SUCCESS;
}*/