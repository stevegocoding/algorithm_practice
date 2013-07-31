
#include "utils.h"
#include "math.h"

using namespace std;

class PalindromePartitioning : public c_leetcode_solution<PalindromePartitioning>
{
	/**
	两个阶段：
	第一个阶段：找出所有substring，可以把每个substring看成一个graph的节点，
	如果S(i, j)表示以i开始，j结束的substring，那么S(i, j)和S(j+1, k)相连。
	如果把S(0, i) (对于所有i，S(0, i)都是S的字串) 当做根节点，那么找出所有
	字串就是找到从这些根节点到任意叶子节点的路径
	*/
public:
	
	vector<vector<string> > partition(string s)
	{
		vector<vector<bool> > is_pa = vector<vector<bool> >(s.length());
		int i = 0; 
		int j = 0; 
		for (i = 0; i < (int)s.length(); ++i)
			is_pa[i].resize(s.length());

		for (i = 0; i < (int)s.length(); ++i)
		{
			is_pa[i][i] = true;
		}
		for (i = (int)s.length()-2; i >= 0; --i)
		{
			is_pa[i][i+1] = (s[i] == s[i+1]);
			for (j = i+2; j < (int)s.length(); ++j)
			{
				is_pa[i][j] = (s[i] == s[j]) && is_pa[i+1][j-1];
			}
		}

		return partition_helper(s, 0, is_pa);
	}

	vector<vector<string> > partition_helper(const string& s, int start, vector<vector<bool> >& dp_mem)
	{	
		vector<vector<string> > pa;
		if (start == s.length())
		{
			pa.push_back(vector<string>()); 
			return pa;
		}
			
		for (unsigned int i = start; i < s.length(); ++i)
		{
			if (dp_mem[start][i])
			{
				vector<vector<string>> res = partition_helper(s, i+1, dp_mem);
				for (unsigned int j = 0; j < res.size(); ++j)
				{
					res[j].insert(res[j].begin(), s.substr(start, i-start+1));
					pa.insert(pa.begin(), res[j]);
				}
			}	
		}

		return pa;
	}


	void test()
	{
		string s = "aab"; 
		vector<vector<string> > result = partition(s);
		
		for (int i = 0; i < (int)result.size(); ++i)
		{
			for (int j = 0; j < (int)result[i].size(); ++j)
				std::cout << result[i][j] << std::endl; 
		}
	}
	
};



class PalindromePartitioningII : public c_leetcode_solution<PalindromePartitioningII>
{
	/*
	 *	dp[i] 表示以i个字符为结尾的字符串的最少切割数目 状态转移方程为：
		dp[i] = min(dp[k-1] + 1)		(for any k in [0, i], if str[k...i] is palindrome)
				0						(if str[0, i] is palindrome)
	 */

public:

	vector<int> dp;
	vector<vector<bool> > palin_dp;
	
	int minCut(string s)
	{
		dp.resize(s.length());
		std::fill(dp.begin(), dp.end(), 0); 
		
		palin_dp.resize(s.length()); 
		for (int i = 0; i < (int)s.length(); ++i)
			palin_dp[i] = vector<bool>(s.length(), false); 
		
		for (int i = 1; i < (int)s.length(); ++i)
		{
			if (is_palindrome(s, 0, i)) 
			{
				dp[i] = 0;
			}
			else
			{
				int min = -1;
				for (int j = 1; j <= i; ++j)
				{
					//if (is_palindrome(s, j, i))
					if (s[i] == s[j] && ((i-j) < 2 || palin_dp[j+1][i-1]))
					{
						palin_dp[j][i] = true;
						if (min == -1 || (1+dp[j-1]) < min)
							min = dp[j-1]+1; 
					}
				}
				dp[i] = min; 
			}
		}

		return dp[s.length()-1]; 
	}

	bool is_palindrome(const string& s, int start, int end)
	{
		while (start < end)
		{
			if (s[start++] != s[end--])
				return false;
		}
		return true; 
	}

	void test()
	{
		string s = "leet"; 
		
		int result = minCut(s);
		cout << result << endl; 
	}
	
};


class SurroundedRegions : public c_leetcode_solution<SurroundedRegions>
{
	/*
	 *	AC
	 */
public:
	
	int w, h;
	
	void solve(vector<vector<char> >& board)
	{
		if (board.empty())
			return; 

		h = board.size(); 
		w = board[0].size(); 

		// Top-most line
		for (int j = 0; j < w; ++j)
			if (board[0][j] == 'O')
				dfs(board, 0, j);

		// Right-most column
		for (int i = 1; i < h; ++i)
			if (board[i][w-1] == 'O')
				dfs(board, i, w - 1);

		// Bottom-most line
		for (int j = 0; j < w - 1; ++j)
			if (board[h-1][j] == 'O')
				dfs(board, h - 1, j);

		// Left-most column
		for (int i = 1; i < h - 1; ++i)
			if (board[i][0] == 'O')
				dfs(board, i, 0);

		for (int i = 0; i < (int)board.size(); ++i)
		{
			for (int j = 0; j < (int)board[i].size(); ++j)
			{
				if (board[i][j] == 'O')
					board[i][j] = 'X';
				else if (board[i][j] == '#')
					board[i][j] = 'O';
			}
		}
	}

	void dfs(vector<vector<char> >& board, int row, int col)
	{
		if (row < 0 || row >= (int)board.size() || col < 0 || col >= (int)board[0].size() || board[row][col] != 'O')
			return; 

		board[row][col] = '#';
			
		dfs(board, row-1, col);
		dfs(board, row+1, col);
		dfs(board, row, col-1);
		dfs(board, row, col+1); 
	}

	void test()
	{
		ifstream ifs("surrounded_regions.in");
		int w = 0; 
		int h = 0; 
		ifs >> w >> h; 

		vector<vector<char> > board;
		/*
		vector<vector<char> > board(h); 
		for (int i = 0; i < h; ++i)
			board[i] = vector<char>(w); 
		
		for (int i = 0; i < (int)board.size(); ++i)
		{
			for (int j = 0; j < (int)board[i].size(); ++j)
			{
				char ch; 
				ifs >> ch; 
				board[i][j] = ch; 
			}
		}
		*/

		/*
		print_board(board);
	
		
		// Top-most line
		for (int j = 0; j < w; ++j)
			if (board[0][j] == 'O')
				dfs(board, 0, j);

		// Right-most column
		for (int i = 1; i < h; ++i)
			if (board[i][w-1] == 'O')
				dfs(board, i, w - 1);
		
		// Bottom-most line
		for (int j = 0; j < w - 1; ++j)
			if (board[h-1][j] == 'O')
				dfs(board, h - 1, j);

		
		// Left-most column
		for (int i = 1; i < h - 1; ++i)
			if (board[i][0] == 'O')
				dfs(board, i, 0);
		
		print_board(board);

		for (int i = 0; i < (int)board.size(); ++i)
		{
			for (int j = 0; j < (int)board[i].size(); ++j)
			{
				if (board[i][j] == 'O')
					board[i][j] = 'X';
				else if (board[i][j] == '#')
					board[i][j] = 'O';
			}
		}

		print_board(board);
		*/
		
		solve(board);
		
		print_board(board);
	}

private: 

	void print_board(const vector<vector<char> >& board)
	{
		for (int i = 0; i < (int)board.size(); ++i)
		{
			for (int j = 0; j < (int)board[i].size(); ++j)
			{
				cout << " " << board[i][j]; 
			}
			cout << endl; 
		}

		cout << endl; 
	}
};


//////////////////////////////////////////////////////////////////////////

struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class SumRootToLeaf : public c_leetcode_solution<SumRootToLeaf>
{
	/*
	 *	AC
	 */
public:

	int total_sum;
	
	int sumNumbers(TreeNode *root)
	{
		if (!root)
			return 0; 
		
		total_sum = 0; 

		vector<int> path; 

		dfs(root, path);
		
		return total_sum; 
	}

	void dfs(TreeNode *node, vector<int>& path)
	{
		if (node->left == NULL && node->right == NULL)
		{
			path.push_back(node->val);
			total_sum += get_num(path);
			return; 
		}
		
		path.push_back(node->val);
		
		if (node->left)
		{
			dfs(node->left, path); 
			path.pop_back();	
		}
		
		if (node->right)
		{
			dfs(node->right, path);
			path.pop_back(); 
		}

	}

	int get_num(vector<int>& path)
	{
		int num = 0; 
		int count = 0; 
		for (int i = path.size()-1; i >= 0; --i, count++)
		{
			num += path[i] * (int)pow(10, count); 
		}
		return num; 
	}

	void test()
	{
		TreeNode root(1);
		TreeNode left(2);
		TreeNode right(3); 
		root.left = &left; 
		root.right = &right; 

		cout << sumNumbers(&root);
	}	
};


//////////////////////////////////////////////////////////////////////////

class LongestConsecutiveSeq : c_leetcode_solution<LongestConsecutiveSeq>
{
public:

	std::map<int, int> map;
	
	int longestConsecutive(vector<int> &num) 
	{
		int max = 0; 
		
		for (int i = 0; i < (int)num.size(); ++i)
		{
			int n = num[i];
			
			if (map.find(n) != map.end()) 
				continue; 

			map.insert(std::pair<int, int>(n, 1));
			
			if (map.find(n-1) != map.end())
				max = std::max(max, merge(map, n-1, n));

			if (map.find(n+1) != map.end())
				max = std::max(max, merge(map, n, n+1)); 
		}
		
		return max; 
	}

	int merge(std::map<int, int>& map, int left, int right)
	{
		int upper = right + map.find(right)->second - 1; 
		int lower = left - map.find(left)->second + 1;
		int len = upper - lower + 1;
		map[upper] = len;
		map[lower] = len;
		return len; 
	}

	void test()
	{
		//int array[] = {100, 4, 200, 1, 3, 2};

		int array[] = {0, 0, -1};
		vector<int> vec(array, array+sizeof(array)/sizeof(int));
		
		int len = longestConsecutive(vec);
		cout << len << std::endl; 
	}
};


//////////////////////////////////////////////////////////////////////////

class WordLadder : public c_leetcode_solution<WordLadder>
{
	/*
	 *	TLE on large test
	 */
public:

	int min_length;
	map<string, bool> visited; 
	
	int ladderLength(string start, string end, unordered_set<string> &dict) 
	{ 
		for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); ++it)
		{
			visited.insert(std::pair<string, bool>(*it, false)); 
		}

		min_length = dict.size() + 2; 
		dfs(start, end, dict, 0);

		if (min_length >= dict.size()+2)
			return 0; 

		return min_length + 1; 
	}


	void dfs(const string& s, const string& end, unordered_set<string>& dict, int length)
	{
		int diff = compare_str(s, end); 
		if (diff == 0)
		{
			min_length = std::min(length, min_length); 
			return; 
		}

		for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); ++it)
		{
			if (visited[*it])
				continue;
			if (compare_str(s, *it) == 1)
			{ 
				visited[*it] = true; 
				dfs(*it, end, dict, length+1);
				visited[*it] = false;
			}
		}
	}

	int compare_str(const string& s1, const string& s2)
	{
		int diff = 0; 
		for (int i = 0; i < (int)s1.size(); ++i)
		{
			if (s1[i] != s2[i])
				++diff; 
		}
		return diff; 
	}

	void test()
	{
		string s = "hit"; 
		string end = "cog";
		std::array<std::string, 5> ar = {"hot","dot","dog","lot","log"}; 
		unordered_set<string> dict(ar.begin(), ar.end());

		int l = ladderLength(s, end, dict);
		
		cout << l + 1 << endl;
		
	}
};


int main(int argc, char **argv)
{
	// c_leetcode_solution<PalindromePartitioning>::run_test();
	
	// c_leetcode_solution<PalindromePartitioningII>::run_test();

	// c_leetcode_solution<SurroundedRegions>::run_test(); 

	// c_leetcode_solution<SumRootToLeaf>::run_test();
	
	// c_leetcode_solution<LongestConsecutiveSeq>::run_test();

	c_leetcode_solution<WordLadder>::run_test();

	return 0;
}