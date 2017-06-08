#include <stdio.h>
int last = -1;
void push(int *stk, int value){
    extern int last;
    stk[++last] = value;
}
 
void pop(){
    extern int last;
    last--;
}
 
int main(){
    FILE *fin, *fout;
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    int n, i;
    extern int last;
    fscanf(fin, "%d", &n);
    int stack[n];
    int arr[n];
    for(i = 0; i < n; i++)
        fscanf(fin, "%d", &arr[i]);
    for(i = 0; i < n; i++)
        stack[i] = 0;
    stack[++last] = arr[n - 1];
    for(i = n - 2; i >= 0; i--){
        if(arr[i] < stack[last]){
            push(stack, arr[i]);
            arr[i] = stack[last-1];
        }
        else{
            while((last > -1) && (arr[i] >= stack[last]))
                pop();
            push(stack, arr[i]);
            if(last)
                arr[i] = stack[last-1];
        }
    }
    for(i = 0; i < n; i++)
        fprintf(fout, "%d ", arr[i]);
}
