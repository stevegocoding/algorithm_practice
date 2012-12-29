#include <iostream>
#include <fstream> 
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <time.h>
#include "gtest/gtest.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
// Utilities 
//////////////////////////////////////////////////////////////////////////

void rands_init()
{
	srand((unsigned int)time(NULL)); 
}

void gen_rand_int(std::vector<int>& rands, int min, int max, int num = -1)
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







//////////////////////////////////////////////////////////////////////////
// Sorting Algorithms
//////////////////////////////////////////////////////////////////////////

// Quick Sort 
int partition(vector<int>& data, int start, int end) 
{
	if (data.empty() || 
		start < 0 || end >= (int)data.size())
		cerr << "Invalid Parameters" << endl; 

	int pivot_idx = data.size() / 2; 
	swap(data[pivot_idx], data[end]);
	
	int small = start - 1;  
	for (int i = start; i < end; ++i)	// note that here is i < end, what if i <= end ? 
	{
		if (data[i] < data[end])
		{
			small++; 
			if (small != i)
				swap(data[i], data[small]); 
		}
	}
	
	++ small; 
	swap(data[small], data[end]);
	
	return small; 
}

void quick_sort(vector<int>& data, int start, int end) 
{ 
	if (start < end)
	{
		int idx = partition(data, start, end); 
		quick_sort(data, start, idx - 1);
		quick_sort(data, idx + 1, end);
	}
}  

void quick_sort_ite(vector<int>& data)
{
	int start = 0; 
	int end = data.size() - 1;
	int idx; 
	stack<int> s; 

	do 
	{
		while (start < end)
		{
			idx = partition(data, start, end); 

			if ((idx-start) < (idx-end))
			{
				s.push(idx+1);
				s.push(end); 
				end = idx - 1 ; 
			} 
			else 
			{
				s.push(start); 
				s.push(idx-1); 
				start = idx + 1;
			}

			if (s.empty())
				return;

			end = s.top(); 
			s.pop(); 
			start = s.top(); 
		}

	}while(1);
	
}

// End of Quick Sort 


// Merge Sort
void merge_array(vector<int>& data, int low, int mid, int high, vector<int>& temp)
{
	int p1 = low; 
	int end1 = mid; 
	int p2 = mid + 1; 
	int end2 = high;
	int k = 0; 

	while (p1 <= end1 && p2 <= end2)
	{
		if (data[p1] <= data[p2])
			temp[k] = data[p1]; 
		else 
			temp[k] = data[p2]; 
		p1++; 
		p2++; 
		k++; 
	}
	
	while (p1 <= end1)
	{
		temp[k] = data[p1]; 
		p1++; 
		k++; 
	}

	while (p2 <= end2)
	{
		temp[k] = data[p2]; 
		p2++; 
		k++; 
	}

	for (unsigned int i = 0; i < temp.size(); ++i)
		data[low+i] = temp[i]; 
}

void merge_sort(vector<int>& data, int low, int high, vector<int>& temp)
{
	if (low < high)
	{
		int mid = low + (high - low) / 2; 
		merge_sort(data, low, mid, temp); 
		merge_sort(data, mid+1, high, temp); 
		merge_array(data, low, mid, high, temp); 
	}
}
// End of Merge Sort


//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// Searching Algorithm 
//////////////////////////////////////////////////////////////////////////

int binary_search(const vector<int>& data, int key)
{
	int n = data.size();
	int left = 0; 
	int right = n - 1;
	
	while (left <= right) 
	{
		int mid = left + ((right - left) >> 1); 

		if (key < data[mid])
			right = mid - 1; 
		else if (key > data[mid])
			left = mid + 1; 
		else 
			return mid; 
	}
	
	return -1;
}

int binary_search_rec(const vector<int>& data, int key, int left, int right)
{
	if (left > right)
		return -1; 

	int mid = left + ((right - left) >> 1); 

	if (key < data[mid])
		return binary_search_rec(data, key, left, mid-1);
	else if (key > data[mid])
		return binary_search_rec(data, key, mid+1, right); 
	else 
		return mid; 
}

//////////////////////////////////////////////////////////////////////////
/// Unit Tests
//////////////////////////////////////////////////////////////////////////

int compare (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

TEST(QuickSortTest, CLRSImpl)
{
	int a[] = {8, 7, 1, 3, 5, 6, 4};
	int n = sizeof(a)/sizeof(int);
	vector<int> data(a, a + n); 
	
	std::qsort(a, n, sizeof(int), compare);
	quick_sort(data, 0, n - 1);
	vector<int> std_sorted(a, a + n);
	
	bool eq = std::equal(data.begin(), data.end(), std_sorted.begin());

	EXPECT_TRUE(eq); 
}

TEST(BinarySearchTest, IterativeImpl)
{
	int a[] = {5, 6, 7, 8, 9, 10}; 
	vector<int> data(a, a + sizeof(a)/sizeof(int)); 
	int pos = binary_search(data, 8);
	
	EXPECT_EQ(pos, 3); 
}

TEST(BinarySearchTest, RecursiveImpl)
{ 
	int a[] = {5, 6, 7, 8, 9, 10}; 
	vector<int> data(a, a + sizeof(a)/sizeof(int)); 
	int pos = binary_search_rec(data, 8, 0, data.size()-1);

	EXPECT_EQ(pos, 3); 
}


//////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	rands_init();

	std::cout << "Running tests" << std::endl;

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS(); 

	/*
	std::vector<int> rands; 
	gen_rand_int(rands, 1, 10, 30); 
	
	ostream_iterator<int> os_it(cout, ", ");
	std::copy(rands.begin(), rands.end(), os_it); 
	*/
	return 0; 
} 