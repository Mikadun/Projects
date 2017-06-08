#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void quicksort(int *, int, int);
 
int main(){
    int n;
    int i;
    FILE *fin;
    FILE *fout;
    srand(time(NULL));
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
 
    fscanf(fin, "%d", &n);
    int numbers[n];
    for(i = 0; i < n; i++)
        fscanf(fin, "%d", &numbers[i]);
    quicksort(numbers, 0, n - 1);
    for(i = 0; i < n; i++)
        fprintf(fout, "%d ", numbers[i]);
    fclose(fin);
    fclose(fout);
}
 
void quicksort(int *arr, int l, int r)
{
    int div;
    void swap(int *arr, int i, int j);
    if (l >= r)
        return;
    swap(arr, l, l + rand() % (r - l + 1)); 
    div = l; 
    for(int i = l + 1; i <= r; i++) 
        if (arr[i] < arr[l])
            swap(arr, ++div, i);
        swap(arr, l, div); 
    quicksort(arr, l, div - 1);
    quicksort(arr, div + 1, r);
}
 
 
void swap(int *arr, int i, int j)
{
    int temp;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
