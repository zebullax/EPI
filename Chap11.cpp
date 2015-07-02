#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <queue>
#include <functional>
#include <cstdlib>
#include <cmath>

using namespace std;
template<class t>
void PrintVector(const vector<t> &v)
{
	for(int i=0;i<v.size();++i)
	{
		cout<<v[i]<<" , ";
	}
}

struct LessSecondElem{
	bool operator()(const pair<int,int> l, const pair<int,int> &r)
	{
		return l.second>r.second;
	}
};

vector<int> Prob11_1(vector<vector<int> > v)
{
	vector<int> result;
	priority_queue<pair<int,int>,vector<pair<int,int> >,LessSecondElem >pq;
	int remainingV=v.size();

	for(int i=0;i<v.size();++i)
	{
		pq.emplace(i,v[i].at(0));
		v[i].erase(v[i].begin());
	}

	while(remainingV!=0)
	{
		pair<int,int> m;
		m=pq.top();pq.pop();
		result.push_back(m.second);
		if(!v[m.first].empty())
		{
			pq.emplace(m.first,v[m.first].at(0));
			v[m.first].erase(v[m.first].begin());
		}
		else
			remainingV--;
	}
	return result;
}
void Prob11_1D()
{
	vector<vector<int> >v; //each vector in v is a sorted collect of increasing ts
	vector<int> t;
	t.push_back(10);t.push_back(11);t.push_back(20);
	v.push_back(t);
	t.clear();t.push_back(12);t.push_back(14);t.push_back(25);
	v.push_back(t);
	t.clear();t.push_back(2);t.push_back(34);t.push_back(35);
	v.push_back(t);
	t=Prob11_1(v);
	for(int i=0;i<t.size();++i)
		cout<<t[i]<<",";
}

struct TriDPts{
	int x,y,z;
	TriDPts(int _x,int _y,int _z):x(_x),y(_y),z(_z){}
};

float DistanceToEarth(TriDPts l)
{
	return(sqrtf(l.x*l.x+l.y*l.y+l.z*l.z));
}
struct MaxQStar{
	bool operator()(const pair<int,TriDPts> &l, const pair<int,TriDPts> &r)
	{
		return(DistanceToEarth(l.second)<DistanceToEarth(r.second));
	}
};

vector<int> Prob11_4(vector<pair<int,TriDPts> >v,int k)
{
	vector<int> r;
	priority_queue<pair<int,TriDPts>,vector<pair<int,TriDPts> >,MaxQStar >pq;
	int i=0;
	for(i=0;i<k;++i)
	{
		pq.push(v[i]);
	}

	while(i<v.size())
	{
		if(DistanceToEarth(v[i].second)<DistanceToEarth(pq.top().second))
		{
			pq.pop();
			pq.push(v[i]);
		}
		++i;
	}
	while(!pq.empty())
	{
		r.push_back(pq.top().first);
		pq.pop();
	}
	return r;
}

void Prob11_4D()
{
	vector<pair<int,TriDPts> >v;
	
	for (int i=0;i<10;++i)
	{
		pair<int,TriDPts> p(i,TriDPts(i,i,i));
		v.emplace_back(p);
	}
	vector<int> r=Prob11_4(v,3);
	for(int i=0;i<r.size();++i)
		cout<<r[i]<<",";
}

void Prob11_3(vector<int> &v, int k)
{
	priority_queue<int,vector<int>,std::greater<int> > minQ;
	for(int i=0;i<k;++i)
	{
		minQ.push(v[i]);
	}
	for (int i = k; i < v.size(); i++)
	{
		v[i-k]=minQ.top();minQ.pop();
		minQ.push(v[i]);
	}
	for (vector<int>::size_type i = v.size()-k; i < v.size(); i++)
	{
		v[i]=minQ.top();
		minQ.pop();
	}	
}
void Prob11_3D()
{
	vector<int> v;
	v.push_back(0);v.push_back(1);v.push_back(6);v.push_back(2);v.push_back(5);v.push_back(4);
	Prob11_3(v,3);
	PrintVector(v);
}
void Prob11_5(const vector<int> &v)
{
	priority_queue<int> low;
	priority_queue<int,vector<int>,std::greater<int> > high;

	low.push(v[0]);cout<<"0 , median="<<low.top()<<endl;
	for(int i=1;i<v.size();++i)
	{
		if(v[i]>low.top())
			high.push(v[i]);
		else
			low.push(v[i]);
		if(low.size()>high.size())
		{
			cout<<i<<" , median="<<low.top()<<endl;
			if(low.size()>high.size()+1)
			{
				high.push(low.top());
				low.pop();
			}
		}
		else if(high.size()>low.size())
		{
			cout<<i<<" , median="<<high.top()<<endl;
			if(high.size()>low.size()+1)
			{
				low.push(high.top());
				high.pop();
			}
		}		
		else if (high.size()==low.size())
		{
			cout<<i<<" , median="<<0.5f*((float)high.top()+(float)low.top())<<endl;
		}		
	}
}

void Prob11_5D()
{
	vector<int> v;
	v.push_back(5);v.push_back( 15);v.push_back( 1);v.push_back( 3);v.push_back( 2);v.push_back( 8);v.push_back( 7);v.push_back( 9);v.push_back( 10);v.push_back( 6);v.push_back( 11);v.push_back( 4);
	Prob11_5(v);
}
int main(int argc,char **argv)
{
	Prob11_5D();
	getchar();
}

