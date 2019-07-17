#include <iostream>
#include <assert.h>
#include <math.h>

using std::cin;
using std::cout;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

namespace polynom
{
	const int cod_inf_num_of_sol = -1; ///< константа для обозначения бесконечного числа решений уравнения

	/*!
		Определяет является ли введённое число нулём
	*/
	bool isZero(double p)
	{
		return abs(p) < 1e-9;
	}

	/*!
		Функция, которая решает квадратное уравнение
		\author TheCompiler
		\date 17.07.2019
		\param a,b,c коэфиценты квадратного уравнения
		\param[out] x1,x2 корни уравнения
		\return число корней
	*/
	int SolvQuadrEquat(double a, double b, double c, double* x1, double* x2)
	{
		assert(x1 != nullptr);
		assert(x2 != nullptr);

		if (isZero(a))
		{
			if (isZero(b))
			{
				if (isZero(c))
				{
					return cod_inf_num_of_sol;
				}
				return 0;
			}
			*x1 = -c / b;
			*x2 = *x1;
			return 1;
		}
		const double discr = b * b - 4 * a*c;  ///< Дискриминант
		if (discr < 0)
			return 0;
		*x1 = sqrt(discr);
		*x2 = (-b + *x1) / (2 * a);
		*x1 = (-b - *x1) / (2 * a);
		return 2;
	}
}

int main()
{
	double a = NAN, b = NAN, c = NAN;
	double x1 = NAN, x2 = NAN;

	cout << "# Please, write first coef of equation:\na = ";
	cin >> a;
	cout << "# Please, write second coef of equation:\nb = ";
	cin >> b;
	cout << "# Please, write third coef of equation:\nc = ";
	cin >> c;
	
	int nm_of_sol = polynom::SolvQuadrEquat(a, b, c, &x1, &x2);

	switch (nm_of_sol)
	{
	case 0:
		cout << "# Equation doesn't have any solutions\n";
		break;
	case 1:
		cout << "# Equation has one solution\n" 
				<< "x = " << x1 << "\n";
		break;
	case 2:
		cout << "# Equation has two solutions\n" 
				<< "x1 = " << x1 << "\n"
				<< "x2 = " << x2 << "\n";
		break;
	case polynom::cod_inf_num_of_sol:
		cout << "# Equation has infinity numbers of solutions\n";
		break;
	default:
		cout << "# It's not good. You got unwaiting numbers of solutions.\n"
				<< "Please, write on this email:cadabra@email.net.\n";
		break;
	}
	return 0;
}
