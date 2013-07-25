#include "utils.h"
#include "gtest/gtest.h"

/********************************************************************
	created:	2013/01/09
	created:	9:1:2013   21:55
	file base:	cracking_problems
	file ext:	cpp
	author:		Guangfu Shi
	
	purpose:	The solutions to questions in the book <<Cracking the Coding Interview>>. 
*********************************************************************/

/*
 *	Question 1.2
 */

void reverse_str(char *str)
{
	if (!str)
		return; 

	char *start = str;
	char *end = str; 
	
	while (*end)
		++end; 
	
	--end;
	
	while (start < end)
	{
		char tmp = *start;
		*start = *end;
		*end = tmp;
		++start;
		--end;
	}
}


/*
 *	Question 1.5
 */
string compress_str(const char *str, int length)
{
	stringstream ss;
	
	int repeat_count = 0;
	int i = 0;
	int j = i+1;
	while (j < length)
	{
		if (str[j] == str[i])
		{
			++repeat_count;
			++j;
		}
		else 
		{
			ss << str[i] << repeat_count;
			i = j;
			++j;
			repeat_count = 0;
		}
	}
	string compressed_str = ss.str();
	if (compressed_str.length() >= length)
		return string(str);
}


/** 
 * Question 1.6
 * Given an image represented by an NxN matrix, write a method to rotate the matrix by 90 degrees(in pleace).
 */
void rotate_mat_90(int **mat, int n)
{
	for (int layer = 0; layer < n / 2; ++layer)
	{
		int first = layer; 
		int last = n - 1 - layer; 
		for (int i = first; i < last; ++i)
		{
			int offset = i - first;
			// Save top 
			int top = mat[first][i];
			// top <= left
			mat[first][i] = mat[last-offset][first]; 
			// left <= bottom 
			mat[last-offset][first] = mat[last][last-offset]; 
			// bottom <= right 
			mat[last][last-offset] = mat[i][last]; 
			// right <= top
			mat[i][last] = top; 
		}
	} 
}

/** 
 * A related question: 
 * Print the matrix in spiral order 
 */ 
void print_matrix_spiral(int **mat, int n)
{
	int max_layer = (n % 2 == 0) ? n/2 : n/2 + 1; 
	for (int layer = 0; layer < max_layer; ++layer)
	{
		int first = layer; 
		int last = n - 1 - first; 
		if (first == last)		// If there is only 1 element in this layer, print it
		{
			std::cout << mat[first][first] << " ";
			continue;
		}
		for (int edge = 0; edge < 4; ++edge)
		{
			for (int i = first; i < last; ++i)
			{
				int offset = i - first; 
				if (edge == 0)		// Print top edge
					std::cout << mat[first][i] << " "; 
				if (edge == 1)		// Print right edge
					std::cout << mat[i][last] << " ";
				if (edge == 2)		// Print bottom edge
					std::cout << mat[last][last-offset] << " "; 
				if (edge == 3)		// Print left edge
					std::cout << mat[last-offset][first] << " "; 
			}
		}
	}
}

TEST(RotateMatrixTest, generalInput)
{
	int n = 4; 
	std::vector<int> data; 
	gen_rand_int(data, 10, 50, n*n);
	int **mat = alloc_matrix(n);
	fill_matrix(mat, n, data);
	std::cout << "Input matrix: " << std::endl;
	print_matrix(mat, n, cout, 1, 3); 

	rotate_mat_90(mat, n); 

	std::cout << "Rotated matrix: " << std::endl;
	print_matrix(mat, n, cout, 1, 3); 

	std::cout << std::endl; 

	free_matrix(mat, n);
}

TEST(PrintMatrixSpiralTest, generalInput)
{
	int n = 5; 
	std::vector<int> data; 
	gen_rand_int(data, 10, 50, n*n);
	int **mat = alloc_matrix(n);
	fill_matrix(mat, n, data);
	std::cout << "Input matrix: " << std::endl;
	print_matrix(mat, n, cout, 1, 3); 
	
	std::cout << "Print matrix in spiral order: " << std::endl;
	print_matrix_spiral(mat, n); 
	
	std::cout << std::endl; 

	free_matrix(mat, n); 
}