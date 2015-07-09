#pragma once

#include <vector>

template <typename T, size_t NX, size_t NY>
class Array2 {
public:
	Array2();

	T operator() (size_t i, size_t j) const;
	T& operator() (size_t i, size_t j);
	inline size_t flattened_index(size_t i, size_t j) const;
private:
	std::vector<T> data;
};

template <typename T, size_t NX, size_t NY>
Array2<T, NX, NY>::Array2() : data(NX * NY) {
}

template <typename T, size_t NX, size_t NY>
T Array2<T, NX, NY>::operator() (size_t i, size_t j) const {
	return data[flattened_index(i, j)];
}

template <typename T, size_t NX, size_t NY>
T& Array2<T, NX, NY>::operator() (size_t i, size_t j) {
	return data[flattened_index(i, j)];
}

template <typename T, size_t NX, size_t NY>
size_t Array2<T, NX, NY>::flattened_index(size_t i, size_t j) const {
	return j + (NY * i);
}


