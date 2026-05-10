#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    // TODO: 在这里添加你的代码
    QueueNode * p = malloc(sizeof(QueueNode));
    p->tree_node = tree_node;
    p->next = q->front;
    if (q->front==NULL) q->rear = p;
    q->front = p;
}

TreeNode* dequeue(Queue *q) {
    // TODO: 在这里添加你的代码
    if (q->rear==NULL) return NULL;
    QueueNode * p = q->front;
    if (p==q->rear){
        TreeNode* tmp = p->tree_node;
        q->front = q->rear = NULL;
        free(p);
        return tmp;
    }
    while(p->next!=q->rear){
        p = p->next;
    }
    TreeNode* tmp = q->rear->tree_node;
    free(q->rear);
    q->rear = p;
    return tmp;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    // TODO: 在这里添加你的代码
    if (size<=0) return NULL;
    Queue* q = create_queue();
    TreeNode* node = malloc(sizeof(TreeNode));
    TreeNode* root = node;
    int idx = 0;
    node->val = level_order[idx];
    node->left = node->right = NULL;
    enqueue(q, node);
    while (!is_empty(q) && (idx < size)){
        node = dequeue(q);
        if ((idx+1)<size && level_order[idx+1]!=INT_MIN){
            TreeNode * left = malloc(sizeof(TreeNode));
            left->left = left->right = NULL;
            node->left = left;
            left->val = level_order[idx+1];
            enqueue(q, left);
        }
        if ((idx+2)<size && level_order[idx+2]!=INT_MIN){
            TreeNode * right = malloc(sizeof(TreeNode));
            right->left = right->right = NULL;
            node->right = right;
            right->val = level_order[idx+2];
            enqueue(q,right);
        }
        idx+=2;
    }
    free_queue(q);
    return root;
}

void preorder_traversal(TreeNode *root) {
    // TODO: 在这里添加你的代码
    if (root==NULL) return;
    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);

}

void preorder_traversal_iterative(TreeNode *root) {
    // TODO: 在这里添加你的代码
    if (root==NULL) return;
    TreeNode* stack[1000];
    int top = -1;
    stack[++top] = root;
    while(top>=0){
        TreeNode *node = stack[top--];
        printf("%d ", node->val);
        if (node->right)
            stack[++top] = node->right;
        if (node->left)
            stack[++top] = node->left;
    }
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
