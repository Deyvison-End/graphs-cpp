#include <queue>
#include <set>

#include "graph.h"

// Crição da aresta src --> dst
void Graph::edge(int src, int dst, int w) {
	if (src < 0) throw std::runtime_error("Src invalido");
	if (dst < 0) throw std::runtime_error("Dst invalido");
	if (w   < 0) throw std::runtime_error("Distancia/peso invalido");
	
	adj[src].push_back({dst, w});

}


int Graph::degree(int src) const {
	if (src < 0 || src >= adj.size()) throw std::runtime_error("Src invalido");
	
	int Tamanho = adj[src].size();
	return Tamanho;

}

list<int> Graph::neighbors(int src) const {
	if (src < 0 || src >= adj.size()) throw std::runtime_error("Src invalido");
	
	list<int> vizinhos;
	for (const auto& par : adj[src]) {
		int vertice_vizinho = par.first;
		vizinhos.push_back(vertice_vizinho);
	}
	return vizinhos;
}

int Graph::weight(int src, int dst) const {
	if (src < 0 || src >= adj.size()) throw std::runtime_error("Src invalido");
	if (dst < 0 || dst >= adj.size()) throw std::runtime_error("Dst invalido");


	for (const auto& par : adj[src]) {
		if(dst == par.first)
		{
			return par.second;
		}
	}
	return -1;
}

void Graph::print() const {
	for (int i = 0; i < this->size(); i++) {
		int d = this->degree(i);
		cout << i << "(" << d << "): ";
		list<int> nei = this->neighbors(i);
		for (int dst : nei) {
			int w = this->weight(i, dst);
			cout << dst << "[" << w << "]; ";
		}
		cout << endl;
	}
}


bool Graph::isConnected() const {

	int n = adj.size();
	vector<int> grupo(n);

// inicializa os grupos apenas uma vez
	for (int i = 0; i < n; i++) {
		grupo[i] = i;
	}

// propaga grupos até que nenhuma mudança ocorra
	bool mudou = true;
	while (mudou) {
		mudou = false;
		for (int v = 0; v < n; v++) {
			for (const auto& par : adj[v]) {
				int dst = par.first;
				int grupo_v = grupo[v];
				int grupo_dst = grupo[dst];

				// se os grupos forem diferentes, une-os
				if (grupo_dst != grupo_v) {
					for (int u = 0; u < n; u++) {
						if (grupo[u] == grupo_dst) {
							grupo[u] = grupo_v;
							mudou = true;
						}
					}
				}
			}
		}
	}

// verifica se todos os vértices estão no mesmo grupo
	int g = grupo[0];
	for (int i = 1; i < n; i++) {
		if (grupo[i] != g) return false;
	}

	return true;

}





list<int> Graph::dfs(int src) {
	if (src < 0 || src >= adj.size())
		throw std::runtime_error("Src invalido");

	list<int> result;
	vector<bool> visited(adj.size(), false);

	DFS(src, visited, result);

	return result;
}

// Busca em profundidade
void Graph::DFS(int src, vector<bool> &visited, list<int> &result) {
	
	visited[src] = true;
	result.push_back(src);
	for (const auto& par : adj[src]) {
		int vizinho = par.first;
		if(visited[vizinho] == false) {
			DFS(vizinho,visited, result);
		}
	}

}

// Busca em largura
list<int> Graph::bfs(int src) {
	if (src < 0 || src >= adj.size())
		throw std::runtime_error("Src invalido");

	list<int> result;
	vector<bool> visited(adj.size(), false);

	BFS(src, visited, result);

	return result;
}

// Busca em largura
void Graph::BFS(int src, vector<bool> &visited, list<int> &result) {
	
    queue<int> fila;
    visited[src] = true;
    fila.push(src);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();
        result.push_back(u);

        for (const auto& par : adj[u]) {
            int vizinho = par.first;
            if (!visited[vizinho]) {
                visited[vizinho] = true;
                fila.push(vizinho);
            }
        }
    }
}


bool Graph::has_cycle() const {
	for (int i = 0; i < adj.size(); i++) {
		if (has_cycle(i)) return true;
	}
	return false;
}

bool Graph::has_cycle(int src) const {
	if (src < 0 || src >= adj.size())
		throw std::runtime_error("Src invalido");

	vector<bool> visited(adj.size(), false);

	return has_cycle(src, visited);
}

bool Graph::has_cycle(int src, vector<bool> &visited) const {
	
	visited[src] = true;

    for (const auto& par : adj[src]) {
        int vizinho = par.first;

        if (visited[vizinho]) {
            return true; 
        } else {
            if (has_cycle(vizinho, visited)) {
                return true; 
            }
        }
    }
    visited[src] = false;
    return false; 
}

bool Graph::reacheable(int src, int dst) const {
	if (src < 0 || src >= adj.size())
		throw std::runtime_error("Src invalido");

	if (dst < 0 || src >= adj.size())
		throw std::runtime_error("Dst invalido");

	
	vector<bool> visited(adj.size(), false);
	queue<int> fila;

	visited[src] = true;
	fila.push(src);
	
	if(src == dst){return true;}

	while (!fila.empty()) {
		int u = fila.front();
		fila.pop();

		for (const auto& par : adj[u]) {
			int vizinho = par.first;

			if (vizinho == dst)
				return true;

			if (!visited[vizinho]) {
				visited[vizinho] = true;
				fila.push(vizinho);
			}
		}
	}

	return false;
}


void Graph::path(int src, const vector<int> &prev, list<int> &result) {
	if (src < 0) return;
	path(prev[src], prev, result);
	result.push_back(src);
}

// Para facilitar a exibição de listas de vértices
ostream & operator <<(ostream &out, const list<int> &l) {
	for (int i : l) out << i << " ";
	return out;
}

void graph() {
	cout << endl << "*** Testando Grafo ***" << endl << endl;

	Graph graph1(6);		// Connected
	graph1.edge(0, 1, 4);
	graph1.edge(0, 2, 2);
	graph1.edge(1, 2, 5);
	graph1.edge(1, 3, 10);
	graph1.edge(2, 4, 3);
	graph1.edge(4, 3, 4);
	graph1.edge(3, 5, 11);
	graph1.edge(5, 1, 11);

	Graph graph2(9);		// Connected
	graph2.edge(0, 1, 4);
	graph2.edge(0, 7, 8);
	graph2.edge(1, 2, 8);
	graph2.edge(1, 7, 11);
	graph2.edge(2, 3, 7);
	graph2.edge(2, 5, 4);
	graph2.edge(2, 8, 2);
	graph2.edge(3, 4, 9);
	graph2.edge(3, 5, 14);
	graph2.edge(4, 5, 10);
	graph2.edge(5, 6, 2);
	graph2.edge(6, 7, 1);
	graph2.edge(6, 8, 6);
	graph2.edge(7, 8, 7);

	Graph graph3(6);		// Not connected
	graph3.edge(0, 1, 12);
	graph3.edge(0, 2, 2);
	graph3.edge(3, 4, 1);
	graph3.edge(4, 5, 10);

	cout << "Graph1 is connected? " << (graph1.isConnected()?"YES":"NO") << endl; // YES
	graph1.print();
	cout << endl;

	cout << "Graph2 is connected? " << (graph2.isConnected()?"YES":"NO") << endl; // YES
	graph2.print();
	cout << endl;

	cout << "Graph3 is connected? " << (graph3.isConnected()?"YES":"NO") << endl; // NO
	graph3.print();
	cout << endl;

	cout << endl;

	cout << "Graph1: " << endl;
	cout << "DFS(0): " << graph1.dfs(0) << endl; // 0 1 2 4 3 5
	cout << "BFS(0): " << graph1.bfs(0) << endl; // 0 1 2 3 4 5
	cout << "Has cycle: " << (graph1.has_cycle()?"yes":"no") << endl; // yes
	cout << "Reachable(0, 5): " << (graph1.reacheable(0, 5)?"yes":"no") << endl; // yes
	cout << "Reachable(5, 0): " << (graph1.reacheable(5, 0)?"yes":"no") << endl; // no
	cout << endl;

	cout << "Graph2: " << endl;
	cout << "DFS(0): " << graph2.dfs(0) << endl; // 0 1 2 3 4 5 6 7 8
	cout << "BFS(0): " << graph2.bfs(0) << endl; // 0 1 7 2 8 3 5 4 6
	cout << "Has cycle: " << (graph2.has_cycle()?"yes":"no") << endl; // no
	cout << "Reachable(0, 5): " << (graph2.reacheable(0, 5)?"yes":"no") << endl; // yes
	cout << "Reachable(5, 0): " << (graph2.reacheable(5, 0)?"yes":"no") << endl; // no
	cout << "Reachable(4, 8): " << (graph2.reacheable(4, 8)?"yes":"no") << endl; // yes
	cout << "Reachable(8, 4): " << (graph2.reacheable(8, 4)?"yes":"no") << endl; // no
	cout << endl;

	cout << "Graph3: " << endl;
	cout << "DFS(0): " << graph3.dfs(0) << endl; // 0 1 2
	cout << "BFS(0): " << graph3.bfs(0) << endl; // 0 1 2
	cout << "Has cycle: " << (graph3.has_cycle()?"yes":"no") << endl; // no
	cout << "Reachable(0, 5): " << (graph3.reacheable(0, 5)?"yes":"no") << endl; // no
	cout << "Reachable(3, 5): " << (graph3.reacheable(3, 5)?"yes":"no") << endl; // yes
	cout << "Reachable(1, 2): " << (graph3.reacheable(1, 2)?"yes":"no") << endl; // no
}

