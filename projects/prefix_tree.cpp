#include <iostream>
#include <string>

using namespace std;

typedef int t_value;

class t_node
{
public:
	t_value value;
	char key;

	t_node* child;

	t_node* next;

	bool is_value;

	t_node( char key, t_node* sibling )
	{
		this->key = key;
		this->child = nullptr;
		this->next = sibling;
		this->is_value = false;
	}

	t_node( char key, t_value value, t_node* sibling, bool is_value )
	{
		this->key = key;
		this->child = nullptr;
		this->next = sibling;
		this->is_value = is_value;
		this->value = value;
	}

}; // t_node


class t_tree
{
private:
	t_node* root;

	t_node* insert( t_node* node, string keys, int idx, t_value value, t_node* sibling )
	{
		char key = keys[ idx ];
		t_node* temp = node->child;
		t_node* prev = temp;

		while( temp != nullptr && key > temp->key )
		{
			prev = temp;
			temp = temp->next;
		}

		if( temp != nullptr && temp->key == key )
		{
			if( idx == keys.length() - 1 )
			{
				temp->value = value;
				temp->is_value = true;
			}
			else
			{
				temp = insert( temp, keys, idx + 1, value, sibling );
			}
		}
		else // if node doesn't exist
		{
			if( prev == temp ) // if node had no childs (or it will be first in order child), then create new and add link to parent
				node->child = insert_new( keys, idx, value, temp );
			else // if node had childs, create new and reconnect links
				prev->next = insert_new( keys, idx, value, temp );
		}

		return node;

	} // insert

	t_node* insert_new( string keys, int idx, t_value value, t_node* sibling )
	{
		t_node* temp = new t_node( keys[idx], value, sibling, idx == keys.length() - 1 );
		if( idx < keys.length() - 1 )
		{
			temp = insert( temp, keys, idx + 1, value, sibling );
		}

		return temp;
	} // insert_new

	void print( t_node* node, char* key, int idx )
	{

		t_node* temp = node->child;

		while( temp != nullptr )
		{
			key[idx] = temp->key;
			if( temp->is_value )
			{
				for( int i = 0; i <= idx; i++ )
					std::cout << key[i];
				std::cout << ": " << temp->value << std::endl;
			}

			print( temp, key, idx + 1 );

			temp = temp->next;
		}
	} // print

	t_value* get_value( t_node* node, string keys, int idx )
	{
		t_node* temp = node->child;
		char key = keys[idx];

		while( temp != nullptr && key > temp->key )
			temp = temp->next;

		if( temp != nullptr && temp->key == key )
			if( idx == keys.length() - 1 )
				return temp->is_value ? &( temp->value ) : nullptr;
			else
				return get_value( temp, keys, idx + 1 );
		else
			return nullptr;
	} // get_value

public:
	// constructor create empty root, that will not storage values, but childs
	t_tree() { root = new t_node( '#', nullptr ); }

	void insert( string keys, t_value value )
	{
		root = insert( root, keys, 0, value, nullptr );
	}

	void print()
	{
		const int MAX_SIZE = 100;
		char* key = new char[ MAX_SIZE ];
		print( root, key, 0 );
	}

	t_value operator[] ( string keys )
	{
		t_value* value = get_value( root, keys, 0 );
		return value != nullptr ? *value : -1;
	}

	void operator() ( string keys, t_value value )
	{
		insert( keys, value );
	}

}; // t_tree

int main()
{
	t_tree tree;
	tree.insert( "hello", 12 );
	tree.print();
	return 0;
}