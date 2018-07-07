#include <stdio.h>
typedef struct {
    char *ans;
    int correct;
} Answer;
 
int main(){
    int i, j, l, n, len, found, count, temp;
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    fscanf(fin, "%d %d\n", &n, &len);
    Answer answers[n];
    for(i = 0; i < n; i++){
        answers[i].ans = malloc(len * sizeof(char) + 1);
        fscanf(fin, "%s\n %d\n", answers[i].ans, &answers[i].correct);
    }
    for(i = 0; i < (1 << len + 1) - 1; i++){
        found = 1;
        for(j = 0; j < n; j++){
            count = 0;
           /* printf("i = %d\n", i);*/
            for(l = 0; l < len; l++){
                temp = (((1 << l) & i) ? 1 : 0) + (answers[j].ans[l] - 44);
                if((temp == 1) || (temp == 0))
                    count++;
                    /*printf("y");*/
            }/* else
                    printf("n");
            printf(" // correct = %d\n", answers[j].correct);*/
            if(count != answers[j].correct){
                found = 0;
                break;
            }
        }
        /*printf("========\n");*/
        if(found){
            for(j = 0; j < len; j++)
                fprintf(fout, "%c", (((1 << j) & i) ? '+' : '-'));
            fclose(fin);
            fclose(fout);
            return 0;
        }
    }
    fclose(fin); fclose(fout);
    return 0;
}
