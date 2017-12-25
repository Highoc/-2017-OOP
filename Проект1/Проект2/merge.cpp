#include <iostream>
#include <stdlib.h>
#include <iterator>
#include <algorithm>
#include <vector>
#include <memory>
#include <string>
#include <thread>

const size_t size = 100000;

using std::cout;
using std::endl;

template <typename Iterator>
void Print_range(Iterator first, Iterator last)
{
	for (auto it = first; it != last; ++it) cout << *it << " ";
	cout << endl;
}

template<typename Iterator , typename Predicate>
void merge_sort(Iterator first, Iterator last, Predicate predicate = std::less<int>())
{
	
	typedef typename std::iterator_traits<Iterator>::value_type type;
	size_t size = std::distance(first, last);
    if (size > 1)
    {
		Iterator left_it = first + size/2;

		Iterator right_it = last - size/2 - size % 2;

        merge_sort(first, left_it, predicate);
        merge_sort(right_it, last, predicate);

		Iterator lidx = first, ridx = right_it;
        std::vector<type> arr (size);
		auto idx = arr.begin();

        while (lidx < left_it || ridx < first + size)
        {
            if (predicate (*lidx, *ridx))
            {
                *(idx++) = std::move(*lidx);
                lidx++;
            }

            else
            {
                *(idx++) = std::move(*ridx);
                ridx++;
            }

            if (lidx == left_it)
            {
                std::copy(ridx, last, idx);
                break;
            }
			
            if (ridx == first + size)
            {
                std::copy(lidx, left_it, idx);
                break;
            }
        }
		
        std::copy(arr.begin(), arr.end(), first);
	}
}

template <typename Iterator, typename Predicate>
void merge_sort_with_threads(Iterator first, Iterator last, Predicate predicate = std::less<int>())
{
	auto middle = ( last - first ) / 2;
	typedef typename std::iterator_traits<Iterator>::value_type type;
	std::thread t1 (merge_sort<Iterator, Predicate>, first, first + middle, predicate);
	std::thread t2 (merge_sort<Iterator, Predicate>, first + middle, last, predicate);
	t1.join();
	t2.join();
	auto size = std::distance(first, last);
	std::vector<type> dst(size);
	std::merge (first, first+middle, first+middle, last, dst.begin(), predicate);
	std::copy(dst.begin(), dst.end(), first);
}

template <typename T>
bool myLess(const T & a, const T & b) {
	return (a < b);
}

template <typename T>
bool myMore(const T & a, const T & b) {
	return !myLess <T>(a, b);
}


int main()
{
	std::vector <int> vec (size);
	for (int& i : vec) i = rand() % size;
    std::vector <int> vec1 (vec);
	std::vector <int> vec2 (vec);

	auto t1 = std::chrono::high_resolution_clock::now();
	merge_sort_with_threads (vec1.begin(), vec1.end(), std::less<int>());
	auto t2 = std::chrono::high_resolution_clock::now();

	cout << "merge sort with threads takes " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1e+6 << " seconds" << endl;

	auto t3 = std::chrono::high_resolution_clock::now();
	merge_sort (vec2.begin(), vec2.end(), std::greater<int>());
	auto t4 = std::chrono::high_resolution_clock::now();

	cout << "merge sort without threads takes " << std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count() / 1e+6 << " seconds" << endl;
	
	//Print_range(vec.begin(), vec.end());
	
	system("pause");
	return 0;
}
