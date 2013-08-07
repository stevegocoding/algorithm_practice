#include <iostream>
#include <fstream> 
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <time.h>

using namespace std; 

//////////////////////////////////////////////////////////////////////////
// Sorting Algorithms
//////////////////////////////////////////////////////////////////////////

// Quick Sort 
int partition(vector<int>& data, int start, int end) 
{
	if (data.empty() || 
		start < 0 || end >= (int)data.size())
		cerr << "Invalid Parameters" << endl; 

	int pivot_idx = (int)data.size() / 2; 
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
	int end = (int)data.size() - 1;
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


/// Heap Sort


void shift_down(vector<int>& data, int start, int end)
{
	int root = start;
	while (root * 2 + 1 <= end)
	{
		int child = root * 2 + 1; 
		int s = root; 
		if (data[s] < data[child])
			s = child; 
		if (child + 1 <= end && data[s] < data[child+1])
			s = child + 1; 
		if (s != root)
		{
			swap(data[root], data[s]); 
			root = s; 
		}
		else
			return; 
	}
}

void heapify(vector<int>& data)
{
	int n = (int)data.size(); 
	int start = (n - 2) / 2;	// last parent node
	while (start >= 0)
	{
		shift_down(data, start, n - 1); 
		start--; 
	}
}

void shift_up(vector<int>& data, int start, int end)
{
	int child = end;
	int parent = -1; 
	while (child > start)
	{
		parent = (child - 1) / 2; 
		if (data[parent] < data[child])
		{
			swap(data[parent], data[child]); 
			child = parent; 
		}
		else 
			return; 
	}
}

void heapify2(vector<int>& data)
{
	int n = (int)data.size(); 
	int end = 1;	// first left child 
	while (end < n);
	{
		shift_up(data, 0, end);
		end++; 
	}
}

void heap_sort(vector<int>& data)
{
	heapify(data);
	int n = (int)data.size(); 
	int end = n - 1; 
	while (end >= 0) 
	{
		swap(data[end], data[0]);
		end--; 
		shift_down(data, 0, end); 
	}
}

/// End of Heap Sort 
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// Searching Algorithm 
//////////////////////////////////////////////////////////////////////////

int binary_search(const vector<int>& data, int key)
{
	int n = (int)data.size();
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

/*

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
	int pos = binary_search_rec(data, 8, 0, (int)data.size()-1);

	EXPECT_EQ(pos, 3); 
} 

*/ 