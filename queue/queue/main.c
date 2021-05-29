#include <stdio.h>
#include <stdlib.h>

#define MAX 5
typedef int element;
typedef struct {
    element data[MAX];
    int front, back;
} QueueType;

//오류함수
void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

//큐 초기화 함수
void init(QueueType *q) {
    q->front = q->back = 0;
}

//공백 상태 확인 함수
int is_empty(QueueType *q) {
    //back과 front가 같을 경우
    return (q->front == q->back);
}

//포화 상태 확인 함수
int is_full(QueueType *q) {
    return ((q->back + 1) % MAX == q->front);
}

//삽입 함수
void push(QueueType *q, element item) {
    if(is_full(q))
        error("queue is full");
    q->back = (q->back + 1) % MAX;
    q->data[q->back] = item;
}

//삭제 함수
element pop(QueueType *q) {
    if(is_empty(q))
        error("Queue is empty");
    q->front = (q->front + 1) % MAX;
    return q->data[q->front];
}

//front를 반환하는 함수
element peek(QueueType *q) {
    if(is_empty(q))
        error("Queue is empty");
    return (q->data[(q->front + 1) % MAX]);
}

