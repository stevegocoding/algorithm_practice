int bsearch(vector<int>& data, int key, int low, int high)
{
	if (low > high) 
		return -1; 
	
	int mid = low + ((high - low) >> 1); 
	if (key < data[mid]) 
		binary_search(data, key, low, mid-1); 
	else if (key > data[mid])
		binary_search(data, key, mid+1, high); 
	else  
		return mid; 
}