#include <stdio.h>
#include <string.h>

int main() {
    int numOfTestCase = 0;
    int lenOfString = 0;
    char string[20] = {0};
    
    scanf("%d", &numOfTestCase);
    
    for(int i = 0; i < numOfTestCase; i++) {
        scanf("%d %s", &lenOfString, string);
        
        for(int j =0; j < strlen(string); j++) {
            for(int k = 0; k < lenOfString; k++) {
                printf("%c", string[j]);
            }
        }
        printf("\n");
    }
    return 0;
}
