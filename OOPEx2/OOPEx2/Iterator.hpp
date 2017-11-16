#pragma once

#include <iterator>

template<typename ValueType>
class Iterator : public std::iterator<std::input_iterator_tag, ValueType>
{
	//friend class Array<ValueType>;
public:
	Iterator();
	Iterator(const Iterator& it);
	Iterator(ValueType* p);

	Iterator& operator=(const Iterator& other);

	bool operator!=(const Iterator& other) const;
	bool operator==(const Iterator& other) const;

	typename Iterator::reference operator*() const;
	Iterator& operator++();
	Iterator& operator--();

private:
	ValueType* p;
};

template<typename ValueType>
Iterator<ValueType>::Iterator() :
	p(nullptr)
{}

template<typename ValueType>
Iterator<ValueType>::Iterator(ValueType* p) :
	p(p)
{}

template<typename ValueType>
Iterator<ValueType>::Iterator(const Iterator& it) :
	p(it.p)
{}


template<typename ValueType>
Iterator<ValueType>& Iterator<ValueType>::operator=(const Iterator<ValueType>& other)
{
	this->p = other.p;
	return *this;
}

template<typename ValueType>
bool Iterator<ValueType>::operator!=(const Iterator& other) const
{
	return p != other.p;
}

template<typename ValueType>
bool Iterator<ValueType>::operator==(const Iterator& other) const
{
	return p == other.p;
}

template<typename ValueType>
typename Iterator<ValueType>::reference Iterator<ValueType>::operator*() const
{
	return *p;
}

template<typename ValueType>
Iterator<ValueType>& Iterator<ValueType>::operator++()
{
	++p;
	return *this;
}

template<typename ValueType>
Iterator<ValueType>& Iterator<ValueType>::operator--()
{
	--p;
	return *this;
}

