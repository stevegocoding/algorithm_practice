#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <queue>

#define SAFE_DELETE(p) if (p) {delete (p); (p) = NULL; }

using namespace std; 

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

void print_by_level(bstree_node *root)
{
	// Empty tree
	if (!root)
		return; 

	queue<bstree_node*> que; 
	que.push(root);
	
	while (!que.empty())
	{
		bstree_node *node_p = que.front();
		cout << node_p->val << " " ; 
		que.pop(); 
		if (node_p->left)
			que.push(node_p->left); 
		if (node_p->right) 
			que.push(node_p->right);	 
	} 
}

void find_path(bstree_node *node_p, std::vector<int>& path, int sum, int expected_sum) 
{
	if (!node_p)
		return; 

	sum += node_p->val; 
	path.push_back(node_p->val); 

	bool is_leaf = (!node_p->left) && (!node_p->right);
	if (sum == expected_sum && is_leaf) 
	{
		vector<int>::iterator it = path.begin(); 
		for (; it != path.end(); ++it)
			cout << *it << " "; 
		cout << std::endl;

		return; 
	}

	if (node_p->left)
		find_path(node_p->left, path, sum, expected_sum); 
	if (node_p->right) 
		find_path(node_p->right, path, sum, expected_sum);
	
	sum -= node_p->val; 
	path.pop_back();  
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

	std::vector<int> path; 
	find_path(root, path, 0, 41); 
	
	// Destroy the bst
	destroy_bstree(root);

	return 0; 
}