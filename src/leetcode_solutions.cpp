
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
		if (start == (int)s.length())
		{
			pa.push_back(vector<string>()); 
			return pa;
		}
			
		for (unsigned int i = start; i < s.length(); ++i)
		{
			if (dp_mem[start][i])
			{
				vector<vector<string> > res = partition_helper(s, i+1, dp_mem);
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

/*
class WordLadder : public c_solution<WordLadder>
{
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
*/


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

class MaxDepth : public c_solution<MaxDepth>
{
public:

	int max_depth;
	int maxDepth(TreeNode *root) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function

		max_depth = 0; 

		if (!root)
			return 0; 

		helper(root, 0);

		return max_depth;

	}

	void helper(TreeNode *node, int depth)
	{
		if (!node->left && !node->right)
		{
			max_depth = std::max(depth+1, max_depth);
			return;
		}

		if (node->left)
			helper(node->left, depth+1);
		if (node->right)
			helper(node->right, depth+1);
	}
};

//////////////////////////////////////////////////////////////////////////

class SymmetricTree : public c_solution<SymmetricTree>
{
public:
	bool isSymmetric(TreeNode *root) 
	{
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		if (root == NULL) return true;
		return helper(root->left,root->right);
	}
	bool helper(TreeNode *left,TreeNode *right)
	{
		if( left == NULL && right == NULL) return true;
		if( left != NULL && right == NULL) return false;
		if( left == NULL && right != NULL) return false;
		if( left->val != right->val) 
			return false;
		else
			return helper(left->left,right->right) && helper(left->right,right->left);
	}
};

//////////////////////////////////////////////////////////////////////////

class SameTree : public c_solution<SameTree>
{
public:
	bool isSameTree(TreeNode *p, TreeNode *q) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function

		if (!p && !q)
			return true;

		if (!p || !q)
			return false;

		if (p->val != q->val)
			return false;

		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}
};

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


//////////////////////////////////////////////////////////////////////////

class RecoverBST : public c_solution<RecoverBST>
{
public:
	void recoverTree(TreeNode *root)
	{
		
		 
	}
};


//////////////////////////////////////////////////////////////////////////


class InterleavingString : public c_solution<InterleavingString>
{
	/*
	 *	Exceeded Time Limit on large data tests using recursion
	 */

public: 
	bool isInterleave(string s1, string s2, string s3)
	{
		if (s3.length() != s1.length() + s2.length())
			return false;

		return helper(s1, s2, s3, 0, 0, 0);
	}

	bool helper(string& s1, string& s2, string& s3, int start1, int start2, int start3)
	{
		if (start1 == s1.length() && start2 == s2.length() && start3 == s3.length())
			return true; 

		bool match_s1 = false;
		if (start1 < (int)s1.length() && s1[start1] == s3[start3])
			match_s1 = helper(s1, s2, s3, start1+1, start2, start3+1); 
		bool match_s2 = false; 
		if (start2 < (int)s2.length() && s2[start2] == s3[start3])
			match_s2 = helper(s1, s2, s3, start1, start2+1, start3+1); 

		return match_s1 || match_s2; 
	}

	void test()
	{
		/*
		string s1 = ""; 
		string s2 = "abc";
		string s3 = "abc";

		bool result = isInterleave(s1, s2, s3); 
		*/ 
	}
};

//////////////////////////////////////////////////////////////////////////

class UniqueBST : public c_solution<UniqueBST>
{
public:

	int numTrees(int n)
	{
		// dp[i] is the number of BSTs with i nodes
		// dp[n] = \sum_{i=1}^n f(i-1) * f(n-i), f(0) = 1, f(1) = 1;
		vector<int> dp(n+1);		
		
		if (n <= 1)
			return 1;

		dp[0] = 1;
		dp[1] = 1;

		for (int i = 2; i <= n; ++i)
		{
			dp[i] = 0;
			for (int left = 0; left < i; ++left)
			{
				int left_ways = dp[left]; 
				int right_ways = dp[i-left-1]; 
				dp[i] += left_ways * right_ways;
			}
		}

		return dp[n]; 
	}
};

//////////////////////////////////////////////////////////////////////////

class UniqueBSTII : public c_solution<UniqueBSTII>
{
public:
	
	vector<TreeNode *> generateTrees(int n)
	{
		return generate_trees(1, n); 
	}

	vector<TreeNode*> generate_trees(int start, int end)
	{
		if (start > end)
			return vector<TreeNode*>(1, (TreeNode*)NULL);
		
		vector<TreeNode*> results;
		
		for (int i = start; i <= end; ++i)
		{
			vector<TreeNode*> left_subtrees = generate_trees(start, i-1);
			vector<TreeNode*> right_subtrees = generate_trees(i+1, end);

			// For each left subtree and each right subtree, create a root node
			// with value i and then link the two subtrees to the root 
			for (int j = 0; j < (int)left_subtrees.size(); ++j)
			{
				for (int k = 0; k < (int)right_subtrees.size(); ++k)
				{
					TreeNode *root = new TreeNode(i); 
					root->left = left_subtrees[j];
					root->right = right_subtrees[k]; 
					results.push_back(root); 
				}
			}
		}
		
		return results; 
	}
};

//////////////////////////////////////////////////////////////////////////

class RestoreIPAddress : public c_solution<RestoreIPAddress>
{
public: 
	vector<string> restoreIpAddresses(string s) 
	{
		vector<string> results; 
		results = restore_ip_helper(s, 0, 0); 

		return results;
	}

	
	vector<string> restore_ip_helper(string& s, int start, int num_sec)
	{
		vector<string> results;

		if (start >= s.length())
			return results;

		if (num_sec == 3 && start < s.length() - 4)
			return results;
		
		if (start >= s.length() - 4 && num_sec == 3)
		{
			string sec = s.substr(start); 
			if (is_valid_ip_section(sec))
				results.push_back(sec); 
			
			return results; 
		}
		
		for (int i = 1; i <= 3; ++i)
		{
			vector<string> ip = restore_ip_helper(s, start+i, num_sec+1);  

			for (int j = 0; j < (int)ip.size(); ++j)
			{
				string new_sec = s.substr(start, i); 
				if (is_valid_ip_section(new_sec))
				{
					string new_ip = new_sec + "." + ip[j]; 
					results.push_back(new_ip); 
				}
			}
		}

		return results;
	}

	/*
	bool is_valid_ip_section(string& s)
	{
		if (s.length() > 3 )
			return false; 
		
		if (!(s[0] > '0' && s[0] <= '2'))
			return false; 

		if (s.length() == 2 && !(s[1] >= '0' && s[1] <= '5'))
			return false; 

		if (s.length() == 3 && !(s[2] >= '0' && s[2] <= '5'))
			return false;

		return true; 
	}
	*/

	bool is_valid_ip_section(string& s)
	{
		if (s.length() > 1 && s[0] == '0')
			return false; 
		
		int num = 0; 
		stringstream ss(s); 
		ss >> num;
		if (num >= 0 && num <= 255) 
			return true; 
		else 
			return false; 
	}

	void test()
	{
		restoreIpAddresses("010010");
	}
};

//////////////////////////////////////////////////////////////////////////

class ReverseLinkedListII : public c_solution<ReverseLinkedListII> 
{
	struct ListNode 
	{
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};
	
public:
	 ListNode *reverseBetween(ListNode *head, int m, int n) 
	 {
		 if (!head)
			 return NULL; 
		 
		 ListNode dummy(0);
		 dummy.next = head; 
		 ListNode *prev_m = NULL;
		 ListNode *prev = &dummy;
		 
		 for (int i = 1; i <= n; ++i)
		 {
			 if (i == m)
				 prev_m = prev;
			 
			 if (i > m && i <= n)
			 {
				 prev->next = head->next;
				 head->next = prev_m->next; 
				 prev_m->next = head; 
				 head = prev;
			 }

			 prev = head;
			 head = head->next;
		 }

		 return dummy.next;
	 }
};

//////////////////////////////////////////////////////////////////////////

class DecodeWays : public c_solution<DecodeWays>
{
public: 
	
	int numDecodings(string s) 
	{
        int n = s.length();
        vector<int> dp(n);
        
        for (int i = 1; i < n; ++i)
        {
            
        }
        
        return dp[n-1]; 
	}
};

//////////////////////////////////////////////////////////////////////////

class GrayCode : public c_solution<GrayCode>
{
    public:
        vector<int> grayCode(int n)
        {
            vector<int> results;
            
            if (n <= 1)
            {
                results.push_back(0);
                if (n == 1)
                    results.push_back(1);

                return results; 
            }

            vector<int> prev_results = grayCode(n-1);
            int highest_bit = 1 << (n-1);
            
            results.insert(results.end(), prev_results.begin(), prev_results.end());
            for (int i = prev_results.size() - 1; i >= 0;  --i)
            {
                results.push_back(prev_results[i] + highest_bit);
            }
            
            return results;
        }
                   
        void test()
        {
            vector<int> codes = grayCode(2);
            cout << "Hello" << std::endl;
        }
}; 

//////////////////////////////////////////////////////////////////////////

class ScrambleString : public c_solution<ScrambleString>
{
    public:
       bool isScramble(string s1, string s2) 
       {
           bool ret = swap_helper(s1, s2, 0);
           return ret;
       }

       bool swap_helper(string& s, string& t, int start)
       {
           if (start == s.length())
               return false; 
           
           if (s.compare(t) == 0)
               return true;

           for (int i = start+1; i < s.length(); ++i)
           {
               char temp = s[start]; 
               s[start] = s[i];
               s[i] = temp;
               
               bool ret = swap_helper(s, t, i);
               if (ret)
                   return ret; 
           }
       }
       
       void test()
       {
           string s = "rgtae";
           string t = "great"; 
           
           bool ret = isScramble(s, t);
           cout << ret << std::endl; 
       }
};

//////////////////////////////////////////////////////////////////////////

class PartitionList : c_solution<PartitionList>
{
    struct ListNode 
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
   
    public:
        ListNode *partition(ListNode *head, int x)
        {
            ListNode *root = new ListNode(-1); 
            ListNode *pivot = new ListNode(x); 
            ListNode *root_last = root; 
            ListNode *pivot_last = pivot; 

            ListNode *p = head;
            
            while (p)
            {
                if (p->val < x)
                {
                    root_last->next = p; 
                    root_last = p;
                }
                else 
                {
                    pivot_last->next = p;
                    pivot_last = p; 
                    pivot_last = NULL;
                }
                p = p->next; 
            }

            root_last->next = pivot->next; 
            return root->next;
        }
};

//////////////////////////////////////////////////////////////////////////

class RemoveDuplicateSortedList : public c_solution<RemoveDuplicateSortedList> 
{    
    struct ListNode 
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
   
    public:
        ListNode *deleteDuplicates(ListNode *head)
        {
            ListNode *p = head; 
            ListNode *q = NULL;
            
            if (!head || !head->next)
                return p; 
            q = p->next; 

            while (q)
            {
                if (p->val != q->val)
                {
                    p = p->next; 
                    q = q->next;
                }
                else 
                {
                    ListNode *t = q; 
                    q = q->next;
                    p->next = q; 
                    delete t;
                }
            }
            
            return head;
        }
};

//////////////////////////////////////////////////////////////////////////

class RemoveDuplicateSortedListII : public c_solution<RemoveDuplicateSortedListII>
{
    /*
     * AC 
     */
    struct ListNode 
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
      
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (!head || !head->next)
            return head;

        ListNode *dummy = new ListNode(head->val - 1); 
        dummy->next = head; 

        ListNode *p = dummy; 
        ListNode *q = p->next;

        while (q)
        {
            ListNode *t = q; 
            while (t->next && t->next->val == t->val)
                t = t->next; 
            if (q != t)
            {
                p->next = t->next; 
                while (q != t->next)
                {
                    ListNode *del_p = q; 
                    q = q->next;
                    delete del_p;
                }
            }
            else
            {
                p = p->next;
                q = q->next;
            }
        }

        return dummy->next;
    }
};

//////////////////////////////////////////////////////////////////////////

class SearchRotatedSortedArray : public c_solution<SearchRotatedSortedArray>
{
    public:
        int search(int A[], int n, int target)
        {
            int low = 0;
            int high = n-1;
            
            while (low <= high)
            {
                int mid = (low+high) / 2; 
                if (A[mid] == target)
                    return mid; 
                
                if (A[mid] >= A[low])
                {
                    if (target >=  A[low] && target < A[mid])
                        high = mid - 1; 
                    else 
                        low = mid + 1; 
                }
                else
                {
                    if (target > A[mid] && target <= A[high])
                        low = mid + 1; 
                    else
                        high = mid - 1; 
                }
            }
            
            return -1; 
        }
}; 

//////////////////////////////////////////////////////////////////////////

class SearchRotatedSortedArrayII : public c_solution<SearchRotatedSortedArrayII>
{
public:
    bool search(int A[], int n, int target)
    {
        int low = 0;
        int high = n-1;

        while (low <= high)
        {
            int mid = (low+high) / 2; 
            if (A[mid] == target)
                return true; 

            if (A[mid] > A[low])
            {
                if (target >=  A[low] && target < A[mid])
                    high = mid - 1; 
                else 
                    low = mid + 1; 
            }
            else if (A[mid] < A[low])
            {
                if (target > A[mid] && target <= A[high])
                    low = mid + 1; 
                else
                    high = mid - 1; 
            }
            else 
                ++low; 
        }

        return false; 
    }   
};

//////////////////////////////////////////////////////////////////////////

class RemoveDuplicatesSortedArray : public c_solution<RemoveDuplicatesSortedArray>
{
public:
    int removeDuplicates(int A[], int n) 
    {
        if (n == 0)
            return 0; 
        if (n == 1)
            return 1;

        int cur = 0; 
        int p = 1;

        while (p < n)
        {
            while (A[p] == A[cur] && p < n)
                ++p;
                
            // if a number differente from cur is not found, then break out
            if (p == n)
                break;
                
            A[++cur] = A[p++];
        }
        return cur+1;
    } 
    
    void test()
    {
        int a[] = {1, 1};
        int ret = removeDuplicates(a, 2);
    }
}; 

////////////////////////////////////////////////////////////////////////// 

class RemoveDuplicatesSortedArrayII: public c_solution<RemoveDuplicatesSortedArrayII>
{
public:
    int removeDuplicates(int A[], int n)
    {    
        int i=0,c=1;
        int j;
        if (n<=2) return n;

        for (j=1;j<n;j++)
        {            
            if (A[j] != A[i])
            {                
                A[++i]=A[j];
                c=1;
            }
            else
            {
                if (c <2)
                {
                    c++;
                    A[++i]=A[j];
                }
            }
        }
        return i+1;  
    }
    
    void test()
    {
        int a[] = {1, 1, 1};
        int ret = removeDuplicates(a, 3);
    }
};

//////////////////////////////////////////////////////////////////////////

class WordSearch : public c_solution<WordSearch>
{
public:
     bool exist(vector<vector<char> > &board, string word) 
     {
         int rows = board.size();
         int cols = board[0].size(); 

         vector<vector<bool> > visited(rows, vector<bool>(cols, false)); 

         for (int i = 0; i < board.size(); ++i)
         {
             for (int j = 0; j < board[0].size(); ++j)
                 if (dfs(i, j, 0, word, board, visited)) return true;
         }
         
         return false;
     }
     
     bool dfs(int row, int col, 
             int depth, 
             string& word, 
             vector<vector<char> >& board, 
             vector<vector<bool> >& visited)
     {
         if (visited[row][col] || board[row][col] != word[depth])
             return false; 
         
         if (depth == word.length() - 1)
             return true; 
         
         visited[row][col] = true; 
         if (row != 0 && dfs(row-1, col, depth+1, word, board, visited)) return true;
         if (row != board.size()-1 && dfs(row+1, col, depth+1, word, board, visited)) return true;
         if (col != 0 && dfs(row, col-1, depth+1, word, board, visited)) return true;
         if (col != board[0].size()-1 && dfs(row, col+1, depth+1, word, board, visited)) return true; 
                 
         visited[row][col] = false; 

         return false;
     }
};

//////////////////////////////////////////////////////////////////////////

class MinimumWindowSubstring : public c_solution<MinimumWindowSubstring>
{
public:
    /*
    string minWindow(string S, string T)
    {
        
    }
    */ 
};

//////////////////////////////////////////////////////////////////////////

class SortColors : public c_solution<SortColors>
{
public:
    void sortColors(int A[], int n)
    {
        int red = 0, white = 0, blue = n-1; 
        for (white = 0; white <= blue;)
        {
            if (A[white] == 0)
                swap(A[red++], A[white++]); 
            else if (A[white] == 2)
                swap(A[blue--], A[white]);
            else 
                ++white;
        }
    }
};

//////////////////////////////////////////////////////////////////////////

class EditDistance : public c_solution<EditDistance>
{
    int minDistance(string word1, string word2)
    {
        /**
         * dp(i, j) represnets the minimum edit distance from 
         * substring word1[0...i] to substring word2[0...j]
         */ 
        int rows = (int)word1.length() + 1;
        int cols = (int)word2.length() + 1;
        vector<vector<int> > dp(rows, vector<int>(cols, 0));
        
        for (int i = 0; i < rows; ++i)
        {
            dp[i][0] = i;
        }
        for (int j = 0; j < cols; ++j)
        {
            dp[0][j] = j;
        }
        
        for (int i = 1; i < rows; ++i)
        {
            char ci = word1[i-1]; 
            for (int j = 1; j < cols; ++j)
            {
                char cj = word2[j-1]; 
                if (ci == cj)
                {
                    dp[i][j] = dp[i-1][j-1];
                }
                else 
                {
                    // Modify ci to cj
                    int d_edit = dp[i-1][j-1] + 1; 
                    
                    // Add cj to wordp[0, i)
                    int d_add = dp[i][j-1] + 1;
                    
                    // Delete ci from wordp[0, i)
                    int d_del = dp[i-1][j] + 1; 
                    
                    int min_d = min(d_edit, d_add); 
                    min_d = min(min_d, d_del); 
                    dp[i][j] = min_d; 
                }
            }
        }

        int result = dp[rows-1][cols-1];
        return result; 
    }
}; 

//////////////////////////////////////////////////////////////////////////

class SimplifyPath : c_solution<SimplifyPath>
{
    /**
     * AC, code needs to be cleaned
     */
public:
    string simplifyPath(string path)
    {
        vector<string> p; 
        
        int idx = 1; 
        while (idx < (int)path.length())
        {
            if (path[idx] == '/')
            {
                ++idx; 
                continue;
            }
            
            int cur = idx;
            
            while (path[idx] != '/' && idx < (int)path.length())
                ++idx;
            
            if (idx == path.length())
            {
                string last = path.substr(cur);
                if (last.compare("..") == 0)
                {
                    if (!p.empty())
                        p.pop_back();
                }
                else if (last.compare(".") != 0)
                    p.push_back(last);
                break;
            }
            
            string str = path.substr(cur, idx-cur);
            if (str.compare("..") == 0)
            {
                if (!p.empty())
                    p.pop_back();
            }
            else if (str.compare(".") != 0)
                p.push_back(str);
            
            ++idx;
        }
        
        string result = "/"; 
        string sep = "";
        for (int i = 0; i < (int)p.size(); ++i)
        {
            result += sep + p[i]; 
            sep = "/";
        }
        
        return result;
    }
    
    void test()
    {
        string path = "/..";
        string new_path = simplifyPath(path); 
        cout << new_path << std::endl;
    }
};

//////////////////////////////////////////////////////////////////////////

class SSearch2DMatrix : public c_solution<SSearch2DMatrix>
{
public: 
    bool searchMatrix(vector<vector<int> > &matrix, int target) 
    {
        int rows = (int)matrix.size(); 
        int cols = (int)matrix[0].size(); 
        
        int r = 0;
        int c = cols-1;
        
        while (r >= 0 && r < rows && c >= 0 && c < cols)
        {
            if (matrix[r][c] == target)
                return true;
            if (matrix[r][c] > target)
            {
                --c;
            }
            else 
            {
                ++r; 
            }
        }
        
        return false;
    }
};

//////////////////////////////////////////////////////////////////////////

class SetMatrixZero : public c_solution<SetMatrixZero>
{
public:
    void setZeroes(vector<vector<int> > &matrix) 
    {
        int rows = (int)matrix.size();
        int cols = (int)matrix[0].size(); 
        
        bool zero_row0 = false;
        bool zero_col0 = false;
        
        for (int i = 0; i < rows; ++i)
        {
            if (matrix[i][0] == 0)
            {
                zero_col0 = true;
                break;
            }
        }
        
        for (int j = 0; j < cols; ++j)
        {
            if (matrix[0][j] == 0)
            {
                zero_row0 = true;
                break;
            }
        }
        
        for (int i = 1; i < rows; ++i)
        {
            for (int j = 1; j < cols; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[0][j] = 0; 
                    matrix[i][0] = 0; 
                }
            }
        }
        
       for (int i = 1; i < rows; ++i)
       {
            for (int j = 1; j < cols; ++j)
            {
                if (matrix[0][j] == 0 || matrix[i][0] == 0)
                    matrix[i][j] = 0; 
            }
       }
       
       if (zero_row0)
       {
           for (int i = 0; i < cols; ++i)
               matrix[0][i] = 0; 
       }
       
       if (zero_col0)
       {    
           for (int i = 0; i < rows; ++i)
               matrix[i][0] = 0; 
       }
    }
};

//////////////////////////////////////////////////////////////////////////

class ClimbingStairs : public c_solution<ClimbingStairs>
{
public:
    int climbStairs(int n)
    {
        vector<int> dp(n+1);

        dp[0] = 0;
        dp[1] = 1; 
        
        for (int i = 2; i <= n; ++i)
        {
            dp[i] = dp[i-2] + dp[i-1];
        }
        return dp[n];
    }
};

//////////////////////////////////////////////////////////////////////////

class SqrtX : public c_solution<SqrtX>
{
public:
    int sqrt(int x)
    {
        if (x == 0)
            return 0;
        double last = 0;
        double res = 1;
        while (res != last)
        {
            last = res;
            res = (res + x / res) / 2;
        }
        return (int)res;
    }
    
    /**
     * Binary Search
     * sqrt(x) always <= (x / 2 + 1)
     */
    int sqrt2(int x)
    {
        long long i = 0;
        long long j = x / 2 + 1;
        
        while (i < j)
        {
            long long mid = (i + j) / 2; 
            long long sq = mid * mid; 
            if (sq == x)
                return mid; 
            if (sq < x)
                i = mid + 1; 
            else j = mid - 1;
        }
        return j;
    }
};

//////////////////////////////////////////////////////////////////////////

class PlusOne : public c_solution<PlusOne>
{
public:
    vector<int> plusOne(vector<int> &digits)
    {
        int idx = (int)digits.size() - 1;
       
        int carry = 0;
        int plus = 1;
        for (; idx >= 0; --idx)
        {
            int t = digits[idx] + plus + carry; 
            carry = t / 10;
            digits[idx] = t % 10;
            plus = 0;
        }
        
        if (carry == 1)
            digits.insert(digits.begin(), 1);
        
        return digits;
    }
};


//////////////////////////////////////////////////////////////////////////

class ValidNumber : public c_solution<ValidNumber>
{
public:
    
    bool isNumber(const char *s)
    {
        enum InputType 
        {
            INVALID,    // 0
            SPACE,      // 1
            SIGN,       // 2
            DIGIT,      // 3
            DOT,        // 4
            EXPONENT,   // 5
            NUM_INPUTS  // 6
        }; 

        int transitionTable[][NUM_INPUTS] = {
            -1,  0,  3,  1,  2, -1,     // next states for state 0
            -1,  8, -1,  1,  4,  5,     // next states for state 1
            -1, -1, -1,  4, -1, -1,     // next states for state 2
            -1, -1, -1,  1,  2, -1,     // next states for state 3
            -1,  8, -1,  4, -1,  5,     // next states for state 4
            -1, -1,  6,  7, -1, -1,     // next states for state 5
            -1, -1, -1,  7, -1, -1,     // next states for state 6
            -1,  8, -1,  7, -1, -1,     // next states for state 7
            -1,  8, -1, -1, -1, -1,     // next states for state 8
        };
        
        int state = 0;
        while (*s != '\0') 
        {
            InputType inputType = INVALID;
            if (isspace(*s))
                inputType = SPACE;
            else if (*s == '+' || *s == '-')
                inputType = SIGN;
            else if (isdigit(*s))
                inputType = DIGIT;
            else if (*s == '.')
                inputType = DOT;
            else if (*s == 'e' || *s == 'E')
                inputType = EXPONENT;

            // Get next state from current state and input symbol
            state = transitionTable[state][inputType];

            // Invalid input
            if (state == -1) return false;
            else ++s;
        }
        // If the current state belongs to one of the accepting (final) states,
        // then the number is valid
        return state == 1 || state == 4 || state == 7 || state == 8;
    }
};

//////////////////////////////////////////////////////////////////////////

class AddBinary : public c_solution<AddBinary>
{
    /**
     * AC
     */
public:
    string addBinary(string a, string b)
    {
        string& shorter = (a.length() < b.length()) ? a : b;
        int len_diff = (int)(a.length() - b.length());
        for (int i = 0; i < std::abs(len_diff); ++i)
            shorter.insert(shorter.begin(), '0');
        
        int idx = (int)a.length()-1;
        int carry = 0;
        string result(a.length()+1, '0');
        for (; idx >= 0; --idx)
        {
            int t = (int)(a[idx] - '0') + (int)(b[idx] - '0') + carry; 
            carry = t / 2;
            result[idx] = (char)('0' + t % 2);
        }
        
        if (carry == 1)
        {
            result.insert(result.begin(),'1'); 
            result.resize(a.length()+1);
        }
        else
            result.resize(a.length());
       
        return result;
    }
    
    void test()
    {
        string a = "11"; 
        string b = "1";
        string result = addBinary(a, b);
        cout << result << std::endl; 
    }
};

//////////////////////////////////////////////////////////////////////////

class MinimumPathSum : public c_solution<MinimumPathSum>
{
public:
    int minPathSum(vector<vector<int> > &grid)
    {
        int rows = (int)grid.size();
        int cols = (int)grid[0].size();

        /*
         * dp(i, j) represents the minimum sum from grid(0, 0) to grid(i, j)
         */
        vector<vector<int> > dp(rows, vector<int>(cols, 0));
        
        dp[0][0] = grid[0][0];
        for (int i = 1; i < cols; ++i)
            dp[0][i] = dp[0][i-1] + grid[0][i];
        for (int j = 1; j < rows; ++j)
            dp[j][0] = dp[j-1][0] + grid[j][0];
        
        for (int i = 1; i < rows; ++i)
        {
            for (int j = 1; j < cols; ++j)
            {
                dp[i][j] = min(dp[i-1][j] + grid[i][j], dp[i][j-1] + grid[i][j]);
            }
        }

        return dp[rows-1][cols-1];
    }
};


//////////////////////////////////////////////////////////////////////////

class UniquePaths : public c_solution<UniquePaths>
{
    /*
     * AC
     */
public:
    int uniquePaths(int m, int n)
    {
        /*
         * dp(i, j) represents number of unique paths from (0, 0) to (i, j)
         * dp(i, j) = dp(i-1, j) + dp(i, j-1)
         */
        vector<vector<int> > dp(m, vector<int>(n, 0));
        
        for (int i = 0; i < m; ++i)
            dp[i][0] = 1; 
        for (int j = 0; j < n; ++j)
            dp[0][j] = 1; 
        
        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        
        return dp[m-1][n-1];
    }
};

//////////////////////////////////////////////////////////////////////////

class UniquePathsII : public c_solution<UniquePaths>
{
    /**
     * DFS will TLE on large judge! 
     * DP
     */
public: 
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid)
    {
        int rows = obstacleGrid.size();
        int cols = obstacleGrid[0].size();
        
        vector<int> pre_dp(cols, 0);
        vector<int> dp(cols, 0);
        
        // First row 
        pre_dp[0] = 1 - obstacleGrid[0][0];
        for (int i = 1; i < cols; ++i)
            pre_dp[i] = pre_dp[i-1] & (1 - obstacleGrid[0][i]);

        for (int i = 1; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (obstacleGrid[i][j] == 1)
                {
                    dp[j] = 0; 
                    continue; 
                }
                
                // From cell above
                dp[j] = pre_dp[j]; 

                // From cell left
                if (j > 0)
                    dp[j] += dp[j-1]; 
            }
            pre_dp.swap(dp);
        }
        return pre_dp[cols-1];
    }
    
    void dfs(vector<vector<int> >& grid, int row, int col, int& paths)
    {
        if (row == (int)grid.size()-1 && col == (int)grid[0].size()-1)
        {
            if (grid[row][col] != 1)
                ++paths;
            return;
        }
        
        if (grid[row][col] == 1)
            return; 
        
        if (row != grid.size()-1)
            dfs(grid, row+1, col, paths);
        if (col != grid[0].size()-1)
            dfs(grid, row, col+1, paths);
    }
}; 


//////////////////////////////////////////////////////////////////////////


class RotateList : public c_solution<RotateList>
{
    /*
     * Incorrect Result 
     */ 
    
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
    
public:
    ListNode *rotateRight(ListNode *head, int k)
    {        
        if (!head || k == 0)
            return head;

        ListNode *fast = head; 
        ListNode *slow = head; 
        ListNode *new_tail = NULL;

        for (int i = 0; i < k && fast->next; ++i)
            fast = fast->next; 
        
        while (fast->next)
        {
            fast = fast->next;
            new_tail = slow;
            slow = slow->next;
        }
        
        if (fast == head)
            return head;
        
        fast->next = head; 
        new_tail = NULL;
        head = slow; 
        
        return head;
    }
};

//////////////////////////////////////////////////////////////////////////

class PermutationSequence : public c_solution<PermutationSequence>
{
    /*
     * Recursion TLE on large judge
     */
public:
    string getPermutation(int n, int k) 
    {
        if (n == 0)
            return "0";
        string solution, res; 
        vector<int> visited(n, 0); 
        int count = 0; 
        permute_helper(n, k, 0, count, solution, res, visited);
        
        return res; 
    }
    
    void permute_helper(int n, int k, int step, int& count, string& solution, string& res, vector<int>& visited)
    {
        if (step == n)
        {
            ++count;
            if (count == k)
                res.assign(solution);
            return; 
        }
        
        for (int i = 1; i <= n; ++i)
        {
            if (visited[i-1] == 0)
            {
                visited[i-1] = 1; 
                solution.push_back(i+'0'); 
                permute_helper(n, k, step+1, count, solution, res, visited); 
                visited[i-1] = 0; 
                
                if (solution.size() > 0)
                    solution.resize(solution.size()-1);
            }
        }
    }
}; 

//////////////////////////////////////////////////////////////////////////

class SpiralMatrixII : public c_solution<SpiralMatrixII>
{
    /*
     * AC
     */ 

public:
    vector<vector<int> > generateMatrix(int n)
    {
        vector<vector<int> > mat(n, vector<int>(n, 0)); 
        
        int val = 1;
        int max_layer = (n % 2 == 0) ? n / 2 : n / 2 + 1; 
        for (int layer = 0; layer < max_layer; ++layer)
        {
            int first = layer;  
            int last = n - 1 - first; 
            
            if (first == last)
            {
                mat[first][first] = val++;
                continue; 
            }
            
            for (int edge = 0; edge < 4; ++edge)
            {
                for (int i = first; i < last; ++i)
                {
                    int offset = i - first;
                    if (edge == 0)      // top
                        mat[first][i] = val++;
                    if (edge == 1)      // right
                        mat[i][last] = val++; 
                    if (edge == 2)      // bottom
                        mat[last][last-offset] = val++; 
                    if (edge == 3)      // left
                        mat[last-offset][first] = val++;
                }
            }
        }
        return mat; 
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

	//c_solution<BinaryTreeFromInorderPostorder>::run_test(); 

	// c_solution<InterleavingString>::run_test(); 

	// c_solution<Permutations>::run_test(); 

	// c_solution<Combinations>::run_test(); 

	// c_solution<Subsets>::run_test(); 

	// c_solution<RestoreIPAddress>::run_test();

    // c_solution<GrayCode>::run_test();
    // c_solution<ScrambleString>::run_test();

    // c_solution<RemoveDuplicatesSortedArray>::run_test();
    
    // c_solution<RemoveDuplicatesSortedArrayII>::run_test();
    
    // c_solution<SimplifyPath>::run_test(); 

    c_solution<AddBinary>::run_test();


	return 0;
}

