#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// Data Structures 
//////////////////////////////////////////////////////////////////////////

/**
	Binary Search Tree
 */
struct bst_node
{
	bst_node(int _val)
		: val(_val)
		, left(NULL)
		, right(NULL) 
	{ }

	int val; 
	bst_node *left, *right; 
};

bst_node *create_bst(const vector<int>& a); 
void delete_bst(bst_node *node);
void inorder_print(bst_node *node); 
void postorder_array(bst_node *node, vector<int>& a);

typedef bst_node tree_node; 
tree_node *create_tree_bfs(const vector<int>& a); 
void delete_tree(tree_node *node);

//////////////////////////////////////////////////////////////////////////

void rands_init();
void gen_rand_int(std::vector<int>& rands, int min, int max, int num = -1); 

#endif