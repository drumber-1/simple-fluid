#pragma once

#include <iostream>

#include <array>
#include <vector>

template <typename T>
class Array2 {
public:
	Array2(size_t nx, size_t ny);
	Array2(const std::array<size_t, 2>& size);

	T operator() (int nx, int ny) const;
	T& operator() (int nx, int ny);
	size_t nx() const;
	size_t ny() const;
	size_t flattened_index(int x, int y) const;
protected:
	std::vector<T> mData;
	const size_t NX;
	const size_t NY;
};

template <typename T>
Array2<T>::Array2(size_t nx, size_t ny): NX(nx), NY(ny) {
	mData.resize(NX*NY);
}

template <typename T>
Array2<T>::Array2(const std::array<size_t, 2>& size) : NX(size[0]), NY(size[1]) {
	mData.resize(NX*NY);
}

template <typename T>
T Array2<T>::operator() (int x, int y) const {
	return mData[flattened_index(x, y)];
}

template <typename T>
T& Array2<T>::operator() (int x, int y) {
	return mData[flattened_index(x, y)];
}

template <typename T>
size_t Array2<T>::flattened_index(int x, int y) const {
	return y + (NY * x);
}

template <typename T>
size_t Array2<T>::nx() const {
	return NX;
}

template <typename T>
size_t Array2<T>::ny() const {
	return NY;
}
