/*#include <cassert>
#include <iostream>


/// Задание по курсу. Написать свой небольшой аналог std::vector.
/// Реализовать класс хранения данных, поддерживающий необходимые операции.
/// В том числе нужно сделать класс исключений и итератор.
/// 
/// Для примера работы программы можно установить значение USE_STL_VECTOR 
/// равным единице. Тогда программа будет использовать стандартную библиотеку.
/// 
/// Ваша программа должна работать, когда USE_STL_VECTOR равно нулю.
/// Если вы делаете реализацию с шаблонами, поставьте 
/// USE_TEMPLATED_REALIZATION равным единице, если реализацию с int -- нулю.
/// 
/// Как можно видеть, ваш класс должен быть расположен в файле "Array.hpp"
/// и находиться в той же папке, где и данный файл.
/// Тогда для компиляции можно использовать, к примеру
/// "g++ -std=c++11 -Wall testArray.cpp -o testArray"
/// 
/// Класс-хранилище должен называться Array (независимо от шаблонности), 
/// класс для исключений должен называться Exception,
/// класс итератора должен быть объявлен внутри Array,
/// обычный итератор называется iterator,
/// итератор в обратном порядке -- reverse_iterator


#define USE_STL_VECTOR 0
#define USE_TEMPLATED_REALIZATION 1


#if USE_STL_VECTOR

#include <vector>
template<typename T>
using Array = std::vector<T>;
using IntArray = Array<int>;
using Exception = std::exception;

#else

#include "Array.hpp"
#if USE_TEMPLATED_REALIZATION
using IntArray = Array<int>;
#else
using IntArray = Array;
#endif

#endif



void testConstructorsAndAssignment() {
	IntArray a;
	IntArray b(10000);
	IntArray c(5, 1);
	IntArray d(b);
	IntArray e({ 1, 1, 1, 1, 1 });

	assert(a.size() == 0);
	assert(b == d);
	assert(b.size() == 10000);
	assert(c == e);

	IntArray tmp = c;
	b = c;
	assert(b == c);
	b = e;
	assert(c == tmp);

	b = b;
	assert(b == e);

	IntArray oldA = a;
	IntArray oldB = b;
	swap(a, b);
	assert(b == oldA);
	assert(a == oldB);
}


void testOperators() {
	IntArray a = { 1, 2, 3 };
	IntArray b = { 1 };
	IntArray c = { 2, 0, 0 };

	assert(!(a == b));
	assert(a != b);

	assert(b < a);
	assert(b <= a);
	assert(c > a);
	assert(c > b);
}


void testAccess() {
	const IntArray a = { 1, 2, 3 };
	assert(a[0] == 1); assert(a[1] == 2); assert(a[2] == 3);
	assert(a.at(0) == 1); assert(a.at(1) == 2); assert(a.at(2) == 3);

	IntArray b;
	b.assign({ 7, 7, 7, 7, 7 });
	assert(b[4] == 7);
	assert(b.at(4) == 7);
	b.assign(a.begin(), a.end());
	assert(b == a);
	b.clear();
	assert(b.size() == 0);
}


void testPushPop() {
	IntArray a;
	a.push_back(5);
	a.push_back(6);
	assert(a[0] == 5 && a[1] == 6);
	a.pop_back();
	assert(a.size() == 1);
	a.pop_back();
	assert(a.size() == 0);
}


void testIteration() {
	IntArray a;
	assert(a.begin() == a.end());
	assert(a.rbegin() == a.rend());

	a = IntArray(10000);
	for (int i = 0; i < 10000; i++) {
		a[i] = i;
	}

	int counter = 0;
	IntArray::iterator aIter;
	for (aIter = a.begin(); aIter != a.end(); ++aIter) {
		assert(*aIter == counter);
		++counter;
	}

	for (IntArray::reverse_iterator aReverseIter = a.rbegin();
		aReverseIter != a.rend(); ++aReverseIter) {
		--counter;
		--aIter;
		assert(*aReverseIter == counter);
	}
	assert(aIter == a.begin());
}


void testExceptions() {
	bool exceptionWasThrown = false;

	IntArray a = { 1, 2 };
	try {
		a.at(2) = 3;
	}
	catch (Exception& e) {
		std::cout << "Exception was thrown: " << e.what() << std::endl;
		exceptionWasThrown = true;
	}

	assert(exceptionWasThrown);
}


void testIterationConstness() {
	IntArray a(10);
	int counter = 0;
	for (IntArray::iterator iter = a.begin(); iter != a.end(); ++iter) {
		*iter = counter++;
	}
	const IntArray b = a;

}



int main() {

	testConstructorsAndAssignment();
	testOperators();
	testAccess();
	testPushPop();
	testIteration();
	testExceptions();
	testIterationConstness();

	return 0;
}*/