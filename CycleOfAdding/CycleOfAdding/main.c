#include <stdio.h>

int main() {
    int num;
    int sum;
    int a, b, c, d;
    int count = 0;
    
    scanf("%d", &num);
    sum = num;
    
    while(1) {
        a = num/10;
        b = num % 10;
        c = (a + b) % 10;
        d = (b*10) + c;
        num = d;
        count++;
        if(d == sum) {
            break;
        }
    }
    printf("%d", count);
}
