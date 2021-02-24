#include <stdio.h>

int main() {
    char string[100] = {0};
    scanf("%s", string);
    for(char a = 'a'; a <= 'z'; a++) {
        int j = 0;
        while(string[j] != 0) {
            if(string[j] == a) {
                break;
            }
            j++;
        }
        if(string[j] == a) {
            printf("%d ", j);
        }
        else {
            printf("-1 ");
        }
        
    }
    return 0;
}
