#include <iostream>

int main(void) {
	static const int N = 5;
	double arr[N] = {2, 4.2, 3.3, 1.7, 6.1};
	
	double extra;
	bool flag = 1;
	
	while (flag) {
		flag = 0;
		for (int i=0; i<N-1; i++) {
			if (arr[i]>arr[i+1]) {
				extra = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = extra;
				flag = 1;
			}
		}
	}
	std::cout << "Array ordinato: ";
	for (int i=0; i<N; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";
	return 0;
}