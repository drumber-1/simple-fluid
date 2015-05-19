#pragma once

#include <iostream>

#include <array>

template <typename T, size_t NX, size_t NY>
class Array2 {
public:
	T operator() (int nx, int ny) const;
	T& operator() (int nx, int ny);
	inline size_t flattened_index(int x, int y) const;
protected:
	std::array<T, NX*NY> mData;
};


template <typename T, size_t NX, size_t NY>
T Array2<T, NX, NY>::operator() (int x, int y) const {
	return mData[flattened_index(x, y)];
}

template <typename T, size_t NX, size_t NY>
T& Array2<T, NX, NY>::operator() (int x, int y) {
	return mData[flattened_index(x, y)];
}

template <typename T, size_t NX, size_t NY>
inline size_t Array2<T, NX, NY>::flattened_index(int x, int y) const {
	return y + (NY * x);
}
