#include "Solver.h"


int main()
{
	cout << "Equation:\n"
		"\t1) Parabola\t: a*x^2 + b*x + c = 0;\n"
		"\t2) Exponent\t: a*e^(x + b) + c = 0;\n"
		"\t3) Logarithm\t: a*ln(x + b) + c = 0.\n";
	cout << "Segment: [double xMin, double xMax]\n";
	cout << "Method:\n"
		"\t1) Bisection;\n"
		"\t2) Newton.\n\n";

	int equationN(0), methodN(0);
	double xMin(0), xMax(0), a(0), b(0), c(0);

	cout << "Equation: "; cin >> equationN;
	cout << "a\t= "; cin >> a;
	cout << "b\t= "; cin >> b;
	cout << "c\t= "; cin >> c;
	cout << "xMin\t= "; cin >> xMin;
	cout << "xMax\t= "; cin >> xMax;
	cout << "Method\t: "; cin >> methodN;


	//Solver *solver(nullptr);
	//Equation* equation(nullptr);

	switch (equationN)
	{
	case 1:
	{
		Sqr equation(a, b, c);
		switch (methodN)
		{
		case 1:
			BisectionSolver<Sqr>().solve(equation, xMin, xMax);
			break;
		case 2:
			NewtonSolver<Sqr>().solve(equation, xMin, xMax);
			break;
		}
		break;
	}
	case 2:
	{
		Exp equation(a, b, c);
		switch (methodN)
		{
		case 1:
			BisectionSolver<Exp>().solve(equation, xMin, xMax);
			break;
		case 2:
			NewtonSolver<Exp>().solve(equation, xMin, xMax);
			break;
		}
		break;
	}
	case 3:
	{
		Log equation(a, b, c);
		switch (methodN)
		{
		case 1:
			BisectionSolver<Log>().solve(equation, xMin, xMax);
			break;
		case 2:
			NewtonSolver<Log>().solve(equation, xMin, xMax);
			break;
		}
		break;
	}
	}

	system("pause");
	return 0;
}


