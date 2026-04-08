#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "timecounter.h"
#include "randfiller.h"
#include "sorting.hpp"

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
	
	for (int i=4; i<=8192; i*=2) {
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
	}
	
	std::cout << "Bubble Sort: ";
	for (size_t i=0; i < vec_times_bubble.size()-1; i++) {
		std::cout << vec_times_bubble[i] << ", ";
	}
	std::cout << vec_times_bubble.back() << '\n';
	
	std::cout << "Insertion Sort: ";
	for (size_t i=0; i < vec_times_insertion.size()-1; i++) {
		std::cout << vec_times_insertion[i] << ", ";
	}
	std::cout << vec_times_insertion.back() << '\n';
	
	std::cout << "Selection Sort: ";
	for (size_t i=0; i < vec_times_selection.size()-1; i++) {
		std::cout << vec_times_selection[i] << ", ";
	}
	std::cout << vec_times_selection.back() << '\n';
	
	std::cout << "Standard Sort: ";
	for (size_t i=0; i < vec_times_std.size()-1; i++) {
		std::cout << vec_times_std[i] << ", ";
	}
	std::cout << vec_times_std.back() << '\n';
	
	return EXIT_SUCCESS;
}