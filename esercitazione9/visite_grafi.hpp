#pragma once
#include <concepts>
#include <vector>
#include <unordered_set>
#include <utility> 
#include <optional>
#include "containers.hpp"
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"

template <typename container, typename I> requires std::integral<I>
undirected_graph<I> graph_visit(const undirected_graph<I>& original_graph, const I& start_node, container& c) {
	
	undirected_graph<I> tree;
	
	// Non uso un array o un vettore perché la struttura del grafo
	// implementato in undirected_graph.hpp permette che gli indici
	// dei nodi non siano contigui
	std::unordered_set<I> visited;
	
	// Arco iniziale, std::nullopt nodo fittizio
	c.put(std::make_pair(std::optional<I>(std::nullopt), start_node));	
	
	while (!c.empty()) {
		
		auto current_edge = c.get().value();		
		
		std::optional<I> p = current_edge.first;
		I u = current_edge.second;
		
		if (visited.find(u) != visited.end()) {
            continue;
        }
		
		visited.insert(u);
		
		// Se (p,u) non è l'arco fittizio lo aggiugo all'albero
		if (p.has_value()) {
		    tree.add_edge(p.value(),u);
        }
		
		auto optional_neighbors = original_graph.neighbors(u);
		
		if (optional_neighbors.has_value()) {
            for (I w : optional_neighbors.value()) {
                // Se il vicino w non è tra i visitati, lo mettiamo in coda/pila
                if (visited.find(w) == visited.end()) {
					c.put(std::make_pair(std::optional<I>(u), w));               
				}
            }
        }
	}
	
	return tree;

}


template <typename I> requires std::integral<I>
void dfs_auxiliary(const undirected_graph<I>& G, const I& u, const std::optional<I>& p, std::unordered_set<I>& visited, undirected_graph<I>& tree) {
	
	visited.insert(u);
	
	// Se (p,u) non è l'arco fittizio lo aggiungo all'albero
	if (p.has_value()) {
		tree.add_edge(p.value(),u);
	}
	
	auto optional_neighbors = G.neighbors(u);
    if (optional_neighbors.has_value()) {
        for (I w : optional_neighbors.value()) {
            if (visited.find(w) == visited.end()) {
                dfs_auxiliary(G, w, std::optional<I>(u), visited, tree);
            }
        }
    }

}

template <typename I> requires std::integral<I>
undirected_graph<I> recursive_dfs(const undirected_graph<I>& original_graph, const I& start_node) {

	undirected_graph<I> tree;

	// Non uso un array o un vettore perché la struttura del grafo
	// implementato in undirected_graph.hpp permette che gli indici
	// dei nodi non siano contigui
	std::unordered_set<I> visited;

	dfs_auxiliary(original_graph, start_node, std::optional<I>(std::nullopt), visited, tree);	

	return tree;
}