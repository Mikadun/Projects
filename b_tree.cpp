#include <iostream>

struct t_node 
{
	int *keys;
	int keys_count;
	t_node **childs;
	bool leaf;

	t_node( int t, bool _leaf )
	{
		leaf = _leaf;
		keys = new int[2*t - 1];
		keys_count = 0;

		childs = new t_node* [2*t];
	}
};

class b_tree
{
public:
	b_tree() { root = nullptr; t = 3; }
	void insert( int key );
	void print( void );
	bool contain( int key );
	void remove( int key );

private:
	t_node* root;
	int t;
	
	t_node* find( t_node* node, int key );
	void print( t_node* node );
	void insert_node( t_node* node, int key );
	void split_childs( t_node* parent, int idx, t_node* node );
	bool is_full( t_node* node );

};

int main()
{
	b_tree tree;
	tree.insert(1);
	tree.insert(3);
	tree.insert(7);
	tree.insert(10);
	tree.insert(11);
	tree.insert(13);
	tree.insert(14);
	tree.insert(15);
	tree.insert(18);
	tree.insert(16);
	tree.insert(19);
	tree.insert(24);
	tree.insert(25);
	tree.insert(26);
	tree.insert(21);
	tree.insert(4);
	tree.insert(5);
	tree.insert(20);
	tree.insert(22);
	tree.insert(2);
	tree.insert(17);
	tree.insert(12);
	tree.insert(6);
	tree.print();
	return 0;
}

bool b_tree::contain( int key )
{
	if( root == nullptr )
		return false;
	return find( root, key ) != nullptr;
}

t_node* b_tree::find( t_node* node, int key )
{
	int i = 0;
	for( i = 0; i < node->keys_count && key > node->keys[i]; i++ );

	if( node->keys[i] == key )
		return node;

	if( node->leaf )
		return nullptr;

	return find( node->childs[i], key );
}

void b_tree::print( void )
{
	if( root != nullptr)
		print( root );
}

void b_tree::print( t_node* node )
{
	for( int i = 0; i <= node->keys_count; i++ )
	{
		if( !node->leaf )
			print( node->childs[i] );

		if( i < node->keys_count)
			std::cout << " " << node->keys[i];
	}
}

bool b_tree::is_full( t_node* node )
{
	return node->keys_count == 2*t - 1;
}

void b_tree::insert( int key )
{
	if( root == nullptr )
	{
		root = new t_node( t, true );
		root->keys[0] = key;
		root->keys_count = 1;
	}
	else
	{
		if( is_full( root ) )
		{
			t_node *new_root = new t_node(t, false);
			new_root->childs[0] = root;
			split_childs( new_root, 0, root );

			if( new_root->keys[0] < key )
				insert_node( new_root->childs[1], key );
			else
				insert_node( new_root->childs[0], key );

			root = new_root;
		}
		else
		{
			insert_node( root, key );
		}
	}
}

void b_tree::insert_node( t_node* node, int key )
{
	int i = node->keys_count - 1;
	if( !node->leaf )
	{
		while( i >= 0 && node->keys[i] > key )
			i--;
		i++;

		if( is_full( node->childs[i] ) )
		{
			split_childs( node, i, node->childs[i] );
			if( node->keys[i] < key )
				i++;
		}

		insert_node( node->childs[i], key );
	}
	else // If is leaf, just put it
	{
		while( i >= 0 && node->keys[i] > key )
		{
			node->keys[i+1] = node->keys[i];
			i--;
		}

		node->keys[i+1] = key;
		node->keys_count++;
	}
}

void b_tree::split_childs( t_node* parent, int idx, t_node* node )
{
	t_node* temp = new t_node( t, node->leaf );
	temp->keys_count = t - 1;

	for( int i = 0; i < t - 1; i++ )
		temp->keys[i] = node->keys[i+t];

	if( !node->leaf )
		for( int i = 0; i < t; i++ )
			temp->childs[i] = node->childs[i+t];

	node->keys_count = t - 1;

	for( int i = parent->keys_count; i > idx; i-- )
		parent->childs[i+1] = parent->childs[i];

	for( int i = parent->keys_count; i >= idx; i-- )
		parent->keys[i+1] = parent->keys[i];

	parent->childs[idx+1] = temp;
	parent->keys[idx] = node->keys[t-1];
	parent->keys_count++;
}

