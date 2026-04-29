#include <iostream>
#include <cstdlib>
#include "sorting.hpp"
#include "timecounter.h"
#include "randfiller.h"


std::vector<std::vector<double>> crea_vecs(int dim) {
	std::vector<std::vector<double>> big_vec(100);
	
	randfiller rf;

	for (int i=0; i < 100; i++) {
		std::vector<double> small_vec(dim);
		rf.fill(small_vec, -20000., +20000.);
		big_vec[i] = small_vec;
	}
	return big_vec;
}

double misura_bubble(const std::vector<std::vector<double>>& big_vec) {
	std::vector<std::vector<double>> copia_big_vec = big_vec;
	timecounter tc;
	
	tc.tic();
	for (int i=0; i<100; i++) {
		bubble_sort(copia_big_vec[i]);
	}
	double time = tc.toc();
	
	return time/100.;
}

double misura_insertion(const std::vector<std::vector<double>>& big_vec) {
	std::vector<std::vector<double>> copia_big_vec = big_vec;
	timecounter tc;
	
	tc.tic();
	for (int i=0; i<100; i++) {
		insertion_sort(copia_big_vec[i]);
	}
	double time = tc.toc();
	
	return time/100.;
}

double misura_selection(const std::vector<std::vector<double>>& big_vec) {
	std::vector<std::vector<double>> copia_big_vec = big_vec;
	timecounter tc;
	
	tc.tic();
	for (int i=0; i<100; i++) {
		selection_sort(copia_big_vec[i]);
	}
	double time = tc.toc();
	
	return time/100.;
}

double misura_merge(const std::vector<std::vector<double>>& big_vec) {
	std::vector<std::vector<double>> copia_big_vec = big_vec;
	timecounter tc;
	
	tc.tic();
	for (int i=0; i<100; i++) {
		merge_sort(copia_big_vec[i]);
	}
	double time = tc.toc();
	
	return time/100.;
}

double misura_quick(const std::vector<std::vector<double>>& big_vec) {
	std::vector<std::vector<double>> copia_big_vec = big_vec;
	timecounter tc;
	
	tc.tic();
	for (int i=0; i<100; i++) {
		quick_sort(copia_big_vec[i]);
	}
	double time = tc.toc();
	
	return time/100.;
}


int main(void) {
	int i_min = 5;
	int k_max = 550;
	int step = 4;
	std::vector<double> dims_bub_mer;
	std::vector<double> dims_bub_qui;
	std::vector<double> dims_ins_mer;
	std::vector<double> dims_ins_qui;
	std::vector<double> dims_sel_mer;
	std::vector<double> dims_sel_qui;

	for (int i=i_min; i<=k_max; i+=step) {
		std::vector<std::vector<double>> big_vec = crea_vecs(i);
		double time_bubble = misura_bubble(big_vec);
		double time_insertion = misura_insertion(big_vec);
		double time_selection = misura_selection(big_vec);
		double time_merge = misura_merge(big_vec);
		double time_quick = misura_quick(big_vec);

		if (time_bubble > time_merge) {
			dims_bub_mer.push_back(i);
		}
		
		if (time_bubble > time_quick) {
			dims_bub_qui.push_back(i);
		}
		
		if (time_insertion > time_merge) {
			dims_ins_mer.push_back(i);
		}
		
		if (time_insertion > time_quick) {
			dims_ins_qui.push_back(i);
		}
		
		if (time_selection > time_merge) {
			dims_sel_mer.push_back(i);
		}
		
		if (time_selection > time_quick) {
			dims_sel_qui.push_back(i);
		}
	
	}

	// Bubble-Merge
	if (dims_bub_mer.empty()) {
		std::cout << "Bubble Sort è più veloce di Merge Sort per tutti i vettori di dimensione fino a " << k_max;
	}
	else {
		bool printed = false;
		for (size_t i=0; i+step < dims_bub_qui.size(); i++) {
			if (dims_bub_mer[i+5]-dims_bub_mer[i] == step*5) {
				std::cout << "Merge Sort è più veloce di Bubble Sort per n > " << dims_bub_mer[i];
				printed = true;
				break;
			}
		}
		if (!printed) {
			std::cout << "Bubble Sort è più veloce di Merge Sort per tutti i vettori di dimensione fino a " << k_max;
		}
	}
	std::cout << '\n';

	// Bubble-Quick
	if (dims_bub_qui.empty()) {
		std::cout << "Bubble Sort è più veloce di Quick Sort per tutti i vettori di dimensione fino a " << k_max;
	}
	else {
		bool printed = false;
		for (size_t i=0; i+step < dims_bub_qui.size(); i++) {
			if (dims_bub_qui[i+5]-dims_bub_qui[i] == step*5) {
				std::cout << "Quick Sort è più veloce di Bubble Sort per n > " << dims_bub_qui[i];
				printed = true;
				break;
			}
		}
		if (!printed) {
			std::cout << "Bubble Sort è più veloce di Quick Sort per tutti i vettori di dimensione fino a " << k_max;
		}
	}
	std::cout << "\n\n";

	// Insertion-Merge
	if (dims_ins_mer.empty()) {
		std::cout << "Insertion Sort è più veloce di Merge Sort per tutti i vettori di dimensione fino a " << k_max;
	}
	else {
		bool printed = false;
		for (size_t i=0; i+step < dims_bub_qui.size(); i++) {
			if (dims_ins_mer[i+5]-dims_ins_mer[i] == step*5) {
				std::cout << "Merge Sort è più veloce di Insertion Sort per n > " << dims_ins_mer[i];
				printed = true;
				break;
			}
		}
		if (!printed) {
			std::cout << "Insertion Sort è più veloce di Merge Sort per tutti i vettori di dimensione fino a " << k_max;
		}
	}
	std::cout << '\n';
	
	// Insertion-Quick
	if (dims_ins_qui.empty()) {
		std::cout << "Insertion Sort è più veloce di Quick Sort per tutti i vettori di dimensione fino a " << k_max;
	}
	else {
		bool printed = false;
		for (size_t i=0; i+step < dims_bub_qui.size(); i++) {
			if (dims_ins_qui[i+5]-dims_ins_qui[i] == step*5) {
				std::cout << "Quick Sort è più veloce di Insertion Sort per n > " << dims_ins_qui[i];
				printed = true;
				break;
			}
		}
		if (!printed) {
			std::cout << "Insertion Sort è più veloce di Quick Sort per tutti i vettori di dimensione fino a " << k_max;
		}
	}
	std::cout << "\n\n";

	// Selection-Merge	
	if (dims_sel_mer.empty()) {
		std::cout << "Selection Sort è più veloce di Merge Sort per tutti i vettori di dimensione fino a " << k_max;
	}
	else {
		bool printed = false;
		for (size_t i=0; i+step < dims_bub_qui.size(); i++) {
			if (dims_sel_mer[i+5]-dims_sel_mer[i] == step*5) {
				std::cout << "Merge Sort è più veloce di Selection Sort per n > " << dims_sel_mer[i];
				printed = true;
				break;
			}
		}
		if (!printed) {
			std::cout << "Selection Sort è più veloce di Merge Sort per tutti i vettori di dimensione fino a " << k_max;
		}
	}
	std::cout << '\n';

	// Selection-Merge	
	if (dims_sel_qui.empty()) {
		std::cout << "Selection Sort è più veloce di Quick Sort per tutti i vettori di dimensione fino a " << k_max;
	}
	else {
		bool printed = false;
		for (size_t i=0; i+step < dims_bub_qui.size(); i++) {
			if (dims_sel_qui[i+5]-dims_sel_qui[i] == step*5) {
				std::cout << "Quick Sort è più veloce di Selection Sort per n > " << dims_sel_qui[i];
				printed = true;
				break;
			}
		}
		if (!printed) {
			std::cout << "Selection Sort è più veloce di Quick Sort per tutti i vettori di dimensione fino a " << k_max;
		}
	}
	std::cout << "\n\n";


	return EXIT_SUCCESS;
}