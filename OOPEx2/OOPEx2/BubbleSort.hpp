#pragma once
#include <iostream>
#include <algorithm>
#include <vector>


template<typename T>
class Compare
{
public:
	bool operator()(T& A, T& B)
	{
		//std::cout << A << " " << B;
		if (A > B)
		{
			return true;
		}
		return false;
	}
};

template<typename iterator_t>
void printRange(iterator_t first, iterator_t last);

template<typename iterator_t, typename predicate_t>
void customSort(iterator_t first, iterator_t last, predicate_t predicate);



/*
int main()
{
	typedef std::vector<int, std::allocator<int>>::iterator iterator;
	Compare<int> compare;

	std::vector<int> test = { 3, 6, 9, 7, 5, 4 };
	printRange<iterator>(test.begin(), test.end());

	customSort<iterator, Compare<int>>(test.begin(), test.end(), f);

	printRange<iterator>(test.begin(), test.end());

	system("pause");
	return 0;
}

*/




template<typename iterator_t>
void printRange(iterator_t first, iterator_t last)
{
	for (; first != last; ++first)
	{
		std::cout << *(first) << " ";
	}
	std::cout << std::endl;
}

template<typename iterator_t, typename predicate_t>
void customSort(iterator_t first, iterator_t last, predicate_t predicate)
{
	for (iterator_t firstA = first; firstA != last; ++firstA)
	{
		for (iterator_t firstB = first; firstB + 1 != last; ++firstB)
		{
			if (predicate(*(firstB), *(firstB + 1)))
			{
				std::swap(*firstB, *(firstB + 1));
				//std::cout << "+\n";
			}
			else
			{
				//std::cout << "-\n";
			}
		}
	}
}
