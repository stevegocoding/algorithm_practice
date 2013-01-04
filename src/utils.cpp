#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <deque>
#include "utils.h"

using namespace std;

#define SAFE_DELETE(p) if ((p)) {delete (p); (p) = NULL; }

////////////////////////////////////////////////////////////////////////// 
// Data Structures
//////////////////////////////////////////////////////////////////////////
void add_bst_node(bst_node *&p, int val)
{
	if (!p)
	{
		p = new bst_node(val);
		return;
	}
	else if (val < p->val)
		add_bst_node(p->left, val);
	else 
		add_bst_node(p->right, val);
}

bst_node *create_bst(const vector<int>& a)
{
	if (a.empty())
		return NULL;  
	bst_node *root = new bst_node(a[0]); 
	for (unsigned int i = 1; i < a.size(); ++i)
		add_bst_node(root, a[i]); 

	return root; 
}

void delete_bst(bst_node *node)
{
	if (!node)
		return; 
	delete_bst(node->left);
	delete_bst(node->right);
	SAFE_DELETE(node); 
}

void inorder_print(bst_node *node)
{
	if (!node)
		return; 
	inorder_print(node->left); 
	cout << node->val << ", ";
	inorder_print(node->right); 
}

void postorder_array(bst_node *node, vector<int>& a)
{
	if (!node)
		return; 
	postorder_array(node->left, a);
	postorder_array(node->right,a); 
	a.push_back(node->val);
}

tree_node *create_tree_bfs(const vector<int>& a)
{
	if (a.empty())
		return NULL; 
	
	tree_node *root = new tree_node(a[0]);
	deque<tree_node**> q; 
	q.push_back(&root); 
	unsigned int i = 0; 
	while (i < a.size())
	{
		tree_node **t = q.front();
		q.pop_front(); 
		if (!(*t))
			*t = new tree_node(a[i]);
		i++; 
		q.push_back(&(*t)->left);
		q.push_back(&(*t)->right); 
	}
	return root;
}

void delete_tree(tree_node *node)
{
	if (!node)
		return; 
	delete_tree(node->left);
	delete_tree(node->right);
	SAFE_DELETE(node); 
}
//////////////////////////////////////////////////////////////////////////
// Utilities 
//////////////////////////////////////////////////////////////////////////

void rands_init()
{
	srand((unsigned int)time(NULL)); 
}

void gen_rand_int(std::vector<int>& rands, int min, int max, int num)
{
	assert(min < max); 

	rands.clear();

	int n = (num == -1)? max - min + 1 : num;

	for (int i = 0; i < n; ++i)
	{
		int r = min + (rand() % (int)(max - min + 1));
		rands.push_back(r); 
	}
} 