#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 500
#define MOVES_COUNT (sizeof(moves) / sizeof(Coord))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
	int x, y;
} Coord;

Coord moves[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int map[MAX_SIZE + 2][MAX_SIZE + 2];
bool used[MAX_SIZE + 2][MAX_SIZE + 2];

Coord bunny[MAX_SIZE * MAX_SIZE];
int way_len = 0;

typedef struct {
	Coord value;
	int key;
} Cell;

Cell heap[MAX_SIZE * MAX_SIZE];
int heap_size = 0;

void swap(Cell *a, Cell *b){
    Cell temp = *a;
    *a = *b;
    *b = temp;
}

void sift_up(int idx){
	heap->size++;
	while(heap[idx].key < heap[(idx - 1) / 2].key){
		swap(heap[idx], heap[(idx - 1) / 2]);
		idx = (idx - 1) / 2;
	}
}

void insert(int priority, Coord value){
	
}

void dfs(Coord pos, int step){
    int i;
	bunny[step] = pos;
	way_len = MAX(way_len, step + 1);
	for(i = 0; i < MOVES_COUNT; i++){
		Coord new_pos;
		new_pos.x = pos.x + moves[i].x;
		new_pos.y = pos.y + moves[i].y;
		if(map[new_pos.x][new_pos.y] > map[pos.x][pos.y]){
			dfs(new_pos, step + 1);
			break;
		}
	}
}

void idx_bfs(Coord pos, int step){
	used[pos.x][pos.y] = true;
	int i;
	for(i = 0; i < MOVES_COUNT; i++){
		Coord new_pos;
		new_pos.x = pos.x + moves[i].x;
		new_pos.y = pos.y + moves[i].y;
		int height = MAX(map[new_pos.x][new_pos.y], step + 1);
		if(height < way_len && !used[new_pos.x][new_pos.y]){
			insert(height, new_pos);
		}
	}
	idx_bfs(extract_min(), step + 1);
}

int main(){
	FILE *fin = fopen("input.txt", "r");
	FILE *fout = fopen("output.txt", "w");
	int i, j, n, m;
	fscanf(fin, "%d%d%d%d", &n, &m, &(bunny[0].x), &(bunny[0].y));
	for(i = 1; i <= n; i++){
		for(j = 1; j <= m; j++){
			fscanf(fin, "%d", &map[i][j]);
		}
	}
	dfs(bunny[0], 0);
	printf("%d\n", way_len);
	for(i = 0; i < way_len; i++){
		printf("(%d, %d: %d) ", bunny[i].x, bunny[i].y, map[bunny[i].x][bunny[i].y]);
	}
	// Don't forget to clear used[] 
	// idx_bfs({1, 1}, 0);
	return 0;
}
