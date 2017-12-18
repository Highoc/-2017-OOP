#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

constexpr double EY = 1.e-1;
constexpr double EX = 1.e-4;


class Sqr
{
public:
	Sqr() :
		a_(0), b_(0), c_(0)
	{}
	Sqr(double a, double b, double c) :
		a_(a), b_(b), c_(c)
	{}
	void printEquational() const
	{
		cout.precision(2);
		cout << a_ << "*x^2 + " << b_ << "*x + " << c_ << ";\n";
	}
	double getY(double x) const
	{
		return a_*x*x + b_*x + c_;
	}
	double derivative(double x) const
	{
		return 2 * a_*x + b_;
	}

	double a_, b_, c_;
};

class Exp
{
public:
	Exp() :
		a_(0), b_(0), c_(0)
	{}
	Exp(double a, double b, double c) :
		a_(a), b_(b), c_(c)
	{}
	void printEquational() const
	{
		cout.precision(2);
		cout << a_ << "*e^(x + " << b_ << ") + " << c_ << ";\n";
	}
	double getY(double x) const
	{
		return a_*exp(x + b_) + c_;
	}
	double derivative(double x) const
	{
		return a_*exp(x + b_);
	}

	double a_, b_, c_;
};

class Log
{
public:
	Log() :
		a_(0), b_(0), c_(0)
	{}
	Log(double a, double b, double c) :
		a_(a), b_(b), c_(c)
	{}
	void printEquational() const
	{
		cout.precision(2);
		cout << a_ << "*ln(x + " << b_ << ") + " << c_ << ";\n";
	}
	double getY(double x) const
	{
		return a_*log(x + b_) + c_;
	}
	double derivative(double x) const
	{
		return a_ / (x + b_);
	}

	double a_, b_, c_;
};

template <typename E>
class Equation {
public:
	Equation(double a, double b, double c)
	{
		equation = E(a, b, c);
	}
	void printEquational() const
	{
		equation.printEquational();
	}
	double getY(double x) const
	{
		return equation.getY(x);
	}
	double derivative(double x) const
	{
		return equation.derivative(x);
	}
	E equation;
};

template <typename E>
class BisectionSolver {
public:
	double solve(const E& equation, double xMin, double xMax) const;
};

template <typename E>
class NewtonSolver {
public:
	double solve(const E& equation, double xMin, double xMax) const;
};


template <typename E>
double BisectionSolver<E>::solve(const E& equation, double xMin, double xMax) const
{
	//assert(equation);

	double nowXMin(xMin), nowXMax(xMax), nowXMid(0);
	double yLeft(equation.getY(xMin)), yRight(equation.getY(xMax)), yMid(0);

	equation.printEquational();
	cout.precision((-1)*log10(EX));

	if (yLeft*yRight > 0)
	{
		cout << "I can't solve this." << endl;
		return 0;
	}

	while (true)
	{
		nowXMid = (nowXMin + nowXMax) / 2;
		yMid = equation.getY(nowXMid);

		if (abs(yMid) < EY)
		{
			cout << "x = " << nowXMid << " (One of solutions on [" << xMin << ", " << xMax << "])." << endl;
			return nowXMid;
		}

		if (yLeft*yMid < 0)
		{
			nowXMax = nowXMid;
		}
		else if (yMid*yRight < 0)
		{
			nowXMin = nowXMid;
		}
		else
		{
			cout << "I can't solve this." << endl;
			return 0;
		}
	}
}

template <typename E>
double NewtonSolver<E>::solve(const E& equation, double xMin, double xMax) const
{
	double nowX((xMin + xMax) / 2), nowY(equation.getY(nowX));

	cout.precision((-1)*log10(EX));

	while (abs(nowY) > EY)
	{
		nowX -= nowY / equation.derivative(nowX);
		nowY = equation.getY(nowX);
	}

	cout << "x = " << nowX << " (Solution on [" << xMin << ", " << xMax << "])." << endl;
	return nowX;
}