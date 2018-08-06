#include <iostream>
#define LIST_SIZE 10000

typedef struct Node{
    Node* next;
    int item;
} node;

int main()
{
   node* l = (node*)malloc(LIST_SIZE*sizeof(node*));
   
   
}
