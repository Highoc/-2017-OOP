#pragma once

#include <initializer_list>
#include <iostream>
#include <cassert>

#include <stdlib.h>

#include "Exception.hpp"
#include "RIterator.hpp"
#include "Iterator.hpp"
#include "BubbleSort.hpp"

template <typename T>
class Array
{
public:
	typedef Iterator<T> iterator;
	typedef Iterator<const T> const_iterator;
	typedef RIterator<T> reverse_iterator;
	//typedef RIterator<const T> const_reverse_iterator;

	Array();
	Array(size_t count);
	Array(size_t count, const T& value);
	Array(const Array& array);
	Array(const std::initializer_list<T>& list);

	~Array();

	Array& operator=(const Array& other);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	T& at(size_t index);
	const T& at(size_t index) const;
	
	void assign(size_t count, const T& value);
	void assign(std::initializer_list<T> list);
	void assign(iterator begin, iterator end);
	void assign(const_iterator begin, const_iterator end);

	void clear();
	size_t size() const;

	void sort();
	void printRange();

	void push_back(const T& value);
	void pop_back();

	iterator begin();
	iterator end();

	reverse_iterator rbegin();
	reverse_iterator rend();

	const_iterator begin() const;
	const_iterator end() const;
private:
	void resize(size_t newSize);

	size_t size_;
	T* data_;
};

template <typename T>
void swap(Array<T>& first, Array<T>& second);

template <typename T>
bool operator==(const Array<T>& first, const Array<T>& second);

template <typename T>
bool operator!=(const Array<T>& first, const Array<T>& second);

template <typename T>
bool operator<=(const Array<T>& first, const Array<T>& second);

template <typename T>
bool operator>=(const Array<T>& first, const Array<T>& second);

template <typename T>
bool operator<(const Array<T>& first, const Array<T>& second);

template <typename T>
bool operator>(const Array<T>& first, const Array<T>& second);


template <typename T>
Array<T>::Array() :
	size_(0), data_(nullptr)
{}

template <typename T>
Array<T>::Array(size_t count) :
	size_(count), data_(nullptr)
{
	data_ = (T*) calloc(count, sizeof(T));
}

template <typename T>
Array<T>::Array(size_t count, const T& value) :
	Array(count)
{
	for (size_t i(0); i < size_; i++)
	{
		data_[i] = value;
	}
}

template <typename T>
Array<T>::Array(const Array<T>& array) :
	Array(array.size())
{
	for (size_t i(0); i < size_; i++)
	{
		data_[i] = array[i];
	}
}

template <typename T>
Array<T>::Array(const std::initializer_list<T>& list) :
	Array(list.size())
{
	int i(0);
	for (auto& now : list)
	{
		(*this)[i++] = now;
	}
}

template <typename T>
Array<T>::~Array()
{
	free(data_);
	data_ = nullptr;
	size_ = 0;
}


template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	resize(other.size_);

	for (size_t i(0); i < this->size_; i++)
	{
		this->at(i) = other.at(i);
	}

	return *this;
}


template <typename T>
T& Array<T>::operator[](size_t index)
{
	return data_[index];
}

template <typename T>
const T& Array<T>::operator[](size_t index) const
{
	return data_[index];
}

template <typename T>
T& Array<T>::at(size_t index)
{
	if ((index < 0) || (index >= size_))
	{
		throw Exception();
	}

	return (*this)[index];
}

template <typename T>
const T& Array<T>::at(size_t index) const
{
	if ((index < 0) || (index >= size_))
	{
		throw Exception();
	}

	return (*this)[index];
}


template <typename T>
void Array<T>::clear()
{
	resize(0);
}

template <typename T>
size_t Array<T>::size() const
{
	return size_;
}


template <typename T>
typename Array<T>::iterator Array<T>::begin()
{
	return iterator(data_);
}

template <typename T>
typename Array<T>::iterator Array<T>::end()
{
	return iterator(data_ + size_);
}

template <typename T>
typename Array<T>::const_iterator Array<T>::begin() const
{
	return const_iterator(data_);
}

template <typename T>
typename Array<T>::const_iterator Array<T>::end() const
{
	return const_iterator(data_ + size_);
}

template <typename T>
typename Array<T>::reverse_iterator Array<T>::rbegin()
{
	return reverse_iterator(data_ + size_ - 1);
}

template <typename T>
typename Array<T>::reverse_iterator Array<T>::rend()
{
	return reverse_iterator(data_ - 1);
}


template <typename T>
void Array<T>::resize(size_t newSize)
{
	if (size_ == newSize)
	{
		return;
	}

	size_ = newSize;
	if (newSize == 0)
	{
		free(data_);
		data_ = nullptr;
		return;
	}

	if (data_ == nullptr)
	{
		data_ = (T*) calloc(size_, sizeof(T));
	}
	else
	{
		data_ = (T*) realloc(data_, size_ * sizeof(T));
	}
}

template <typename T>
void Array<T>::sort()
{
	Compare<int> compare;
	customSort(begin(), end(), compare);
}

template <typename T>
void Array<T>::printRange()
{
	for (size_t i(0); i < this->size_; i++)
	{
		std::cout << at(i) << " ";
	}
	std::cout << std::endl;
}


template <typename T>
void Array<T>::push_back(const T& value)
{
	//capacity???
	resize(size_ + 1);
	this->at(size_ - 1) = value;
}

template <typename T>
void Array<T>::pop_back()
{
	resize(size_ - 1);
}


template <typename T>
void Array<T>::assign(size_t count, const T& value)
{
	resize(count);
	for (size_t i(0); i < size_; i++)
	{
		(*this)[i] = value;
	}
}

template <typename T>
void Array<T>::assign(std::initializer_list<T> list)
{
	resize(list.size());

	int i(0);
	for (auto& now : list)
	{
		(*this)[i++] = now;
	}
}

template <typename T>
void Array<T>::assign(iterator begin, iterator end)
{
	assign((const_iterator&)begin, (const_iterator&)end);
}

template <typename T>
void Array<T>::assign(const_iterator begin, const_iterator end)
{
	resize(0);
	for (Array::const_iterator i(begin); i != end; ++i)
	{
		push_back(*i);
	}
}


template <typename T>
void swap(Array<T>& first, Array<T>& second)
{
	Array<T> temp = first;
	first = second;
	second = temp;
}


template <typename T>
bool operator==(const Array<T>& first, const Array<T>& second)
{
	bool result = true;

	if (first.size() != second.size())
	{
		return 0;
	}

	for (Array<T>::const_iterator i(first.begin()), j(second.begin()); result && (i != first.end()) && (j != second.end()); ++i, ++j)
	{
		result = result && (*i == *j);
	}

	return result;
}

template <typename T>
bool operator!=(const Array<T>& first, const Array<T>& second)
{
	return !(first == second);
}

template <typename T>
bool operator<=(const Array<T>& first, const Array<T>& second)
{
	for (Array<T>::const_iterator i(first.begin()), j(second.begin());; ++i, ++j)
	{
		if (*i != *j)
		{
			return (*i < *j) ? true : false;
		}

		if (i == first.end())
		{
			return true;
		}
		else if (j == second.end())
		{
			return false;
		}
	}
}

template <typename T>
bool operator>=(const Array<T>& first, const Array<T>& second)
{
	for (Array<T>::const_iterator i(first.begin()), j(second.begin());; ++i, ++j)
	{
		if (*i != *j)
		{
			return (*i > *j) ? true : false;
		}

		if (j == second.end())
		{
			return true;
		}
		else if (i == first.end())
		{
			return false;
		}
	}
}

template <typename T>
bool operator<(const Array<T>& first, const Array<T>& second)
{
	return !(first >= second);
}

template <typename T>
bool operator>(const Array<T>& first, const Array<T>& second)
{
	return !(first <= second);
}
