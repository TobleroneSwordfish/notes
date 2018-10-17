#include "list.h"
#include "stdlib.h"
#include "assert.h"

typedef struct node node;
struct node
{
    item value;
    node *back;
    node *next;
};

struct list
{
    node *next;
    node *back;
    node *start;
    node *end;
};

list *newList()
{
    list *newList = malloc(sizeof(list));
    //initialise the pointers to NULL to ensure that there is no accidental garbage memory access
    newList->next = NULL;
    newList->back = NULL;
    newList->start = NULL;
    newList->end = NULL;
    return newList;
}

void start(list *l)
{
    l->next = l->start;
    l->back = NULL;
}

void end(list *l)
{
    l->back = l->end;
    l->next = NULL;
}

bool atStart(list *l)
{
    return l->next == l->start;
}

bool atEnd(list *l)
{
    return l->back == l->end;
}

void forward(list *l)
{
    assert(!atEnd(l));
    node *currentNext = l->next;
    l->next = l->next->next;
    l->back = currentNext;
}

void backward(list *l)
{
    assert(!atStart(l));
    node *currentBack = l->back;
    l->back = l->back->back;
    l->next = currentBack;
}

void insertBefore(list *l, item x)
{
    bool isFirst = atStart(l);
    bool isLast = atEnd(l);
    node *newNode = malloc(sizeof(node));
    newNode->value = x;
    if (l->next != NULL)
    {
        l->next->back = newNode;
    }
    if (l->back != NULL)
    {
        l->back->next = newNode;
    }
    //these are actually fine, because they will just copy the NULL pointer
    newNode->back = l->back;
    newNode->next = l->next;
    //move the current position
    l->back = newNode;
    l->start = isFirst ? newNode : l->start; //you may ask why I used a ternary here. that is a very good question
    l->end = isLast ? newNode : l->end;
}

void insertAfter(list *l, item x)
{   
    bool isLast = atEnd(l);
    bool isFirst = atStart(l);
    node *newNode = malloc(sizeof(node));
    newNode->value = x;
    if (l->next != NULL)
    {
        l->next->back = newNode;
    }
    if (l->back != NULL)
    {
        l->back->next = newNode;
    }
    //these are actually fine, because they will just copy the NULL pointer
    newNode->back = l->back;
    newNode->next = l->next;
    //move the current position
    l->next = newNode;
    l->end = isLast ? newNode : l->end; //you may ask why I used a ternary here. that is a very good question
    l->start = isFirst ? newNode : l->start;
}

item getBefore(list *l)
{
    assert(!atStart(l));
    return l->back->value;
}

item getAfter(list *l)
{
    assert(!atEnd(l));
    return l->next->value;
}

void setBefore(list *l, item x)
{
    assert(!atStart(l));
    l->back->value = x;
}

void setAfter(list *l, item x)
{
    assert(!atEnd(l));
    l->next->value = x;
}

//so because this isn't in the header file it isn't exposed to external code, right? C almost has access modifiers!
void delete(list *l, node *doomed)
{
    bool isLast = (doomed == l->end);
    bool isFirst = (doomed == l->start);
    if (!isFirst)
    {
        doomed->back->next = doomed->next;
    }
    else
    {
        l->start = doomed->next;
    }
    if (!isLast)
    {
        doomed->next->back = doomed->back;
    }
    else
    {
        l->end = doomed->back;
    }
    free(doomed);
}

void deleteBefore(list *l)
{
    assert(!atStart(l));
    node *doomed = l->back;
    l->back = doomed->back;
    delete(l, doomed);
}

void deleteAfter(list *l)
{
    assert(!atEnd(l));
    node *doomed = l->next;
    l->next = doomed->next;
    delete(l, doomed);
}
//dia de los muertos
