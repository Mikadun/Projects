#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 255;

struct t_node 
{
	char key;
	int freq;
	t_node* left;
	t_node* right;
	t_node( char _key, int _freq ) { key = _key; left = right = nullptr; freq = _freq; }
};

class t_tree
{
public:
	t_node* root;
	string* encode_table;
	t_tree( string str );
	void build_tree( string str );
	t_node* combine_nodes( t_node* f_node, t_node* s_node );
	void make_table( );
	void traversal( t_node* node, string code );

	string encode( string str );
	string decode( string str );
	bool is_leaf( string str );
	t_node* get_node_by_way( string str );
};

int main()
{
	string input = "abracadabra"
	t_tree tree( input );
	for( int i = 0; i < MAX_SIZE; i++ )
	{
		if( tree.encode_table[i] != "" )
			cout << (char) i << " " << tree.encode_table[i] << endl;
	}

	string code = tree.encode( input );
	cout << code << endl;
	cout << tree.decode( code ) << endl;
	return 0;
}

t_tree::t_tree( string str )
{
	root = nullptr;

	build_tree( str );
}

bool cmp_func( t_node* f_node, t_node* s_node )
{
	return f_node->freq < s_node->freq;
}

void t_tree::build_tree( string str )
{
	int *count = new int[MAX_SIZE]{0};
	int subtrees_count = 0;
	t_node** subtrees = new t_node* [MAX_SIZE];
	for( int i = 0; i < str.length(); i++ )
		count[ str[i] ]++;

	for( int i = 0; i < MAX_SIZE; i++ )
	{
		if( count[i] )
		{
			subtrees[ subtrees_count++ ] = new t_node( i, count[i] );
		}
	}

	while( subtrees_count > 1 )
	{
		sort( subtrees, subtrees + subtrees_count, cmp_func );
		subtrees[0] = combine_nodes( subtrees[0], subtrees[1] );
		subtrees_count--;
		subtrees[1] = subtrees[subtrees_count];
	}

	root = subtrees[0];
	make_table( );
}

t_node* t_tree::combine_nodes( t_node* f_node, t_node* s_node )
{
	t_node* temp = new t_node( '#', f_node->freq + s_node->freq );
	temp->left = f_node;
	temp->right = s_node;
	return temp;
}

void t_tree::make_table( )
{
	encode_table = new string[MAX_SIZE]{""};
	traversal( root, "" );
}

void t_tree::traversal( t_node* node, string code )
{
	if( node->key != '#' )
		encode_table[node->key] = code;

	if( node->left && node->right )
	{
		traversal( node->left, code + '0' );
		traversal( node->right, code + '1' );
	}
}

string t_tree::encode( string str )
{
	string result = "";
	for( int i = 0; i < str.length(); i++ )
	{
		result += encode_table[ str[i] ];
	}
	return result;
}

bool t_tree::is_leaf( string str )
{
	return !get_node_by_way( str )->left;
}

t_node* t_tree::get_node_by_way( string str )
{
	t_node* node = root;
	for( int i = 0; i < str.length(); i++ )
	{
		node = str[i] == '0' ? node->left : node->right;
	}
	return node;
}

string t_tree::decode( string str )
{
	string temp = "";
	string result = "";
	for( int i = 0; i < str.length(); i++ )
	{
		temp += str[i];
		if( is_leaf( temp ) )
		{
			result += get_node_by_way( temp )->key;
			temp = "";
		}
	}
	return result;
}