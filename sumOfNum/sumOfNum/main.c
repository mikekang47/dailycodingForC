#include <stdio.h>

void sumOfNum(void);

int main() {
    sumOfNum();
    return 0;
}

void sumOfNum() {
    int num;
    char string[100] = "";
    scanf("%d", &num);
    scanf("%s", string);
    int sum = 0;
    for(int i = 0; i < num; i++) {
        sum += (int)(string[i] - 48);
    }
    printf("%d\n", sum);
}


