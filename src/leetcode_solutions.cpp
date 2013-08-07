
#include "utils.h"
#include "math.h"

using namespace std;

class PalindromePartitioning : public c_solution<PalindromePartitioning>
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



class PalindromePartitioningII : public c_solution<PalindromePartitioningII>
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


class SurroundedRegions : public c_solution<SurroundedRegions>
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


class SumRootToLeaf : public c_solution<SumRootToLeaf>
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

class LongestConsecutiveSeq : c_solution<LongestConsecutiveSeq>
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

class WordLadder : public c_solution<WordLadder>
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

		if (min_length >= (int)dict.size()+2)
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


//////////////////////////////////////////////////////////////////////////

class ValidPalindrome : public c_solution<ValidPalindrome>
{
	/*
	 *	AC
	 */
public:
	 bool isPalindrome(string s) 
	 {
		 if (s.empty())
			 return true; 

		 int start = 0; 
		 int end = s.length()-1;

		 while (!is_valid_char(s[start]) && start < (int)s.length())
		 {
			 ++start;
		 }

		 while (!is_valid_char(s[end]) && end < (int)s.length())
		 {
			 ++end; 
		 }

		 if (start == end)
			 return true; 

		 if (start > end)
			 return false;

		 while (start < end)
		 {
			 if (!is_valid_char(s[start]))
			 {
				 ++start; 
				 continue;
			 }
			 if (!is_valid_char(s[end]))
			 {
				 --end;
				 continue;
			 }

			 if (s[start] != s[end] && tolower(s[start]) != tolower(s[end]))
				 return false;
			 
			 ++start;
			 --end; 
		 }

		 return true; 
	 }

	 bool is_valid_char(char ch)
	 {
		 return (ch >= 'a' && ch <= 'z' ) || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'); 
	 }

	 /*
	 void process_str(string& s)
	 {
		 int p = 0;
		 int last = 0;
		 int len = s.length();
		 
		 while ()
		 
		 for (int i = 0; i < s.length(); ++i)
		 {
			 if ((s[i] >= 'a' && s[i] <= 'z' ) || (s[i] >= 'A' && s[i] <= 'Z'))
				 
			 
		 }
		 
	 }
	 */

	 void test()
	 {
		 string s = "1a2"; 

		 bool result = isPalindrome(s);
		 cout << result << endl; 
	 } 
};


//////////////////////////////////////////////////////////////////////////


class TreeMaxPathSum : c_solution<TreeMaxPathSum>
{
	/*
	 *	AC
	 */
	struct TreeNode 
	{
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};


public:

	int maxPathSum(TreeNode *root) 
	{
		int max_sum = -999999; 
		int current_sum = 0;
		
		helper(root, current_sum, max_sum); 
		
		return max_sum; 
	}

	int helper(TreeNode *node, int& current_sum, int& max_sum)
	{
		if (node == NULL)
		{ 
			return 0; 
		} 

		int left_sum = helper(node->left, current_sum, max_sum);
		int right_sum = helper(node->right, current_sum, max_sum);
		
		current_sum = std::max(node->val, std::max(node->val+left_sum, node->val+right_sum)); 
		max_sum = std::max(max_sum, std::max(current_sum, node->val+left_sum+right_sum));
		
		return current_sum;
	}
	
	void test()
	{
		TreeNode root(1);
		TreeNode left(2);
		TreeNode right(3); 
		root.left = &left; 
		root.right = &right; 

		int result = maxPathSum(&root);

		cout << result << endl; 

	}
};


//////////////////////////////////////////////////////////////////////////

class MaxProfit : public c_solution<MaxProfit>
{
public:
	
	int maxProfit(vector<int> &prices) 
	{
		int min_day = 0;
		int max_profit = 0; 

		for (int i = 1; i < (int)prices.size(); ++i)
		{
			if (prices[i] < prices[min_day])
				min_day = i; 

			if (prices[i] - prices[min_day] > max_profit)
				max_profit = prices[i] - prices[min_day]; 
		}

		return max_profit;
	}

	void test()
	{
		int array[] = {1, 2, 4}; 
		vector<int> prices(array, array+sizeof(array)/sizeof(int));
		
		int max = maxProfit(prices); 
		
		cout << max << endl; 
	}

};

//////////////////////////////////////////////////////////////////////////

class MaxProfitII : public c_solution<MaxProfitII>
{
public:
	
	int maxProfit(vector<int> &prices) 
	{
		int max_profit = 0; 

		for (int i = 1; i < (int)prices.size(); ++i)
		{
			if (prices[i] - prices[i-1] > 0)
				max_profit += prices[i] - prices[i-1]; 
		}
		
		return max_profit; 
	}

	void test()
	{
		int array[] = {1, 2}; 
		vector<int> prices(array, array+sizeof(array)/sizeof(int));

		int max = maxProfit(prices); 

		cout << max << endl; 
	}

};


//////////////////////////////////////////////////////////////////////////

class MaxProfitIII : public c_solution<MaxProfitII>
{
public: 
	
	int maxProfit(vector<int> &prices)
	{
		int f[3] = {0};
		int g[3] = {0};

		int n = prices.size() - 1;
		for (int i = 0; i < n; ++i) {
			int diff = prices[i+1] - prices[i];
			int m = min(i+1, 2);
			for (int j = m; j >= 1; --j) {
				f[j] = max(f[j], g[j-1]) + diff;
				g[j] = max(g[j], f[j]);
			}
		}
		return max(g[1], g[2]);
	}
	

};


////////////////////////////////////////////////////////////////////////// 

class Triangle : c_solution<Triangle>
{
	/*
	 *	AC
	 */
public:
	vector<vector<int> > dp;
	
	int minimumTotal(vector<vector<int> > &triangle) 
	{
		int num_rows = triangle.size();

		dp.resize(num_rows);
		
		for (int i = 1; i <= num_rows; ++i)
		{
			dp[i-1] = vector<int>(i);
			for (int j = 0; j < i; ++j)
			{
				dp[i-1][j] = 0; 
			}
		}

		if (triangle.size() == 1)
			return triangle[0][0];

		dp[0][0] = triangle[0][0]; 
		for (int row = 1; row < num_rows; ++row)
		{
			for (int i = 0; i <= row; ++i)
			{
				if (i == 0)
					dp[row][i] = dp[row-1][i] + triangle[row][i];
				else if (i == row)
					dp[row][i] = dp[row-1][i-1] + triangle[row][i]; 
				else
					dp[row][i] = min(dp[row-1][i] + triangle[row][i], dp[row-1][i-1] + triangle[row][i]);
			}
		}

		int min_sum = dp[num_rows-1][0]; 
		for (int i = 0; i < num_rows; ++i)
			min_sum = std::min(min_sum, dp[num_rows-1][i]); 

		return min_sum; 
	}

	void test()
	{
		vector<vector<int> > triangle(2);
		
		int r1[] = {1}; 		
		triangle[0] = vector<int>(r1, r1+sizeof(r1)/sizeof(int));

		int r2[] = {2, 3};
		triangle[1] = vector<int>(r2, r2+sizeof(r2)/sizeof(int));

		/*
		int r3[] = {6, 5, 7};
		triangle[2] = vector<int>(r3, r3+sizeof(r3)/sizeof(int));

		int r4[] = {4, 1, 8, 3};
		triangle[3] = vector<int>(r4, r4+sizeof(r4)/sizeof(int));
		*/

		int ans = minimumTotal(triangle); 
		
		cout << ans << endl; 
	}
}; 

//////////////////////////////////////////////////////////////////////////

class PascalTriangle : public c_solution<PascalTriangle>
{
public:
	vector<vector<int> > generate(int numRows) 
	{
		vector<vector<int> > rows;
		
		if (numRows <= 0)
			return rows; 

		rows.push_back(vector<int>(1,1));		// first row 

		if (numRows < 2)
			return rows; 

		rows.push_back(vector<int>(2, 1));		// second row

		for (int i = 2; i < numRows; ++i)
		{
			vector<int> row;
			row.push_back(1);
			for (int j = 1; j < i; ++j)
			{
				row.push_back(rows[i-1][j-1] + rows[i-1][j]);
			}
			row.push_back(1);
			rows.push_back(row);
		}

		return rows; 
	}
	
	void test()
	{
		vector<vector<int> > triangles = generate(5);
	}
};

//////////////////////////////////////////////////////////////////////////

class PascalTriangleII : public c_solution<PascalTriangleII>
{
public:
	
	vector<int> getRow(int rowIndex) 
	{
		vector<int> res;
		if(rowIndex < 0)
			return res;
		res.push_back(1);
		if(rowIndex == 0)
			return res;
		res.push_back(1);
		if(rowIndex == 1)
			return res;
		int tmp1 = 0;
		int tmp2 = 0;
		for(int i = 2; i <= rowIndex; i++)
		{
			tmp2 = 1;
			for(int j = 1; j < i; j++)
			{
				tmp1 = tmp2;
				tmp2 = res[j];
				res[j] = tmp1+tmp2;
			}
			res.push_back(1);
		}
		return res; 
	}

	void test()
	{
		vector<int> row = getRow(3);
	}
};


//////////////////////////////////////////////////////////////////////////

class PopulatingNextRightPointers : c_solution<PopulatingNextRightPointers>
{
	struct TreeLinkNode 
	{
		int val;
		TreeLinkNode *left, *right, *next;
		TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
	};
	
public: 

	void connect(TreeLinkNode *root) 
	{
		if (!root)
			return;
		
		TreeLinkNode *cur = root;
		TreeLinkNode *head = root;
		root->next = NULL; 
		
		while (cur)
		{
			TreeLinkNode *p_left = cur->left;
			TreeLinkNode *p_right = cur->right; 

			if (p_left)
			{
				p_left->next = p_right; 
				if (cur->next)
					p_right->next = cur->next->left; 
				else 
					p_right->next = NULL; 
			}
			
			if (cur->next)
				cur = cur->next; 
			else
			{
				cur = head->left; 
				head = cur; 
			}
		} 
	} 
};

//////////////////////////////////////////////////////////////////////////

class PopulatingNextRightPointersII : public c_solution<PopulatingNextRightPointersII>
{
	struct TreeLinkNode 
	{
		int val;
		TreeLinkNode *left, *right, *next;
		TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
	};

public: 

	void connect(TreeLinkNode *root) 
	{ 
		TreeLinkNode *n = root;
		while (n) {
			TreeLinkNode * next = NULL; // the first node of next level
			TreeLinkNode * prev = NULL; // previous node on the same level
			for (; n; n=n->next) {
				if (!next) next = n->left?n->left:n->right;

				if (n->left) {
					if (prev) prev->next = n->left;
					prev = n->left;
				}
				if (n->right) {
					if (prev) prev->next = n->right;
					prev = n->right;
				}
			}
			n = next; // turn to next level
		}
	} 
};


//////////////////////////////////////////////////////////////////////////

class FlattenBinaryTree : public c_solution<FlattenBinaryTree>
{
	struct TreeNode 
	{
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
public:
	void flatten(TreeNode *root) 
	{
		// Recursive Approache. AC
		/*
		if (!root)
			return; 
		
		helper(root); 
		*/ 

		// Iterative Approach. AC
		
		if (!root)
		{
			return;
		}

		TreeNode *node = root;
		while (node)
		{
			if (node->left)
			{
				TreeNode *temp = node->right; 
				node->right = node->left; 
				node->left = NULL;

				// Find the tail of the original left subtree
				TreeNode *p = node;
				while (p->right) p = p->right; 

				p->right = temp; 
			}

			node = node->right;
		}


	}

	void helper(TreeNode *node)
	{
		if (!node)
		{
			return; 
		}
		
		helper(node->left); 
		
		if (node->right)
		{
			TreeNode *temp = node->right; 
			node->right = node->left; 
			node->left = NULL;
			TreeNode *p = node;
			while (p->right) p = p->right; 
			p->right = temp; 
		}
		else 
		{
			node->right = node->left;
			node->left = NULL;
		}

		helper(node->right);
	}

	void test()
	{
		TreeNode root(1);
		TreeNode left(2);
		TreeNode right(3); 
		root.left = &left; 
		root.right = NULL;
		left.left = &right;

		flatten(&root);

	}
};

//////////////////////////////////////////////////////////////////////////

class PathSum : public c_solution<PathSum>
{
	/*
	 *	AC
	 */
public:

	bool hasPathSum(TreeNode *root, int sum)
	{
		if (!root)
			return false;

		return path_sum_helper(root, sum);
	}


	bool path_sum_helper(TreeNode *node, int sum)
	{
		if (!node->left && !node->right)
		{
			return (sum-node->val == 0); 
		}
		
		bool left = false;
		if (node->left)
			left = path_sum_helper(node->left, sum-node->val);
		
		bool right = false;
		if (node->right)
			right = path_sum_helper(node->right, sum-node->val);

		return left || right;
	}


};

//////////////////////////////////////////////////////////////////////////

class PathSumII : public c_solution<PathSumII>
{
	/*
	 *	AC
	 */
public:

	vector<vector<int> > all_paths;

	vector<vector<int> > pathSum(TreeNode *root, int sum)
	{
		if (!root)
			return all_paths;

		vector<int> path;
		path_sum_helper(root, sum, path);

		return all_paths;
	}


	void path_sum_helper(TreeNode *node, int sum, vector<int>& path)
	{
		if (!node->left && !node->right)
		{
			path.push_back(node->val);
			if (sum == node->val)
			{
				all_paths.push_back(path);
			}
			path.pop_back();
			return; 
		}
		
		if (node->left)
		{
			path.push_back(node->val); 
			path_sum_helper(node->left, sum-node->val, path);
			path.pop_back();
		}
		if (node->right)
		{
			path.push_back(node->val); 
			path_sum_helper(node->right, sum-node->val, path);
			path.pop_back(); 
		}
	}

	void test()
	{
		TreeNode root(1);
		
		pathSum(&root, 0);
	}
};

//////////////////////////////////////////////////////////////////////////

class MinimumDepthBinaryTree : public c_solution<MinimumDepthBinaryTree>
{
	/*
	 *	AC
	 */
public: 

	int minDepth(TreeNode *root) 
	{
		if (!root)
			return 0;

		typedef std::pair<TreeNode*, int> elem;
		
		elem r(root, 1);
		deque<elem> q; 
		q.push_back(r);

		while (!q.empty())
		{
			elem node = q.front(); 
			q.pop_front(); 

			if (!node.first->left && !node.first->right)
			{
				return node.second; 
			}

			if (node.first->left)
				q.push_back(elem(node.first->left, node.second+1));
			if (node.first->right)
				q.push_back(elem(node.first->right, node.second+1));
		}
		
		return -1;
	}

	void test()
	{
		TreeNode root(1);
	}
};

//////////////////////////////////////////////////////////////////////////

class ConvertSortedListToBST : public c_solution<ConvertSortedListToBST>
{
	struct ListNode 
	{
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};

	struct TreeNode 
	{
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

public:

	TreeNode *sortedListToBST(ListNode *head)
	{
		if (!head)
			return NULL; 
		
		ListNode *p = head;
		int count = 0; 
		while (p)
		{
			++count; 
			p = p->next; 
		}

		if (count == 1)
		{
			return new TreeNode(head->val);
		}
		else 
			return helper(head, count); 
		
	}

	TreeNode *helper(ListNode *head, int k)
	{
		if (k <= 0)
			return NULL;

		ListNode *p = head;
		int root_idx = k/2; 
		for (int i = 0; i < root_idx; ++i)
		{
			p = p->next; 
		}

		TreeNode *root = new TreeNode(p->val);
		root->left = helper(head, root_idx); 
		root->right = helper(p->next, k-root_idx-1);

		return root;
	}

	void delete_bst(TreeNode *node)
	{
		if (!node)
			return; 
		delete_bst(node->left);
		delete_bst(node->right);
		SAFE_DELETE(node); 
	}

	void test()
	{
		ListNode head(3); 
		ListNode a(5); 
		ListNode b(8); 

		head.next = &a;
		a.next = &b;

		TreeNode *root = sortedListToBST(&head);

		delete_bst(root);

	}

};

//////////////////////////////////////////////////////////////////////////

class ConvertSortedArrayToBST : public c_solution<ConvertSortedArrayToBST>
{
	/*
	 *	AC
	 */ 
public:
	TreeNode *sortedArrayToBST(vector<int> &num) 
	{
		return build_bst(num, 0, num.size()-1); 
	}

	TreeNode *build_bst(vector<int>& num, int start, int end)
	{
		if (start > end)
			return NULL; 

		int mid = (start + end) / 2;

		TreeNode *root = new TreeNode(num[mid]); 
		
		root->left = build_bst(num, start, mid-1); 
		root->right = build_bst(num, mid+1, end); 

		return root; 
	}
};

//////////////////////////////////////////////////////////////////////////

class BinaryTreeFromInorderPostorder : public c_solution<BinaryTreeFromInorderPostorder> 
{
	/*
	 *	AC
	 */
public: 
	TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
	{
		if (inorder.empty() || postorder.empty())
			return NULL; 
		
		return build_tree_helper(inorder, postorder, 0, inorder.size()-1, 0, postorder.size()-1); 
	}

	TreeNode *build_tree_helper(vector<int> &inorder, 
		vector<int> &postorder, 
		int inorder_start, int inorder_end, 
		int postorder_start, int postorder_end)
	{
		if (inorder_start > inorder_end || postorder_start > postorder_end)
			return NULL; 
		
		int inorder_root = inorder_start;
		for (int i = inorder_start; i <= inorder_end; ++i)
		{
			if (inorder[i] == postorder[postorder_end])
			{
				inorder_root = i;
				break;
			}
		}

		TreeNode *root = new TreeNode(inorder[inorder_root]);
		
		int num_left = inorder_root - inorder_start; 
		root->left = build_tree_helper(inorder, postorder, inorder_start, inorder_root-1, postorder_start, postorder_start+num_left-1); 
		root->right = build_tree_helper(inorder, postorder, inorder_root+1, inorder_end, postorder_start+num_left, postorder_end-1); 
		
		return root; 
	}

	void test()
	{
		int a[] = {2, 1}; 
		int b[] = {2, 1}; 

		vector<int> inorder(a, a+sizeof(a)/sizeof(int)); 
		vector<int> postorder(b, b+sizeof(b)/sizeof(int));
		
		buildTree(inorder, postorder);

	}
	
};


class BalancedBinaryTree : public c_solution<BalancedBinaryTree>
{
	/*
	 *	AC 
	 */
public:
	bool isBalanced(TreeNode *root) 
	{
		if (!root)
			return true; 
		
		int left_depth = -1;
		int right_depth = -1; 
		if (root->left)
			left_depth = depth(root->left);
		if (root->right)
			right_depth = depth(root->right);
		
		if (abs(left_depth-right_depth) > 1)
			return false;
		else 
			return isBalanced(root->left) && isBalanced(root->right);
	}

	int depth(TreeNode *root)
	{
		if (!root->left && !root->right)
			return 0; 

		int left_depth = -1;
		int right_depth = -1;

		if (root->left)
			left_depth = 1 + depth(root->left);

		if (root->right)
			right_depth = 1 + depth(root->right);

		return std::max(left_depth, right_depth);
	}
	
};

//////////////////////////////////////////////////////////////////////////

class Permutations : public c_solution<Permutations>
{
public:
	vector<vector<int> > permute(vector<int> &num) 
	{
		vector<vector<int> > results; 
		results = permute_helper(num, num.size()-1); 
		return results;
	}

	vector<vector<int> > permute_helper(vector<int>& num, int end)
	{
		vector<vector<int> > new_results; 
		if (end == 0)
		{
			vector<int> vec; 
			vec.push_back(num[end]);
			new_results.push_back(vec);
			return new_results; 
		}

		vector<vector<int> > results = permute_helper(num, end-1);

		for (int i = 0; i < (int)results.size(); ++i)
		{
			for (int j = 0; j <= (int)results[i].size(); ++j)
			{
				vector<int> ns = insert_at(results[i], num[end], j);
				new_results.push_back(ns); 
			}
		}
		return new_results; 
	}

	vector<int> insert_at(vector<int> vec, int val, int pos)
	{
		vec.insert(vec.begin()+pos, val); 
		return vec; 
	}

	void test()
	{
		int array[] = {1, 2}; 
		vector<int> nums(array, array+sizeof(array)/sizeof(int)); 

		vector<vector<int> > results = permute(nums); 
	}
};

////////////////////////////////////////////////////////////////////////// 

class Combinations : public c_solution<Combinations>
{
public: 

	vector<vector<int> > combine(int n, int k) 
	{ 
		vector<int> path;
		vector<int> nums;
		for (int i = 1; i <= n; ++i)
			nums.push_back(i); 
		
		vector<vector<int> > results = combine_helper(nums, path, 0, k); 
		return results;
	}

	vector<vector<int> > combine_helper(vector<int>& nums, vector<int>& path, int start, int k)
	{
		vector<vector<int> > results; 

		if (path.size() == k)
		{
			results.push_back(path); 
			return results; 
		}

		for (int i = start; i < (int)nums.size(); ++i)
		{
			path.push_back(nums[i]); 

			vector<vector<int> > r = combine_helper(nums, path, i+1, k); 
			
			for (int j = 0; j < (int)r.size(); ++j)
			{
				results.push_back(r[j]);
			}

			path.pop_back();
		}

		return results; 
	}

	void test()
	{
		combine(4, 2);
	}

};


//////////////////////////////////////////////////////////////////////////

class Subsets : public c_solution<Subsets>
{
public:
	vector<vector<int> > subsets(vector<int> &S)
	{
		sort(S.begin(), S.end());
		vector<vector<int> > results;
		vector<int> path; 
		subsets_helper(S, 0, path, results); 
		
		return results;

		/*

		vector<vector<int> > v(1);
		for(int i = 0; i < S.size(); ++i) {
			int j = v.size();
			while(j-- > 0) {
				v.push_back(v[j]);
				v.back().push_back(S[i]);
			}
		}
		
		return v;
		*/
	}

	void subsets_helper(vector<int>& s, int pos, vector<int>& path, vector<vector<int> >& results)
	{
		results.push_back(path);
		
		for (int i = pos; i < (int)s.size(); ++i)
		{
			path.push_back(s[pos]);
			subsets_helper(s, i+1, path, results);
			path.pop_back(); 
		}
	}
	
	void test()
	{
		int arry[] = {1, 2, 3};
		vector<int> s(arry, arry+sizeof(arry)/sizeof(int));
		vector<vector<int> > results = subsets(s);
	}
};


int main(int argc, char **argv)
{
	// c_leetcode_solution<PalindromePartitioning>::run_test();
	
	// c_leetcode_solution<PalindromePartitioningII>::run_test();

	// c_leetcode_solution<SurroundedRegions>::run_test(); 

	// c_leetcode_solution<SumRootToLeaf>::run_test();
	
	// c_leetcode_solution<LongestConsecutiveSeq>::run_test();

	// c_leetcode_solution<WordLadder>::run_test();

	// c_leetcode_solution<ValidPalindrome>::run_test(); 

	// c_leetcode_solution<TreeMaxPathSum>::run_test();

	// c_leetcode_solution<MaxProfit>::run_test(); 
	
	// c_leetcode_solution<MaxProfitII>::run_test(); 

	// c_leetcode_solution<MaxProfitIII>::run_test(); 
	
	// c_leetcode_solution<Triangle>::run_test(); 

	//c_leetcode_solution<PascalTriangleII>::run_test(); 

	// c_solution<PascalTriangle>::run_test(); 

	// c_solution<FlattenBinaryTree>::run_test();

	// c_solution<PathSumII>::run_test(); 

	// c_solution<ConvertSortedListToBST>::run_test();

	c_solution<BinaryTreeFromInorderPostorder>::run_test(); 


	// c_solution<Permutations>::run_test(); 

	// c_solution<Combinations>::run_test(); 

	// c_solution<Subsets>::run_test(); 

	return 0;
}