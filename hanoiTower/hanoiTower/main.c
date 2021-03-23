#include <stdio.h>

void mergeSort(int low, int mid, int high);

int main() {
    int array[10000001];
    int length;
    scanf("%d", &length);
    for(int i = 0; i < length; i++) {
        scanf("%d", &array[i]);
    }
//    mergeSort(array);
}

void mergeSort(int low, int mid, int high) {
    int i, j, k, l;
    i = low; j = mid + 1; k = low;
    while(i <= mid && k <= high) {
        
    }
    
}

