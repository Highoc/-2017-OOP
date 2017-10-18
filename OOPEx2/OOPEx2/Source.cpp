#include <cassert>
#include <iostream>
#include "IntArray.hpp"

/// ������� �� �����. �������� �����-������ ������ ������������� ������� ����� �����
/// ����������� ����� �������� ������, �������������� ��� ��������, ����� ��������� ���������������
/// � ������������ ��� ������.
/// ��� ����� ������ ���� ���������� � ����� "IntArray.hpp", ���������� IntArray 
/// � ���������� � ��� �� �����, ��� � ������ ����.
/// ����� ��� ���������� ����� ������������, � �������
/// "g++ -std=c++11 -Wall testArray-1.cpp"


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



int main() {

	testConstructorsAndAssignment();
	testOperators();
	testAccess();
	testPushPop();

	return 0;
}