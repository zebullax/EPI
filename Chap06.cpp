#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
using namespace std;

void Swap(vector<int> *v, int j,int k)
{
	int tmp = (*v)[j];
	(*v)[j] = (*v)[k];
	(*v)[k] = tmp;
}

void DutchFlagPartition(vector<int> *v, int pivot_idx)
{
	int  l = 0, m = 0, h = v->size()-1;
	int pivot = (*v)[pivot_idx];
	while (m<=h)
	{
		if ((*v)[m]<pivot)
		{
			Swap(v, m++, l++);			
		}
		else if ((*v)[m] == pivot)
		{
			m++;
		}
		else if ((*v)[m] > pivot)
		{
			Swap(v, m, h--);			
		}
	}
}

void Prob6_1D()
{
	vector<int> v;
	v.push_back(23); v.push_back(12); v.push_back(5); v.push_back(0); v.push_back(12); v.push_back(5);
	v.push_back(23); v.push_back(9); v.push_back(-23); v.push_back(230);
	for (int elem : v)
	{
		cout << elem << ",";
	}
	cout << endl;
	DutchFlagPartition(&v, 1);
	for (int elem : v)
	{
		cout << elem << ",";
	}
	cout << endl;
}

string BigIntMultiplication(string A,string B)
{
	bool is_neg = false;	

	if (A[0] == '-')
	{
		if (B[0] == '-')
		{
			A = A.substr(1, A.size() - 1);
			B = B.substr(1, B.size() - 1);
		}
		else
		{
			is_neg = true;
			A = A.substr(1, A.size() - 1);
		}
	}
	else if (B[0] == '-')
	{
		is_neg = true;
		B = B.substr(1, B.size() - 1);
	}
	
	string result(static_cast<int>(A.size()) + static_cast<int>(B.size()), '0');
	int carry = 0;
	int digit_value;
	for (int i = A.size()-1; i >=0; --i)
	{
		for (int j = B.size() - 1; j >= 0;--j)
		{
			digit_value = (result[i+j+1]-'0')+carry + (B[j] - '0') * (A[i] - '0');
			carry = digit_value / 10;
			result[i + j + 1] = '0'+(digit_value % 10);
		}
		if (carry != 0)
		{
			result[i] = '0' + carry;
			carry = 0;
		}
	}
	if (!is_neg)
		return result;
	else
	{
		return ("-" + result);
	}
}
void Prob6_3D()
{
	string A = "-99999999";
	string B = "999999999999999999999999";
	string result = BigIntMultiplication(A, B);
	cout << result << endl;
}

int Prob6_10(const vector<int> &v)
{
	vector<int> back(v.size()), forw(v.size());
	for (int i = 0; i < v.size();++i)
	{
		back[i] = (i == 0 ? v[0] : back[i - 1] * v[i]);		
		forw[v.size() - 1 - i] = (i == 0 ? v[v.size() - 1] : forw[v.size() - i] * v[v.size() - 1 - i]);
	}
	int max_product = numeric_limits<int>::min();
	for (int i = 0; i < v.size();++i)
	{
		max_product = max(max_product, (i == 0 ? 1 : back[i - 1])*(i == v.size() - 1 ? 1 : forw[i + 1]));
	}
	return max_product;
}

void Prob6_10D()
{
	vector<int> v;
	v.push_back(3); v.push_back(-2); v.push_back(6); v.push_back(6); v.push_back(-12);
	cout << "Max=" << Prob6_10(v);
}

pair<int,int> Prob6_11(const vector<int> &v)
{
	int max_s = 0, max_e = 0;
	int tmp_s = 0;
	int local_sum = 1, global_max = 1;

	for (int i = 1; i < v.size(); ++i)
	{
		if (v[i]<v[i - 1])
		{
			if (local_sum > global_max)
			{
				max_s = tmp_s;
				max_e = i - 1;
				global_max = local_sum;
			}
			tmp_s = i;
			local_sum = 1;
		}
		else
			local_sum ++;
	}
	return make_pair(max_s, max_e);
}
void Prob6_11D()
{
	vector<int> v;
	v.push_back(3); v.push_back(2); v.push_back(3); v.push_back(4);
	v.push_back(2); v.push_back(8); v.push_back(-2); v.push_back(-1); v.push_back(0); v.push_back(23); v.push_back(0);
	pair<int, int> idx = Prob6_11(v);
	cout << "start=" << idx.first << ", end=" << idx.second;
}
vector<int> Prob6_12(int n)
{
	vector<bool> v(n + 1,true);
	vector<int> result;
	for (int i = 2; i <= n; ++i)
	{
		if (v[i])
			result.push_back(i);
		for (int j = i * i; j <= n; j+=i)
			v[j] = false;
	}
	return result;
}
void Prob6_12D()
{
	int n = 100;
	vector<int> result = Prob6_12(n);
	for (int i = 0; i < result.size(); ++i)
		cout << result[i] << ",";
}

template<class T>
void RandomShuffle(vector<T> &v)
{
	random_device rnb_init;
	default_random_engine generator(rnb_init());
	uniform_int_distribution<int> distrib(0, v.size()-1);
	int n = distrib(generator);

	for (int i = v.size()-1; i >=0;--i)
	{
		uniform_int_distribution<int>::param_type p(0, i);
		n = distrib(generator,p) ;
		swap(v[i], v[n]);
	}
}

template<class T>
void Prob6_13(vector<T> &v, vector<int> p)
{
	for (int i = 0; i < v.size();++i)
	{
		while (i != p[i])
		{
			std::swap(v[p[i]], v[i]);
			swap(p[p[i]], p[i]);
		}
	}
}

void Prob6_13D()
{
	random_device rnb_init;
	default_random_engine generator(rnb_init());
	uniform_int_distribution<int> distrib(1, 100);
	int n = distrib(generator);
	vector<int> v(n), p(n), check(n);

	for (int i = 0; i < n; ++i) 
	{
		v[i]=i;
		p[i]=i;
	}
	RandomShuffle(p);
	check = v;
	Prob6_13(v, p);	
	for (int i = 0; i < v.size(); ++i)
	{
		assert(v[p[i]] == check[i]);
	}
	cout << "Ok\n";
}

vector<int> Prob6_14(const vector<int> &vect)
{
	vector<int> v = vect;
	int min_i = v.size() - 1, max_i = v.size() - 1;
	int max = v[max_i], min = v[min_i];
	int s_i = v.size() - 2;
	while (v[s_i]>v[s_i+1]&& s_i>=0)
		s_i--;
	int e_i = s_i+1;
	for (int i = s_i + 1; i < v.size() ;++i)
	{
		if (v[i]>=v[s_i])
			e_i = i;
	}
	swap(v[s_i], v[e_i]);
	reverse(v.begin() + s_i + 1, v.end());
	return v;
}

void Prob6_14D()
{
	vector<int> v;
	v.push_back(1); v.push_back(0); v.push_back(3); v.push_back(2);
	v = Prob6_14(v);
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << ",";
}

template <class T>
T Prob6_20(vector<T> t, vector<float> p)
{
	vector<float> c(p.size());
	for (int i = 0; i < p.size(); ++i)
		c[i] = (i == 0 ? p[0] : c[i - 1] + p[i]);
	random_device rd;
	default_random_engine generator(rd());
	uniform_real_distribution<float> distribution(.0f, 1.0f);
	float rnb = distribution(generator);
	int i = 0;
	while(i < c.size() && c[i] < rnb) ++i;
	return t[i];
}
void Prob6_20D()
{
	vector<int> t;
	t.push_back(0); t.push_back(1); t.push_back(2); t.push_back(4);
	vector<float> p;
	p.push_back(0.1f); p.push_back(0.1f); p.push_back(0.5f); p.push_back(0.3f);
	unordered_map<int, float> samples;
	for (int i = 0; i < 1000; ++i)
	{
		int res = Prob6_20(t, p);
		samples[res]+=0.001f;
	}
	for (int i = 0; i < t.size(); ++i)
		cout << t[i] << "=" << samples[t[i]] << endl;
}
bool Prob6_21(vector<vector<int> >v)
{
	vector<unordered_set<int> > rows(9, unordered_set<int>()), cols(9, unordered_set<int>()), squares(9, unordered_set<int>());
	
	for (int r = 0; r < 9; ++r)
	{
		for (int c = 0; c < 9; ++c)
		{
			if (v[r][c] != 0)
			{
				if (rows[r].find(v[r][c]) == rows[r].end())
					rows[r].insert(v[r][c]);
				else
					return false;

				if (cols[c].find(v[r][c]) == cols[c].end())
					cols[c].insert(v[r][c]);
				else
					return false;
				int sq_idx = 3 * (r / 3) + c / 3;
				if (squares[sq_idx].find(v[r][c]) == squares[sq_idx].end())
					squares[sq_idx].insert(v[r][c]);
				else
					return false;
			}
		}
	}
	return true;
}
void Prob6_21D()
{
	vector<vector<int> >v(9, vector<int>(9,0));
	v[0][0] = 5;	v[0][1] = 3;	v[0][2] = 0;	v[0][3] = 0;	v[0][4] = 7;	v[0][5] = 0;	v[0][6] = 0;	v[0][7] = 0;	v[0][8] = 0;
	v[1][0] = 6;	v[1][1] = 0;	v[1][2] = 0;	v[1][3] = 1;	v[1][4] = 9;	v[1][5] = 5;	v[1][6] = 0;	v[1][7] = 0;	v[1][8] = 0;
	v[2][0] = 0;	v[2][1] = 9;	v[2][2] = 8;	v[2][3] = 0;	v[2][4] = 0;	v[2][5] = 0;	v[2][6] = 0;	v[2][7] = 6;	v[2][8] = 0;
	v[3][0] = 8;	v[3][1] = 0;	v[3][2] = 0;	v[3][3] = 0;	v[3][4] = 6;	v[3][5] = 0;	v[3][6] = 0;	v[3][7] = 0;	v[3][8] = 3;
	v[4][0] = 4;	v[4][1] = 0;	v[4][2] = 0;	v[4][3] = 8;	v[4][4] = 0;	v[4][5] = 3;	v[4][6] = 0;	v[4][7] = 0;	v[4][8] = 1;
	v[5][0] = 7;	v[5][1] = 0;	v[5][2] = 0;	v[5][3] = 0;	v[5][4] = 2;	v[5][5] = 0;	v[5][6] = 0;	v[5][7] = 0;	v[5][8] = 6;
	v[6][0] = 0;	v[6][1] = 6;	v[6][2] = 0;	v[6][3] = 0;	v[6][4] = 0;	v[6][5] = 0;	v[6][6] = 2;	v[6][7] = 8;	v[6][8] = 0;
	v[7][0] = 0;	v[7][1] = 0;	v[7][2] = 0;	v[7][3] = 4;	v[7][4] = 1;	v[7][5] = 9;	v[7][6] = 0;	v[7][7] = 0;	v[7][8] = 5;
	v[8][0] = 0;	v[8][1] = 0;	v[8][2] = 0;	v[8][3] = 0;	v[8][4] = 8;	v[8][5] = 0;	v[8][6] = 0;	v[8][7] = 7;	v[8][8] = 9;
	cout << Prob6_21(v)<<endl;
	v[1][3] = 4;
	cout << Prob6_21(v)<<endl;
}
int main(int argc,char** argv)
{
	Prob6_13D();
	getchar();  
	return 0;
}