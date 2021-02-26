#include <stdio.h>
#include <string.h>
#define SIZE 1000000

int main() {
    char string[SIZE] = " ";
    int count = 0;
    scanf("%[^\n]s", string);
    int i = 0;
    while(string[i] != '\0') {
        if(string[i] == 32 && string[i+1] != 32 && string[i+1] != '\0') {
            count++;
        }
        i++;
    }
    if(string[0] == 32) {
        count--;
    }
    count++;
    printf("%d\n", count);
}
