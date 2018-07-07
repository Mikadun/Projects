#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

typedef string t_key;

struct t_node
{
	t_key key;
	t_node *left;
	t_node *right;
	t_node( t_key _key ) { key = _key; left = right = NULL; }
};

class t_tree
{

public:
	void set( t_key exp );
	float calc( void );
	void print( void );
	t_tree() { root = NULL; }

private:
	t_node* root;

	t_node* add( t_key key );
	float get_value( t_node* node );
	void print( t_node* node );

	int last_op( t_key key );
	int get_priority( char op );
};

int main()
{
    t_tree tree;
    string str;
    cin >> str;
    tree.set( str );
    //tree.print();
    cout << endl << tree.calc();
	return 0;
}

void t_tree::set( t_key exp )
{
	root = add( exp );
}

void t_tree::print( void )
{
	print( root );
}

float t_tree::calc( void )
{
	if( root ) return get_value( root );
	return 0;
}

t_node* t_tree::add( t_key key )
{
	t_node* node;
	if( last_op( key ) != -1 )
	{
		int idx = last_op( key );
		node = new t_node( string(1, key[idx]) );
		node->left = add( key.substr( 0, idx ) );
		node->right = add( key.substr( idx + 1, key.length() - idx - 1 ) );
	}
	else
	{
		node = new t_node( key );
	}

	return node;
}

void t_tree::print( t_node* node )
{
	if( node )
	{
		print( node->left );
		std::cout << node->key;
		print( node->right );
	}
}

float t_tree::get_value( t_node* node )
{
	if( node->left && node->right )
	{
		float a = get_value( node->left );
		float b = get_value( node->right );
		switch( node->key[0] )
		{
			case '+': return a + b;
			case '-': return a - b;
			case '*': return a * b;
			case '/': return a / b;
		}
	}

	return strtof( node->key.c_str(), NULL );
}


int t_tree::last_op( t_key key )
{
	int idx = 0;
	for( int i = 0; i < key.length(); i++ )
	{
		if( get_priority(key[i]) >= get_priority(key[idx]) )
			idx = i;
	}

	return get_priority(key[idx]) ? idx : -1;
}

int t_tree::get_priority( char op )
{
	switch( op )
	{
		case( '+' ): return 2;
		case( '-' ): return 2;
		case( '*' ): return 1;
		case( '/' ): return 1;
	}
	return 0;
}
