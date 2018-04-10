#include <iostream>
struct t_node 
{
	int key;
	t_node *left, *right;
	int height;
	t_node(int _key) { key = _key; left = right = NULL; height = 1; }
};

class t_tree 
{
	public:
		t_tree() { _root = NULL; }

		void print_tree(void);
		void insert(int);
		bool search(int);
		void remove(int);
	private:
		t_node* _root;
		t_node* find_min(t_node *);
		t_node* insert_node(t_node *, int);
		t_node* search_node(t_node *, int);
		t_node* remove_node(t_node *, int);

		t_node* balance(t_node *);
		t_node* rotate_right(t_node *);
		t_node* rotate_left(t_node *);
		int height(t_node *);
		int fix_height(t_node *);
		int bfactor(t_node *);
		void print_node(t_node *);
};

int main()
{
	t_tree tree;
	tree.insert(5);
	tree.insert(1);
	tree.insert(4);
	tree.insert(-1);
	tree.remove(5);
	tree.print_tree();
}

void t_tree::print_tree(void)
{
	print_node(_root);
}

void t_tree::insert(int key)
{
	_root = insert_node(_root, key);
}

bool t_tree::search(int key)
{
	return search_node(_root, key) == NULL;
}

void t_tree::remove(int key)
{
	_root = remove_node(_root, key);
}

void t_tree::print_node(t_node *node)
{
	if(node)
	{
		print_node(node->left);
		std::cout << node->key << " ";
		print_node(node->right);
	}
}

t_node* t_tree::insert_node(t_node *node, int key)
{
	if(node == NULL) return new t_node(key);
	if(key < node->key)
		node->left = insert_node(node->left, key);
	else
		node->right = insert_node(node->right, key);
	return balance(node);
}

t_node* t_tree::search_node(t_node *node, int key)
{
	if(node == NULL || node->key == key) return node;
	if(key < node->key)
		return search_node(node->left, key);
	else
		return search_node(node->right, key);
}

t_node* t_tree::remove_node(t_node *node, int key)
{
	if(node == NULL) return node;
	if(key < node->key)
		node->left = remove_node(node->left, key);
	else if(key > node->key)
		node->right = remove_node(node->right, key);
	else
	{
		if(node->left == NULL || node->right == NULL)
		{
			t_node *temp = node->left ? node->left : node->right;
			if(temp == NULL)
			{
				temp = node;
				node = NULL;
			}
			else
				*node = *temp;
			delete temp;
		}
		else
		{
			t_node *temp = find_min(node->right);
			node->key = temp->key;
			node->right = remove_node(node->right, node->key);
		}
	}
	return balance(node);
}


int t_tree::height(t_node *node)
{
	if(node == NULL)
		return 0;
	else
		return node->height;
}

int t_tree::fix_height(t_node *node)
{
	int hl = height(node->left);
	int hr = height(node->right);
	node->height = (hl > hr ? hl : hr) + 1;
}

int t_tree::bfactor(t_node *node)
{
	return height(node->right) - height(node->left);
}

t_node* t_tree::rotate_right(t_node *node)
{
	t_node* temp = node->left;
	node->left = temp->right;
	temp->right = node;
	fix_height(node);
	fix_height(temp);
	return temp;
}

t_node* t_tree::rotate_left(t_node *node)
{
	t_node* temp = node->right;
	node->right = temp->left;
	temp->left = node;
	fix_height(node);
	fix_height(temp);
	return temp;
}

t_node* t_tree::balance(t_node *node)
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

t_node* t_tree::find_min(t_node *node)
{
	if(node->left)
		return find_min(node->left);
	return node;
}