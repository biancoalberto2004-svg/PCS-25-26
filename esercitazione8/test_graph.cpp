#include <iostream>
#include <cassert>
#include <optional>
#include <set>
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"

void test_undirected_edge() {
    std::cout << "Test undirected_edge... ";
    
    // 1. Test costruttore e ordinamento interno (from < to)
    undirected_edge<int> e1(5,2);
    assert(e1.from() == 2 && e1.to() == 5); 

    // 2. Test operatore di uguaglianza
    undirected_edge<int> e2(2,5);
    assert(e1 == e2);

    // 3. Test operatore di confronto (<)
    undirected_edge<int> e3(3,4);
    assert(e1 < e3); //

    std::cout << "OK!\n";
}

void test_undirected_graph_basics() {
    std::cout << "Test operazioni base grafo (add, nodes, edges, neighbors)... ";
    
    undirected_graph<int> g;
    undirected_edge<int> e1(1,2);
    undirected_edge<int> e2(2,3);
    undirected_edge<int> e3(1,3);

    // Test inserimento
    g.add_edge(e1);
    g.add_edge(e2);
    g.add_edge(e3);

    // Test conteggio nodi e archi
    assert(g.all_nodes().size() == 3);
    assert(g.all_edges().size() == 3);

    // Test vicini
    std::optional<std::set<int>> opt_n1 = g.neighbors(1);
    assert(opt_n1.has_value());
    assert(opt_n1.value().size() == 2);  

    // Test nodo inesistente 
    std::optional<std::set<int>> opt_n99 = g.neighbors(10);
    assert(!opt_n99.has_value());

    std::cout << "OK!\n";
}

void test_undirected_graph_indexing() {
    std::cout << "Test indicizzazione (edge_number, edge_at)...";
    
    undirected_graph<int> g;
    undirected_edge<int> e(10,20);
    g.add_edge(e);

    std::optional<size_t> opt_id = g.edge_number(e);
    assert(opt_id.has_value());  
	
    std::optional<undirected_edge<int>> opt_e = g.edge_at(opt_id.value());
    assert(opt_e.has_value()); 
    assert(opt_e.value() == e);

    std::cout << "OK!\n";
}

void test_undirected_graph_difference() {
    std::cout << "Test differenza... ";
    
    undirected_graph<int> g1;
    g1.add_edge(undirected_edge<int>(1,2));
    g1.add_edge(undirected_edge<int>(2,3));
    g1.add_edge(undirected_edge<int>(3,4));

    undirected_graph<int> g2;
    g2.add_edge(undirected_edge<int>(2,3));
	g2.add_edge(undirected_edge<int>(5,3));

    undirected_graph<int> g3 = g1 - g2;

    assert(g3.all_edges().size() == 2);
    assert(g3.all_nodes().size() == 4); 

    std::cout << "OK!\n";
}

void test_undirected_graph_copy() {
    std::cout << "Test costruttore di copia... ";
    
    undirected_graph<int> g1;
    g1.add_edge(undirected_edge<int>(1,2));

    undirected_graph<int> g2(g1);
    assert(g2.all_edges().size() == 1);

    g1.add_edge(undirected_edge<int>(2,3));
    assert(g1.all_edges().size() == 2);
    assert(g2.all_edges().size() == 1); 

    std::cout << "OK!\n";
}

int main() {
    
    test_undirected_edge();
    test_undirected_graph_basics();
    test_undirected_graph_indexing();
    test_undirected_graph_difference();
    test_undirected_graph_copy();
    
    std::cout << "Tutti i test superati con successo! \n";
    return 0;
}
