#include <stdio.h>
#include <stdlib.h>
 
int average_up(int x, int y){ 
    if((x+y) % 2)
        return (x+y) / 2 + 1;
    else
        return (x+y) / 2;
}
 
int main(){
    FILE *fin; FILE *fout;
    fin = fopen("linear.in", "r");
    fout = fopen("linear.out", "w");
    int peaces_count; int i;
    int position; int direction;
    fscanf(fin, "%d", &peaces_count);
    int stack[peaces_count]; int s_high = -1;
    int destr_times[peaces_count]; int t_high = -1; 
    for(i = 0; i < peaces_count; i++){
        fscanf(fin, "%d %d", &position, &direction);
        if(direction == 1)
            stack[++s_high] = position;
        else if(s_high > -1)
            destr_times[++t_high] = average_up((-1)*stack[s_high--], position);
    }
    int t_count;
    fscanf(fin, "%d", &t_count);
    int times[t_count];
    int arr[t_count];
    for(i = 0; i < t_count; i++){
        fscanf(fin, "%d", &times[i]);
        arr[i] = 0;
    }
    int l; int r; int mid; 
    for(i = 0; i < t_high + 1; i++){
        if((destr_times[i]) <= times[0]){
            arr[0] += 2;
            continue;
        }
        l = 0; r = t_count;
        while(r - l > 1){
            mid = l + (r - l) / 2;
            if(destr_times[i] > times[mid])
                l = mid;
            else
                r = mid;
 
        }
        arr[r] += 2;
    }
 
    for(i = 1; i < t_count; i++)
        arr[i] += arr[i - 1];
    for(i = 0; i < t_count; i++)
        fprintf(fout, "%d ", peaces_count - arr[i]);
 
    fclose(fin);
    fclose(fout);
}
