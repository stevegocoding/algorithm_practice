int partition(vector<int>& data, int low, int high) 
{
	int pivot = data[high]; 
	int small = low - 1;  
	for (int i = low; i < high; ++i) 
	{
		if (data[i] < data[high])
		{
			small++; 
			if (small != i)
				swap(data[i], data[small]); 
		}
	}
	++small; 
	swap(data[high], data[small]);
	return small; 
}

void quicksort(vector<int>& data, int low, int high)
{
	if (low < high)
	{
		int k = partition(data, low, high); 
		quicksort(data, low, k-1);
		quicksort(data, k+1, high); 
	}	
}