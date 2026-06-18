#include <iostream>
#include <list>
#include <vector>

using namespace std;

// Implementa um grafo direcionado simples.
class Graph {
private:
    // ATENCAO:
    // Esse codigo assume que todos os vertices de 0 ateh (adj.size() - 1) existem no grafo.
    // Isto eh, nao pode haver uma grafo com vertices 0, 1 e 3, 4.
    // O vertice 2 eh assumido que existe tambem nesse caso.
    // Isso tem impacto, por exemplo, em determinar se o grafo eh conexo.
	 vector<list<pair<int, int>>> adj;

public:
    explicit Graph(int size) : adj(size) {}
	~Graph() = default;

	int size() const { return static_cast<int>(adj.size()); }	// retorna número de vértices

	
	void edge(int src, int dst, int w);		// Cria src -> dst com peso w
	int degree(int vtx) const;              // retorna grau de um vértice
    list<int> neighbors(int vtx) const;	    // retorna lista de vertices ligados a src
    int weight(int src, int dst) const;	    // retorna peso da aresta de src para dst
	bool isConnected() const;

	
	list<int> dfs(int src); // Busca em profundidade
	list<int> bfs(int src); // Busca em largura
	list<int> spf(int src, int dst); // Menor caminho entre src e dst

    bool has_cycle() const;
    bool has_cycle(int src) const;

    bool reacheable(int src, int dst) const;

	void print() const; // Exibe o grafo

private:
	
	void DFS(int src, vector<bool> &visited, list<int> &result); // DFS de fato
	void BFS(int src, vector<bool> &visited, list<int> &result); // BFS de fato

    void dijkstra(int src, vector<int> &prev, vector<long> &dist); // acha os menores caminhos
    void path(int src, const vector<int> &prev, list<int> &result); // extrai menor caminho de prev

    bool has_cycle(int src, vector<bool> &visited) const;
};



