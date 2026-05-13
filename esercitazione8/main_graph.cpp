#include <iostream>
#include <cstdlib>
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"


int main() {
	
	// Definizione grafo
	undirected_edge<int> a(2,5);
	undirected_edge<int> b(5,6);
	undirected_edge<int> c(3,4);
	undirected_edge<int> d(2,6);
	undirected_edge<int> e(2,4);
	
	undirected_graph<int> g;
	g.add_edge(a);
	g.add_edge(b);
	g.add_edge(c);
	g.add_edge(d);
	g.add_edge(e);
	g.add_node(7);
	
	// Stampa nodi e archi grafo
	std::cout << "Grafo g: \n";
	
	std::cout << "Nodi: ";
	for (int node : g.all_nodes()) {
		std::cout << node << ' ';
	}
	std::cout << '\n';
	
	std::cout << "Archi: ";
	for (undirected_edge edge : g.all_edges()) {
		std::cout << edge << ' ';
	}
	std::cout << "\n\n";
	
	// Stampa neighbors
	std::cout << "Nodi vicini a 2: ";
	std::set<int> neighbors_2 = g.neighbors(2).value();
	for (int neighbor : neighbors_2) {
		std::cout << neighbor << ' ';
	}
	std::cout << "\n\n";
	
	// Stampa edge_number
	size_t c_id = g.edge_number(c).value();
	std::cout << "L'arco " << c << " ha indice = " << c_id << '\n';
	
	// Stampa edge_id
	undirected_edge edge_3 = g.edge_at(3).value();
	std::cout << "L'indice 3 è associato all'arco " << edge_3 << "\n\n";
	
	// Nuovo grafo
	undirected_graph<int> g2;
	g2.add_edge(a);
	g2.add_edge(c);
	g2.add_edge(d);
	g2.add_node(10);
	g2.add_node(11);
	
	std::cout << "Grafo g2: \n";
	
	std::cout << "Nodi: ";
	for (int node : g2.all_nodes()) {
		std::cout << node << ' ';
	}
	std::cout << '\n';
	
	std::cout << "Archi: ";
	for (undirected_edge edge : g2.all_edges()) {
		std::cout << edge << ' ';
	}
	std::cout << "\n\n";
	
	// Differenza
	undirected_graph<int> g_diff = g-g2;
	std::cout << "g-g2: \n";
	
	std::cout << "Nodi: ";
	for (int node : g_diff.all_nodes()) {
		std::cout << node << ' ';
	}
	std::cout << '\n';
	
	std::cout << "Archi: ";
	for (undirected_edge edge : g_diff.all_edges()) {
		std::cout << edge << ' ';
	}
	std::cout << "\n\n";
	
	return EXIT_SUCCESS;
}