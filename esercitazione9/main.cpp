#include <iostream>
#include <utility> 
#include <algorithm>
#include "undirected_graph.hpp"
#include "containers.hpp"
#include "visite_grafi.hpp"
#include "cammini_minimi.hpp"


template <typename I>
void print_graph(const undirected_graph<I>& G) {
    
	auto edges = G.all_edges();
    if (edges.empty()) {
        std::cout << "(Grafo vuoto o contenente solo nodi isolati)";
    } else {
        for (const auto& edge : edges) {
            std::cout << edge << " "; 
        }
    }
    std::cout << '\n';
}

template <typename I>
void print_path(I target, const std::map<I, std::optional<I>>& pred, I source) {
    
	if (target == source) {
        std::cout << source;
        return;
    }
    
    auto it = pred.find(target);
    if (it == pred.end() || !it->second.has_value()) {
        std::cout << "[Non Raggiungibile]";
        return;
    }
    
    // Risale l'albero dei predecessori fino alla sorgente
    print_path(it->second.value(), pred, source);
    
    // Stampa il nodo corrente durante il ritorno della ricorsione
    std::cout << " -> " << target;
}

int main() {
	
    undirected_graph<int> G;

    /* Struttura:
           0
          / \
         1   2
         | \ | \
         3   4--5
	     | \ | /|
	     6   7  8    */
	
    G.add_edge(0,1);
    G.add_edge(0,2);
    G.add_edge(1,3);
    G.add_edge(1,4);
    G.add_edge(2,4);
	G.add_edge(2,5);
	G.add_edge(3,6);
	G.add_edge(3,7);
	G.add_edge(4,5);
	G.add_edge(4,7);
	G.add_edge(5,7);
	G.add_edge(5,8);

	int source_node = 0;
	
	std::cout << '\n';

    std::cout << "Grafo Originale: \n";
    print_graph(G);
    std::cout << '\n';

    fifo<std::pair<std::optional<int>, int>> q;
    undirected_graph<int> bfs_tree = graph_visit(G, source_node, q);

	std::cout << "Nodo sorgente: " << source_node << "\n\n";

    std::cout << "Albero risultante da BFS: \n";
    print_graph(bfs_tree);
    std::cout << '\n';

    lifo<std::pair<std::optional<int>, int>> s;
    undirected_graph<int> dfs_tree = graph_visit(G, source_node, s);

    std::cout << "Albero risultante da DFS: \n";
    print_graph(dfs_tree);
    std::cout << '\n';

	undirected_graph<int> recursive_dfs_tree = recursive_dfs(G, source_node);
	
    std::cout << "Albero risultante da DFS ricorsiva: \n";
	print_graph(recursive_dfs_tree);
    std::cout << '\n';

	std::cout << "Algoritmo di Dijkstra: \n";
    
    dijkstra_result<int> result = dijkstra(G, source_node);

    auto dist = result.dist;
	auto pred = result.pred;
	
	for (int node : G.all_nodes()) {
        int distance = dist[node];
        
        if (distance > static_cast<int>(G.all_nodes().size()+1)) {
            std::cout << "Nodo " << node << ": distanza infinito. Cammino minimo: nessuno\n";
        } else {
            std::cout << "Nodo " << node << ": distanza " << distance << ". Cammino minimo: ";
			print_path(node, pred, source_node);
			std::cout << '\n';
        }
    }
	std::cout << '\n'; 

    return 0;
}