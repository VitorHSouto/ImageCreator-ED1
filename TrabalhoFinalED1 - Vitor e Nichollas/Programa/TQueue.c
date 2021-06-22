#include <stdlib.h>
#include <stdio.h>
#include "TQueue.h"

typedef struct list_node list_node;

struct list_node
{
    ponto data;
    list_node *next;
};

struct TQueue
{
    list_node *head;
};

TQueue *queue_create()
{
    TQueue* list;
    list = malloc(sizeof(TQueue));
    if(list!=NULL)
        list->head=NULL;
    
    return list;
}

int queue_free(TQueue* list)
{
    if (list == NULL)
        return INVALID_NULL_POINTER;

    list_node *aux;

    aux = list->head;
    while (aux != NULL)
    {
        list->head = aux->next;
        free(aux);
        aux = list->head;
    }

    free(list);
    return SUCCESS;
}

int queue_push(TQueue* list, ponto p)
{
    if(list==NULL)
        return INVALID_NULL_POINTER;

    list_node *node;
    node = malloc(sizeof(list_node));
    if(node==NULL)
        return OUT_OF_MEMORY;
    node->data = p;
    node->next = NULL;

    if (list->head == NULL) // a lista está vazia
    { 
        list->head = node;
    }
    else // a lista tem pelo menos um nó
    { 
        list_node *aux;
        aux = list->head;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = node;
    }

    return SUCCESS;
}

int queue_pop(TQueue* list)
{
    if(list==NULL)
        return INVALID_NULL_POINTER;

    if(list->head==NULL || list->head->next==NULL)
    {
        list->head = NULL;
        return SUCCESS;
    }

    list_node *aux;
    aux = list->head;

    list->head = aux->next;
    free(aux);

    return SUCCESS;
}

ponto* queue_pop_top(TQueue* list);

int queue_top(TQueue* list, ponto *p)
{
    if(list==NULL)
        return INVALID_NULL_POINTER;

    *p = list->head->data;
    return SUCCESS;
}

int queue_empty(TQueue* list)
{
    if(list==NULL)
        return INVALID_NULL_POINTER;

    if(list->head==NULL) return 1;
    else return 0;
}