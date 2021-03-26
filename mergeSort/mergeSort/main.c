#include <stdio.h>


int array[] = {0, };
void merge(int a[], int low, int mid, int high);
void bottomUpMergeSort(int a[]);

int main() {
    int a[] = {1, 5, 2, 6, 3, 8, 9, 10};
    bottomUpMergeSort(a);
    for(int i = 0; i < 8; i++) {
        printf("%d\n", a[i]);
    }
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

