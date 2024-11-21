#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <stack>
#include <time.h>

using namespace std;

int** create_adjacency_matrix(int v);
int cout_matrix(int** G, int v);

void BFS_matrix(int** g, int v, int size, bool* vis, int* d);
void DFSD_matrix(int** g, int s, int size, bool* vis, int* depth);

void main()
{
	clock_t start = 0, end = 0, res_BFS = 0, res_DFS = 0;
	int size, to_start_with;

	cout << endl << "input input number of vertex to star with: ";
	cin >> to_start_with;

	for (size = 1000; size <= 10000; size = size + 1000) 
	{
		int** M = create_adjacency_matrix(size);
		//cout_matrix(M, size);

		bool* visited = new bool[size];
		int* depth = new int[size];
		for (int i = 0; i < size; i++)
		{
			visited[i] = 0;
			depth[i] = -1;
		}

		//cout << "Breadth-first search: " << endl;

		start = clock();
		while (!visited[to_start_with])
		{
			BFS_matrix(M, to_start_with, size, visited, depth);
		}
		end = clock();
		res_BFS = end - start;

		/*
		cout << endl << endl << "  Depth of vertexes: " << endl;
		cout << "vertex		depth" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << "  " << i << "		  " << depth[i] << endl;
		}
		cout << endl << "--------------------------------------------" << endl;
		*/

		start = 0, end = 0;
		for (int i = 0; i < size; i++)
		{
			visited[i] = 0;
			depth[i] = -1;
		}

		//cout << "Deep-first search: " << endl;

		start = clock();
		DFSD_matrix(M, to_start_with, size, visited, depth);
		end = clock();
		res_DFS = end - start;

		cout << "---------------------------------" << endl;

		cout << "matrix size: " << size << endl;
		cout << "time spent on Breadth-first search: " << res_BFS / 10000.0 << endl;
		cout << "time spent on Deep-first search: " << res_DFS / 10000.0 << endl;
		delete[] M;
		delete[] visited;
		delete[] depth;
	}
	return;
}

int** create_adjacency_matrix(int v)
{
	srand(time(NULL));
	int** G = new int* [v];

	for (int i = 0; i < v; i++)
	{
		G[i] = new int[v];
	}

	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			if (j < i)
			{
				G[i][j] = G[j][i];
			}
			else
			{
				G[i][j] = rand() % 2;
			}
		}
	}

	return G;
}

int cout_matrix(int** g, int v)
{
	cout << "    ";
	for (int i = 0; i < v; i++)
	{
		cout << i << " ";
	}
	cout << endl << endl;
	for (int i = 0; i < v; i++)
	{
		cout << i << "   ";
		for (int j = 0; j < v; j++)
		{
			cout << g[i][j] << " ";
		}
		cout << endl;
	}
	return 1;
}

void BFS_matrix(int** g, int v, int size, bool* vis, int* d)
{
	queue<int> q;
	q.push(v);
	vis[v] = 1;
	d[v] = 0;

	while (!q.empty())
	{
		v = q.front();
		q.pop();
		//cout << v << " -> ";
		for (int i = 0; i < size; i++)
		{
			if (g[v][i] == 1 && !vis[i])
			{
				d[i] = d[v] + 1;
				vis[i] = 1;
				q.push(i);
			}
		}
	}
}

void DFSD_matrix(int** g, int s, int size, bool* vis, int* d)
{
	stack<int> st;
	st.push(s);
	vis[s] = 1;
	d[s] = 0;

	while (!st.empty())
	{
		int v = st.top();
		st.pop();
		//cout << v << " -> ";

		for (int i = size - 1; i >= 0; i--)
		{
			if (g[v][i] == 1 && vis[i] == 0)
			{
				st.push(i);
				vis[i] = 1;
				d[i] = d[v] + 1;
			}
		}
	}
}