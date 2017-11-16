/*#include "IntArray.hpp"

IntArray::IntArray():
	size_(0), data_(nullptr)
{}

IntArray::IntArray(size_type count) :
	size_(count), data_(nullptr)
{
	data_ = (T* ) calloc(count, sizeof(T));
}

IntArray::IntArray(size_type count, const T& value) :
	IntArray(count)
{
	for (size_t i(0); i < size_; i++)
	{
		data_[i] = value;
	}
}

IntArray::IntArray(const IntArray& intArray) :
	IntArray(intArray.size())
{
	for (size_t i(0); i < size_; i++)
	{
		data_[i] = intArray[i];
	}
}

IntArray::IntArray(const std::initializer_list<T>& list) :
	IntArray(list.size())
{
	int i(0);
	for (auto& now : list)
	{
		(*this)[i++] = now;
	}
}


IntArray::~IntArray()
{
	free(data_);
	data_ = nullptr;
	size_ = 0;
}


IntArray& IntArray::operator=(const IntArray& other)
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


IntArray::T& IntArray::operator[](size_type index)
{
	return data_[index];
}

const IntArray::T& IntArray::operator[](size_type index) const
{
	return data_[index];
}

IntArray::T& IntArray::at(size_type index)
{
	assert((index >= 0) && (index < size_));
	return (*this)[index];
}

const IntArray::T& IntArray::at(size_type index) const
{
	assert((index >= 0) && (index < size_));
	return (*this)[index];
}


void IntArray::clear()
{
	resize(0);
}

IntArray::size_type IntArray::size() const
{
	return size_;
}


IntArray::iterator IntArray::begin()
{
	return iterator(data_);
}

IntArray::iterator IntArray::end()
{
	return iterator(data_ + size_);
}

IntArray::const_iterator IntArray::begin() const
{
	return const_iterator(data_);
}

IntArray::const_iterator IntArray::end() const
{
	return const_iterator(data_ + size_);
}


void IntArray::resize(size_t newSize)
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
		data_ = (T* ) calloc(size_, sizeof(T));
	}
	else
	{
		data_ = (T* ) realloc(data_, size_ * sizeof(T));
	}
}


void IntArray::push_back(const T& value)
{
	resize(size_ + 1);
	this->at(size_ - 1) = value;
}

void IntArray::pop_back()
{
	resize(size_ - 1);
}


void IntArray::assign(size_type count, const T& value)
{
	resize(count);
	for (size_t i(0); i < size_; i++)
	{
		(*this)[i] = value;
	}
}

void IntArray::assign(std::initializer_list<T> list)
{
	resize(list.size());

	int i(0);
	for (auto& now : list)
	{
		(*this)[i++] = now;
	}
}

void IntArray::assign(iterator begin, iterator end)
{
	assign((const_iterator& ) begin, (const_iterator& ) end);
}

void IntArray::assign(const_iterator begin, const_iterator end)
{
	resize(0);
	for (IntArray::const_iterator i(begin);i != end; ++i)
	{
		push_back(*i);
	}
}


void swap(IntArray& first, IntArray& second)
{	
	IntArray temp = first;
	first = second;
	second = temp;
}

bool operator==(const IntArray& first, const IntArray& second)
{
	bool result = true;

	if (first.size() != second.size())
	{
		return 0;
	}

	for (IntArray::const_iterator i(first.begin()), j(second.begin()); result && (i != first.end()) && (j != second.end()) ; ++i, ++j)
	{
		result = result && (*i == *j);
	}

	return result;
}

bool operator!=(const IntArray& first, const IntArray& second)
{
	return !(first == second);
}

bool operator<=(const IntArray& first, const IntArray& second)
{
	for (IntArray::const_iterator i(first.begin()), j(second.begin());; ++i, ++j)
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

bool operator>=(const IntArray& first, const IntArray& second)
{
	for (IntArray::const_iterator i(first.begin()), j(second.begin());; ++i, ++j)
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

bool operator<(const IntArray& first, const IntArray& second)
{
	return !(first >= second);
}

bool operator>(const IntArray& first, const IntArray& second)
{
	return !(first <= second);
}*/