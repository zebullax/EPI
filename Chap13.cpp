﻿#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>
#include<queue>
using namespace std;

pair<int, int> Prob13_10(const vector<string> &Q, const vector<string> &A) {
	pair<int, int> min_idx(-1, -1);
	int l = -1, r = 0;
	int next_match = 0;

	while (r != A.size()) {
		while (r != A.size() && next_match < Q.size()) {
			bool reduce_left = (Q.size() > 1 && next_match == 1 && A[r] == Q[0]);
			if (A[r] == Q[next_match] ||reduce_left) {
				if (next_match==0 || reduce_left)
					l = r;
				if (!reduce_left)
					next_match++;
			}
			r++;
		}
		if (next_match==Q.size()&&(min_idx.first == -1 || r -1- l < min_idx.second - min_idx.first))
			min_idx = make_pair(l, r - 1);
		next_match = 0;
		l = r;
	}
	return min_idx;
}
void Prob13_10D() {
	
	string declaration("My paramount object in this struggle is to save the Union , and is not either to save or to destroy slavery . If I could save the Union without freeing any slave I would do it , and if I could save it by freeing all the slaves I would do it ; and if I could save it by freeing some and leaving others alone I would also do that");
	string buf; 
	stringstream ss(declaration); 
	vector<string> A,Q; 
	while (ss >> buf)
		A.push_back(buf);	

	Q.push_back("Union"); Q.push_back("save");
	pair<int, int> min = Prob13_10(Q, A);
	assert(min.first == 10 && min.second == 17);
	A.clear(); Q.clear();
	A.push_back("a"); A.push_back("a"); A.push_back("a"); A.push_back("a"); A.push_back("b"); A.push_back("c");
	Q.push_back("a"); Q.push_back("c");
	min = Prob13_10(Q, A);
	assert(min.first == 3 && min.second == 5);
	A.clear(); Q.clear();
	A.push_back("a"); A.push_back("a"); A.push_back("a"); A.push_back("b"); A.push_back("a");  A.push_back("b"); A.push_back("c");
	Q.push_back("a"); Q.push_back("c");
	min = Prob13_10(Q, A);
	assert(min.first == 4 && min.second == 6);
	
	Q = { "0", "2", "9", "4", "6" };
	A = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "2", "4", "6", "10", "10", "10", "3", "2", "1", "0" };
	min = Prob13_10(Q, A);
	assert(min.first == 0 && min.second == 12);
	min = Prob13_10(Q, A);
}
vector<vector<string> > Prob13_1(const vector<string> &d)
{
	unordered_map<string,vector<string> > ana;
	string sortedS;
    vector<vector<string> > ret;
    
	for(int i=0;i<d.size();++i)
	{
		sortedS=d[i];
		sort(sortedS.begin(),sortedS.end());
		ana[sortedS].push_back(d[i]);
	}
    for(unordered_map<string,vector<string> >::iterator it=ana.begin();it!=ana.end();++it)
        ret.push_back(it->second);
    return ret;
}
pair<int, int> Prob13_11(const vector<int> &v) {
	list<pair<int, int>> l; // <nb,idx>
	pair<int, int> idx(0, 0);
	unordered_set<int> dic;
	for (int i = 0; i < v.size(); ++i) {
		unordered_set<int>::iterator it = dic.find(v[i]);
		if (it != dic.end()) {
			while (!l.empty() && l.front().first != v[i]) {
				dic.erase(dic.find(l.front().first));
				l.pop_front();
			}
			dic.erase(it);
			l.pop_front();
			it = dic.find(v[i]);
		}		
		if (it == dic.end()) {
			dic.insert(v[i]);
			l.push_back(make_pair(v[i], i));
			if (l.back().second - l.front().second > idx.second - idx.first)
				idx=make_pair(l.front().second, l.back().second);
		}
	}
	return idx;
}
void Prob13_11D() {
	vector<int>v;
	v.push_back(5); v.push_back(7); v.push_back(5); v.push_back(11); v.push_back(13); v.push_back(2); v.push_back(11); v.push_back(19); v.push_back(2); v.push_back(11);
	pair<int, int> p(Prob13_11(v));
	assert(p.first == 1 && p.second == 5);
}

vector<string> Prob13_13(const string &s, const vector<string> &l) {
	vector<string> results;
	string current_match;
	unordered_set<string> dico(l.begin(),l.end());
	unordered_set<string> already_matched;
	int len = l.front().size();
	int started_matching = -1;
	int i = 0;
	while (i <= s.size() - len) {
		while (i <= s.size() - len && already_matched.size() != l.size()) {
			string cur_substr(s.substr(i, len));
			if (dico.find(cur_substr) != dico.end() && already_matched.find(cur_substr) == already_matched.end()) {
				if (already_matched.size() == 0)
					started_matching = i;
				current_match += cur_substr;
				already_matched.insert(cur_substr);
				i += len;			
			}else {
				if (already_matched.size() != 0)
				{
					i = started_matching + 1;
					already_matched.clear();
					current_match = "";
				}
				else
					i++;
			}
		}
		if (already_matched.size() == l.size()){
			results.push_back(current_match);
			current_match = "";
			already_matched.clear();
		}
	}
	return results;
}
void Prob13_13D() {
	string s("amanaplanacanal");
	vector<string> l;
	l.push_back("can"); l.push_back("apl"); l.push_back("ana");
	vector<string> results(Prob13_13(s, l));
	for (const string& s:results) 
		cout << s << ",";
	
}
void Prob13_1D()
{
	vector<string> d;
    vector<vector<string> > dico;
	d.push_back("babar");d.push_back("babra");d.push_back("bob");d.push_back("raoul");d.push_back("raulo");
	d.push_back("boob");d.push_back("bobo");d.push_back("obbo");
	d.push_back("eric");d.push_back("cire");
	d.push_back("prout");
    dico=Prob13_1(d);
    for(vector<vector<string> >::iterator it=dico.begin();it!=dico.end();++it)
    {
        for(vector<string>::iterator jt=it->begin();jt!=it->end();++jt)
            cout<<*jt<<",";
        cout<<endl;
    }
}
bool Prob13_3(string j, string t)
{
    unordered_map<char,int> hash;
    for_each(j.begin(), j.end(),[&hash](const char &c){ hash[c]++;} );
    for_each(t.begin(), t.end(),[&hash](const char &c){ hash[c]--;} );
    for(unordered_map<char,int>::iterator it=hash.begin();it!=hash.end();++it)
    {
        if (it->second <0)
            return false;
    }
    return true;
    
}
void Prob13_3D()
{
    string t="Thank you very much for your prompt reply!Let me get back to you next week on more details.";
    string j_ok="Thank you kkjsdflksjdfkljdflkjdfvery much for your prompt rep,,f,f,f,f,,,f,,,,,,ssfsdfjksdfly!Let me get back to you next wesdfk:sdf:;lsfek on more details.";
    string j_nok="Thank you very much for your prompt reply!Let me get back to you";
    if(Prob13_3(j_ok,t))
        cout<<"Ok"<<endl;
    else
        cout<<"Not Ok"<<endl;
    if(Prob13_3(j_nok,t))
        cout<<"Ok"<<endl;
    else
        cout<<"Not Ok"<<endl;
}

int GetMedian(const vector<int> &v)
{
	priority_queue<int> low;
	priority_queue<int,vector<int>,std::greater<int> > high;
    int median=-1;

	low.push(v[0]);cout<<"0 , median="<<low.top()<<endl;
	for(int i=1;i<v.size();++i)
	{
		if(v[i]>low.top())
			high.push(v[i]);
		else
			low.push(v[i]);
		if(low.size()>high.size())
		{
			median=low.top();
			if(low.size()>high.size()+1)
			{
				high.push(low.top());
				low.pop();
			}
		}
		else if(high.size()>low.size())
		{
			median=high.top();
			if(high.size()>low.size()+1)
			{
				low.push(high.top());
				high.pop();
			}
		}		
		else if (high.size()==low.size())
		{
			median=0.5f*((float)high.top()+(float)low.top());
		}		
	}
	return median;
}
class ISBNCache{
private:	
	unordered_map<string,pair<string,int> >hash;//isbn -> (title,tstamp)
	map<string,string> cat;

	int maxCapacity;
	int currentStamp;
	
	void EvictLRU()
	{
		cout<<"Log: EvictLRU\n";
		int medianTS=0;
		vector<int> v;
		for(unordered_map<string,pair<string,int> >::iterator it=hash.begin();it!=hash.end();++it)
		{
			v.push_back(it->second.second);
		}
		medianTS=GetMedian(v);
		for(unordered_map<string,pair<string,int> >::iterator it=hash.begin();it!=hash.end();)
		{
			if(it->second.second<medianTS)
				it=hash.erase(it);
			else
				++it;
		}		
	}
	void InsertIntoCache(string isbn,string title)
	{
		hash.emplace(isbn,pair<string,int>(title,currentStamp++));
		if(hash.size()==2*maxCapacity)
		{
			cout<<"log: Max capacity reached\n";
			EvictLRU();
		}
	}
public:
	ISBNCache(int max_,map<string,string> cat_):maxCapacity(max_),currentStamp(0),cat(cat_){}
	string GetTitle(string ISBN)
	{
		if(hash.find(ISBN)==hash.end())
		{
			cout<<"log: Insert into cache\n";
			InsertIntoCache(ISBN,cat[ISBN]);
		}
		cout<<"log: Get from cache\n";
		return (hash[ISBN].first);
	}
};

bool IsPalindromable(const string &s)
{
	unordered_map<char,int> count;
	bool oddSize=(s.size()%2!=0?true:false);
	int oddOccur=0;

	for(int i=0;i<s.size();++i)
	{
		count[s[i]]++;
	}

	for(unordered_map<char,int>::iterator it=count.begin();it!=count.end();++it)
	{
		if(it->second%2!=0)		
			oddOccur++;
	}

	if((!oddSize&&oddOccur==0) || (oddSize && oddOccur==1))
		return true;
	else
		return false;

}

void Prob13_2D()
{
	cout<<IsPalindromable("edified")<<endl;
	cout<<IsPalindromable("boooob")<<endl;
	cout<<IsPalindromable("raoul")<<endl;
}
void Prob13_4D()
{
	map<string,string> cat;
	cat.emplace("978-1-891830-75-4","Per¢ by Tony Consiglio, $12.95");cat.emplace("978-1-60309-050-6"," The 120 Days of Simon, $14.95");cat.emplace("978-1-60309-266-1"," A Matter of Life, $14.95");
	cat.emplace("978-0-9577896-6-1"," Alec (Vol 4): After the Snooter by Eddie Campbell, $14.95");cat.emplace("978-1-60309-025-4"," Alec: The Years Have Pants, $35.00");cat.emplace("978-1-60309-047-6"," Alec: The Years Have Pants -- HARDCOVER, $49.95");
	cat.emplace("978-1-60309-322-4","rs (16+) Alone Forever, $9.95");cat.emplace("978-1-891830-85-3"," American Elf (Book 2), $19.95");cat.emplace("978-1-60309-016-2"," American Elf (Book 3), $19.95");
	cat.emplace("978-1-60309-265-4","r (16+) American Elf (Book 4), $24.95");cat.emplace("978-1-60309-2395M","American Elf 1999 by James Kochalka, TBD");cat.emplace("978-1-60309-077-3"," Any Empire, $19.95");
	cat.emplace("978-1-60309-069-8","(13+) August Moon, $14.95");cat.emplace("978-1-60309-042-1","(18+) Ax (Vol 1): A Collection of Alternative Manga, $29.95");cat.emplace("978-1-891830-10-5"," Banks/Eubanks by Tom Hart, $9.95");
	cat.emplace("978-1-891830-37-2","(13+) The Barefoot Serpent (softcover) by Scott Morse, $14.95");cat.emplace("978-1-60309-029-2","(13+) BB Wolf and the 3 LP's, $12.95");cat.emplace("978-1-891830-40-2"," Beach Safari by Mawil, $9.95");
	cat.emplace("978-1-891830-16-7","(13+) Big Clay Pot by Scott Mills, $12.95");cat.emplace("978-1-891830-43-3"," Blankets, $29.95");cat.emplace("978-1-891830-43-3"," Blankets (Original Softcover) by Craig Thompson, $29.95");
	cat.emplace("978-1-60309-096-4"," Blankets -- HARDCOVER, $39.95");cat.emplace("978-1-60309-153-4"," Blue, $14.95");cat.emplace("978-1-60309-063-6","rs (16+) The Bojeffries Saga, $14.95");
	cat.emplace("978-1-891830-46-4"," Bop!: More Box Office Poison by Alex Robinson, TBD");cat.emplace("978-1-891830-19-8"," Box Office Poison by Alex Robinson, $29.95");cat.emplace("978-1-891830-13-6"," Bughouse (Vol 1) by Steve Lafler, $14.95");
	cat.emplace("978-1-891830-27-3"," Bughouse (Vol 2): Baja by Steve Lafler, $9.95");cat.emplace("978-1-891830-67-9"," Bughouse (Vol 3): Scalawag by Steve Lafler, $12.95");cat.emplace("978-0-9858751-3-8","(13+) Burning Building Comix, $19.95");
	cat.emplace("978-1-891830-60-0"," Carnet de Voyage by Craig Thompson (GN), $14.95");cat.emplace("978-1-60309-066-7","(18+) Chester 5000, $14.95");cat.emplace("978-1-891830-21-1"," Cicada: A Broken Fender Book by Josué Menjivar, $12.95");
	cat.emplace("978-1-891830-80-8","(13+) Coffee and Donuts by Max Estes, $10.00");cat.emplace("978-1-60309-100-8"," Crater XV, $19.95");cat.emplace("978-1-891830-81-5","(13+) Cry Yourself to Sleep by Jeremy Tinder, TBD");
	cat.emplace("978-1-891830-07-5"," Daydream Lullabies (Billy Dogma) by Dean Haspiel, $7.95");
	
	ISBNCache cache(5,cat);
	cout<<cache.GetTitle("978-1-891830-75-4");cout<<cache.GetTitle("978-1-891830-75-42");cout<<cache.GetTitle("978-1-60309-050-6");
	cout<<cache.GetTitle("978-1-60309-266-1");cout<<cache.GetTitle("978-1-60309-025-4");cout<<cache.GetTitle("978-1-60309-047-62");
	cout<<cache.GetTitle("978-1-60309-322-4");cout<<cache.GetTitle("978-1-891830-85-3");cout<<cache.GetTitle("978-1-60309-016-2");
	cout<<cache.GetTitle("978-1-60309-265-4");cout<<cache.GetTitle("978-1-60309-2395M");cout<<cache.GetTitle("978-1-60309-077-3");
	cout<<cache.GetTitle("978-1-60309-069-8");cout<<cache.GetTitle("978-1-60309-042-1");cout<<cache.GetTitle("978-1-891830-10-5");
	cout<<cache.GetTitle("978-1-891830-37-2");cout<<cache.GetTitle("978-1-60309-029-2");cout<<cache.GetTitle("978-1-891830-40-2");
	cout<<cache.GetTitle("978-1-891830-16-7");cout<<cache.GetTitle("978-1-891830-43-3");cout<<cache.GetTitle("978-1-891830-43-3");
	cout<<cache.GetTitle("978-1-60309-096-4");cout<<cache.GetTitle("978-1-60309-153-4");cout<<cache.GetTitle("978-1-60309-063-6");
	cout<<cache.GetTitle("978-1-891830-46-4");cout<<cache.GetTitle("978-1-891830-19-8");cout<<cache.GetTitle("978-1-891830-13-6");
	cout<<cache.GetTitle("978-1-891830-27-3");cout<<cache.GetTitle("978-1-891830-67-9");cout<<cache.GetTitle("978-1-891830-60-0");
	cout<<cache.GetTitle("978-1-60309-066-7");cout<<cache.GetTitle("978-1-891830-21-1");cout<<cache.GetTitle("978-1-891830-80-8");
	cout<<cache.GetTitle("978-1-60309-100-8");cout<<cache.GetTitle("978-1-891830-81-5");cout<<cache.GetTitle("978-1-891830-07-5");

}

void Prob13_8(const vector<string> &v,string *near,int *startdIdx, int *endIdx)
{
	unordered_map<string,int> hash;
	int minDist=v.size()+1,lastIdx=0;
	string nearest;
	string curr;

	for(vector<string>::size_type i=0;i<v.size();++i)
	{
		curr=v[i];
		if(hash.find(curr)==hash.end())
		{
			hash.emplace(curr,i);
		}
		else
		{
			if(minDist>(i-hash[curr]))
			{
				lastIdx=hash[curr];
				minDist=i-lastIdx;
				nearest=curr;
				hash[curr]=i;
			}
		}				
	}
	*near=nearest;
	*startdIdx=lastIdx;
	*endIdx=hash[nearest];
}
void Prob13_8D()
{
	vector<string> dico;
	dico.push_back("All");dico.push_back("work");dico.push_back("and");dico.push_back("no");dico.push_back("play");dico.push_back("makes");
	dico.push_back("for");dico.push_back("no");dico.push_back("work");dico.push_back("no");dico.push_back("fun");dico.push_back("and");
	dico.push_back("no");dico.push_back("results");
	string nearest;
	int start,end;
	Prob13_8(dico,&nearest,&start,&end);
	cout<<nearest<<" : "<<start<<" - "<<end<<endl;
}
bool DoesCover(vector<string> &t,const vector<string> &s, int l,int r)
{
	vector<string>::iterator it;

	for (int i=0;i<s.size();++i)
	{
		it=find(t.begin()+l,t.begin()+r+1,s[i]);
		if (it==t.begin()+r+1)
			return false;
	}
	return true;
}
pair<int,int> Prob13_9(vector<string> &a,const vector<string> &q)
{
    pair<int,int> res;
    unordered_set<string> dico(q.begin(),q.end());
    unordered_map<string,int> count;
    
    int l=0,r=0;
    int minCover=(int)a.size()+1;
    
    while(r<a.size())
    {
        while( (r<a.size()) && (count.size()!=dico.size()) )
        {
            if(dico.find(a[r])!=dico.end())
                count[a[r]]++;
            r++;
        }
        
        if(count.size()==dico.size())
        {
            if(r-l-1<minCover)
            {
                minCover=r-l-1;
                res=make_pair(l,r-1);
            }
        }
        
        while( l<r && (count.size()==dico.size()) )
        {
            if(dico.find(a[l])!=dico.end())
                count[a[l]]--;
            if(count[a[l]]==0)
            {
                if(r-l-1<minCover)
                {
                    minCover=r-l-1;
                    res=make_pair(l,r-1);
                }
                count.erase(a[l]);
            }
            l++;
        }
    }
    return res;
}
void Prob13_9D()
{
	vector<string> a;
	a.push_back("save"); a.push_back("me");  a.push_back("or"); a.push_back("you");  a.push_back("or");  a.push_back("save");  a.push_back("the");  a.push_back("union"); 
	a.push_back("or");  a.push_back("the");  a.push_back("union");  a.push_back("will");  a.push_back("not");  a.push_back("want");  a.push_back("to");  a.push_back("save"); 
	a.push_back("you");  a.push_back("nor");  a.push_back("the");  a.push_back("union");
	vector<string> q;
	q.push_back("save");q.push_back("the");q.push_back("union");
	pair<int,int> res=Prob13_9(a,q);
    cout<<res.first<<" , "<<res.second<<endl;
}
int longest_range_len(int a, const unordered_set<int> &S,unordered_map<int,int>*L)
{
	if (S.find(a)==S.end())
		return 0;
	if(L->find(a)==L->end())
		(*L)[a]=longest_range_len(a-1,S,L)+1;
	return (*L)[a];
}
pair<int,int> Prob13_12(const vector<int> &A)
{
	unordered_set<int> s;
	for(int i=0;i<A.size();++i)	
		s.insert(A[i]);
	int max_len=0;
	pair<int,int> max_range(0,-1);
	unordered_map<int,int> L;
	for(int i=0;i<A.size();++i)	
	{
		int len=longest_range_len(A[i],s,&L);
		if (len>max_len)
		{
			max_len=len;
			max_range=make_pair(A[i]-len+1,A[i]);
		}
	}
	return max_range;
}
void Prob13_12D()
{
	vector<int> s;
	s.push_back(3);s.push_back(-2);s.push_back(7);s.push_back(9);s.push_back(8);s.push_back(1);s.push_back(2);s.push_back(0);
	pair<int,int> res=Prob13_12(s);
	cout<<res.first<<" "<<res.second<<endl;
}

struct compareFreqQueries
{
	bool operator()(const pair<string, int> &left, const pair<string, int> &right){
		return (left.second > right.second);
	}
};

vector<string> Prob13_6(const vector<string> &v, int k) {
	priority_queue<pair<string, int>, vector<pair<string, int> >, compareFreqQueries > min_q;
	unordered_map<string, int> h_tbl;
	for (vector<string>::const_iterator it = v.begin(); it != v.end(); ++it) {
		h_tbl[*it]++;
	}
	for (unordered_map<string, int>::iterator it = h_tbl.begin(); it != h_tbl.end(); ++it) {
		pair<string, int> tmp(it->first, it->second);
		if (min_q.size() < k)
			min_q.push(tmp);
		else if (it->second > min_q.top().second) {
			min_q.pop();
			min_q.push(tmp);
		}
	}
	vector<string> result;
	while (!min_q.empty()) {
		result.push_back(min_q.top().first);
		min_q.pop();
	}
	return result;
}
void Prob13_6D() {
	vector<string> v;
	v.push_back("mohito"); v.push_back("mohito"); v.push_back("mohito"); v.push_back("mohito"); v.push_back("mohito");
	v.push_back("cuba libre"); v.push_back("cuba libre"); v.push_back("cuba libre"); v.push_back("cuba libre");
	v.push_back("rum"); v.push_back("rum"); v.push_back("rum");
	v.push_back("gin"); v.push_back("beer"); v.push_back("calori mate");
	vector<string> result = Prob13_6(v, 1);
	for (const string &s : result) {
		cout << s << endl;
	}
}

bool TestCollatzConjectureHelper(unordered_set<int> &inspected, size_t n) {
	
	while (inspected.find(n) == inspected.end()) {
		inspected.insert(n);
		if (n % 2)
			n = n * 3 + 1;
		else
			n /= 2;
		if (n == 1)
			return true;
	}
	return false;
}

bool TestCollatzConjecture(const int n) {
	unordered_set<int> confirmed, inspected;

	for (size_t i = 1; i < n;++i) {
		if (confirmed.find(i) == confirmed.end()){
			bool pass = TestCollatzConjectureHelper(inspected, i);
			if (!pass)
				return false;
			confirmed.insert(inspected.begin(), inspected.end());
			inspected.clear();
		}
	}
	return true;
}
void Prob13_16D() {
	int n = 50;
	assert(TestCollatzConjecture(100));
}
int main(int argc, char **argv)
{
	Prob13_16D();
    getchar();
}