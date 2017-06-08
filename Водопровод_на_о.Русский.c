#include <stdio.h>
#define MAX_SIZE 200
#define MAX_WAYS 2
#define true 1
#define false 0
#define MOVES_COUNT 4
 
typedef struct {
    int x, y;
} Coord;
 
char *ans_variants[] = {{"NO"}, {"YES"}, {"MULTIPLE"}};
Coord moves[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
 
int map[MAX_SIZE + 2][MAX_SIZE + 2];
int used[MAX_SIZE + 2][MAX_SIZE + 2];
 
typedef struct {
    Coord coords[MAX_SIZE * MAX_SIZE];
    int len;
} Way;
 
int ways_count = 0;
Way way;
Way answer[MAX_WAYS];
 
int w, h;
 
void dfs(int x, int y, int depth){
    used[x][y] = true;
    int i;
    way.coords[depth].x = x;
    way.coords[depth].y = y;
    way.len = depth + 1;
    if(y == w){
        if(ways_count == MAX_WAYS)
            return;
        for(i = 0; i < way.len; i++){
            answer[ways_count].coords[i] = way.coords[i];
        }
        answer[ways_count].len = way.len;
        ways_count++;
    }
    for(i = 0; i < MOVES_COUNT; i++){
        int tx = x + moves[i].x; int ty = y + moves[i].y;
        if(!used[tx][ty] && map[tx][ty] && (ways_count < MAX_WAYS)){
            dfs(tx, ty, depth + 1);
        }
    }
    used[x][y] = false;
}
 
int main(){
    int i, j;
    char str[MAX_SIZE + 1];
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    fscanf(fin, "%d %d\n", &h, &w);
    for(i = 1; i <= h; i++){
        fscanf(fin, "%s\n", &str);
        for(j = 1; j <= w; j++){
            map[i][j] = str[j - 1] == '#';
        }
    }
 
    for(i = 1; i <= h; i++){
        if(!used[i][1] && map[i][1]){
            if(ways_count == MAX_WAYS)
                break;
            dfs(i, 1, 0);
        }
    }
 
    fprintf(fout, "%s\n", ans_variants[ways_count]);
 
    for(i = 0; i < ways_count; i++){
        fprintf(fout, "%d ", answer[i].len);
        for(j = 0; j < answer[i].len; j++){
            fprintf(fout, "%d %d  ", answer[i].coords[j].x, answer[i].coords[j].y);
        }
        fprintf(fout, "\n");
    }
    fclose(fin);
    fclose(fout);
 
    return 0;
}
