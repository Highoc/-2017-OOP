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


	Solver *solver(nullptr);
	switch (methodN)
	{
	case 1:
		solver = new BisectionSolver();
		break;
	case 2:
		solver = new NewtonSolver();
		break;
	default:
		cout << "Unknow method.\n";
		return 1;
	}

	Equation* equation(nullptr);
	switch (equationN)
	{
	case 1:
		equation = new SqrEquation(a, b, c);
		break;
	case 2:
		equation = new ExpEquation(a, b, c);
		break;
	case 3:
		equation = new LogEquation(a, b, c);
		break;
	default:
		cout << "Unknow equation.\n";
		return 1;
	}
	
	solver->solve(equation, xMin, xMax);

	delete solver;
	delete equation;

	system("pause");
	return 0;
}