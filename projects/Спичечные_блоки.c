#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int w, h;
} Way;
 
Way *way = NULL;
int max_h = 0;
FILE *fout = NULL;
 
int calc_match(int w, int h){
    return (w + 2*w*h + h);
}
 
void write_ans(int n){
    int i;
    fprintf(fout, "%d ", n);
    for(i = 1; i < n + 1; i++){
        fprintf(fout, "%d %d ", way[i].h, way[i].w);
    }
    fprintf(fout, "\n");
}
 
void step(int w, int h, int depth, int left){
    int i;
    //printf("[%d][%d]\n", w, h);
    way[depth].w = w;
    way[depth].h = h;
    if(!left){
        write_ans(depth);
    }
    for(i = h; i < max_h + 1; i++){
        while(left - calc_match(i, w) >= 0){
            if(i <= w){
                step(w, i, depth + 1, left - calc_match(w, i));
            }
            w++;
        }
        w = h + 1;
    }
 
 
}
 
int main(){
    FILE *fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    int i = 1, n;
    fscanf(fin, "%d", &n);
    way = (Way *)malloc(n * sizeof(Way));
    for(max_h = 1; calc_match(max_h, max_h) < n; max_h++);
    //printf("%d\n", max_h);
    step(1, 1, 0, n);
    fprintf(fout, " ");
    fclose(fin); fclose(fout);
}
