#pragma once

#include <vector>
#include <utility>

template<typename T>
bool is_sorted(const std::vector<T>& vec)
{
	if (vec.size() == 0) {
		return true;
	}
	
	for (size_t i = 0; i < vec.size()-1; i++) {
		if (vec[i] > vec[i+1]) {
			return false;
		}
	}
	return true;
}

template <typename T>
void bubble_sort(std::vector<T>& vec) {
	size_t n = vec.size();
	bool swapped;
	
    for (size_t i = 0; i+1 < n; ++i) {
		swapped = false;
        for (size_t j = n-1; j > i; --j) {
            if (vec[j] < vec[j-1]) {
                std::swap(vec[j], vec[j-1]);
				swapped = true;
            }
        }
		if (!swapped) {
			break;
		}
    }
}

template <typename T>
void insertion_sort(std::vector<T>& vec) {
    size_t n = vec.size();
    for (size_t j = 1; j < n; ++j) {
        T key = vec[j];
        size_t i = j;
        
        while (i > 0 && vec[i-1] > key) {
            vec[i] = vec[i-1];
            i -= 1;
        }
        vec[i] = key;
    }
}

template <typename T>
void selection_sort(std::vector<T>& vec) {
    size_t n = vec.size();
    for (size_t i = 0; i+1 < n; ++i) {
        size_t min = i;
        for (size_t j = i+1; j < n; ++j) {
            if (vec[j] < vec[min]) {
                min = j;
            }
        }
        std::swap(vec[i], vec[min]);
    }
}

template <typename T>
void merge(std::vector<T>& A, size_t p, size_t q, size_t r) {
	size_t n1 = q-p+1;
	size_t n2 = r-q;
	std::vector<T> L(n1);
	std::vector<T> R(n2);
	
	for (size_t i=0; i < n1; i++) {
		L[i] = A[p+i];
	}
	for (size_t j=0; j < n2; j++) {
		R[j] = A[q+1+j];
	}
	
	size_t i=0;
	size_t j=0;
	size_t k=p;
	
	while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
	
	while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }
	
	while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void merge_sort_recursive(std::vector<T>& A, size_t p, size_t r) {
	if (p < r) {
		size_t q = (p+r)/2;
		merge_sort_recursive(A, p, q);
		merge_sort_recursive(A, q+1, r);
		merge(A,p,q,r);
	}
}

template <typename T>
void merge_sort(std::vector<T>& A) {
    if (A.empty()) {
        return; 
    }
    merge_sort_recursive(A, 0, A.size() - 1);
}

template <typename T>
size_t partition(std::vector<T>& A, size_t p, size_t r) {
	T x = A[r];
	size_t i = p;
	
	for (size_t j = p; j < r; j++) {
		if (A[j] <= x) {
			std::swap(A[i], A[j]);
			i++;
		}
	}
	
	std::swap(A[i], A[r]);
	return i;
}

template <typename T>
void quick_sort_recursive(std::vector<T>& A, size_t p, size_t r) {
	if (p < r) {
		size_t q = partition(A,p,r);
		if (q > p) {
            quick_sort_recursive(A, p, q-1);
        }
		quick_sort_recursive(A, q+1, r);
	}
}

template <typename T>
void quick_sort(std::vector<T>& A) {
    if (A.size() == 0) {
        return; 
    }
    quick_sort_recursive(A, 0, A.size() - 1);
}

template <typename T>
void insertion_sort_segment(std::vector<T>& vec, size_t p, size_t r) {
    for (size_t j = p + 1; j <= r; ++j) {
        T key = vec[j];
        size_t i = j;
        
        while (i > p && vec[i-1] > key) {
            vec[i] = vec[i-1];
            i -= 1;
        }
        vec[i] = key;
    }
}

template <typename T>
void my_sort_recursive(std::vector<T>& A, size_t p, size_t r) {
	if (p < r) {
		if (r-p+1 < 165) {
			insertion_sort_segment(A, p, r);
		}
		else {
			size_t q = partition(A,p,r);
			if (q > p) {
				my_sort_recursive(A, p, q-1);
			}
			my_sort_recursive(A, q+1, r);
		}
	}
}

template <typename T>
void my_sort(std::vector<T>& A) {
	size_t N = A.size();
	if (N == 0) {
        return; 
	}
	else {
		my_sort_recursive(A, 0, N-1);
	}
}
