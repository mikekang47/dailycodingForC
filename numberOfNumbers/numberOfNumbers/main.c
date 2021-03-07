#include <stdio.h>

int main() {
    int a, b, c;
    int array[10] = {0, };
    int rest;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    int result = a * b * c;
    
    while(result > 0) {
        rest = result % 10;
        result = result / 10;
        array[rest]++;
    }
    
    for(int i = 0; i < 10; i++) {
        printf("%d\n", array[i]);
    }
    return 0;
}
