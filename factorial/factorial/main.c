#include <stdio.h>

int fact(int a);
int sum = 1;
int main() {
    int num;
    scanf("%d", &num);
    printf("%d\n", fact(num));
}
int fact(int a){
    if(a == 0) {
        return sum;
    }
    else {
        sum *= a;
        return fact(a-1);
    }
}
