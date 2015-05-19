#pragma once

#include <array>

template <typename T, size_t NX, size_t NY>
class Array2 {
public:
	T operator() (size_t nx, size_t ny) const;
	T& operator() (size_t nx, size_t ny);
	inline size_t flattened_index(size_t x, size_t y) const;
protected:
	std::array<T, NX*NY> mData;
};


template <typename T, size_t NX, size_t NY>
T Array2<T, NX, NY>::operator() (size_t x, size_t y) const {
	return mData[flattened_index(x, y)];
}

template <typename T, size_t NX, size_t NY>
T& Array2<T, NX, NY>::operator() (size_t x, size_t y) {
	return mData[flattened_index(x, y)];
}

template <typename T, size_t NX, size_t NY>
inline size_t Array2<T, NX, NY>::flattened_index(size_t x, size_t y) const {
	return y + (NY * x);
}


