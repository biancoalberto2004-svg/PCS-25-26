#include <iostream> 
#include <cmath>
#include <numeric> 

int main(void) {
	static const int N = 5;
	double arr[N] = {2, 4.2, 3.3, 1.7, 6.1};
	
	double min_val = arr[0];
	double max_val = arr[0];
	for (int i=1; i<N; i++) {
		min_val = std::min(min_val, arr[i]);
		max_val = std::max(max_val, arr[i]);
	}
	
	double avg = std::accumulate(std::begin(arr), std::end(arr), 0.0)/N;
	double sum_sq = 0;
	for (int i=0; i<N; i++) {
		sum_sq += std::pow(arr[i]-avg,2);
	}
	double std_dev = std::sqrt((sum_sq)/N); 
	
	std::cout << "Minimo: " << min_val << "\n";
	std::cout << "Massimo: " << max_val << "\n";
	std::cout << "Media: " << avg << "\n";
	std::cout << "Deviazione Standard: " << std_dev << "\n";
	return 0;

}