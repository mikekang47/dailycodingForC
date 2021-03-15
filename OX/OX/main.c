#include <stdio.h>
#include <string.h>

int main() {
    int sum, add;
    char arr[81];
    int testCase;
    scanf("%d", &testCase);
    
    for(int i = 0 ; i < testCase; i++) {
        sum = 0; add = 1;
        scanf("%s", arr);
        for(int j = 0; j < strlen(arr); j++) {
            if(arr[j] == 'O') {
                sum += add;
                add++;
            }
            else {
                add = 1;
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}
