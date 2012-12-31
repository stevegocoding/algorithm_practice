#include <vector>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "utils.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
// Utilities 
//////////////////////////////////////////////////////////////////////////

void rands_init()
{
	srand((unsigned int)time(NULL)); 
}

void gen_rand_int(std::vector<int>& rands, int min, int max, int num)
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