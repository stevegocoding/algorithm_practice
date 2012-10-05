#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

struct bstree_node
{
	bstree_node(int _val)
		: val(_val) 
		, left(NULL)
		, right(NULL)
	{}

	int val;
	bstree_node *left, *right; 
};

// BS tree root
bstree_node *bstree_root = NULL; 

// Double list
typedef bstree_node bstree_dbl_list;
bstree_dbl_list *head = NULL;
bstree_dbl_list *list_p = NULL; 

void add_bstree_node(bstree_node *& node_p, int val)
{
	if (!node_p)
		node_p = new bstree_node(val);
	else 
	{
		if (val < node_p->val)
			add_bstree_node(node_p->left, val); 
		else if (val > node_p->val)
			add_bstree_node(node_p->right, val); 
	}
}

void create_bstree(bstree_node *& root, const vector<int>& vals_vec)
{
	if (vals_vec.empty())
		return; 
	
	vector<int>::const_iterator it; 
	for (it = vals_vec.begin(); it != vals_vec.end(); ++it)
		add_bstree_node(root, *it);
}

void tree_to_list(bstree_node *node_p)
{
	node_p->left = list_p;
	
	if (NULL != list_p)
		list_p->right = node_p; 
	else 
		head = node_p; 

	list_p = node_p; 	
}

void inorder_trav_bstree(bstree_node *node_p)
{
	if (NULL == node_p)
		return; 
	if (NULL != node_p->left)
		inorder_trav_bstree(node_p->left);

	// link to list 
	tree_to_list(node_p);

	if (NULL != node_p->right)
		inorder_trav_bstree(node_p->right); 
}
	
int main(int argc, char **argv)
{
	ifstream ifs("ms100_01.in");

	vector<int> data_vec;
	copy(istream_iterator<int>(ifs), istream_iterator<int>(), back_inserter(data_vec));
	
	ifs.close();

	create_bstree(bstree_root, data_vec); 
	inorder_trav_bstree(bstree_root); 

	bstree_dbl_list *p = head; 
	while (p)
	{
		cout << p->val << " "; 
		p = p->right; 
	}

	return 0;
}