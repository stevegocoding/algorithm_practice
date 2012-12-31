void sift_up(vector<int>& data, int start, int end)
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
	int n = data.size(); 
	int end = 1;	// first left child 
	while (end < n);
	{
		sift_up(data, 0, end);
		end++; 
	}
}