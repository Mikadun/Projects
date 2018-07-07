#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1
  
typedef struct list{
    int value;
    struct list *next;
} list;
  
typedef struct{
    list *head;
} List;
 
char *used;
List *g;
int *ans;
int anslen = 0;
char iscycle = false;
  
void dfs(int v){
    if(used[v] == 1){
        iscycle = true;
    }
    used[v] = 1;
    list *p;
    for(p = g[v].head->next; p != NULL; p = p->next){
        if(used[p->value] != 2 && !iscycle)
            dfs(p->value);
    }
    used[v] = 2;
    ans[anslen++] = v;
}
 
void push_to_front(int idx, int value){
    list *p = (list *) malloc(sizeof(list));
    p->value = value;
    p->next = g[idx].head->next;
    g[idx].head->next = p;
}
 
int main(){
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    int i, n, m;
    fscanf(fin, "%d%d", &n, &m);
    g = (List *) malloc(sizeof(List) * n);
    ans = (int *) calloc(n, sizeof(int));
    used = (char *) calloc(n, sizeof(char));
    for(i = 0; i < n; i++){
        g[i].head = (list *) malloc(sizeof(list));
        g[i].head->next = NULL;
    }
    int a, b;
    for(i = 0; i < m; i++){
        fscanf(fin, "%d%d", &a, &b);
        push_to_front(a - 1, b - 1);
    }
 
    i = 0;
    while(i < n && !iscycle){
        if(used[i] == 0){
            dfs(i);
        }
        i++;
    }
    if(iscycle){
        fprintf(fout, "-1");
    } else {
        for(i = n; i > 0; i--){
            fprintf(fout, "%d ", ans[i - 1] + 1);
        }
    }
    list *p, *temp;
    for(i = 0; i < n; i++){
        for(p = g[i].head->next; p != NULL; p = temp){
            temp = p->next;
            free(p);
        }
    }
    free(g); free(ans); free(used);
    fclose(fin);
    fclose(fout);
}
