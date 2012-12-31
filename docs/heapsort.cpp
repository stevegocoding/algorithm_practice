void sift_down(vector<int>& data, int start, int end)
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
	int n = data.size(); 
	int start = (n - 2) / 2;	// last parent node
	while (start >= 0)
	{
		sift_down(data, start, n - 1); 
		start--; 
	}
}

void heap_sort(vector<int>& data)
{
	heapify(data);
	int n = data.size(); 
	int end = n - 1; 
	while (end >= 0) 
	{
		swap(data[end], data[0]);
		end--; 
		sift_down(data, 0, end); 
	}
}