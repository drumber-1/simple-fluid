#pragma once

#include <iostream>

#include <array>
#include <vector>

template <size_t N>
using Indices = std::array<size_t, N>;

template <typename T, size_t N>
class ArrayN {
public:
	ArrayN(const std::array<size_t, N>& size);

	bool is_on_grid(const Indices<N>& indices) const;
	T operator() (const Indices<N>& indices) const;
	T& operator() (const Indices<N>& indices);
	size_t size(size_t dim) const;
	size_t total_size() const;
	size_t get_flattened_index(const Indices<N>& indices) const;
	Indices<N> get_unflattened_indices(size_t index) const;
protected:
	std::vector<T> mData;
	const std::array<size_t, N> mSize;
};

template <typename T, size_t N>
ArrayN<T, N>::ArrayN(const std::array<size_t, N>& size) : mSize(size) {
	size_t total_cells = 1;
	for (size_t i = 0; i < N; ++i) {
		total_cells *= size[i];
	}
	mData.resize(total_cells);
}

template <typename T, size_t N>
bool ArrayN<T, N>::is_on_grid(const Indices<N>& indices) const {
	for (int i = 0; i < N; ++i) {
		if (indices[i] < 0 || indices[i] >= mSize[i]) {
			return false;
		}
	}
	return true;
}

template <typename T, size_t N>
T ArrayN<T, N>::operator() (const Indices<N>& indices) const {
	return mData[get_flattened_index(indices)];
}

template <typename T, size_t N>
T& ArrayN<T, N>::operator() (const Indices<N>& indices) {
	return mData[get_flattened_index(indices)];
}

template <typename T, size_t N>
size_t ArrayN<T, N>::get_flattened_index(const Indices<N>& indices) const {
	size_t index = indices[0];
	for (size_t i = 1; i < N; ++i) {
		index *= mSize[i - 1];
		index += indices[i];
	}
	return index;
}

template <typename T, size_t N>
Indices<N> ArrayN<T, N>::get_unflattened_indices(size_t index) const {
	std::array<size_t, N> indices;
	size_t remainder = index;
	for (size_t id = N - 1; id != -1; --id) {
		indices[id] = remainder % mSize[id];
		remainder = (remainder - indices[id]) / mSize[id];
	}
	return indices;
}

template <typename T, size_t N>
size_t ArrayN<T, N>::size(size_t n) const {
	return mSize[n];
}

template <typename T, size_t N>
size_t ArrayN<T, N>::total_size() const {
	size_t total = 1;
	for (size_t i = 0; i < N; ++i) {
		total *= mSize[i];
	}
	return total;
}
