#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

int GetScoreCombinationNumber(const vector<int> &w, int score)
{
	vector<int> NbComb(score + 1, 0);
	NbComb[0] = 1;

	for (int i = 0; i <= score; ++i)
	{
		for (int j = 0; j < w.size(); ++j)
		{
			if (i >= w[j])
				NbComb[i] += NbComb[i - w[j]];
		}
	}
	return NbComb[score];
}
void Prob17_1D()
{
	vector<int> w; w.push_back(2); w.push_back(3); w.push_back(7);	
	unsigned int score = 12;	
	cout << GetScoreCombinationNumber(w,score)<< " possible combinations to reach " << score << endl;
}

int EditCost(const string &a, const string &b)
{
	vector<vector<int> > edit_costs(a.size() + 1, vector<int>(b.size() + 1, 0));
	for (int i = 0; i < b.size() + 1; ++i)
		edit_costs[0][i] = i;
	for (int i = 0; i < a.size() + 1; ++i)
		edit_costs[i][0] = i;
	for (int i = 1; i <= a.size(); ++i)
	{
		for (int j = 1; j <= b.size(); ++j)
		{
			int swapCost = (a[i-1] == b[j-1] ? edit_costs[i - 1][j - 1] : edit_costs[i - 1][j - 1] + 1);
			int InsertCost = 1 + edit_costs[i][j - 1];
			int DeleteCost = 1 + edit_costs[i - 1][j];
			edit_costs[i][j] = min(swapCost, min(InsertCost, DeleteCost));
		}
	}
	/*
	for (int i = 0; i <= a.size(); ++i)
	{
		for (int j = 0; j <= b.size(); ++j)
		{
			cout << edit_costs[i][j];
		}
		cout << endl;
	}*/
	return edit_costs[a.size() ][b.size() ];
}
void Prob17_2D()
{
	string a = "meilenstein";
	string b = "levenshtein";

	cout << "Edit distance " << a << "->" << b << " = " << EditCost(a, b);

}

int GetMazeTraversalCounts(unsigned int n, unsigned int m)
{
	vector<vector<int> > counts(n+1, vector<int>(m+1, 0));
	for (unsigned int i = 0; i <= m ; ++i)
		counts[0][i] = 0;
	for (unsigned int i = 0; i <= n; ++i)
		counts[i][0] = 0;
	
	counts[1][1] = 0;
	for (unsigned int i = 1; i <= n; ++i)
	{
		for (unsigned int j = 1; j <= m; ++j)
		{
			counts[i][j] = counts[i - 1][j]  + counts[i][j - 1] ;
		}
	}
	return counts[n][m];
}
void Prob17_4D()
{
	unsigned int n = 3;
	unsigned int m = 3;
	cout << "In a "<<n<<"x"<<m<<" maze, the nb of valid paths is:"<<GetMazeTraversalCounts(n, m)<<endl;
}
bool IsAConcatenation(string url,const unordered_set<string> &dic){
    vector<bool> validPrefix(url.size()+1,false);
    validPrefix[0]=true;
    
    for (unsigned int i=1; i<=url.size(); ++i)
    {
        for(unsigned int j=0;j<=i;++j)
        {
            if((validPrefix[j] && dic.find(url.substr(j,i-j))!=dic.end() ))
            {
                validPrefix[i]=true;
                break;
            }
        }
    }
    return validPrefix[url.size()];
}

void Prob17_12D(){
    unordered_set<string> dic;
	dic.emplace("beyond"); dic.emplace("hand"); dic.emplace("and"); dic.emplace("bed"); dic.emplace("bath");
    string url="bedbathandbeyond";
    cout<<IsAConcatenation(url, dic);
}
pair<int,int> KadaneMaxSubArraySum(vector<int> v,int start_i,int end_i)
{
	int max_so_far_i = 0, total_max_i = 0, idx_max_i = 0;
	for (int i = start_i; i <= end_i; ++i)
	{
		max_so_far_i = max(0, max_so_far_i + v[i]);
		if (max_so_far_i>total_max_i)
		{
			total_max_i = max_so_far_i;
			idx_max_i = i;
		}
	}
	return make_pair(idx_max_i,total_max_i);
}
int Prob17_11(vector<int> v)
{
	vector<int> WrappedSubsums(v.size(),0);
	pair<int, int> max_starting_here_i, max_ending_here_i;
	int global_max_i = 0;
	for (int i = 0; i < v.size(); ++i)
	{
		max_ending_here_i = KadaneMaxSubArraySum(v, 0, i);
		max_starting_here_i = KadaneMaxSubArraySum(v, i + 1, v.size() - 1);			
		WrappedSubsums[i] = max_ending_here_i.second + (max_starting_here_i.first == v.size() - 1 ? max_starting_here_i.second:0);
		global_max_i = max(global_max_i, WrappedSubsums[i]);
	}
	return global_max_i;
}
void Prob17_11D()
{
	vector<int> v;
	//v.push_back(904); v.push_back(40); v.push_back(523); v.push_back(12); v.push_back(-335); v.push_back(-385); v.push_back(-124); v.push_back(481); v.push_back(-31);
	v.push_back(10); v.push_back(-4); v.push_back(5); v.push_back(-4); v.push_back(10); 
	cout <<"Max subset sum in circular array:"<< Prob17_11(v)<<endl;
}
int Prob17_12(const vector<int> &A)
{
	int global_max_i = 1;
	vector<int> len(A.size(), 0);
	len[0] = 1;
	for (int i = 1; i < A.size(); ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (A[i]>=A[j])
			{
				len[i] = max(len[i], len[j] + 1);
				global_max_i = max(global_max_i, len[i]);
			}
		}
	}
	return global_max_i;
}
void Prob17_21D()
{
	vector<int> A;
	A.push_back(0); A.push_back(8); A.push_back(4); A.push_back(12); A.push_back(2); A.push_back(10); A.push_back(6); A.push_back(14); A.push_back(1); A.push_back(9);
	cout << "longest Nondecreasing seq has length " << Prob17_12(A) << endl;
}

int Prob17_12(const vector<int> &v, const vector<int> &w,int max_capacity_i)
{
	vector<vector<int> > maxBenef(v.size()+1, vector<int>(max_capacity_i+1, 0));
	for (int i = 1; i <= v.size(); ++i)
	{
		for (int j = 1; j <= max_capacity_i; ++j)
		{
			if (j >= w[i - 1])
			{
				maxBenef[i][j] = max(maxBenef[i - 1][j], maxBenef[i-1][j - w[i - 1]] + v[i - 1]);
			}
			else
				maxBenef[i][j] =maxBenef[i - 1][j];
		}
	}
	/*for (int i = 1; i <= v.size(); ++i)
	{
		for (int j = 1; j <= max_capacity_i; ++j)
		{
			cout << maxBenef[i][j]<<" ";
		}
		cout << endl;
	}*/
	return maxBenef[v.size()][max_capacity_i];
}
void Prob17_7D()
{
	vector<int> v,w;
	v.push_back(4); v.push_back(2); v.push_back(2); v.push_back(1); v.push_back(10);
	w.push_back(12); w.push_back(1); w.push_back(2); w.push_back(1); w.push_back(4);
	cout<< "max value is "<<Prob17_12(v, w, 15)<<endl;
}
int main(int argc, char** argv)
{
	Prob17_1D();

	getchar();
	return 0;
}