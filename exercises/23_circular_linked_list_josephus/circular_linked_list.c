#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    // TODO: 在这里添加你的代码
    Node* head = malloc(sizeof(Node));
    head->id = 1;
    Node * p = NULL;
    Node * prev = head;
    for (int i=2;i<=n;i++){
        p = malloc(sizeof(Node));
        p->id = i;
        prev->next = p;
        prev = p;
    }
    p->next = head;
    return head;
}

void free_list(Node* head) {
    // TODO: 在这里添加你的代码
    if (head==NULL) return;
    Node * p = head->next;
    while (p!=NULL && p!=head){
        Node * tmp = p;
        p = p->next;
        free(tmp);
    }
    free(head);
}
