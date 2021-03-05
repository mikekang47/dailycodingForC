#include <stdio.h>

int main() {
    int a, b;
   
    while(1) {
        scanf("%d %d", &a, &b);
        if(a >= 10 || b >= 10) {
            break;
        }
        printf("%d\n", a + b);
        fflush(stdin);
    }
}
