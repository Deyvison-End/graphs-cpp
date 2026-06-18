#include "graph.h"

vector<int> overloaded(Graph capacity, Graph traffic) {

	vector<int> sobrecarregados;

    int n = capacity.size();
    
	for (int v = 0; v < n; v++) {
        int capacidade_saida = 0;
        int trafego_entrada = 0;

        // soma capacidade de saída
        for (int dst : capacity.neighbors(v)) {    
            int peso = capacity.weight(v, dst);    
            capacidade_saida += peso;               
        }

        // soma tráfego de entrada
        for (int u = 0; u < n; u++) {                    
            for (int dst : traffic.neighbors(u)) {       
            if (dst == v) {                          
            trafego_entrada += traffic.weight(u, dst);  
            }
        }
    }

        // verifica sobrecarga
        if (trafego_entrada > capacidade_saida) {
            sobrecarregados.push_back(v);
        }
    }

    return sobrecarregados;
}

// int main() {
void network() {
	cout << endl << "*** Testando Network ***" << endl << endl;

	// Grafo de capacidade da rede
	Graph capacity(6);
	capacity.edge(0, 1, 10);
	capacity.edge(0, 2, 5);
	capacity.edge(1, 2, 3);
	capacity.edge(1, 3, 3);
	capacity.edge(2, 4, 3);
	capacity.edge(4, 3, 4);
	capacity.edge(3, 5, 12);
	capacity.edge(5, 4, 8);

	// Grafo de trafego atual da rede
	Graph traffic(6);
	traffic.edge(0, 1, 7);
	traffic.edge(0, 2, 2);
	traffic.edge(1, 2, 4);
	traffic.edge(1, 3, 2);
	traffic.edge(2, 4, 3);
	traffic.edge(4, 3, 4);
	traffic.edge(3, 5, 8);
	traffic.edge(5, 4, 8);

	auto over = overloaded(capacity, traffic);

	cout << "Sobrecarregados: "; // 1 2 4
	for (int i : over) cout << i << " ";
	cout << endl;

}
