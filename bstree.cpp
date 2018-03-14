#include <iostream>
using namespace std;

struct node 
{
	int key;
	node *left, *right;
	int height;
	node(int k) 
	{
		key = k;
		left = 0;
		right = 0;
		height = 1;
	}
};

node* find_min(node *p)
{
	if(p->left)
		return find_min(p->left);
	else if(p->right)
		return find_min(p->right);
	else
	{
		return p;
	}
}


node* find_max(node *p)
{
	if(p->right)
		return find_max(p->right);
	else if(p->left)
		return find_max(p->left);
	else
	{
		return p;
	}
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
	if(p->key == k)
	{
		if(p->right)
		{
			node* temp = p;
			p = find_min(p->right);
			p->left = temp->left;
			p->right = temp->right;
			delete temp;
		}
		else if(p->left)
		{
			node* temp = p;
			p = find_max(p->left);
			p->left = temp->left;
			p->right = temp->right;
			delete temp;
		}
		else
		{
			delete p;
			p = NULL;
		}
	} else 
	{
		if(k < p->key)
			p->left = remove(p->left, k);
		else
			p->right = remove(p->right, k);
	}
	return p;
}

void print(node *p){
	if(p)
	{
		print(p->left);
		cout << p->key << " ";
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
	root = remove(root, 20);
	print(root);
}
