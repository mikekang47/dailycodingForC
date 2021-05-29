#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
typedef int element;
element stack[MAX_SIZE];
int top = -1;

//공백 상태인지 확인
int is_empty(void) {
    return (top == -1);
}

//포화 상태인지 확인
int is_full(void) {
    return (top == (MAX_SIZE - 1));
}

//push(삽입)함수
void push(element item) {
    if(is_full()) {
        fprintf(stderr, "error(stack full)");
        return;
    } else {
        stack[++top] = item;
    }
}

//pop(삭제)함수
element pop(void) {
    if(is_empty()) {
        fprintf(stderr, "error(stack empty)");
        exit(1);
    } else {
        return stack[top--];
    }
}

//peek함수(top을 po하지 않고, 반환)
element peek(void) {
    if(is_empty()) {
        fprintf(stderr, "error(stack empty)");
        exit(1);
    } else {
        return stack[top];
    }
}

