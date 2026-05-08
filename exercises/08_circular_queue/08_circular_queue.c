#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

void init_queue(Queue * q, int n){
    for (int i=0;i<n;i++)
        q->data[i].id = i+1;
    q->head = 0;
    q->tail = n -1;
    q->count = n;
}

bool enqueue(Queue * q, People p){
    if (q->count == MAX_PEOPLE)
        return false;
    if (q->tail == (MAX_PEOPLE-1)) 
        q->tail = 0;
    else
        q->tail += 1;
    q->data[q->tail] = p;
    q->count++;
    return true;
}

People dequeue(Queue * q){
    People p;
    p.id = 0;
    if (q->count == 0)
        return p;
    p = q->data[q->head];
    if (q->head == (MAX_PEOPLE-1))
        q->head = 0;
    else
        q->head += 1;
    q->count--;
    return p;
}

bool is_empty(Queue *q){
    return (q->count==0);
}

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    // TODO: 在这里添加你的代码
    init_queue(&q, total_people);
    while (q.count>1){
        for (int i=1;i<report_interval;i++){
            People p = dequeue(&q);
            if (!enqueue(&q, p))
                return -1;
        }
        People out = dequeue(&q);
        printf("淘汰: %d\n", out.id);
    }
    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}