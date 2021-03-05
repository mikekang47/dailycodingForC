#include <stdio.h>

int main() {
    int a[10];
    int i = 0;
    int max = 0;
    int index = 0;
    for(int i = 0; i < 9; i++) {
        scanf("%d", &a[i]);
    }
    while(a[i] != '\0') {
        if(max < a[i]) {
            max = a[i];
            index = i;
        }
        i++;
    }
    printf("%d\n%d\n", max, index+1);
}
