#include <stdio.h>


int array[] = {0, };
void merge(int a[], int low, int mid, int high);
void bottomUpMergeSort(int a[]);

int main() {
    int a[1000001] = {0, };
    int num;
    scanf("%d", &num);
    for(int i = 0; i < num; i++) {
        scanf("%d", &a[i]);
    }
    bottomUpMergeSort(a);
    for(int i = 0; i < num; i++) {
        printf("%d\n", a[i]);
    }
    return 0;
}


void merge(int a[], int low, int mid, int high) {
    for(int k = low; k <= high; k++) {
        array[k] = a[k];
    }
    
    int i = low;
    int j = mid + 1;
    
    for(int k = low; k <= high; k++) {
        if (i > mid) {
            a[k] = array[j++];
        } else if (j > high) {
            a[k] = array[i++];
        } else if (array[j] < array[i]) {
            a[k] = array[j++];
        } else {
            a[k] = array[i++];
        }
    }
}
    

void bottomUpMergeSort(int a[]) {
    int length = 0;
    int i = 0;
    while(a[i] != '\0') {
        length++;
        i++;
    }
    for(int size = 1; size < length; size = size * 2) {
        for(int low = 0; low < length - size; low += size * 2) {
            merge(a, low, low + size - 1,  (low + size * 2 - 1 < length - 1 ? low + size * 2 - 1 : length - 1));
            
        }
    }
    
}

