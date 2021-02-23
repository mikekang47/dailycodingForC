#include <stdio.h>

int sequence(int a);

int main() {
    int a;
    scanf("%d", &a);
    printf("%d\n", sequence(a));
    
}

int sequence(int a) {
    int count = 0;
    for(int i = 1; i <= a; i++) {
        if(i < 100) {
            count++;
        }
        else {
            if(((i / 100) - (i % 100)/10) == (((i % 100)/10)-((i%100)%10))) {
                count++;
            }
        }
    }
    return count;
}
