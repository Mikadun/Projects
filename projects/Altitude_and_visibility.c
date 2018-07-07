#include <stdio.h>
int last = -1;
 
int compare(int a, int b){
    if((a == 0) || (b == 0))
        return (a > b ? a : b);
    else
        return (a < b ? a : b);
}
 
int abs(int numb){
    if(numb < 0)
        return (-1)*numb;
    else
        return numb;
}
 
void push(int *stk, int *pos, int value, int pos_v){
    extern int last;
    stk[++last] = value;
    pos[last] = pos_v;
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
    int stack[n]; int positions[n];
    int arr[n];
    int answer[n];
    for(i = 0; i < n; i++){
        fscanf(fin, "%d", &arr[i]);
        answer[i] = 0;
        stack[i] = 0;
    }
 
    stack[++last] = arr[n - 1];
    positions[last] = n - 1;
    for(i = n - 2; i >= 0; i--){
        if(arr[i] < stack[last]){
            push(stack, positions, arr[i], i);
            answer[i] = compare(answer[i], abs(positions[last - 1] - i));
        }
        else{
            while((last > -1) && (arr[i] >= stack[last]))
                pop();
            push(stack, positions, arr[i], i);
            if(last)
                answer[i] = compare(answer[i], abs(positions[last - 1] - i));
        }
    }
    last = -1;
 
    stack[++last] = arr[0];
    positions[last] = 0;
    for(i = 1; i < n; i++){
        if(arr[i] < stack[last]){
            push(stack, positions, arr[i], i);
            answer[i] = compare(answer[i], i - (positions[last - 1]));
        }
        else{
            while((last > -1) && (arr[i] >= stack[last]))
                pop();
            push(stack, positions, arr[i], i);
            if(last)
                answer[i] = compare(answer[i], i - (positions[last - 1]));
        }
    }
    for(i = 0; i < n; i++)
        fprintf(fout, "%d ", answer[i]);
}
