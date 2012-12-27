#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>
#include <iterator>

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

	int pivot_idx = data.size() / 2; 
	swap(data[pivot_idx], data[end]);
	
	int small = start - 1;  
	for (int i = start; i < end; ++i) 
	{
		if (data[i] < data[end])
		{
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
	if (start == end)
		return; 

	int idx = partition(data, start, end); 
	if (idx > start)
		quick_sort(data, start, idx - 1);
	if (idx < end) 
		quick_sort(data, idx + 1, start);
} 

// End of Quick Sort 
//////////////////////////////////////////////////////////////////////////




int main(int argc, char **argv)
{
	return 0; 
}