#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX_SIZE = 10;

typedef struct {
	string key;
	string name;
	vector<string> genre;
	string producer;
	int date;
	float duration;
	float rating;
} Data;

typedef struct {
	string key;
	Data *p;
} Hash_cell;

Hash_cell hash_table[MAX_SIZE];
Data* data[MAX_SIZE];
int counter = 0;

Data *data_constructor(string key, string name, vector<string> genre, string producer, int date, float duration, float rating){
	Data *temp = new Data;
	temp->key = key;
	temp->name = name;
	temp->genre = genre;
	temp->producer = producer;
	temp->date = date;
	temp->duration = duration;
	temp->rating = rating;
	return temp;
}

int is_cell_empty(int index){
	return hash_table[index].p == NULL;
}

int hash_function(string key, int i){
	return ((int) key[0] + (int) key[1] + i) % MAX_SIZE;
}

int add_hash(Data *d){
	int index;
	for(int i = 0; i <= MAX_SIZE; i++){
		if(i == MAX_SIZE)
			return -1; // Hash table is full to add this data
		index = hash_function(d->key, i);
		if(is_cell_empty(index))
			break;
	}
	data[counter++] = d;
	hash_table[index].key = d->key;
	hash_table[index].p = d;
	return 0; // Successeful
}

Data* search_hash(string key){
	int index;
	for(int i = 0; i <= MAX_SIZE; i++){
		if(i == MAX_SIZE)
			return NULL; // Not found
		index = hash_function(key, i);
		if(is_cell_empty(index))
			return NULL; // Not found
		if(hash_table[index].key == key)
			return hash_table[index].p; // Successful
	}
}

int delete_hash(string key){
	int index;
	for(int i = 0; i <= MAX_SIZE; i++){
		if(i == MAX_SIZE)
			return -1; // Not found
		index = hash_function(key, i);
		if(is_cell_empty(index))
			return -1; // Not found
		if(hash_table[index].key == key){
			;
			// Do we delete from data table too or hash table only?
			// Expected only hash table delete
		}
	}
}

int print(Data *d){
    if(d == NULL)
        return 0;
    cout << d->key << " " << d->name << " ";
    for(auto j : d->genre)
        cout << j << " ";
    cout << d->producer << " " << d->date << " "
         << d->duration << " " << d->rating << endl;
}

int print_all_data(){
	for(int i = 0; i < MAX_SIZE; i++){
        if(data[i] != NULL){
            cout << i << ": ";
            print(data[i]);
        }
	}
}

int main(){
    vector<string> genre {"Comedy", "Fantasy"};
    Data *a = data_constructor("ks", "KonoSuba", genre, "A-1 Project", 2012, 24.0, 8.12);
    add_hash(a);
    genre = {"Horror"};
    a = data_constructor("lr", "It", genre, "Sunrise", 2008, 154.0, 0.2);
    add_hash(a);
    print_all_data();
    print(search_hash("ks"));
    print(search_hash("lr"));
	return 0;
}
