#include <iostream>
#include <stdlib.h>
#define LIST_SIZE 10000
#include <stdio.h>

typedef struct list {
    struct list* next;
    int item;
} list;

void insert(list** l, int x) {
    list* p = (list*)malloc(sizeof(list));
    p->item = x;
    p->next = *l;
    *l = p;
}

void reverse(list** l) {
    list *cur, *prev, *next;
    //daca primul sau al doilea element sunt nule
    if (!l || !(*l))
    {
        return;
    }

    cur = *l;
    next = NULL;
    prev = NULL;

    while (cur) 
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    *l = prev;
}

int main()
{
  list** l;
  l = (list**)malloc(sizeof(list));
  insert(l, 6); 
  insert(l, 5);  
  insert(l, 4); 
  insert(l, 3);  
  insert(l, 2); 
  insert(l, 1);

  printf("%d\n", (*l)->item);
  printf("%d\n", (*l)->next->item);
  printf("%d\n", (*l)->next->next->item);
  printf("%d\n", (*l)->next->next->next->item); 
  printf("%d\n", (*l)->next->next->next->next->item); 
  printf("%d\n", (*l)->next->next->next->next->next->item);
  printf("Dupa avem :\n");
  reverse(l);
  printf("%d\n", (*l)->item);
  printf("%d\n", (*l)->next->item);
  printf("%d\n", (*l)->next->next->item);
  printf("%d\n", (*l)->next->next->next->item);
  printf("%d\n", (*l)->next->next->next->next->item);
  printf("%d\n", (*l)->next->next->next->next->next->item);
}
