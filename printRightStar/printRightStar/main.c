#include <stdio.h>

int main() {
    int s, j;
    int a;
    scanf("%d", &a);
    for(j = 0; j < a; j++) {
        for(s = 0; s < a-j-1; s++) {
            printf(" ");
        }
        for(s = 0; s <= j; s++) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
