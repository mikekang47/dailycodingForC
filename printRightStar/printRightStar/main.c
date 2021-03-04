#include <stdio.h>

int main() {
    int a;
    char c = '*';
    scanf("%d", &a);
    for(int i = 0; i < a; i++) {
        for(int j = i; j > i; j--) {
            printf("%c", c);
        }
        printf("\n");
    }
}
