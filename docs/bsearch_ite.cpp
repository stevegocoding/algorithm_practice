int bsearch(const vector<int>& data, int key)
{
	int low = 0; 
	int high = data.size() - 1;
	while (low <= high)
	{
		int mid = low + ((high - low) >> 1); 
		if (key < data[mid]) 
			high = mid - 1;
		else if (key > data[mid])
			low = mid + 1; 
		else 
			return mid;
	}
	return -1; 
}