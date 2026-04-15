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
