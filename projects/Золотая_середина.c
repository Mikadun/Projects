#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500001
 
typedef enum {max, min} Heap_type;
typedef struct {
    int size;
    int *data;
    Heap_type type;
} Heap;
 
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
void sift_up(int idx, Heap *heap){
    heap->size++;
    while(heap->type == max ? (heap->data[idx] > heap->data[(idx - 1) / 2]) : (heap->data[idx] < heap->data[(idx - 1) / 2])){
        swap(&(heap->data[idx]), &(heap->data[(idx - 1) / 2]));
        idx = (idx - 1) / 2;
    }
}
 
void sift_down(int idx, Heap *heap){
    int child_l, child_r, child_temp;
    while(2 * idx + 1 < heap->size){
        child_l = 2 * idx + 1;
        child_r = 2 * idx + 2;
        child_temp = child_l; 
        if(child_r < heap->size){
            if(heap->type == max ? heap->data[child_r] > heap->data[child_l] : heap->data[child_r] < heap->data[child_l]){
                child_temp = child_r;
            }
        }
        if(heap->type == max ? heap->data[idx] >= heap->data[child_temp] : heap->data[idx] <= heap->data[child_temp]){
            break;
        }
        swap(&(heap->data[idx]), &(heap->data[child_temp]));
        idx = child_temp;
    }
}
 
void add(int num, Heap *heap){
    heap->data[heap->size] = num;
    sift_up(heap->size, heap);
}
 
int get_root(Heap *heap){
    int root = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    sift_down(0, heap);
    return root;
}
 
int main(){
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    Heap min_heap, max_heap;
    min_heap.data = (int *) malloc(MAX_SIZE * sizeof(int)); min_heap.type = min; min_heap.size = 0;
    max_heap.data = (int *) malloc(MAX_SIZE * sizeof(int)); max_heap.type = max; max_heap.size = 0;
    int i, n, num;
    fscanf(fin, "%d", &n);
    for(i = 0; i < n; i++){
        fscanf(fin, "%d", &num);
        if(max_heap.size == 0 || max_heap.data[0] > num){
            add(num, &max_heap);
            if(min_heap.size < max_heap.size - 1){
                add(get_root(&max_heap), &min_heap);
            }
        } else {
            add(num, &min_heap);
            if(max_heap.size < min_heap.size){
                add(get_root(&min_heap), &max_heap);
            }
        }
        fprintf(fout, "%d ", max_heap.data[0]);
    }
    free(min_heap.data); free(max_heap.data);
    fclose(fin); fclose(fout);
}
