#include <vector>
#include <iostream>
#include <iterator>
#include "utils.h"
#include "gtest/gtest.h"

using namespace std;

/**
 * ΢������100�� 5.
 * ����n�����������������С��k����
 * @TODO:
	- ����qsort��partition�㷨��ʵ��ѡ��
	- ����ʱ�临�Ӷ�
 */ 

/* 
	����1�� ����С����
*/

bool is_min_heap(const vector<int>& data, int i)
{
	int left = 2 * i + 1; 
	int right = left + 1;
	int n = data.size(); 
	if (i >=n || left >= n)
		return true; 
	else 
	{
		if (data[i] > data[left])
			return false;
		if (right < n && data[i] > data[right])
			return false; 
	}
	return is_min_heap(data, left) && is_min_heap(data, right); 
}

void sift_down(vector<int>& data, int start, int end) 
{
	int root = start; 
	while (root * 2 + 1 <= end)
	{
		int left = root * 2 + 1; 
		int s = root;
		if (data[s] > data[left])
			s = left; 
		if ((left + 1) <= end && data[s] > data[left+1])
			s = left + 1; 
		if (s != root)
		{
			swap(data[root], data[s]);
			root = s; 
		}
		else 
			return;
	}
}

void min_heapify(vector<int>& data)
{
	int n = data.size(); 
	int start = (n - 2) / 2;
	while (start >= 0)
	{
		sift_down(data, start, n-1); 
		start--; 
	}
}

int get_min(vector<int>& data, int count, int k)
{ 
	int min = data[0]; 
	swap(data[0], data[count-1]); 
	int j = k - 1; 
	while (j > 0)
	{ 
		sift_down(data, 0, k); 
		j--; 
	}
	return min;
}

void k_min(vector<int>& data, int k, vector<int>& out)
{
	int n = data.size(); 
	min_heapify(data);		// build a min heap 
	while (k > 0)
	{
		int min = get_min(data, n, k); 
		n--; 
		k--;
		out.push_back(min); 
	} 
}

// -----------------------------------------------
// TESTS 
TEST(isMinHeapTest, minHeap)
{
	int a[] = {10, 38, 20, 49, 76, 65, 49, 97}; 
	vector<int> data(a, a + sizeof(a)/sizeof(int)); 
	bool res = is_min_heap(data, 0);
	EXPECT_TRUE(res); 
}

TEST(minHeapifyTest, positive)
{
	std::vector<int> data; 
	gen_rand_int(data, 10, 50, 10); 
	
	// Print original data 
	cout << "Input: " << endl;
	ostream_iterator<int> os_it(cout, ", ");
	std::copy(data.begin(), data.end(), os_it); 

	cout << endl; 
	
	// Heapify 
	min_heapify(data);

	cout << "After heapfiy: " << endl; 
	ostream_iterator<int> os_it2(cout, ", ");
	std::copy(data.begin(), data.end(), os_it2); 

	cout << endl; 

	bool res = is_min_heap(data, 0); 

	EXPECT_TRUE(res); 
}

TEST(kMinTest, positive)
{
	std::vector<int> data; 
	gen_rand_int(data, 10, 50, 10); 

	// Print original data 
	cout << "Input: " << endl;
	ostream_iterator<int> os_it(cout, ", ");
	std::copy(data.begin(), data.end(), os_it); 

	cout << endl; 

	vector<int> mins; 
	k_min(data, 4, mins); 
	
	// Print results
	cout << "K Mins: " << endl;
	ostream_iterator<int> os_it2(cout, ", ");
	std::copy(mins.begin(), mins.end(), os_it2);

	cout << endl; 
}


//////////////////////////////////////////////////////////////////////////

/**
 * ΢������100�� 9.
 * ����һ���������У��ж����Ƿ���һ������������ĺ���������.
 * ˼·��
	����������ĺ����������һ��Ԫ�ؿ϶�Ϊ���ڵ㣬����ֳ����������У��ֱ������������������ݹ�ʵ��
 */ 

bool is_bst_postorder(vector<int>& data, int start, int end)
{
	if (data.empty() || start > end) 
		return false; 
	int root = data[end];
	int i = start;
	for (; i < end; ++i)
	{
		if (data[i] > root) 
			break; 

	}
	int j = i;
	for (; j < end; ++j) 
	{
		if (data[j] < root) 
			return false; 
	}
	bool left = true;
	if ((i-1) > start)
		left = is_bst_postorder(data, start, i-1); 
	bool right = true; 
	if ((end-1) > i)
		right = is_bst_postorder(data, i, end-1); 

	return left && right;
}

// -----------------------------------------------
// TESTS 

TEST(createBSTTest, normalInput)
{
	std::vector<int> data; 
	gen_rand_int(data, 10, 50, 10); 

	// Print original data 
	cout << "Input: " << endl;
	ostream_iterator<int> os_it(cout, ", ");
	std::copy(data.begin(), data.end(), os_it); 

	cout << endl; 

	bst_node *root = create_bst(data); 
	
	// Print BST inorder
	inorder_print(root); 

	cout << endl; 
}

TEST(isBSTPostOrder, bstInput)
{
	//int a[] = {19, 42, 42, 22, 49, 37, 45, 14, 21, 31};
	//int a[] = {28, 13, 49, 31, 30, 41, 12, 34, 11, 31};
	//std::vector<int> data(a, a+sizeof(a)/sizeof(int)); 
	std::vector<int> data; 
	gen_rand_int(data, 10, 50, 10); 

	// Print original data 
	cout << "Input: " << endl;
	ostream_iterator<int> os_it(cout, ", ");
	std::copy(data.begin(), data.end(), os_it); 

	cout << endl; 

	bst_node *root = create_bst(data); 

	// BST postorder to array 
	std::vector<int> bst_array;
	postorder_array(root, bst_array); 
	cout << "Post order array: " << endl; 
	std::copy(bst_array.begin(), bst_array.end(), os_it); 

	cout << endl;

	// Verify 
	bool res = is_bst_postorder(bst_array, 0, bst_array.size()-1); 

	EXPECT_TRUE(res);

	cout << endl; 
}


////////////////////////////////////////////////////////////////////////// 

/**
 * ΢������100�� 11
 * ��������ڵ��������
 */ 

//////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	rands_init();

	std::cout << "Running tests" << std::endl;

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS(); 
	
	return 0; 
} 