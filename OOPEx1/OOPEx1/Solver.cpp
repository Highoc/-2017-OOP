/*#include "Solver.h"


Equation::Equation(double a, double b, double c):
	a_(a), b_(b), c_(c)
{}



SqrEquation::SqrEquation(double a, double b, double c) :
	Equation(a, b, c)
{}

void SqrEquation::printEquational() const
{
	cout.precision(2);
	cout << a_ << "*x^2 + " << b_ << "*x + " << c_ << ";\n";
}

double SqrEquation::getY(double x) const
{
	return a_*x*x + b_*x + c_;
}

double SqrEquation::derivative(double x) const
{
	return 2*a_*x + b_;
}



ExpEquation::ExpEquation(double a, double b, double c) :
	Equation(a, b, c)
{}

void ExpEquation::printEquational() const
{
	cout.precision(2);
	cout << a_ << "*e^(x + " << b_ << ") + " << c_ << ";\n";
}

double ExpEquation::getY(double x) const
{
	return a_*exp(x + b_) + c_;
}

double ExpEquation::derivative(double x) const
{
	return a_*exp(x + b_);
}



LogEquation::LogEquation(double a, double b, double c) :
	Equation(a, b, c)
{}

void LogEquation::printEquational() const
{
	cout.precision(2);
	cout << a_ << "*ln(x + " << b_ << ") + " << c_ << ";\n";
}

double LogEquation::getY(double x) const
{
	return a_*log(x + b_) + c_;
}

double LogEquation::derivative(double x) const
{
	return a_/(x + b_);
}


template <typename E>
double BisectionSolver<E>::solve(const E* equation, double xMin, double xMax) const
{
	assert(equation);

	double nowXMin(xMin), nowXMax(xMax), nowXMid(0);
	double yLeft(equation->getY(xMin)), yRight(equation->getY(xMax)), yMid(0);
	
	equation->printEquational();
	cout.precision((-1)*log10(EX));

	if (yLeft*yRight > 0)
	{
		cout << "I can't solve this." << endl;
		return 0;
	}

	while (true)
	{
		nowXMid = (nowXMin + nowXMax) / 2;
		yMid = equation->getY(nowXMid);

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
double BisectionSolver<E>::solve(const E& equation, double xMin, double xMax) const
{
	return solve(&equation, xMin, xMax);
}

template <typename E>
double NewtonSolver<E>::solve(const E* equation, double xMin, double xMax) const
{
	assert(equation);

	double nowX((xMin + xMax) / 2), nowY(equation->getY(nowX));

	cout.precision((-1)*log10(EX));

	while (abs(nowY) > EY)
	{
		nowX -= nowY / equation->derivative(nowX);
		nowY = equation->getY(nowX);
	}

	cout << "x = " << nowX << " (Solution on [" << xMin << ", " << xMax << "])." << endl;
	return nowX;
}

template <typename E>
double NewtonSolver<E>::solve(const E& equation, double xMin, double xMax) const
{
	return solve(&equation, xMin, xMax);
}*/