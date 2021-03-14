#include <stdio.h>

int main() {
    int length;
    double subject[1000];
    scanf("%d", &length);
    
    for(int i = 0; i < length; i++) {
        scanf("%lf", &subject[i]);
    }
    
    int max = subject[0];
    for(int i = 0; i < length; i++) {
        if(max < subject[i]) {
            max = subject[i];
        }
    }
    
    double sum = 0;
    for(int i = 0; i < length; i++) {
        subject[i] = subject[i]/max * 100;
        sum += subject[i];
    }
    printf("%.2lf\n", sum / length);
}
