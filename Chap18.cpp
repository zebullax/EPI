#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

bool BinarySearch(const vector<int> &v,int l,int h, int elem, int *pos)
{
	int m;
	while (l<=h)
	{
		m = l + (h - l) >> 1;
		if (v[m] > elem)
			h = m - 1;
		else if (v[m] < elem)
			l = m + 1;
		else
		{
			*pos = m;
			return true;
		}
	}
	return false;
}

bool Find2Sum(const vector<int> &v, int* l, int* h, int elem)
{
	int i = *l, j = *h;

	while (i<=j)
	{
		if (v[i] + v[j] > elem)
			j--;
		else if (v[i] + v[j] < elem)
			i++;
		else
		{
			*l = i;
			*h = j;
			return true;
		}
	}
	return false;
}

bool Prob18_6(vector<int> v, int s, tuple<int, int, int> *result)
{
	int j=0,k=v.size()-1;
	
	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); ++i)
	{
		j = i;
		if(Find2Sum(v, &j, &k, s - v[i]))
		{
			*result=make_tuple(i, j, k);
			return true;
		}
	}
	return false;

}
void Prob18_6D()
{
	vector<int> v;
	tuple<int, int, int> result;
	
	v.push_back(8); v.push_back(3); v.push_back(7); v.push_back(2); v.push_back(1); v.push_back(9);
	int score = 8;
	if (Prob18_6(v, score, &result))	
		cout << "3Creates :" << get<0>(result) << "," << get<1>(result) << "," << get<2>(result) << "\n";
	else
		cout << "!3Creates\n";
}

int Prob18_3(const vector<int> &v)
{
	int global_max_idx = 0;
	int max_left_idx=0, max_right_idx=0;
	int global_capacity_i = 0;
	
	for (int i = 0; i < v.size(); ++i)
		global_max_idx = max(global_max_idx, v[i]);
	for (int i = 0; i < global_max_idx; ++i)
	{
		max_left_idx = max(max_left_idx, v[i]);
		global_capacity_i += max_left_idx-v[i];
	}
	for (int i = v.size()-1; i > global_max_idx; --i)
	{
		max_right_idx = max(max_right_idx, v[i]);
		global_capacity_i += max_right_idx-v[i];
	}
	return global_capacity_i;
}
void Prob18_3D()
{
	vector<int> h;
	h.push_back(1); h.push_back(2); h.push_back(1); h.push_back(3); h.push_back(4); h.push_back(4); h.push_back(5); h.push_back(1); h.push_back(2); h.push_back(0); h.push_back(3);
	cout << "Global capacity :" << Prob18_3(h);
}

int Prob18_9(const vector<int> &v)
{
	int WinCount = 1;
	int MajElem = v[0];
	for (int i = 0; i < v.size(); ++i)
	{
		if (MajElem == v[i])
			WinCount++;
		else
		{
			WinCount = max(WinCount - 1, 0);
			if (WinCount==0)
			{
				MajElem = v[i];
				WinCount = 1;
			}
		}
	}
	return MajElem;
}
void Prob18_9D()
{
	vector<int> v;
	v.push_back(0); v.push_back(2); v.push_back(1); v.push_back(2); v.push_back(0); v.push_back(3); v.push_back(3); v.push_back(3); v.push_back(0); v.push_back(0); v.push_back(4);
	v.push_back(0); v.push_back(0); v.push_back(0); v.push_back(0);
	cout << "Majority element : " << Prob18_9(v)<<endl;
}

int Prob18_11(const vector<int> &v)
{
	int i = 0,j = v.size() - 1, maxL = v[i], maxR = v[j];
	int globalMax = (j-i)*min(v[i],v[j]), localMax = globalMax;
	
	while (i<j)
	{
		if (maxL > maxR){
			while (v[j] <= maxR && i < j)
				j--;
			maxR = v[j];
			localMax = max((j - i)*min(v[i], v[j]), localMax);
			globalMax = max(globalMax, localMax);
		}
		else
		{
			while (v[i] <= maxL && i < j)
				i++;
			maxL = v[i];
			localMax = max((j - i)*min(v[i], v[j]), localMax);
			globalMax = max(globalMax, localMax);
		}
	}
	/*
	//brute force
	for (int i = 0; i < v.size(); ++i)
	{
		localMax = 0;
		for (int j = i+1; j < v.size(); ++j)
		{
			localMax = max((j - i)*min(v[i], v[j]), localMax);
		}
		globalMax = max(globalMax, localMax);
	}
	*/
	return globalMax;
}
void Prob18_11D()
{
	vector<int> v;
	v.push_back(1); v.push_back(2); v.push_back(1); v.push_back(3); v.push_back(4); v.push_back(4); v.push_back(5); v.push_back(6);
	v.push_back(2); v.push_back(1); v.push_back(3); v.push_back(1); v.push_back(3); v.push_back(2); v.push_back(1); v.push_back(2); v.push_back(4); v.push_back(1); 
	cout << "Max trapped water : " << Prob18_11(v)<<endl;
}
int main(int argc,char** argv)
{
	Prob18_11D();

	getchar();
	return 0;
}