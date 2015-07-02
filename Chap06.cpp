#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

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
int main(int argc,char** argv)
{
	Prob6_3D();
	getchar();
	return 0;
}