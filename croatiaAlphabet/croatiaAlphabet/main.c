#include <stdio.h>
#include <string.h>

int main() {
    char string[100] = {0,};
    int count = 0;
    scanf("%s", string);
    for(int i = 0; i < strlen(string); i++) {
        count++;
        if(string[i] == 'c' && string[i+1] == '=') {
            count--;
        }
        else if(string[i] == 'c' && string[i+1] == '-') {
            count--;
        }
        else if(string[i] == 'd' && string[i+1] == 'z' && string[i+2] == '=') {
            count--;
        }
        else if(string[i] == 'd' && string[i+1] == '-') {
            count--;
        }
        else if(string[i] == 'l' && string[i+1] == 'j') {
            count--;
        }
        else if(string[i] == 'n' && string[i+1] == 'j') {
            count--;
        }
        else if(string[i] == 's' && string[i+1] == '=') {
            count--;
        }
        else if(string[i] == 'z' && string[i+1] == '=') {
            count--;
        }
    }
    printf("%d\n",count);
    
}
