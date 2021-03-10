#include <stdio.h>

void swap(int array[], int i, int j) {
    int temp;
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

int main() {
    int digit;
    int num[1001];
    int i = 0;
    scanf("%d", &digit);
    for(int i = 0; i < digit; i ++) {
        scanf("%d", &num[i]);
    }
    
    for(int i = 0; i < digit -1 ; i++) {
        for(int j = i+1; j < digit; j++) {
            if(num[i] > num[j]) {
                swap(num, i, j);
            }
        }
    }
    for(int i = 0; i < digit; i ++) {
        printf("%d\n", num[i]);
    }
    
}
