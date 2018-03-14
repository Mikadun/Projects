#include <iostream>
using namespace std;

struct t_node 
{
	int key;
	t_node *left, *right;
	int height;
	t_node(int _key) { key = _key; left = right = NULL; height = 1; }
};

t_node* find_min(t_node *);
t_node* insert(t_node *, int);
t_node* search(t_node *, int);
t_node* remove(t_node *, int);

t_node* balance(t_node *);
t_node* rotate_right(t_node *);
t_node* rotate_left(t_node *);
int height(t_node *);
int fix_height(t_node *);
int bfactor(t_node *);

void print(t_node *);
void print_tree(t_node *, int);

int main()
{
	t_node *root = NULL;
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 32);
	root = insert(root, 25);
	root = insert(root, 15);
	root = insert(root, 16);
	root = insert(root, 12);
	root = insert(root, 5);
	root = insert(root, 8);
	root = remove(root, 25);
	print_tree(root, 0);
}

void print(t_node *node)
{
	if(node)
	{
		print(node->left);
		cout << node->height << ": " << node->key << endl;
		print(node->right);
	}
}

void print_tree(t_node *node, int depth)
{
	if(node)
	{
		cout << depth << ": " << node->key << endl;
		print_tree(node->left, depth + 1);
		print_tree(node->right, depth + 1);
	}
}

int height(t_node *node)
{
	if(node == NULL)
		return 0;
	else
		return node->height;
}

int fix_height(t_node *node)
{
	int hl = height(node->left);
	int hr = height(node->right);
	node->height = (hl > hr ? hl : hr) + 1;
}

int bfactor(t_node *node)
{
	return height(node->right) - height(node->left);
}

t_node* rotate_right(t_node *node)
{
	t_node* temp = node->left;
	node->left = temp->right;
	temp->right = node;
	fix_height(node);
	fix_height(temp);
	return temp;
}

t_node* rotate_left(t_node *node)
{
	t_node* temp = node->right;
	node->right = temp->left;
	temp->left = node;
	fix_height(node);
	fix_height(temp);
	return temp;
}

t_node* balance(t_node *node)
{
	if(!node)
		return node;
	fix_height(node);
	if(bfactor(node) == 2)
	{
		if(bfactor(node->right) < 0)
			node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	if(bfactor(node) == -2)
	{
		if(bfactor(node->left) > 0)
			node->left = rotate_left(node->left);
		return rotate_right(node);
	}
	return node;
}

t_node* find_min(t_node *node)
{
	if(node->left)
		return find_min(node->left);
	return node;
}

t_node* insert(t_node *node, int key)
{
	if(node == NULL) return new t_node(key);
	if(key < node->key)
		node->left = insert(node->left, key);
	else
		node->right = insert(node->right, key);
	return balance(node);
}

t_node* search(t_node *node, int key)
{
	if(node == NULL || node->key == key) return node;
	if(key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

t_node* remove(t_node *node, int key)
{
	if(node == NULL) return node;
	if(key < node->key)
		node->left = remove(node->left, key);
	else if(key > node->key)
		node->right = remove(node->right, key);
	else
	{
		if(node->left == NULL)
		{
			t_node *temp = node->right;
			delete node;
			return balance(temp);
		}
		else if(node->right == NULL)
		{
			t_node *temp = node->left;
			delete node;
			return balance(temp);
		}
		t_node *temp = find_min(node->right);
		node->key = temp->key;
		node->right = remove(node->right, node->key);
	}
	return balance(node);
}

/* Literature and other code examples
https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
https://gist.github.com/harish-r/a7df7ce576dda35c9660
https://gist.github.com/danicat/7075125
*/
