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

class Equation {
public:
	Equation(double a, double b, double c);
	virtual void printEquational() const = 0;
	virtual double getY(double x) const = 0;
	virtual double derivative(double x) const = 0;
	double a_, b_, c_;
};

class SqrEquation : public Equation {
public:
	SqrEquation(double a, double b, double c);
	virtual void printEquational() const override;
	virtual double getY(double x) const override;
	virtual double derivative(double x) const override;
};

class ExpEquation : public Equation {
public:
	ExpEquation(double a, double b, double c);
	virtual void printEquational() const override;
	virtual double getY(double x) const override;
	virtual double derivative(double x) const override;
};

class LogEquation : public Equation {
public:
	LogEquation(double a, double b, double c);
	virtual void printEquational() const override;
	virtual double getY(double x) const override;
	virtual double derivative(double x) const override;
};


class Solver {
public:
	virtual double solve(const Equation* equation, double xMin, double xMax) const = 0;
};

class BisectionSolver : public Solver {
public:
	virtual double solve(const Equation* equation, double xMin, double xMax) const override;
};

class NewtonSolver : public Solver {
public:
	virtual double solve(const Equation* equation, double xMin, double xMax) const override;
};