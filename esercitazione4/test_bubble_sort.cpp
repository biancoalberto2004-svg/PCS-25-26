#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include "sorting.hpp"
#include "randfiller.h"

// test su vettori di lunghezza random
bool test_random() {
	randfiller rf;
	
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 5000);
	
	for (int i=0; i<100; i++) {
		int N = dist(gen);
		std::vector<double> vec(N);
		rf.fill(vec, -10000., +10000.);
		bubble_sort(vec);
		if (!is_sorted(vec)) {
			return false;
		}
	}
	return true;
}

// test su valori stringhe
bool test_stringa() {
	std::vector<std::string> nomi = {"Carretto", "gerbi", "Botteon", "RABAGLIATI", "Tinto", "aMBROGIO", "gianotto", " ", "123456", "Giovanni Bianco"};
	bubble_sort(nomi);
	if (is_sorted(nomi)) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
    if (test_random()) {
        if (test_stringa()) {
			std::cout << "Test superato!\n";
			return EXIT_SUCCESS;
		}	
		else {
			std::cerr << "Test stringa fallito\n";
			return EXIT_FAILURE;
		}
    } 
	else {
        std::cerr << "Test numeri random fallito\n";
        return EXIT_FAILURE;
    }
}