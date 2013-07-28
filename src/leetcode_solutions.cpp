
#include "utils.h"

using namespace std;

class PalindromePartitioning : public c_leetcode_solution<PalindromePartitioning>
{
	/**
	�����׶Σ�
	��һ���׶Σ��ҳ�����substring�����԰�ÿ��substring����һ��graph�Ľڵ㣬
	���S(i, j)��ʾ��i��ʼ��j������substring����ôS(i, j)��S(j+1, k)������
	�����S(0, i) (��������i��S(0, i)����S���ִ�) �������ڵ㣬��ô�ҳ�����
	�ִ������ҵ�����Щ���ڵ㵽����Ҷ�ӽڵ��·��
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
	 *	dp[i] ��ʾ��i���ַ�Ϊ��β���ַ����������и���Ŀ ״̬ת�Ʒ���Ϊ��
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
		for (int i = 0; i < s.length(); ++i)
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

int main(int argc, char **argv)
{
	// c_leetcode_solution<PalindromePartitioning>::run_test();
	
	c_leetcode_solution<PalindromePartitioningII>::run_test();

	return 0;
}