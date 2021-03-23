#include <stdio.h>
#include <string.h>

int main() {
    int testCase;
    double numberOfStudent;
    int scores[1001];
    int sum = 0;
    double average;
    int count = 0;
    scanf("%d", &testCase);
    for(int i = 0; i < testCase; i++) {
        scanf("%lf", &numberOfStudent);
        for(int j = 0; j < numberOfStudent; j++) {
            scanf("%d", &scores[j]);
            sum += scores[j];
        }
        average = sum / numberOfStudent;
        for(int k = 0; k < numberOfStudent;k++) {
            if(scores[k] > average) {
                count++;
            }
        }
        printf("%.3lf%%\n", (double)(count / numberOfStudent * 100));
        sum = 0;
        average = 0;
        count = 0;
    }
}
