#include "utils.h"

/********************************************************************
	created:	2013/01/09
	created:	9:1:2013   21:55
	file base:	cracking_problems
	file ext:	cpp
	author:		Guangfu Shi
	
	purpose:	The solutions to questions in the book <<Cracking the Coding Interview>>. 
*********************************************************************/


/*
 *	Question 1.1
 */
class AllUniqueChars : public c_solution<AllUniqueChars>
{
public: 
	
	bool is_unique_chars(string s)
	{
		bool chars[256];
		
		for (int i = 0; i < (int)s.length(); ++i)
		{
			if (chars[s[i]]) 
				return false; 
			chars[s[i]] = true; 
		}
		return true;
	} 
};


//////////////////////////////////////////////////////////////////////////


/*
 *	Question 1.2
 */ 
class ReverseCString : public c_solution<ReverseCString>
{
public:
	void reverse_str(char *str)
	{
		if (!str)
			return; 

		char *start = str;
		char *end = str; 

		while (*end && *end != '\0')
			++end; 

		while (start < end)
		{
			char tmp = *start;
			*start = *end;
			*end = tmp;
			++start;
			--end;
		}
	}
};

//////////////////////////////////////////////////////////////////////////

/*
 *	Question 1.3
 */
class RemoveDuplicateChars : public c_solution<RemoveDuplicateChars>
{
public:
	
	void remove_duplicate(string& s)
	{
		if (s.empty())
			return; 
		if (s.length() < 2)
			return; 
		
		int tail = 1; 
		for (int i = 1; i < (int)s.length(); ++i)
		{
			int j = 0;
			for (j = 0; j < tail; ++j)
			{
				if (s[j] == s[i])
					break; 
			}
			if (j == tail)
			{
				s[tail] = s[i];
				++tail; 
			}
		}

		s[tail] = 0; 
	} 

	void test()
	{
		string s = "aabc"; 

		remove_duplicate(s);
		
		cout << s << endl; 
	}
};


//////////////////////////////////////////////////////////////////////////

/*
 *	Question 1.4
 */
class Anagrams : public c_solution<Anagrams>
{
public:
	
	bool is_anagrams(string& s, string& t)
	{ 
		int letters[256]; 
		int num_unique_chars = 0; 
		int num_completed_t = 0; 

		for (int i = 0; i < (int)s.length(); ++i)
		{
			if (letters[s[i]] == 0)
				++num_unique_chars; 
			letters[s[i]]++;  
		}
		
		for (int j = 0; j < (int)t.length(); ++j)
		{
			if (letters[t[j]] == 0)
				return false;

			letters[t[j]]--; 

			if (letters[t[j]] == 0)
			{
				++num_completed_t; 
				if (num_completed_t == num_unique_chars)
				{
					return j == t.length()-1;
				}
			}
		}

		return false; 
	}
};


/*
 *	Question 1.5
 */

class ReplaceSpace : c_solution<ReplaceSpace>
{
};


/** 
 * Question 1.6
 * Given an image represented by an NxN matrix, write a method to rotate the matrix by 90 degrees(in pleace).
 */
class RotateMatrix90Degrees : public c_solution<RotateMatrix90Degrees>
{
public: 
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

	void test()
	{
	}
};


////////////////////////////////////////////////////////////////////////// 

/*
 *	Question 1.7
 */

class SetMatrixZero : public c_solution<SetMatrixZero>
{
public:
	
	void set_zeros(vector<vector<int> >& mat)
	{
		vector<int> zero_rows, zero_cols; 
		int num_rows = (int)mat.size(); 
		int num_cols = (int)mat[0].size();

		for (int i = 0; i < num_rows; ++i)
		{
			for (int j = 0; j < num_cols; ++j)
			{
				if (mat[i][j] == 0)
				{
					zero_rows.push_back(i); 
					zero_cols.push_back(j); 
				}
			}
		}

		for (int r = 0; r < (int)zero_rows.size(); ++r)
		{
			for (int j = 0; j < num_cols; ++j)
			{
				mat[zero_rows[r]][j] = 0;
			}
		}


		for (int c = 0; c < (int)zero_cols.size(); ++c)
		{
			for (int i = 0; i < num_rows; ++i)
			{
				mat[i][zero_cols[c]] = 0;
			}
		}
	}

	void test()
	{
		int r0[] = {1, 1, -1, 2};
		int r1[] = {2, 0, 3, 4};
		int r2[] = {1, 1, 1, 1};
		int r3[] = {1, 1, 1, 1}; 
		
		vector<vector<int> > mat; 
		mat.push_back(vector<int>(r0, r0+sizeof(r0)/sizeof(int)));
		mat.push_back(vector<int>(r1, r1+sizeof(r1)/sizeof(int)));
		mat.push_back(vector<int>(r2, r2+sizeof(r2)/sizeof(int)));
		mat.push_back(vector<int>(r3, r3+sizeof(r3)/sizeof(int)));

		set_zeros(mat); 

		print_matrix(mat, cout, 4, 4); 	
	}
};


//////////////////////////////////////////////////////////////////////////

/*
 *	Question 1.8
 */

class SubstringRotation : public c_solution<SubstringRotation>
{
};


//////////////////////////////////////////////////////////////////////////

/*
 *	Question 2.1 
 */

class RemoveDuplicateListNode : c_solution<RemoveDuplicateListNode> 
{
	struct LinkedListNode
	{
		LinkedListNode(int _val)
			: val(_val)
			, next(NULL)
		{}
		int val;
		LinkedListNode *next; 
	};
public:
	void remove_dups(LinkedListNode *head)
	{
		if (!head)
			return; 

		LinkedListNode *prev = head;
		LinkedListNode *current = head;

		while (current)
		{
			LinkedListNode *runner = head;
			
			while (runner != current)
			{
				if (runner->val == current->val)
				{
					LinkedListNode *temp = current->next;
					prev->next = temp; 
					temp = current; 
					break;
				}
				runner = runner->next; 
			}

			if (runner == current)
			{
				prev = current; 
				current = current->next; 
			}	
		} 
	}
};

//////////////////////////////////////////////////////////////////////////

/*
 *	Question 2.2
 */

class NthToLast : c_solution<NthToLast>
{
	struct LinkedListNode
	{
		LinkedListNode(int _val)
			: val(_val)
			, next(NULL)
		{}
		int val;
		LinkedListNode *next; 
	};
	
public:
	LinkedListNode *nth_to_last(LinkedListNode *head, int n)
	{
		return NULL; 
	}
};

////////////////////////////////////////////////////////////////////////// 

/*
 *	Question 2.3
 */

class RemoveListNode : c_solution<RemoveListNode>
{
	
};

////////////////////////////////////////////////////////////////////////// 

/*
 *	Question 2.4
 */




//////////////////////////////////////////////////////////////////////////


/************************************************************************/
/* Chapter 4 : Trees and Graphs */
/************************************************************************/


class CreateBSTMinHeight : c_solution<CreateBSTMinHeight> 
{
public:
	
};


//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/* Chapter 9 : Recursion and Dynamic Programming */
/************************************************************************/


/*
 *	Question 9.5 : All permutations of a string
 */
class StringPermutations : public c_solution<StringPermutations>
{
public:
	
	vector<string> get_permutations(string& s)
	{
		vector<string> results;
		results = helper(s, s.length()-1);

		return results; 
	}

	vector<string> helper(string& s, int end)
	{
		vector<string> new_results; 
		if (end == 0)
		{
			new_results.push_back(s.substr(0,1));
			return new_results; 
		}

		vector<string> results = helper(s, end-1);

		for (int i = 0; i < (int)results.size(); ++i)
		{
			for (int j = 0; j <= results[i].length(); ++j)
			{
				string ns = insert_char_at(results[i], s[end], j);
				new_results.push_back(ns); 
			}
		}
		
		return new_results; 
	}

	string insert_char_at(string& s, char c, int i)
	{
		string start = s.substr(0, i);
		string end = s.substr(i);

		return start + string(&c) + end;
	}

	void test()
	{
		vector<string> perms = get_permutations(string("abc")); 
	}
};





/*

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

*/

int main(int argc, char **argv)
{
	// c_solution<RemoveDuplicateChars>::run_test(); 

	// c_solution<RotateMatrix90Degrees>::run_test(); 

	// c_solution<SetMatrixZero>::run_test(); 

	c_solution<StringPermutations>::run_test(); 


	return 0; 
}