#include <stdio.h>
#include <stdlib.h>
#define MAX_VALUE 1000000000
#define min(a, b) ((a) < (b) ? (a) : (b))
 
typedef struct {
    int v, w;
} Coin;
 
int n, coins_weight;
int *D;
Coin *coins;
 
int main(){
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    int empty_weight, full_weight, i, weight, minimum;
    fscanf(fin, "%d%d%d", &empty_weight, &full_weight, &n);
    coins_weight = full_weight - empty_weight;
    D = (int *) malloc((coins_weight + 1) * sizeof(int));
    coins = (Coin *) malloc(n * sizeof(Coin));
    for(i = 0; i < n; i++){
        fscanf(fin, "%d%d", &coins[i].v, &coins[i].w);
    }
    D[0] = 0;
    for(i = 0; i < coins_weight; i++){
        D[i + 1] = -1;
    }
    for(weight = 1; weight <= coins_weight; weight++){
        minimum = MAX_VALUE;
        for(i = 0; i < n; i++){
            if(weight - coins[i].w >= 0 && D[weight - coins[i].w] != -1){
                minimum = min(minimum, coins[i].v + D[weight - coins[i].w]);
            }
        }
        D[weight] = (minimum == MAX_VALUE ? -1 : minimum);
    }
    fprintf(fout, "%d", D[coins_weight]);
    fclose(fin); fclose(fout);
    free(D); free(coins);
}
