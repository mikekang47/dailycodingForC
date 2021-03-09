#include <stdio.h>
#include <string.h>

int count = 0;
void inspecting(char string[100]);

int main() {
    int number;
    char string[100];
    scanf("%d", &number);
    for(int k = 0; k < number; k++) {
        scanf("%s", string);
        inspecting(string);
    }
    printf("%d\n", count);
}

void inspecting(char string[100]) {
    for(int i = 0; i < strlen(string); i++) {
        if(string[i] == string[i+1]) {
            for(int j = 0; j < strlen(string); j++) {
                if(string[j] == string[i] && j != i) {
                    break;
                }
            }
        }
        count++;
    }
    
}
