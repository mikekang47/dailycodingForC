#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    if(N == 1) {
        return 0;
    }
    
    for(int i = 2; i <= N; i++) {
        if(N == 0) {
            return 0;
        }
        
        if(N % i == 0) {
            printf("%d\n", i);
            N = N / i;
            i = 1;
        }
    }
}
