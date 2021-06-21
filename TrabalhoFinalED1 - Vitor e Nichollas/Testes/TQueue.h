#ifndef _TQueueh_
#define _TQueueh_

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4

struct Ponto
{
    int x;
    int y;
};

typedef struct TQueue TQueue;
typedef struct Ponto ponto;

TQueue *queue_create();
int queue_free(TQueue* list);

int queue_push(TQueue* list, ponto p);
int queue_pop(TQueue* list);
ponto* queue_pop_top(TQueue* list);
int queue_top(TQueue* list, ponto *p);

int queue_empty(TQueue* list);

#endif