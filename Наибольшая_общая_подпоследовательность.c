#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) ((a > b) ? (a) : (b))
 
int dp[1010][1010];
 
int main(){
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    int i, j;
    char fs[1010];
    char ss[1010];
 
    fscanf(fin, "%s%s", fs, ss);
    int len_f = strlen(fs);
    int len_s = strlen(ss);
 
    for(i = 1; i < len_f + 2; i++)
        for (j = 1; j < len_s + 2; j++ )
            dp[i][j] = -1;
 
 
    for(i = 0; i < len_f + 1; i++){
        for(j = 0; j < len_s + 1; j++){
            if (dp[i][j] == -1)
                continue;
            dp[i + 1][j] = max(dp[i][j], dp[i + 1][j]);
            dp[i][j + 1] = max(dp[i][j], dp[i][j + 1]);
            if(fs[i] == ss[j])
                dp[i + 1][j + 1] = max(dp[i][j] + 1, dp[i + 1][j + 1]);
        }
    }
 
    int l = dp[len_f][len_s];
    i = len_f - 1;
    j = len_s - 1;
    char ans[1010];
    while(l != 0 && i >= 0 && j >= 0){
        if(fs[i] == ss[j]){
            ans[--l] = fs[i];
            i--;
            j--;
        }
        else if(dp[i][j + 1] == dp[i + 1][j + 1])
            i--;
        else
            j--;
    }
    for(i = 0; i < dp[len_f][len_s]; i++)
        fprintf(fout, "%c", ans[i]);
 
    fclose(fin); fclose(fout);
    return 0;
}
