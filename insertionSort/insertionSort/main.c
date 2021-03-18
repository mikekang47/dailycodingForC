#include<stdio.h>


int main() {
    int testCase;
    int arr[81];
    int keyValue;
    int j;
    scanf("%d", &testCase);
    for(int i = 0; i < testCase; i++) {
        scanf("%d", &arr[i]);
    }
    
    for (int i = 0; i < testCase-1; i++) {
        keyValue = arr[i + 1];
        for (j = i; j > -1; j--) {
            if (arr[j] > keyValue) {
                arr[j + 1] = arr[j];
            }
            else {
                break;
            }
        }
        arr[j + 1] = keyValue;
    }
    for (int i = 0; i < testCase; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}


