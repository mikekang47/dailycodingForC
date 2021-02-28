#include <stdio.h>

int main() {
    char string[15];
    scanf("%s", string);
    int i = 0;
    int sum = 0;
    int len = 1;
    while(string[i] != '\0') {
        if(string[i] == 'A' || string[i] == 'B' || string[i] == 'C') {
            sum += 3;
        }
        else if(string[i] == 'D' || string[i] == 'E' || string[i] == 'F') {
            sum += 4;
        }
        else if(string[i] == 'G' || string[i] == 'H' || string[i] == 'I') {
            sum += 5;
        }
        else if(string[i] == 'J' || string[i] == 'K' || string[i] == 'L') {
            sum += 6;
        }
        else if(string[i] == 'M' || string[i] == 'N' || string[i] == 'O') {
            sum += 7;
        }
        else if(string[i] == 'P' || string[i] == 'Q' || string[i] == 'R' || string[i] == 'S') {
            sum += 8;
        }
        else if(string[i] == 'T' || string[i] == 'U' || string[i] == 'V') {
            sum += 9;
        }
        else if(string[i] == 'W' || string[i] == 'X' || string[i] == 'Y' || string[i] == 'Z') {
            sum += 10;
        }
        i++;
        len++;
    }

    printf("%d\n", sum);
    
}

