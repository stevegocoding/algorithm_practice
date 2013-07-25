
#include "utils.h"

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
		
		for (int i = 0; i < result.size(); ++i)
		{
			for (int j = 0; j <result[i].size(); ++j)
				std::cout << result[i][j] << std::endl; 
		}
	}
	
};

int main(int argc, char **argv)
{
	c_leetcode_solution<PalindromePartitioning>::run_test();
	
	return 0;
}