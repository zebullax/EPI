#include <list>
#include <vector>
#include <tuple>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

struct unweighted_graph
{
private:
	int V;    // No. of vertices
	list<int> *adj;    // Pointer to an array containing adjacency lists
	
	void DFS_visit(int current_vertice, int &t, vector<bool> &visited, vector<int> &parent, vector<vector<int> > &timestamps)
	{
		//init	
		visited[current_vertice] = true;
		timestamps[0][current_vertice] = t++;

		list<int> neighbours_list = GetNeighbours(current_vertice);
		for (list<int>::iterator it = neighbours_list.begin(); it != neighbours_list.end(); ++it)
		{
			if (!visited[*it])
			{
				parent[*it] = current_vertice;
				DFS_visit(*it, t, visited, parent, timestamps);
			}
		}
		timestamps[1][current_vertice] = t++;
	}
public:
	static int const NIL = INT_MIN;
	explicit unweighted_graph(int V)
	{
		this->V = V;
		adj = new list<int>[V];
	}
	void addSingleEdge(int v, int w)//v->w
	{
		adj[v].push_back(w); 
	}
	void addBothEdges(int v, int w)
	{
		adj[v].push_back(w);
		adj[w].push_back(v);
	}
	list<int> GetNeighbours(int u)
	{
		return adj[u];
	}
	int GetVerticesNB()
	{
		return V;
	}
	void DFS_Traversal(vector<int> &parent_vector, vector<vector<int> > &timestamps_vector)
	{
		vector<bool> visited(GetVerticesNB());
		vector<int> parent(GetVerticesNB());
		vector<vector<int> > timestamps(2, vector<int>(GetVerticesNB(), 0)); //0:discovery time.1:end time
		int timestamp = 0;

		for (int i = 0; i < GetVerticesNB(); ++i)
		{
			if (!visited[i])
			{
				parent[i] = NIL;
				DFS_visit(i, timestamp, visited, parent, timestamps);
			}
		}
		parent_vector = parent;
		timestamps_vector = timestamps;
	}
};

struct weighted_graph
{
private:
	int NoVertices;    // No. of vertices
	list<int> *adj;    // Pointer to an array containing adjacency lists
	vector<vector<float> > *weights;

	void DFS_visit(int current_vertice, int &t, vector<bool> &visited, vector<int> &parent, vector<vector<int> > &timestamps)
	{
		//init	
		visited[current_vertice] = true;
		timestamps[0][current_vertice] = t++;

		list<int> neighbours_list = GetNeighbours(current_vertice);
		for (list<int>::iterator it = neighbours_list.begin(); it != neighbours_list.end(); ++it)
		{
			if (!visited[*it])
			{
				parent[*it] = current_vertice;
				DFS_visit(*it, t, visited, parent, timestamps);
			}
		}
		timestamps[1][current_vertice] = t++;
	}
public:
	static int const NIL = -1;

	explicit weighted_graph(int V)
	{
		this->NoVertices = V;
		adj = new list<int>[V];
		weights = new vector<vector<float> >(V, vector<float>(V, 0.0f));
	}
	void addSingleEdge(int v, int w,float weight)//v->w
	{
		adj[v].push_back(w);
		(*weights)[v][w] = weight;
	}
	void addBothEdges(int v, int w,float weight)
	{
		adj[v].push_back(w);
		adj[w].push_back(v);
		(*weights)[v][w] = weight;
		(*weights)[w][v] = weight;
	}
	list<int> GetNeighbours(int u) const
	{
		return adj[u];
	}
	int GetVerticesNB() const
	{
		return NoVertices;
	}
	float GetWeight(int u, int v) const
	{
		return (*weights)[u][v];
	}
	void DFS_Traversal(vector<int> &parent_vector, vector<vector<int> > &timestamps_vector)
	{
		vector<bool> visited(GetVerticesNB());
		vector<int> parent(GetVerticesNB());
		vector<vector<int> > timestamps(2, vector<int>(GetVerticesNB(), 0)); //0:discovery time.1:end time
		int timestamp = 0;

		for (int i = 0; i < GetVerticesNB(); ++i)
		{
			if (!visited[i])
			{
				parent[i] = NIL;
				DFS_visit(i, timestamp, visited, parent, timestamps);
			}
		}
		parent_vector = parent;
		timestamps_vector = timestamps;
	}
};


bool sortTuplesFromDFS(const tuple<int, int, int> &left, const tuple<int, int, int> &right)
{
	return get<2>(left) > get<2>(right);
}

vector<int> topologicalSort(weighted_graph g)
{
	vector<int> scratch_vector(g.GetVerticesNB());
	vector<vector<int> > timestamps(2, vector<int>(g.GetVerticesNB(), 0));
	vector<tuple<int, int, int> >times(g.GetVerticesNB());

	g.DFS_Traversal(scratch_vector, timestamps);
	for (int i = 0; i < g.GetVerticesNB(); ++i)
	{
		times[i] = make_tuple(i, timestamps[0][i], timestamps[1][i]);
	}
	sort(times.begin(), times.end(), sortTuplesFromDFS);
	for (int i = 0; i < g.GetVerticesNB(); ++i)
	{
		scratch_vector[i] = get<0>(times[i]);
	}
	
	return scratch_vector;
}

vector<int> topologicalSort(unweighted_graph g)
{
	vector<int> scratch_vector(g.GetVerticesNB());
	vector<vector<int> > timestamps(2, vector<int>(g.GetVerticesNB(), 0));
	vector<tuple<int, int, int> >times(g.GetVerticesNB());

	g.DFS_Traversal(scratch_vector, timestamps);
	for (int i = 0; i < g.GetVerticesNB(); ++i)
	{
		times[i] = make_tuple(i, timestamps[0][i], timestamps[1][i]);
	}
	sort(times.begin(), times.end(), sortTuplesFromDFS);
	for (int i = 0; i < g.GetVerticesNB(); ++i)
	{
		scratch_vector[i] = get<0>(times[i]);
	}

	return scratch_vector;
}

bool SortTuplesFromDistanceVector(const pair<int, float> &left, const pair<int, float> &right)
{
	return left.second < right.second;
}

void SingleSourceShortestPath(weighted_graph g, int source_vertex_i, vector<float> *distances, vector<int> *parents)
{
	vector<float> distance(g.GetVerticesNB()); // processes,dist
	vector<int> parent(g.GetVerticesNB(), unweighted_graph::NIL);

	distance[source_vertex_i] = 0;
	for (int i = 0; i < g.GetVerticesNB(); ++i)
	{
		if (i!=source_vertex_i)
			distance[i] = FLT_MAX;
	}	
	
	for (int j = 0; j < g.GetVerticesNB(); ++j)
	{
		for (int i = 0; i < g.GetVerticesNB(); ++i)
		{
			list<int> neighbours = g.GetNeighbours(i);
			for (list<int>::iterator it = neighbours.begin(); it != neighbours.end(); ++it)
			{
				if (distance[i] + g.GetWeight(i, *it) < distance[*it])
				{
					//cout << *it << " : " << distance[*it] << "-> " << distance[i] + g.GetWeight(i, *it) << endl;
					distance[*it] = distance[i] + g.GetWeight(i, *it);
					parent[*it] = i;
				}
			}
		}
	}	
	*distances= distance;	
	*parents = parent;
}

void AllPairShortestPaths(weighted_graph &g, vector<vector<float> > *all_distances_ret, vector<vector<int> > *all_parents_ret)
{
	vector<float> distances;
	vector<vector<float> > all_distances;
	vector<int> parents;
	vector<vector<int> > all_parents;

	for (int i = 0; i < g.GetVerticesNB(); ++i)
	{
		SingleSourceShortestPath(g, i, &distances, &parents);
		all_distances.push_back(distances);
		all_parents.push_back(parents);
		distances.clear();
		parents.clear();
	}
	*all_distances_ret = all_distances;
	*all_parents_ret = all_parents;
}