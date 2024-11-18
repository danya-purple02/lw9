#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>

using namespace std;

int** create_adjacency_matrix(int v);
int cout_matrix(int** g, int v);
void DFSD_matrix(int** g, int s, int size, int* vis, int* depth);

struct Node
{
	int vertex;
	struct Node* next;
};

struct Graph
{
	int vertexes_amount;
	struct Node** list;
};

struct Graph* create_adjacency_list(int vertexes);
struct Node* create_vertex(int vertex);
void connect_vertexes(struct Graph* graph, int coll, int dest);
void cout_adjacency_list(struct Graph* graph);
void DFSD_list(struct Graph* G, int s, int size, bool* vis);

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

	struct Graph* G1 = create_adjacency_list(vertexes);
	for (int i = 0; i < vertexes; i++)
	{
		for (int j = 0; j < vertexes; j++)
		{
			if (M[i][j] == 1)
			{
				connect_vertexes(G1, i, j);
			}
		}
	}
	cout_adjacency_list(G1);

	for (int i = 0; i < vertexes; i++)
	{
		visited[i] = 0;
		depth[i] = -1;
	}

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

struct Graph* create_adjacency_list(int vertexes)
{
	struct Graph* graph = new struct Graph;
	graph->vertexes_amount = vertexes;
	graph->list = new struct Node* [vertexes];
	for (int i = 0; i < vertexes; i++)
	{
		graph->list[i] = new struct Node[vertexes];
	}

	for (int i = 0; i < vertexes; i++)
	{
		graph->list[i] = create_vertex(i);
	}

	return graph;
}

struct Node* create_vertex(int vertex)
{
	struct Node* new_node = new struct Node;
	new_node->vertex = vertex;
	new_node->next = NULL;
	return new_node;
}

void connect_vertexes(struct Graph* graph, int coll, int dest)
{
	struct Node* new_node = create_vertex(dest);
	int i = 0;
	while (graph->list[i]->vertex != coll)
	{
		i++;
	}

	struct Node* tmp = graph->list[i];
	while (tmp->next != NULL)
	{

		tmp = tmp->next;
	}

	tmp->next = new_node;
}

void cout_adjacency_list(struct Graph* graph)
{
	cout << endl << "adjacency list:" << endl;
	struct Node* tmp;
	for (int i = 0; i < graph->vertexes_amount; i++)
	{
		tmp = graph->list[i];
		while (tmp)
		{
			cout << tmp->vertex;
			tmp = tmp->next;
			if (tmp != NULL)
			{
				cout << " -> ";
			}
		}
		cout << endl;
	}
}

void DFSD_list(struct Graph* G, int s, int size, bool* vis)
{
	std::stack<int> st;
	st.push(s);
	vis[s] = true;

	while (!st.empty())
	{
		int v = st.top();
		st.pop();
		cout << v << " -> ";

		Node* l = G->list[v];
		while (l != NULL)
		{
			int neighbor = l->vertex;
			if (!vis[neighbor])
			{
				st.push(neighbor);
				vis[neighbor] = true;
			}
			l = l->next;
		}
	}
}