#include <vector>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <ctime>

using namespace std;

int Prob12_1(const vector<int> &v,int e)
{
	int minIdx=-1;
	int low=0,high=v.size()-1;
	int i;
	while(low<=high )
	{
		i=low+((high-low)>>1);
		if(v[i]>e)
			high=i-1;
		else if (v[i]<e)
			low=i+1;
		else
		{
			minIdx=i;
			high=i-1;
		}		
	}
	return(minIdx);
}

void Prob12_1D()
{
	vector<int> v;
	v.push_back(-14);v.push_back(-10);v.push_back(2);v.push_back(108);v.push_back(108);v.push_back(243);v.push_back(285);v.push_back(285);v.push_back(285);v.push_back(401);
	cout<<Prob12_1(v,108)<<endl;
	cout<<Prob12_1(v,285)<<endl;
}

int Prob12_6(int k)
{
	int low=0,high=k;
	int mid=low+(high-low)>>1;
	int i=0;

	while(low<=high)
	{
		if(mid*mid>k)
			high=mid-1;
		else
		{
			i=mid;
			low=mid+1;
		}
		mid=low+((high-low)>>1);
	}
	return mid;
}
void Prob12_6D()
{
	cout<<"300:"<<Prob12_6(300)<<endl;
	cout<<"16:"<<Prob12_6(16)<<endl;
}

int Prob12_4(const vector<int> &v)
{
	int l=0,h=v.size()-1,p=l+((h-l)>>1);
	while((h-l)>1)
	{
		if(v[l]<v[p])
			l=p;
		else
			h=p;
		p=l+((h-l)>>1);
	}
	return min(v[l],v[h]);
}
void Prob12_4D()
{
	vector<int> v;
	v.push_back(378);v.push_back(478);v.push_back(550);v.push_back(631);v.push_back(103);v.push_back(203);v.push_back(220);v.push_back(234);v.push_back(279);v.push_back(368);
	cout<<"Min:"<<Prob12_4(v);
}

unsigned int MakeIp(unsigned int a,unsigned int b,unsigned int c,unsigned int d) //a.b.c.d
{
	return ((a<<24)|(b<<16)|(c<<8)|d);
}
int Prob12_14(const vector<unsigned int> &v)
{
	vector<unsigned int> idx(1<<16,0);
	int tmp=v[17825792];
	int i=0;
	for(i=0;i<v.size();++i)
	{			
		idx[(v[i]&0xffff0000)>>16]++;
	}
	
	i=0;
	while(idx[i]==(1<<16))
		++i;
	
	int missingIpHeader=idx[i];
	idx.clear();
	for(i=0;i<v.size();++i)
	{
		if((v[i]&missingIpHeader)==missingIpHeader)
			idx[v[i]&0xffff]++;
	}

	while(idx[i]!=0)
		++i;
	return(missingIpHeader<<16|idx[i]);
}

void Prob12_14D()
{
	vector<unsigned int> v(1<<24,0);
	for (int i=0;i<255;i+=2)
	{
		for (int j=0;j<255;j+=2)
		{
			for(int k=0;k<255;k+=2)
			{
				v.push_back(MakeIp(i,j,k,1));
			}
		}
	}
	Prob12_14(v);
}
void swapVecElem(vector<int> &v,int i,int j)
{
	int t=v[i];
	v[i]=v[j];
	v[j]=t;
}
int partitionOrderStat(vector<int> &v,int low,int high)
{
	int i,j;
	i=low;j=low;
	int elem=v[high];
	while(j<high)
	{
		if(v[j]<elem)
		{
			++j;
		}
		else
		{
			swapVecElem(v,i,j);
			++i;
			++j;
		}
	}
	swapVecElem(v,i,high);
	return i;
}
int Prob12_11(const vector<int> &v_,int k)
{
	vector<int> v=v_;
	srand (time(NULL));
	int low=0,high=v.size()-1;	
	int p=0;	
	while(low<=high)
	{		
		p=partitionOrderStat(v,low,high);
		if(p==k)
			return (v[p]);
		if(p>k)
			high=p-1;
		if(p<k)
			low=p+1;		
	}
}
void Prob12_11D()
{
	vector<int> v;
	v.push_back(108);v.push_back(1108);v.push_back(85);v.push_back(285);v.push_back(2);v.push_back(243);v.push_back(5);v.push_back(401);v.push_back(-14);v.push_back(-10);
	for(int i=0;i<v.size()-1;++i)
	{
		cout<<i<<" order stat:"<<Prob12_11(v,i)<<endl;
	}
}

float RealRoot(float n)
{
	float threshold=.00001f;
	float prev=-1,now=0;
	float l=0,h=n;
	while(abs(now-prev)>threshold)
	{
		prev=now;
		now=(l+(h-l)/2.0f)*(l+(h-l)/2.0f);
		if(now>n)
			h=(l+(h-l)/2.0f);
		else
			l=(l+(h-l)/2.0f);
	}
	return l;
}
void Prob12_7D()
{
	cout<<"Root of 2.5:"<<RealRoot(2.5f)<<endl;
	cout<<"Root of 8.2:"<<RealRoot(8.2f)<<endl;
	cout<<"Root of 42.35:"<<RealRoot(42.35f)<<endl;
}
int main(int argc,char**argv)
{
	Prob12_7D();
	getchar();
}