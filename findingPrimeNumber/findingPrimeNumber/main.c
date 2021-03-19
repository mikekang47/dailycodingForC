#include <stdio.h>

int main() {
    int count = 0;
    int num;
    int digit[1001] = {0, };
    int divider = 0;
    scanf("%d", &num);
    for(int i = 0; i < num; i++) {
        scanf("%d", &digit[i]);
        if(digit[i] == 1)
            continue;
        for(int j = 2; j < digit[i]; j++) {
            if(digit[i] % j == 0) {
                divider = 1;
                break;
            }
        }
        
        if(divider == 0) {
            count++;
        }
        divider = 0;
    }
    
    printf("%d\n", count);
}
