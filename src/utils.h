#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_set>
#include <deque>
#include <array>
#include <iomanip>  
#include <stdlib.h>
#include <time.h>
#include <assert.h>


using namespace std;

#define SAFE_DELETE(p) if ((p)) {delete (p); (p) = NULL; }
#define SAFE_DELETE_ARRAY(p) if ((p)) {delete[] (p); (p) = NULL; }

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

//////////////////////////////////////////////////////////////////////////
// Matrix 
//////////////////////////////////////////////////////////////////////////
int **alloc_matrix(int n); 
void free_matrix(int **mat, int n); 
void fill_matrix(int **mat, int n, const std::vector<int>& data); 
void print_matrix(int **mat, int n, std::ostream& os = std::cout,  int prec = 4, int width = 8); 

void rands_init();
void gen_rand_int(std::vector<int>& rands, int min, int max, int num = -1); 

template <class T>
class c_leetcode_solution
{
	
public:
	static void run_test()
	{
		T *instance = new T();
		
		instance->test();

		delete instance; 
	}

	virtual void test()
	{
	}
};

#endif