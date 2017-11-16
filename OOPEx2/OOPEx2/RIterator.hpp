#pragma once

#include <iterator>

template<typename ValueType>
class RIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
public:
	RIterator(const RIterator& it);
	RIterator(ValueType* p);

	bool operator!=(const RIterator& other) const;
	bool operator==(const RIterator& other) const;

	typename RIterator::reference operator*() const;
	RIterator& operator++();

private:
	ValueType* p;
};


template<typename ValueType>
RIterator<ValueType>::RIterator(ValueType* p) :
	p(p)
{}

template<typename ValueType>
RIterator<ValueType>::RIterator(const RIterator& it) :
	p(it.p)
{}

template<typename ValueType>
bool RIterator<ValueType>::operator!=(const RIterator& other) const
{
	return p != other.p;
}

template<typename ValueType>
bool RIterator<ValueType>::operator==(const RIterator& other) const
{
	return p == other.p;
}

template<typename ValueType>
typename RIterator<ValueType>::reference RIterator<ValueType>::operator*() const
{
	return *p;
}

template<typename ValueType>
RIterator<ValueType>& RIterator<ValueType>::operator++()
{
	--p;
	return *this;
}
