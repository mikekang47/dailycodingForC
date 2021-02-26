#include <stdio.h>
#include <string.h>
#define SIZE 1000

char change(char string[SIZE]);
void compare(char *string1, char *string2);

int main() {
    char string1[SIZE] = " ";
    char string2[SIZE] = " ";
    scanf("%s %s", string1, string2);
    change(string1);
    change(string2);
    compare(string1, string2);
}

char change(char string[SIZE]) {
    char temp;
    temp = string[0];
    string[0] = string[2];
    string[2] = temp;
    return *string;
}

void compare(char *string1, char *string2) {
    for(int i = 0; i < 3; i++) {
        if(string1[i] > string2[i]) {
            printf("%s", string1);
            break;
        }
        else if(string1[i] < string2[i]) {
            printf("%s", string2);
            break;
        }
    }
}
