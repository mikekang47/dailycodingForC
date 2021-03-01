#include <stdio.h>
#include <string.h>

int main() {
    
    int cnt = 0, mcnt = 0;
    char string[1000000];
    char ma;
    scanf("%s", string);
    for (int i = 'a'; i <= 'z'; i++) {
        for (int j = 0; j < strlen(string); j++) {
            if (string[j] == i || string[j] == i - 32)
                cnt++;
        }
        
        if (mcnt < cnt) {
            mcnt = cnt;
            ma = i;
            if (ma >= 97)
                ma -= 32;
        }
        else if (mcnt == cnt)
            ma = '?';
        
        cnt = 0;
    }
    printf("%c", ma);
}
