#pragma once
#include <iostream>
#include <concepts>

template<typename I> requires std::integral<I>
class undirected_edge {
private:
    I n_from;
    I n_to;

public:

    undirected_edge() = delete;

    undirected_edge(const I& A,const I& B) {
		if (A < B) {
			n_from = A;
			n_to = B;
		}
		else {
			n_from = B;
			n_to = A;
		}
	}
	
	I from() const {
		return n_from;
	}

	I to() const {
		return n_to;
	}
	
	bool operator<(const undirected_edge& other) const {
		if (n_from != other.n_from) {
			return n_from < other.n_from;
		}
		return n_to < other.n_to;
	}
	
	bool operator==(const undirected_edge& other) const {
		if (n_from == other.n_from && n_to == other.n_to) {
			return true;
		}
		else {
			return false;
		}
	}
	
};

template<typename I> requires std::integral<I>
std::ostream&
operator<<(std::ostream& os, const undirected_edge<I>& edge) {
    os << "{" << edge.from() << ", " << edge.to() << "}";
    return os;
}
