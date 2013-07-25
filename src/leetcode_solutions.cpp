
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