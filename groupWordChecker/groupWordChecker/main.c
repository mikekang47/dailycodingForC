#include <stdio.h>
#include <string.h>
#include <stdbool.h>


bool wordCheck(char str[101]) {
    bool alphabet[26] = {false};
    
    for(int i = 0; i < strlen(str); i++) {
        if(alphabet[str[i]-'a']) {
            return false;
        }
        else {
            char temp = str[i];
            alphabet[str[i]-'a'] = true;
            
            while(1) {
                if(temp != str[++i]) {
                    i--;
                    break;
                }
            }
        }
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int count = 0;
    
    for(int i = 0; i < n; i++) {
        char string[101];
        scanf("%s", string);
        
        if(wordCheck(string)){
            count++;
        }
    }
    
    printf("%d\n", count);
    return 0;
}
