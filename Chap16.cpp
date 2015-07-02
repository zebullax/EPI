#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <cmath>
#include <functional>
using namespace std;

void Hanoi(vector<stack<int> >&v,int s,int d,int t,int n){
    //trivial case : Moving a single puck
    if(n==1){
        v[d].push(v[s].top());
        v[s].pop();
    }
    else{
        // move n-1 from s->t
        // move 1 from s->d
        // move back n-1 from t to d
        Hanoi(v,s,t,d,n-1);
        v[d].push(v[s].top());
        v[s].pop();
        Hanoi(v,t,d,s,n-1);
    }
}
void Prob01_D(){
    vector<stack<int> >v(3);
    v[0].push(5);v[0].push(4);v[0].push(3);v[0].push(2);v[0].push(1);
    Hanoi(v, 0, 1, 2,5);
    while(!v[1].empty()){
        cout<<v[1].top()<<endl;
        v[1].pop();
    }
}

bool NextPut(vector<vector<int> > &b,int &r, int &c){
	for(int i=0;i<b.size();++i){
		for(int j=0;j<b.size();++j){
			if(b[i][j]==0){
				r=i;
				c=j;
				return true;
			}
		}
	}
	return false;
}
void UpdateBoard(vector<vector<int> > &b,int r, int c,int k){
	for(int i=0;i<b.size();++i){
		b[r][i] = k;
		b[i][c] = k;
		if(r-i>=0){
			if(c-i>=0){
				b[r - i][c - i] = k;
			}
			if(c+i<b.size()){
				b[r - i][c + i] = k;
			}			
		}
		if (r + i<b.size()){
			if(c-i>=0){
				b[r + i][c - i] = k;
			}
			if (c + i<b.size()){
				b[r + i][c + i] = k;
			}			
		}
	}

}
void DisplayConfig(vector<pair<int, int> >b)
{
	pair<int, int> q;
	vector<vector<int> >r(b.size(),vector<int>(b.size(),0));

	for (int i = 0; i < b.size(); ++i){
		r[b[i].first][b[i].second] = 1;
	}

	for(int i=0;i<b.size();++i){
		for (int j = 0; j < b.size(); ++j){
			cout << (r[i][j] == 1 ? "Q" : ".");
		}
		cout << endl;		
	}
	cout<<endl;
}
void PutQueens(vector<vector<int> >b, vector<pair<int,int> >config, int n){
	if(n==0 ){
        DisplayConfig(config);
		return;
	}
	else{
        for(int i=0;i<b.size();++i){
            for(int j=0;j<b.size();++j){
                if(b[i][j]==0){
                    vector<vector<int> >before=b;
                    UpdateBoard(b, i, j, 2);
                    b[i][j]=1;
                    config.push_back(make_pair(i, j));
                    PutQueens(b, config, n - 1);
                    config.pop_back();
                    b=before;
                }
            }
        }
    }
}
void Prob16_3D(){
	int n=4;
	vector<vector<int> >board(n,vector<int>(n,0)); //0:empty, 1:Q 2:taboo	
	vector<pair<int,int> >config;
	PutQueens(board,config,n);
}

void PrintPermut(stack<int> s){
	static int i = 1;
	cout<<i++<<":{";
	while(!s.empty()){
		cout<<s.top();s.pop();
		if(!s.empty())
			cout<<",";
	}
	cout<<"}\n";
}
void PermutN(queue<int> v,stack<int> s){
	if (v.empty()){
		PrintPermut(s);
		return;
	}
	for(int i=0;i<v.size();++i){
		int t = v.front();
		s.push(t);
		v.pop();
		PermutN(v,s);
		s.pop();
		v.push(t);
	}
}
void Prob16_4D(){
	queue<int> v;
	stack<int> s;
	v.push(7); v.push(5); v.push(3); v.push(2); 
	PermutN(v,s);
}

void Prob16_5(const vector<char> &v)
{
	unsigned int mask = 1;
	cout << "{},";
	while (mask < (1<< v.size()) ){
		cout << "{";
        int x=mask;
		while(x){
            cout<<log2(x&~(x-1))<<",";
            x=x&x-1;
			/*if ((1 << j & mask) == (1 << j))
				cout << v[j] << ",";
             */
		}
		cout << "},";
		++mask;
	}
}
void Prob16_5D(){
	vector<char> v; v.push_back('a'); v.push_back('b'); v.push_back('c');
	Prob16_5(v);
}

int SplitAndMergerAndCount(vector<int> &vIn, vector<int> vScratch,int l, int h){
	if (l+1>=h)
		return 0;

	int m = l + ((h - l) >> 1);
	int LowCount = SplitAndMergerAndCount(vIn,vScratch, l, m);
	int HighCount = SplitAndMergerAndCount(vIn,vScratch,m,h);
	int inversionCount = LowCount + HighCount;
	int writeIdx = l, leftIdx = l, rightIdx = m;
	while(leftIdx<m && rightIdx<h){
		if (vIn[leftIdx] < vIn[rightIdx]){
			vScratch[writeIdx++] = vIn[leftIdx++];
		}
		else{
			inversionCount += (m - leftIdx);
			vScratch[writeIdx++] = vIn[rightIdx++];
		}
	}
	while (leftIdx < m){
		vScratch[writeIdx++] = vIn[leftIdx++];
	}
	while (rightIdx < h){
		inversionCount += (m - leftIdx);
		vScratch[writeIdx++] = vIn[rightIdx++];
	}
	for (int i = l; i < h; ++i)
		vIn[i] = vScratch[i];
	return inversionCount;
}
int SortAndCountInversion(vector<int> v){
	vector<int> scratchV(v.size());
	return SplitAndMergerAndCount(v, scratchV, 0, v.size());
}
void Prob16_13D(){
	vector<int> v; 
	v.push_back(2); v.push_back(4); v.push_back(1); v.push_back(3); v.push_back(5);// v.push_back(2); v.push_back(8); v.push_back(18);
	int inversionCount = SortAndCountInversion(v);
	cout << "Nb of inversions:" << inversionCount << endl;
}

struct Building{
	int left_coord_i_;
	int right_coord_i_;
	int height_i_;
	Building(int lc_i, int rc_i, int h_i) :left_coord_i_(lc_i), right_coord_i_(rc_i), height_i_(h_i){}
};
struct compareBuildings
{
	bool operator()(const Building &l, const Building &r)
	{
		return l.height_i_ < r.height_i_;
	}
};
void Prob16_15(const vector<Building> &v,int max_right_i)
{
	priority_queue<Building, vector<Building>,compareBuildings > max_queue(v.begin(),v.end());
	vector<int> skyline(max_right_i,0);

	while (!max_queue.empty())
	{
		Building next_building = max_queue.top(); max_queue.pop();
		for (int IDX = next_building.left_coord_i_; IDX < next_building.right_coord_i_; ++IDX)
		{
			skyline[IDX] = max(skyline[IDX], next_building.height_i_);
		}
	}
	for (int i = 0; i < max_right_i; ++i)
	{
		(i == 0 || skyline[i] != skyline[i - 1]) ? cout << "|" << skyline[i] : cout << skyline[i];
		
	}
}
void Prob16_15D()
{
	vector<Building> buildings;
	buildings.emplace_back(0, 3, 1); buildings.emplace_back(1,6,3); buildings.emplace_back(4,8,4); buildings.emplace_back(5,9,2);
	buildings.emplace_back(7,14,3); buildings.emplace_back(10,12,6); buildings.emplace_back(11,17,1); buildings.emplace_back(13,16,2);
	Prob16_15(buildings,17);
}

int main(int argc, char**argv){

	Prob16_15D();
	getchar();
	return 0;
}