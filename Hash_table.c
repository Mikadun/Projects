#include <stdio.h>
#define MAX_SIZE 10
#define string_malloc malloc(256 * sizeof(char))


// https://istarik.ru/blog/programmirovanie/13.html краткий справ
// https://www.onlinegdb.com/online_c_compiler компилятор

typedef struct {
	char *key;
	char *name;
	char **genre;
	int genres_count;
	char *producer;
	int date;
	float duration;
	float rating;
} Film;

typedef struct {
	char *key;
	Film *p;
} Hash_cell;

Hash_cell hash_table[MAX_SIZE];
Film films[MAX_SIZE];

int is_empty(int index){
	return hash_table[index].p == NULL;
}

int hash_function(char *key){
	int index;
	for(int i = 0; i < MAX_SIZE + 1; i++){
        if(i == MAX_SIZE)
            return -1;
        index = (key[0] + key[1] + i) % MAX_SIZE;
        if(is_empty(index))
            break;
	}
	return index;
}

int add(Film *film){
	int index = hash_function(film->key);
	if(index == -1)
		return -1;
	hash_table[index].key = film->key;
	hash_table[index].p = film;
}

int main(){

	for(int i = 0; i < MAX_SIZE; i++){
		hash_table[i].p == NULL;
		Film *f = &films[i];
		f->key = string_malloc;
		f->name = string_malloc;
		f->producer = string_malloc;
		f->genre = (char **) malloc(5 * sizeof(char *));
		for(int j = 0; j < 5; j++){
			f->genre[j] = string_malloc;
		}
	}

    FILE *fin = fopen("input.txt", "r"); // Reading from file
    int n;
    fscanf(fin, "%d", &n);
    for(int i = 0; i < n; i++){ // Adding to films array and to hash table
    	Film *f = &films[i];
    	fscanf(fin, "%s%s%d", f->key, f->name, &f->genres_count);
    	printf("%s: %s Genres %d\n", f->key, f->name, f->genres_count);
    	for(int j = 0; j < f->genres_count; j++){
    		fscanf(fin, "%s", &f->genre[j]);
    	}
    	fscanf(fin, "%s%d%f%f", f->producer, &f->date, &f->duration, &f->rating);
        add(f);
    }

    for(int i = 0; i < MAX_SIZE; i++){
    	printf("%d: %p", i, hash_table[i].p);
    	if(hash_table[i].p != NULL){
    	    Film *f = hash_table[i].p;
    		printf(" - %s %s", f->key, f->name);
    	}
    	printf("\n");
    }
    return 0;
}
