#include <vector>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include<queue>
using namespace std;

struct calendarEvent{
	unsigned int begin;
	unsigned int end;
	calendarEvent(unsigned int b,unsigned int e):begin(b),end(e){}
	bool operator<(const calendarEvent& that){return (this->begin<that.begin);}
};


int Prob14_5(const vector<calendarEvent> &v)
{
	vector<calendarEvent> cal=v;
	sort(cal.begin(),cal.end());

	unsigned int maxHeight=1;
	for(unsigned int i=0;i<cal.size();++i)
	{
		unsigned int currHeight=0;
		for(unsigned int j=i+1;j<cal.size() && cal[j].begin<cal[i].end;++j,++currHeight);
		maxHeight=max(maxHeight,currHeight);
	}
	return maxHeight;
}
void Prob14_5D()
{
	vector<calendarEvent> events;
	events.push_back(calendarEvent(6,10));events.push_back(calendarEvent(8,9));events.push_back(calendarEvent(9,17));
	events.push_back(calendarEvent(1,5));events.push_back(calendarEvent(2,7));events.push_back(calendarEvent(4,5));
	events.push_back(calendarEvent(11,13));events.push_back(calendarEvent(12,15));events.push_back(calendarEvent(14,15));
	
	cout<<Prob14_5(events)<<endl;
}
vector<pair<int,int> > Prob14_7(const vector<calendarEvent> &v)
{
	vector<calendarEvent> cal=v;
	sort(cal.begin(),cal.end());

	unsigned int start=0,maxEnding=0;
	vector<pair<int,int> > unions;
	int i=0,j=0;
	while(i<cal.size())
	{
		start=cal[i].begin;
		maxEnding=cal[i].end;
		j=i+1;
		while(j<cal.size()&&cal[j].begin<=maxEnding)
		{
			maxEnding=max(maxEnding,cal[j].end);
			++j;
		}
		unions.push_back(make_pair(start,maxEnding));
		i=j;
	}
	return unions;
}
void Prob14_7D()
{
	vector<calendarEvent> events;
	events.push_back(calendarEvent(0,3));events.push_back(calendarEvent(2,4));events.push_back(calendarEvent(3,4));events.push_back(calendarEvent(1,1));
	events.push_back(calendarEvent(5,7));events.push_back(calendarEvent(7,8));events.push_back(calendarEvent(8,11));events.push_back(calendarEvent(9,11));
	events.push_back(calendarEvent(12,14));events.push_back(calendarEvent(12,16));events.push_back(calendarEvent(13,13));events.push_back(calendarEvent(16,17));

	vector<pair<int,int> > unions=Prob14_7(events);
	for(int i=0;i<unions.size();++i)
	{
		cout<<"["<<unions[i].first<<","<<unions[i].second<<"]"<<endl;
	}
}

template<class T>
struct listNode{
	T val;
	listNode<T> *next;
	listNode(T elem_):val(elem_),next(NULL){}
};
template<class T>
listNode<T>* makeNode(T elem)
{
	listNode<T>* n=new listNode<T>(elem);
	return n;
}

template<class T>
void SplitListAroundMiddleElement(listNode<T> *h, listNode<T> **l,listNode<T> **r)
{
	listNode<T> *slow=h,*fast=h;
	listNode<T> *prev=slow;
	while(fast && fast->next)
	{
		prev=slow;
		slow=slow->next;
		fast=fast->next->next;
	}
	prev->next=NULL;
	*r=slow;
	*l=h;
}

template<class T>
listNode<T>* MergeSortLists(listNode<T>* l, listNode<T>* r)
{
	listNode<T>* dummy=makeNode(0);
	listNode<T>* ret=dummy;	
	while(l&&r)
	{
		if(l->val<r->val)
		{
			listNode<T>* tmp=l->next;
			dummy->next=l;
			dummy->next->next=NULL;
			l=tmp;
		}
		else
		{
			listNode<T>* tmp=r->next;
			dummy->next=r;
			dummy->next->next=NULL;
			r=tmp;
		}
		dummy=dummy->next;
	}
	if (l)
		dummy->next=l;
	if (r)
		dummy->next=r;
	return ret->next;
}

template<class T>
listNode<T>* TopDownSplit(listNode<T>* h)
{
	if (!h || !(h->next))
		return h;
	listNode<T> *left,*right;
	SplitListAroundMiddleElement<T>(h,&left,&right);
	left=TopDownSplit(left);
	right=TopDownSplit(right);
	left=TopDownSplit(left);
	right=TopDownSplit(right);
	return MergeSortLists(left,right);
}

void Prob14_12D()
{
	listNode<int> *h=makeNode(3);
	h->next=makeNode(1);h->next->next=makeNode(2);h->next->next->next=makeNode(2);h->next->next->next->next=makeNode(2);h->next->next->next->next->next=makeNode(0);
	listNode<int> *sortedList=TopDownSplit(h);
	while(sortedList)
	{
		cout<<sortedList->val<<",";
		sortedList=sortedList->next;
	}
}

struct Interval
{
	unsigned int left, right;
	Interval(int l, int r) :left(l), right(r){}
	bool operator<(const Interval &that){return this->left < that.left;}
};
bool Intersect(Interval &a, const Interval &b) {
	if (min(a.right, b.right) < max(a.left, b.left))
		return false; //empty intersection
	a.left = max(a.left, b.left);
	a.right= min(a.right, b.right);
	return true;
}
vector<int> Prob14_8(vector<Interval> v) {
	vector<int> result;
	sort(v.begin(), v.end());
	int i = 0;
	while (i != v.size()) {
		Interval in = v[i];
		while (i != v.size() && Intersect(in, v[i]))
			++i;
		result.push_back(in.left);
	}
	return result;
}

void Prob14_8D() {
	vector<Interval> tasks;
	tasks.push_back(Interval(0, 3)); tasks.push_back(Interval(2, 4)); 
	tasks.push_back(Interval(3, 4)); tasks.push_back(Interval(1, 1));
	tasks.push_back(Interval(5, 7)); tasks.push_back(Interval(7, 8)); 
	tasks.push_back(Interval(8, 11)); tasks.push_back(Interval(9, 11));
	tasks.push_back(Interval(12, 14)); tasks.push_back(Interval(12, 16)); 
	tasks.push_back(Interval(13, 13)); tasks.push_back(Interval(16, 17));
	vector<int> results(Prob14_8(tasks));
	for (const int &v : results)
		cout << v << " ";
}
int main(int argc,char**argv)
{
	Prob14_8D();
	getchar();

	return 0;
}