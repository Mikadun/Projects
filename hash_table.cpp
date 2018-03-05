#include <iostream>
#include <string>

using namespace std;

const int max_len = 255;

typedef string key_type;
typedef int value_type;

struct List {
	key_type key;
	value_type value;
	List *next;
};

List *hash_table = new List[max_len]; // new sets next pointers to zero. It's rly good

int hash_function(key_type key){
	int hash_value = 0;
    for(int i = 0; i < key.length(); i++){
    	hash_value += (int) key[i];
    }
    return hash_value % max_len;
}

int print(List *h){
	for(int i = 0; i < max_len; i++){
		List *p = &h[i];
		while(p->next != NULL){
			p = p->next;
			cout << i << ": " << p->key << " " << p->value << endl;
		}
	}
}

int add_hash(List *h, key_type key, value_type value){
	int index = hash_function(key);
	List *p = &h[index];
	while(p->next != NULL){
		p = p->next;
	}
	List *temp = new List;
	temp->key = key; // Key or hash_function(key) ?
	temp->value = value;
    p->next = temp;
}

List* search_hash(List *h, key_type key, value_type value){
    int index = hash_function(key);
    List *p = &h[index];
    while(p->next != NULL){
        p = p->next;
        if(p->value == value){
            return p; // Found
        }
    }
    return NULL; // Not found
}

int delete_hash(List *h, key_type key, value_type value){
    int index = hash_function(key);
    List *p = &h[index];
    while(p->next != NULL){
        List *temp = p->next;
        if(temp->value == value){
            p->next = temp->next;
            delete temp;
            return 0; // Successful
        }
        p = temp;
    }
    return -1; // Not found
}

int main(){
    //cout << "1. 'a' code is " << hash_function("a") << endl;
	//cout << "2. summary code is 352. So 352 % 255 is " << hash_function("a .  q");
	add_hash(hash_table, "a", 12);
	add_hash(hash_table, "a .  q", 10);
	delete_hash(hash_table, "a", 12);
	print(hash_table);
	return 0;
}
