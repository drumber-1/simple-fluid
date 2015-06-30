#pragma once

#include <array>

template <typename T, size_t NX, size_t NY>
class Array2 {
public:
	T operator() (size_t i, size_t j) const;
	T& operator() (size_t i, size_t j);
	inline size_t flattened_index(size_t i, size_t j) const;
	std::array<T, NX*NY> mData;
};


template <typename T, size_t NX, size_t NY>
T Array2<T, NX, NY>::operator() (size_t i, size_t j) const {
	return mData[flattened_index(i, j)];
}

template <typename T, size_t NX, size_t NY>
T& Array2<T, NX, NY>::operator() (size_t i, size_t j) {
	return mData[flattened_index(i, j)];
}

template <typename T, size_t NX, size_t NY>
size_t Array2<T, NX, NY>::flattened_index(size_t i, size_t j) const {
	return j + (NY * i);
}


