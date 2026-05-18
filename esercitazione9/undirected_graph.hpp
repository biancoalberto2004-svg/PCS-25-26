#pragma once
#include <iostream>
#include <concepts>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <optional>
#include "undirected_edge.hpp"

template<typename I> requires std::integral<I>
class undirected_graph {
private:
    
	// Garantisce complessità media di O(1) nel lookup dei nodi
    std::unordered_map<I, std::set<I>> adj_list; 
	
	
	// Uso due mappe per garantire velocità logaritmica per 
	// entrambi i metodi edge_at e edge_number, facendo attenzione
	// alla coerenza dei dati
	
	// Sfruttiamo l'ordinamento di undirected_edge
    std::map<undirected_edge<I>, size_t> edge_to_id; 

	// Considerando che gli indici sono numeri naturali progressivi,
	// std::vector avrebbe garantito complessità O(1) per edge_at().
	// Nonostante non sia presente un metodo remove_edge() in quanto
	// non richiesto, è un'aggiunta naturale alla classe, e a quel punto
	// andando a rimuovere un'arco si andrebbe a far scalare tutti gli 
	// archi successivi, perdendo la coerenza degli indici. Ho quindi
	// deciso di usare std::map, pur pagando una complessità O(log(E))
    std::map<size_t, undirected_edge<I>> id_to_edge;    
    
	size_t next_edge_id = 0; 

public:
	undirected_graph() 
        : adj_list(), 
          edge_to_id(), 
          id_to_edge(), 
          next_edge_id(0) 
	{}
	
	
	undirected_graph(const undirected_graph& other) 
		: adj_list(other.adj_list),
          edge_to_id(other.edge_to_id),
          id_to_edge(other.id_to_edge),
          next_edge_id(other.next_edge_id) 
	{}
		

    std::optional<std::set<I>> neighbors(const I& node) const {
		auto it = adj_list.find(node);
		
		if (it != adj_list.end()) {
			auto [found_node, found_neighbors] = *it;
			return found_neighbors; 
		}
		
		// Nodo non presente
		return std::nullopt; 
	}


	void add_node(const I& node) {		// Permette di aggiungere nodi isolati
	
	// Se il nodo è presente non fa nulla, altrimenti lo aggiunge
	// e inizializza l'insieme dei nodi vicini come insieme nullo 
		if (adj_list.find(node) == adj_list.end()) {
            adj_list[node] = std::set<I>();
        }
	}	


	void add_edge(const undirected_edge<I>& edge) { 
	
		// Aggiunge i nodi se non sono già presenti
        add_node(edge.from());
        add_node(edge.to());

        
        if (edge_to_id.find(edge) == edge_to_id.end()) {
			
			edge_to_id.insert({edge, next_edge_id});			
			id_to_edge.insert({next_edge_id, edge});
            next_edge_id++;

            adj_list[edge.from()].insert(edge.to());
            adj_list[edge.to()].insert(edge.from());
        }
    }

	// Aggiunta rispetto alla scorsa esercitazione 
	void add_edge(I from, I to) { 
	
		undirected_edge<I> edge(from,to);
		add_edge(edge);
    }	
	
	// Modifica rispetto a esercitazione passata: 
    // all_edges() e all_nodes() restituiscono std::vector
	// al posto di std::set
	
	std::vector<undirected_edge<I>> all_edges() const { 
		
		std::vector<undirected_edge<I>> edges;
		edges.reserve(edge_to_id.size()); // Alloca la memoria in anticipo!
        
		for (const auto& [edge, id] : edge_to_id) {
            edges.push_back(edge);
        }
		
		return edges;
	}
	
	
	std::vector<I> all_nodes() const {
		
		std::vector<I> nodes;
		nodes.reserve(adj_list.size()); 
        
		for (const auto& [node, neighbors] : adj_list) {
            nodes.push_back(node);
        }
		
		return nodes;
	}
	
	
	std::optional<size_t> edge_number(const undirected_edge<I>& edge) const {
        
		auto it = edge_to_id.find(edge);
        
		if (it != edge_to_id.end()) {
			auto [found_edge, id] = *it;
            return id;
        }
		
		// Arco non presente 
		return std::nullopt;
    }
	
	
	std::optional<undirected_edge<I>> edge_at(size_t id) const {
		
		auto it = id_to_edge.find(id);
		
		if (it != id_to_edge.end()) {
			auto [found_id, edge] = *it;
            return edge;
        }
		
		// Numero di arco non valido
		return std::nullopt;
	}


	undirected_graph operator-(const undirected_graph& other) const { 
        undirected_graph result;

		// Aggiunge al nuovo grafo tutti i nodi di quello attuale
        for (const auto& [node, neighbors] : adj_list) {
            result.add_node(node);
        }

        // Calcola la differenza sugli archi
        for (const auto& [edge, id] : edge_to_id) {
            if (other.edge_to_id.find(edge) == other.edge_to_id.end()) {
                result.add_edge(edge);
            }
        }
        return result;
    }

};