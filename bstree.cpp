#include <iostream>

struct node 
{
	int key;
	node *left, *right;
	node(int k) { key = k; left = right = NULL; }
};

node* find_min(node *p)
{
	if(p->left)
		return find_min(p->left);
	return p;
}

node* insert(node *p, int k)
{
	if(!p) return new node(k);
	if(k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return p;
}

node* search(node *p, int k)
{
	if(!p || p->key == k) return p;
	if(k < p->key)
		return search(p->left, k);
	else
		return search(p->right, k);
}

node* remove(node *p, int k)
{
	if(!p) return p;
	if(k < p->key)
		p->left = remove(p->left, k);
	else if(k > p->key)
		p->right = remove(p->right, k);
	else
	{
		if(!p->left)
		{
			node *temp = p->right;
			delete p;
			return temp;
		}
		else if(!p->right)
		{
			node *temp = p->left;
			delete p;
			return temp;
		}
		node *temp = find_min(p->right);
		p->key = temp->key;
		p->right = remove(p->right, p->key);
	}
	return p;
}

void print(node *p){
	if(p)
	{
		print(p->left);
		std::cout << p->key << " ";
		print(p->right);
	}
}

int main()
{
	node *root = NULL;
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
