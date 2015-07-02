#include <vector>
#include <map>
#include <unordered_set>
#include <iostream>
#include <string>
#include <utility>
#include "GraphEPI.h"

using namespace std;

void PrintPath(vector<int> parent, int src,int dest)
{
	stack<int> path;
	int currentVertex = dest;
	while (currentVertex != unweighted_graph::NIL && currentVertex!=parent[src])
	{
		path.push(currentVertex);
		currentVertex = parent[currentVertex];
	}
	while (!path.empty())
	{
		cout << path.top() << "->";
		path.pop();
	}
}

void Prob19_1D()
{
	//5*5 maze
	unweighted_graph g(25);
	g.addBothEdges(0, 1); g.addBothEdges(0, 5); g.addBothEdges(1, 2); g.addBothEdges(2, 3); g.addBothEdges(3, 4);
	g.addBothEdges(3, 8); g.addBothEdges(5, 10); g.addBothEdges(10, 11); g.addBothEdges(8, 13); g.addBothEdges(13,14);
	g.addBothEdges(10, 15); g.addBothEdges(11, 16); g.addBothEdges(15, 16); g.addBothEdges(14, 19); g.addBothEdges(15,20);
	g.addBothEdges(19,24);

	vector<int> parent(25);
	vector<vector<int> > timestamps(25, vector<int>(2, 0));
	g.DFS_Traversal(parent, timestamps);

	PrintPath(parent, 0, 24);
}

void Prob19_9D()
{
	int NoVertices = 8;
	vector<int> durations_vector(NoVertices);
	vector<vector<bool> >predecessors_vector(NoVertices, vector<bool>(NoVertices, false));
	vector<float> distances;
	vector<vector<float> > all_distances;
	vector<int> parents;
	vector<vector<int> > all_parents;

	durations_vector[0] = 2; durations_vector[1] = 8; durations_vector[2] = 1;
	durations_vector[3] = 3; durations_vector[4] = 8; durations_vector[5] = 1; durations_vector[7] = 1;
	predecessors_vector[0][1] = true; predecessors_vector[1][3] = true; predecessors_vector[2][3] = true; predecessors_vector[3][4] = true;
	predecessors_vector[3][5] = true; predecessors_vector[4][5] = true;
	predecessors_vector[0][2] = true;
	weighted_graph g(NoVertices);
	for (int i = 0; i < NoVertices; ++i)
	{
		for (int j = 0; j < NoVertices; ++j)
		{
			if (predecessors_vector[i][j])
				g.addSingleEdge(i, j, durations_vector[i]);
		}
	}

	AllPairShortestPaths(g, &all_distances, &all_parents);

	for (int i = 0; i < g.GetVerticesNB(); ++i)
	{
		cout << i << ":";
		for (int j = 0; j < g.GetVerticesNB(); ++j)
		{
			if (all_distances[i][j] != FLT_MAX)
				cout << all_distances[i][j]<<",";
			else
				cout << "X,";
		}
		cout << endl;
	}
	

}

bool IsValid(string l, string r)
{
	bool mismatch = false;
	if (l.size() != r.size())
		return false;
	for (int i = 0; i < l.size(); ++i)
	{
		if (l[i] != r[i])
		{
			if (!mismatch)
				mismatch = true;
			else
				return false;
		}
	}
	return true;
}

list<string> GetNeighbours(string src, unordered_set<string> D)
{
	list<string> result;
	for (string s: D)
	{
		if (IsValid(src, s))
			result.push_back(s);
	}
	return result;
}

bool StringProduction(string src, string dst, unordered_set<string> dico, list<string>* prod_seq)
{
	if (dico.find(src) == dico.end() || dico.find(dst) == dico.end())
		return false;

	map<string, string> parents;
	unordered_set<string> processed;
	queue<string> discovered;
	
	//init the bfs
	discovered.push(src); 
	parents[src] = "";
	while (!discovered.empty())
	{
		string current = discovered.front();discovered.pop();
		processed.insert(current);
		list<string> neighbours = GetNeighbours(current, dico);
		for (string s : neighbours)
		{
			if (processed.find(s) == processed.end())
			{
				parents[s] = current;
				discovered.push(s);
			}
		}		
	}
	if (processed.find(dst) == processed.end())
		return false;
	
	while (dst!="")
	{
		prod_seq->push_front(dst);
		dst = parents[dst];
	}
	return true;
}

void Prob19_5D()
{
	string src = "tart";
	string dst = "fall";
	unordered_set<string> dico;
	dico.insert("tart"); dico.insert("fall"); dico.insert("tool"); dico.insert("tall"); dico.insert("tarp");
	dico.insert("fart"); dico.insert("fall"); dico.insert("faller"); dico.insert("farl");
	list<string> prod_sequence;
	if (StringProduction(src,dst,dico,&prod_sequence))
	{
		for (list<string>::iterator it = prod_sequence.begin(); it != prod_sequence.end();++it)
			std::cout << *it << " -> ";
	}
}

struct ColoredSquare
{
	int x, y;
	bool is_black;
	ColoredSquare(int x_, int y_, bool is_black_) : x( x_), y( y_), is_black(is_black_){}
	ColoredSquare() :ColoredSquare(0, 0, false){}
};

list<ColoredSquare> GetSameColorNeighbours(const vector<vector<ColoredSquare> > &board, ColoredSquare src)
{
	list<ColoredSquare> result;
	int x = src.x;
	int y = src.y;
	bool is_black = src.is_black;

	if (x > 0)
		if (board[y][x - 1].is_black == is_black)
			result.emplace_front(ColoredSquare(x - 1, y, is_black));
	if (y > 0)
		if (board[y - 1][x].is_black == is_black)
			result.emplace_front(ColoredSquare(x, y - 1, is_black));
	if (x < board[0].size()-1)
		if (board[y][x + 1].is_black == is_black)
			result.emplace_front(ColoredSquare(x + 1, y, is_black));
	if (y < board.size() - 1)
		if (board[y + 1][x].is_black == is_black)
			result.emplace_front(ColoredSquare(x, y + 1, is_black));
	return result;
}

void FlipRegionColor(vector<vector<ColoredSquare> > *board, int x,int y)
{
	stack<ColoredSquare> s;
	vector<vector<bool> > discovered( (*board).size(),vector<bool>((*board)[0].size(),false) );
	ColoredSquare src = (*board)[y][x];
	s.push(src);
	while (!s.empty())
	{
		ColoredSquare cur_square = s.top();
		s.pop();
		discovered[cur_square.x][cur_square.y] = true;;
		list<ColoredSquare> same_colored_neighbours = GetSameColorNeighbours(*board, cur_square);
		for (ColoredSquare neighbour:same_colored_neighbours)
		{
			if (!discovered[neighbour.x][neighbour.y])
			{
				s.push(neighbour);
			}
		}
		(*board)[cur_square.y][cur_square.x].is_black = !cur_square.is_black;
	}
}
void Prob19_2D()
{
	vector<vector<ColoredSquare> > board(5, vector<ColoredSquare>(5));
	for (int i = 0; i < 5;++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			board[i][j].x = j;
			board[i][j].y = i;
			board[i][j].is_black = false;
		}
	}
	board[0][3].is_black = board[0][4].is_black = true;
	board[1][1].is_black = board[1][2].is_black = board[1][4].is_black = true;
	board[2][0].is_black = board[2][2].is_black = true;
	board[3][1].is_black = board[3][4].is_black = true;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			cout << board[i][j].is_black;
		}
		cout << endl;
	}
	cout << endl;
	FlipRegionColor(&board,1,2);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			cout << board[i][j].is_black;
		}
		cout << endl;
	}
	cout << endl;
	FlipRegionColor(&board, 1, 2);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			cout << board[i][j].is_black;
		}
		cout << endl;
	}
}
int main()
{
	Prob19_2D();
	getchar();
	return 0;
}