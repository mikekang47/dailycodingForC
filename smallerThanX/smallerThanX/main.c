#include <stdio.h>

int main() {
    int a, b;
    int num[10000];
    scanf("%d %d", &a, &b);
    for(int i = 0; i < a; i++) {
        scanf("%d", &num[i]);
        if(num[i] < b) {
            printf("%d ", num[i]);
        }
    }
}
