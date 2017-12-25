#include <stdio.h>
#include <Windows.h>
#include <initializer_list>
#include <iostream>
#include <conio.h>
#include <assert.h>
#include <clocale>
#include <limits.h>

using std::cout;
using std::cin;
using std::endl;

const unsigned int SIZE_ = 10;
const unsigned int needed_capacity = 5;

template <typename T>

class Array
{
private:
	T *data;
	unsigned int size_;
	unsigned int capacity_;
	bool ok() const { return (this) ? true : false; }
public:

	//////////iterator////////////////////////

	struct iterator {
	protected:
		T *ptr;
	public:
		iterator (T* ptr_ = 0) : ptr(ptr_) {}
		T& operator*()  { return *ptr; }
		T* operator->() { return ptr; }
		T* operator++() { return ++ptr; }
		T* operator++(int) { iterator ans(*this); ++(*this); return ans; }
		T* operator--() { return --ptr; }
		T* operator--(int) { iterator ans(*this); --(*this); return ans; }
		bool operator ==(const iterator& a) const { return ptr == a.ptr; }
		bool operator !=(const iterator& a) const { return !(ptr == a.ptr); }
	};

	iterator begin() const { return iterator(data);}
	iterator end() const  { return iterator(data + size_);}

	//////////////////////////////////////////

	//reverse_iterator////////////////////////

	struct reverse_iterator : public iterator {
		using iterator::iterator;
		T* operator++() { return --ptr; }
		T* operator--() { return ++ptr; }
	};

	reverse_iterator rbegin() const { return (data + size_ - 1); }
	reverse_iterator rend() const { return (data - 1); }

	///////////////////////////////////////////

	//ctors//
	Array();
	Array(Array<T>&);
	Array(int);
	Array(int, const T);
	Array(std::initializer_list<T>);
	~Array();


	//methods//
	void dump() const;
	void reserve(unsigned int);
	void resize(unsigned int, const T);
	void clear();
	bool empty_vector() const;
	unsigned int size() const;
	unsigned int capacity() const;
	void push_back(const T);
	void pop_back();
	T& at(unsigned int);
	T at(unsigned int) const;
	void assign (std::initializer_list <T>);
	void assign(iterator, iterator);


	//operators//
	Array<T>& operator = (Array<T>&);
	bool operator == (const Array<T>&) const;
	T& operator [] (unsigned int j) { return *(data + j); }             // ?!?!?!?!?!?!?? pochemu tak ?
	T  operator [] (unsigned int j) const { return *(data + j); }
	Array<T>& operator + (Array<T>&);
	void operator += (Array<T>&);
	Array<T>& operator - (Array<T>&);
	void operator -= (Array<T>&);
	bool operator != (const Array<T>&) const;
	bool operator >  (const Array<T>&) const;
	bool operator <  (const Array<T>&) const;
	bool operator >=  (const Array<T>&) const;
	bool operator <=  (const Array<T>&) const;
};

class Exception : public std::exception
{
	private:
		const char* excep;
	public:
		Exception() {}

		Exception(const char* str) { excep = str; }

		virtual ~Exception() throw() {}

		const char *what() const throw() { return excep; }
};

//////////////////////
//////////////////////
//////////////////////Конструкторы
//////////////////////
//////////////////////


template <typename T>

Array<T>::Array()
{
	size_ = 0;
	capacity_ = 0;
	data = NULL;
}

template <typename T>

Array<T>::Array(Array<T> & a)
{
	if (a.ok() == false) { a.dump(); exit(-1); }
	size_ = a.size_;
	capacity_ = a.capacity_;
	data = new T[size_];
	for (unsigned int i = 0; i < size_; i++)
		data[i] = a.data[i];
}

template <typename T>

Array<T>::Array( int n )
{
	try {
		if (n < 0 || n >= UINT_MAX) throw Exception("Error in constructing object, check input parametres");
		size_ = n;
		capacity_ = n;
		data = new T[size_];
		for (unsigned int i = 0; i < n; i++) *(data + i) = 0;
	}
	catch (Exception& exc) { cout << exc.what() << endl; }
}

template <typename T>

Array<T>::Array(int n, const T k)
{
	try {
		if (n < 0 || n >= UINT_MAX) throw Exception("Error in constructing object, check input parametres");
		size_ = n;
		capacity_ = n;
		data = new T[size_];
		for (unsigned int i = 0; i < n; i++) *(data + i) = k;
	}
	catch (Exception& exc) { cout << exc.what() << endl; }
}

template <typename T>

Array<T>::Array(std::initializer_list<T> list)
{
	size_ = list.size();
	capacity_ = size_;
	data = new T[list.size()];
	int i = 0;
	for (int value : list) { data[i++] = value; }
}

template <typename T>

Array<T>::~Array()
{
	delete[] data;
	//cout << "Destructor!!" << endl;// for an opportunity to see how many objects were destroyed
}

//////////////////////
//////////////////////
//////////////////////Методы
//////////////////////
//////////////////////

template <typename T>

void Array<T>::assign(std::initializer_list<T> list)
{
	delete [] data;
	(*this) = Array({ list });
}

template <typename T>

void Array<T>::assign (iterator first, iterator last)
{
	clear();
	for (auto it = first; it != last; ++it)
	{
		push_back(*it);
	}
}

template <typename T>

void Array<T>::reserve(unsigned int new_capacity)
{
	if (new_capacity <= capacity_) return;
	if (!data)
	{
		size_ = 0;
		capacity_ = new_capacity;
		data = new T[capacity_];
		return;
	}
	T *temp = new T[size_];
	for (unsigned int i = 0; i < size_; i++) temp[i] = data[i];
	delete[] data;
	capacity_ = new_capacity;
	data = new T[capacity_];
	for (unsigned int i = 0; i < size_; i++) data[i] = temp[i];
}

template <typename T>

void Array<T>::resize(unsigned int new_size, const T val)//function, that resizes vector to new size (if new size > old size, then new elements equals to val)
{
	if (!ok()) { dump(); exit(-1); }
	assert(new_size >= 0 && new_size < UINT_MAX);
	if (new_size == 0)
	{
		data = NULL;
		size_ = new_size;
	}
	if (new_size == size_) return;
	T *temp = new T[size_];
	int tmp_size = size_;
	unsigned int i = 0;
	for (i = 0; i < tmp_size; i++)
		temp[i] = data[i];
	delete[] data;
	size_ = new_size;
	if (size_ > tmp_size && size_ <= capacity_)
	{
		data = new T[size_];
		for (i = 0; i < tmp_size; i++)
			data[i] = temp[i];
		for (; i < size_; i++)
			data[i] = val;
	}
	else if (size_ < tmp_size)
	{
		data = new T[size_];
		for (i = 0; i < size_; i++)
			data[i] = temp[i];
	}
	else if (size_ > capacity_)
	{
		reserve(size_ + needed_capacity);
		resize(size_ + needed_capacity, val);
	}
}

template <typename T>

void Array<T>::dump() const
{
	if (!ok()) { cout << "Smth is wrong" << endl; exit(-1); }
	if (empty_vector()) cout << "Vector is empty" << endl;
	else for (unsigned int i = 0; i < size_; i++)
	{
		if (i) cout << "||";
		cout << data[i];
	}
}

template <typename T>

bool Array<T>::empty_vector() const
{
	if (!ok()) { dump(); exit(-1); }
	return (!size_) ? true : false;
}

template <typename T>

void Array<T>::clear()
{
	data = NULL;
	size_ = 0;
	capacity_ = 0;
}

template <typename T>

unsigned int Array<T>::size() const
{
	if (!ok()) { dump(); exit(-1); }
	else return size_;
}

template <typename T>

unsigned int Array<T>::capacity() const
{
	if (!ok()) { dump(); exit(-1); }
	else return capacity_;
}

template <typename T>

void Array<T>::push_back(const T val)
{
	if (!ok()) { dump(); exit(-1); }
	if (size_ >= capacity_) reserve(capacity_ + needed_capacity);
	data[(size_)++] = val;
}

template <typename T>

void Array<T>::pop_back()
{
	if (!ok()) { dump(); exit(-1); }
	if (empty_vector()) { cout << "vector is empty, cannot pop anymore" << endl; return; }
	else resize(--(size_), NULL);
}

template <typename T>

T Array<T>::at(unsigned int j) const
{
	if (!ok()) { dump(); return NULL; }
	if (j < 0 || j >= size_)
		throw (Exception ("Access to non-existing part of vector"));
	else return data[j];
}

template <typename T>

T& Array<T>::at(unsigned int j)
{
	if (!ok()) { dump(); return NULL; }
	
	if (j < 0 || j >= size_)
		throw (Exception ("Access to non-existing part of vector"));
	
	else return data[j];
}

//////////////////////
//////////////////////
//////////////////////Операции с объектами
//////////////////////
//////////////////////

template <typename T>

void Array<T>::operator += (Array<T>& a) A = A + B; X = 2 + 3;
{
	if (!ok() || !(a.ok())) { dump(); a.dump(); exit(-1); }
	if (a.size_ == size_)
	{
		for (unsigned int i = 0; i < size_; i++)
			data[i] += a.data[i];
	}
	else cout << "Cannot sum up vectors" << endl;
}

template <typename T>

void Array<T>::operator -= (Array<T>& a)
{
	if (!ok() || !(a.ok())) { dump(); a.dump(); exit(-1); }
	if (a.size_ == size_)
		for (unsigned int i = 0; i < size_; i++)
			data[i] -= a.data[i];
	else cout << "Cannot substract vectors" << endl;
}

template <typename T>

Array<T>& Array<T>::operator = (Array<T>& a)
{
	if (size_ != a.size_)
	{
		delete[] data;
		data = new T[a.size_];
		size_ = a.size_;
		capacity_ = a.capacity_;
		for (int i = 0; i < size_; i++)
			data[i] = a.data[i];
	}
	else for (int i = 0; i < size_; i++)
			data[i] = a.data[i];
	return (*this);
}

template <typename T>

Array<T>& Array<T>::operator + (Array<T>& a)
{
	if (!ok() || !(a.ok())) { dump(); a.dump(); exit(-1); }
	Array& temp = *this;
	temp += a;
	return temp;
}

template <typename T>

Array<T>& Array<T>::operator - (Array<T>& a)
{
	if (!ok() || !(a.ok())) { dump(); a.dump(); exit(-1); }
	Array& temp = *this;
	temp -= a;
	return temp;
}


//////////////////////
//////////////////////
//////////////////////Операторы сравнения
//////////////////////
//////////////////////


template <typename T>

bool Array<T>::operator== (const Array<T> & a) const
{
	if (!ok() || !(a.ok())) { dump(); a.dump(); exit(-1); }
	if (a.size_ != size_) return false;
	int num = 0;
	for (unsigned int i = 0; i < size_; i++)
		if (data[i] == a.data[i]) num++;
	return (num == size_) ? true : false;
}

template <typename T>

bool Array<T>::operator!= (const Array<T> & a) const
{
	if (!ok() || !(a.ok())) { dump(); a.dump(); exit(-1); }
	return !(a == (*this));
}

template <typename T>

bool Array<T>::operator >  (const Array<T>& a) const
{
	if (!ok() || !(a.ok())) { dump(); a.dump(); exit(-1); }
	if (size_ > a.size_) return true;
	else if (size_ == a.size_) 
	{
		int num = 0;
		for (int i = 0; i < a.size_; i++)
			if (a.data[i] < data[i]) num++;
		if (num == size_) return true;
	}
	else return false;
}

template <typename T>

bool Array<T>::operator <  (const Array<T>& a) const
{
	return (a == (*this) || (*this) > a) ? false : true;
}

template <typename T>

bool Array<T>::operator >=  (const Array<T>& a) const
{
	return (a < (*this)) ? false : true;
}

template <typename T>

bool Array<T>::operator <=  (const Array<T>& a) const
{
	return (a > (*this)) ? true : false;
}
