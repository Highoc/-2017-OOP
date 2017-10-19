#pragma once

#include <initializer_list>
#include <iostream>
#include <cassert>

#include <stdlib.h>

#include "Iterator.hpp"


class IntArray
{
public:
	typedef size_t size_type;
	typedef int T;

	typedef Iterator<T> iterator;
	typedef Iterator<const T> const_iterator;

	IntArray();
	IntArray(size_type count);
	IntArray(size_type count, const T& value);
	IntArray(const IntArray& intArray);
	IntArray(const std::initializer_list<T>& list);

	~IntArray();

	IntArray& operator=(const IntArray& other);

	T& operator[](size_type index);
	const T& operator[](size_type index) const;

	T& at(size_type index);
	const T& at(size_type index) const;
	
	void assign(size_type count, const T& value);
	void assign(std::initializer_list<T> list);
	void assign(iterator begin, iterator end);
	void assign(const_iterator begin, const_iterator end);

	void clear();
	size_type size() const;

	void push_back(const T& value);
	void pop_back();

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;
private:
	void resize(size_t newSize);

	size_t size_;
	T* data_;
};

void swap(IntArray& first, IntArray& second);

bool operator==(const IntArray& first, const IntArray& second);
bool operator!=(const IntArray& first, const IntArray& second);
bool operator<=(const IntArray& first, const IntArray& second);
bool operator>=(const IntArray& first, const IntArray& second);
bool operator<(const IntArray& first, const IntArray& second);
bool operator>(const IntArray& first, const IntArray& second);