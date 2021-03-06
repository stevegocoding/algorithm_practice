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

/**
	找最小的四个数
 */

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


int main(int argc, char **argv)
{
	
	
	return 0;
}