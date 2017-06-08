#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int value;
    int index;
} Element;
  
typedef struct {
    int high;
    int low;
    Element *elements;
} Deck;
  
void dequeue(Deck *s, int del){
    if(s->high - s->low > - 1)
        if(s->elements[s->low].index < del)
            s->low = (s->low) + 1;
}
  
void enqueue(Deck *s, int val, int idx){
    while(s->high - s->low > -1)
        if(s->elements[s->high].value <= val)
            s->high = (s->high) - 1;
        else
            break;
    s->high = (s->high) + 1;
    s->elements[s->high].value = val;
    s->elements[s->high].index = idx;
}
  
int main(){
    FILE *fin; FILE *fout;
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    int i, n, m, j = 0, deleted = 0;
    fscanf(fin, "%d", &n);
    int *seq = (int *) malloc(n * sizeof(int) + 10);
    Deck stack;
    stack.elements = (int *) calloc(n,sizeof(int) + 10);
    stack.low = 0;
    stack.high = -1;
    for(i = 0; i < n; i++)
        fscanf(fin, "%d", &seq[i]);
    fscanf(fin, "%d\n", &m);
    enqueue(&stack, seq[j], j);
    char c;
    for(i = 0; i < m; i++){
        fscanf(fin, "%c", &c);
        if(c == 'R'){
            ++j;
            enqueue(&stack, seq[j], j);
        } else if(c == 'L'){
            deleted = deleted + 1;
            dequeue(&stack, deleted);
        } else {
            return 0;
        }
        fprintf(fout, "%d ", stack.elements[stack.low].value);
    }
    free(stack.elements);
    free(seq);
    fclose(fin);
    fclose(fout);
    return 0;
}
