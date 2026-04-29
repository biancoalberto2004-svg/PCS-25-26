#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "timecounter.h"
#include "randfiller.h"
#include "sorting.hpp"

/* 
Questo programma serve a misurare i tempi di esecuzione degli algoritmi di ordinamento
testandoli su vettori di dimensione n=i^2 con i=2,...,14. Serve per valutare l'andamento
globale degli algoritmi in maniera abbastanza qualitativa. Per questo motivo non ho
usato la metodologia di misurazione espressa nella consegna (fare la media su un 
centinaio di vettori preallocati) per limitare i tempi di esecuzione del programma
(per ordinare i vettori per n=16384 il Bubble Sort ci avrebbe impiegato più di un minuto).
Invece, nel programma confronta_tempi.cpp, che serve per trovare il punto di sorpasso
degli algoritmi linearitmici su quelli quadratici, la metodologia è stata applicata correttamente.
*/

double measure_bubble(std::vector<double> vec) {
    timecounter tc; 
    tc.tic(); 
    bubble_sort(vec); 
    double time = tc.toc(); 
    return time; 
}

double measure_insertion(std::vector<double> vec) {
    timecounter tc;
    tc.tic();
    insertion_sort(vec); 
    double time = tc.toc();
    return time; 
}

double measure_selection(std::vector<double> vec) {
    timecounter tc;
    tc.tic();
    selection_sort(vec); 
    double time = tc.toc();
    return time; 
}

double measure_std(std::vector<double> vec) {
    timecounter tc;
	tc.tic();
    std::sort(vec.begin(), vec.end()); 
    double time = tc.toc();
    return time; 
}

double measure_merge(std::vector<double> vec) {
	timecounter tc;
	tc.tic();
    merge_sort(vec); 
    double time = tc.toc();
    return time;
}

double measure_quick(std::vector<double> vec) {
	timecounter tc;
	tc.tic();
    quick_sort(vec); 
    double time = tc.toc();
    return time;
}

double measure_my(std::vector<double> vec) {
	timecounter tc;
	tc.tic();
    my_sort(vec); 
    double time = tc.toc();
    return time;
}

int main() {
	randfiller rf;
	std::vector<double> vec_times_bubble;
	vec_times_bubble.reserve(12);
	std::vector<double> vec_times_insertion;
	vec_times_insertion.reserve(12);
	std::vector<double> vec_times_selection;
	vec_times_selection.reserve(12);
	std::vector<double> vec_times_std;
	vec_times_std.reserve(12);
	std::vector<double> vec_times_merge;
	vec_times_merge.reserve(12);
	std::vector<double> vec_times_quick;
	vec_times_quick.reserve(12);
	std::vector<double> vec_times_my;
	vec_times_my.reserve(12);
	
	for (size_t i=4; i<=16384; i*=2) { 
		std::vector<double> vec(i);
		rf.fill(vec, -10000., 10000.);
		double time_bub = measure_bubble(vec);
		vec_times_bubble.push_back(time_bub);
	    double time_ins = measure_insertion(vec);
		vec_times_insertion.push_back(time_ins);
		double time_sel = measure_selection(vec);
		vec_times_selection.push_back(time_sel);
	    double time_std = measure_std(vec);
		vec_times_std.push_back(time_std);
		double time_merge = measure_merge(vec);
		vec_times_merge.push_back(time_merge);
		double time_quick = measure_quick(vec);
		vec_times_quick.push_back(time_quick);
		double time_my = measure_my(vec);
		vec_times_my.push_back(time_my);
	}
	
	std::cout << "Bubble Sort: ";
	for (size_t i=0; i < vec_times_bubble.size()-1; i++) {
		std::cout << vec_times_bubble[i] << ", ";
	}
	std::cout << vec_times_bubble.back() << "\n\n";
	
	std::cout << "Insertion Sort: ";
	for (size_t i=0; i < vec_times_insertion.size()-1; i++) {
		std::cout << vec_times_insertion[i] << ", ";
	}
	std::cout << vec_times_insertion.back() << "\n\n";
	
	std::cout << "Selection Sort: ";
	for (size_t i=0; i < vec_times_selection.size()-1; i++) {
		std::cout << vec_times_selection[i] << ", ";
	}
	std::cout << vec_times_selection.back() << "\n\n";
	
	std::cout << "Merge Sort: ";
	for (size_t i=0; i < vec_times_merge.size()-1; i++) {
		std::cout << vec_times_merge[i] << ", ";
	}
	std::cout << vec_times_merge.back() << "\n\n";
	
	std::cout << "Quick Sort: ";
	for (size_t i=0; i < vec_times_quick.size()-1; i++) {
		std::cout << vec_times_quick[i] << ", ";
	}
	std::cout << vec_times_quick.back() << "\n\n";
	
	std::cout << "My Sort: ";
	for (size_t i=0; i < vec_times_my.size()-1; i++) {
		std::cout << vec_times_my[i] << ", ";
	}
	std::cout << vec_times_my.back() << "\n\n";
	
	std::cout << "Standard Sort: ";
	for (size_t i=0; i < vec_times_std.size()-1; i++) {
		std::cout << vec_times_std[i] << ", ";
	}
	std::cout << vec_times_std.back() << "\n\n";

	return EXIT_SUCCESS;
}