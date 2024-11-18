#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>

using namespace std;

int** create_adjacency_matrix(int v);
int cout_matrix(int** g, int v);

void DFSD_matrix(int** g, int s, int size, int* vis, int* depth);

void main() 
{
	int** M;
	int vertexes = 0;
	int to_start_with = 0;

	cout << "input graph size: ";
	cin >> vertexes;

	M = create_adjacency_matrix(vertexes);
	cout_matrix(M, vertexes);

	int* visited = new int[vertexes];
	int* depth = new int[vertexes];
	for (int i = 0; i < vertexes; i++)
	{
		visited[i] = 0;
		depth[i] = -1;
	}

	cout << endl << "input input number of vertex to star with: ";
	cin >> to_start_with;

	cout << endl << "First-deep search: " << endl;
	DFSD_matrix(M, to_start_with, vertexes, visited, depth);

	cout << endl << endl << "  Depth of vertexes: " << endl;
	cout << "vertex		depth" << endl;
	for (int i = 0; i < vertexes; i++)
	{
		cout << "  " << i << "		  " << depth[i] << endl;
	}
	cout << endl << "--------------------------------------------" << endl;
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

void DFSD_matrix(int** g, int s, int size, int* vis, int* d)
{
	stack<int> st;
	st.push(s);
	vis[s] = 1;
	d[s] = 0;

	while (!st.empty())
	{
		int v = st.top();
		st.pop();
		cout << v << " -> ";

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