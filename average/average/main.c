#include <stdio.h>

int findMax(int array[], int max, int length) {
    for(int i = 1; i < length; i++) {
        if(max < array[i]) {
            max = array[i];
        }
    }
    return max;
}

void modifyValue(int array[], int modified) {
    int i = 0;
    while(array[i] != '\0') {
        array[i] = array[i] / modified;
        i++;
    }
}

double printAverage(int array[]) {
    int sum = 0;
    int i = 0;
    double average = 0;
    while(array[i] != '\0') {
        sum += array[i];
        i++;
    }
    average = sum / i;
    return average;
}

int main() {
    int length;
    int modified;
    int result[1001];
    scanf("%d", &length);
    for(int i = 0; i < length; i++) {
        scanf("%d", &result[i]);
    }
    int max = result[0];
    modified = findMax(result, max, length) * 100;
    modifyValue(result, modified);
    printf("%lf\n", printAverage(result));
    return 0;
}

