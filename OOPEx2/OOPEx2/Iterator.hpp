#pragma once

#include <iterator>

template<typename ValueType>
class Iterator : public std::iterator<std::input_iterator_tag, ValueType>
{
	friend class IntArray;
public:
	Iterator(const Iterator& it);

	bool operator!=(const Iterator& other) const;
	bool operator==(const Iterator& other) const;

	typename Iterator::reference operator*() const;
	Iterator& operator++();

private:
	Iterator(ValueType* p);
};