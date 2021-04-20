#include <stdio.h>

int target[10] = {7, 5, 9, 0, 3, 1, 6, 2, 4, 8};
int n = 10;

void swap(int *a, int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int partiton(int* a, int left, int right) {
    int p = a[left];
    int i = left + 1;
    for(int j = left + 1; j <= right; j++) {
        if(a[j] < p) {
            swap(a, j, i);
            i++;
        }
    }
    swap(a, left, i-1);
    
    return i-1;
}

void sort(int* a, int left, int right) {
    if(right <= left) {
        return ;
    }
    int p = partiton(a, left, right);
    sort(a, left, p - 1);
    sort(a, p + 1, right);
}

int main() {
    sort(target, 0, n-1);
    for(int i = 0; i < n; i++) {
        printf("%d ", target[i]);
    }
    return 0;
}
