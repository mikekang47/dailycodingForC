#include <stdio.h>

int main() {
    int input[11];
    int rest[43] = {0, };
    int count = 0;
    for(int i = 0; i < 10; i++) {
        scanf("%d", &input[i]);
    }
    for(int i = 0; i < 10; i++) {
        rest[input[i] % 42]++;
    }
    for(int i = 0; i < 43; i++) {
        if(rest[i] != 0) {
            count++;
        }
    }
    printf("%d\n", count);
    
}
