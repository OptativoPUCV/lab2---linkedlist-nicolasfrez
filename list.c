#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* lista= (List*)malloc(sizeof(List));
  lista->head=NULL;
  lista->tail=NULL;
  lista->current=NULL;
     return lista;
}

void * firstList(List * list) {
  if(list->head==NULL)
    return NULL;
  list->current->next=list->head;
  return list->head->data;
}

void * nextList(List * list) {
  if(list->current==NULL || list->current->next==NULL) return NULL;
  list->current=list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if(list->tail==NULL || list->current==NULL ) return NULL;
  list->current=list->tail;
  return list->tail->data;
}

void * prevList(List * list) {
  if(list->current==NULL || list->current->prev==NULL) return NULL;
  list->current=list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node *nuevo = createNode(data);
  if(list->head==NULL)
    list->head=nuevo;
  else
  {
    nuevo->next=list->head;
    list->head=nuevo;
  }
  list->current = nuevo;
  list->tail = list->current;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node *nuevo = createNode(data);
  if(list->head==NULL)
    pushFront(list, data);
  list->current->next = nuevo;
  nuevo->prev = list->current;
  list->tail=nuevo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
  if(list->head==NULL || list->current==NULL)
  {
    void *data = list->current->data;
    Node *temp = list->current;
      
    if (list->current->prev)
    {
      list->current->prev->next = list->current->next;
    }
    else
    {
      list->head = list->current->next;
      list->tail->next = NULL;
    }
    if(list->current->next)
    {
      list->current->next->prev = list->current->prev;
    }
    else
    {
      list->tail = list->current->prev;
    }
    list->current = list->current->next;
    free(temp);
    return data;
  }
  return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}