#pragma once
#include <list>
#include <vector>

template<typename T> 
class fifo {
private:
	
	std::list<T> data;

public:
	fifo() : data() {}
	
	void put(const T& value) {
		data.push_back(value);
	}
	
	std::optional<T> get(){
		if(data.empty()){
			return std::nullopt;
		} else {
			T x = data.front();
			data.pop_front();
			return x;
		}
	}

	bool empty() const {
		return data.empty();
	}
};

template<typename T> 
class lifo {
private:

	std::vector<T> data;

public:
	lifo() : data() {}
	
	void put(const T& value) {
		data.push_back(value);
	}
	
	std::optional<T> get(){
		if(data.empty()){
			return std::nullopt;
		} else {
			T x = data.back();
			data.pop_back();
			return x;
		}
	}

	bool empty() const {
		return data.empty();
	}

};


