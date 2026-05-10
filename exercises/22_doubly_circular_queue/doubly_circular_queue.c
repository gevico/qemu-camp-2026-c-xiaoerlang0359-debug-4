#include "doubly_circular_queue.h"

#include <stdlib.h>

// 头尾哨兵
static struct node tailsentinel;
static struct node headsentinel = {0, NULL, &tailsentinel};
static struct node tailsentinel = {0, &headsentinel, NULL};

static link head = &headsentinel;
static link tail = &tailsentinel;

link make_node(int data) {
    // TODO: 在这里添加你的代码
    link n = malloc(sizeof(struct node));
    n->data =data;
    return n;
}

void free_node(link p) {
    // TODO: 在这里添加你的代码
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
}

link search(int key) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    while (p!=tail){
        if (p->data == key){
            return p;
        }
        p = p->next;
    }
}

void insert(link p) {
    // TODO: 在这里添加你的代码
    p->next = head->next;
    p->prev = head;
    head->next->prev = p;
    head->next = p;
}

void delete(link p) {
    // TODO: 在这里添加你的代码
    free_node(p);
}

void traverse(void (*visit)(link)) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    while (p!=tail){
        visit(p);
        p = p->next;
    }
}

void destroy(void) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    while (p!=tail){
        link tmp = p;
        p = p->next;
        delete(p);
    }
}

int is_empty(void){
    return (head->next==tail);
}
