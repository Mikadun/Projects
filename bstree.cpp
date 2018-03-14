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
void print(t_node *);

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
	root = remove(root, 10);
	print(root);
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
	return node;
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
			return temp;
		}
		else if(node->right == NULL)
		{
			t_node *temp = node->left;
			delete node;
			return temp;
		}
		t_node *temp = find_min(node->right);
		node->key = temp->key;
		node->right = remove(node->right, node->key);
	}
	return node;
}

void print(t_node *node)
{
	if(node)
	{
		print(node->left);
		cout << node->key << " ";
		print(node->right);
	}
}
