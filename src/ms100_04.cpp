#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <deque>

#define SAFE_DELETE(p) if (p) {delete (p); (p) = NULL; }

struct bstree_node
{
	bstree_node(int _val)
		: val(_val) 
		, left(NULL)
		, right(NULL)
	{}

	~bstree_node() 
	{
		left = right = NULL; 
		// cout << "node: " << val << " has been deleted!" << endl; 
	}

	int val;
	bstree_node *left, *right; 
};

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

void destroy_bstree(bstree_node *& node_p)
{
	if (!node_p)
		return; 

	if (!node_p->left && !node_p->right) 
	{
		SAFE_DELETE(node_p);
		return; 	
	}

	destroy_bstree(node_p->left); 

	destroy_bstree(node_p->right); 

	SAFE_DELETE(node_p); 
}

int main(int argc, char **argv)
{
	ifstream ifs("ms100_04.in");
	vector<int> data_vec;
	copy(istream_iterator<int>(ifs), istream_iterator<int>(), back_inserter(data_vec));
	ifs.close();

	bstree_node *root = NULL; 

	// Create the bst
	create_bstree(root, data_vec);
	
	// Destroy the bst
	destroy_bstree(root);

	return 0; 
}